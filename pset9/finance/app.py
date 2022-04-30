from hashlib import new
import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # User reaches index after login
    userfunds = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    indexfolio = db.execute(
        "SELECT *, TOTAL (shares) AS total_shares FROM portfolios WHERE user_id = :id GROUP BY symbol, user_id = :id", id=session["user_id"])

    # Calculate the total holdings of the user's account
    totalholdings = 0
    for r in indexfolio:
        totalholdings += r['price'] * r['total_shares']
    totalholdings = totalholdings + userfunds[0]["cash"]

    # stocksymbol = [d['symbol'] for d in indexfolio]
    # stockticker = []

    # # Check updated prices for stocks in portfolio
    # for symbol in stocksymbol:
    #     stockticker.append(lookup(symbol))

    # Render the user portfolio
    return render_template("index.html", portfolios=indexfolio, sharetotals=totalholdings, funds=userfunds[0]["cash"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # If stock does not exist
        if not lookup(request.form.get("symbol")):
            return apology("please use a valid stock symbol", 400)

        # Ensure shares are present
        elif not request.form.get("shares"):
            return apology("please use a valid number of shares", 400)

        # Ensure shares are numbers
        elif request.form.get("shares").isalpha():
            return apology("please use numbers", 400)

        # Ensure shares are whole numbers
        elif float(request.form.get("shares")) % 1 != 0:
            return apology("please use whole numbers", 400)

        # Ensure shares are positive
        elif float(request.form.get("shares")) < 1:
            return apology("please use positive numbers", 400)

        # Purchase stock and update database
        else:
            userfunds = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
            stockticker = lookup(request.form.get("symbol"))
            stockcost = (float(request.form.get("shares")) * float(stockticker["price"]))

            # Ensure user has enough funds to complete the transaction
            if int(userfunds[0]["cash"]) < stockcost:
                return apology("insufficient funds available")

            # Perform the transaction and update portfolio
            else:
                userbalance = float(userfunds[0]["cash"]) - float(stockcost)
                rows = db.execute("SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?",
                                  session["user_id"], request.form.get('symbol'))

                # Create the entry in the user's portfolio
                if len(rows) != 1:
                    db.execute("INSERT INTO portfolios (user_id, symbol, entity, shares, price) VALUES (?, ?, ?, ?, ?)",
                               session["user_id"], stockticker['symbol'], stockticker['name'], int(request.form.get('shares')), float(stockticker['price']))

                # Or update the entry if it already exists
                else:
                    updatedsharecount = rows[0]['shares'] + int(request.form.get('shares'))
                    db.execute("UPDATE portfolios SET shares = ?, price = ? WHERE user_id = ? AND symbol = ?",
                               updatedsharecount, float(stockticker['price']), session["user_id"], stockticker['symbol'])

                # Ensure the transaction is logged
                db.execute("INSERT INTO transactions (user_id, symbol, shares, price, type, datetime) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], stockticker['symbol'],
                           int(request.form.get('shares')), float(stockticker['price']), "BUY", str(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")))

                # Ensure the users cash balance is updated
                db.execute("UPDATE users SET cash = ? WHERE id = ?", userbalance, session["user_id"])

                # notify the user of the successful transaction
                purchaseConf = int(request.form.get('shares')) * float(stockticker['price'])
                return render_template("buy.html", purchaseConfirmation=usd(purchaseConf), cashremaining=usd(userbalance))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactionlist = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", histories=transactionlist)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # If stock does not exist
        if not lookup(request.form.get("symbol")):
            return apology("please use a valid stock symbol", 400)

        # If stock exists
        else:
            # return dict from lookup
            stocked = lookup(request.form.get("symbol"))
            # eg: {'name': 'NetFlix Inc', 'price': 412.89, 'symbol': 'NFLX'}
            return render_template("quote.html", stocksymbol=stocked["symbol"], stockname=stocked["name"], stockprice=usd(stocked["price"]))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("you cannot register without a username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("you cannot register without a password", 400)

        # Ensure passwords submitted match each other
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("the supplied passwords do not match", 400)

        # Check if username already exists
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) == 1:
            return apology("username already exists", 400)

        # Register new user
        else:
            hashedpass = generate_password_hash(request.form.get("password"))
            newuser = request.form.get("username")
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", newuser, hashedpass)

        # Redirect user to home page
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        sharecount = db.execute("SELECT *, TOTAL (shares) AS total_shares FROM portfolios WHERE user_id = :id AND symbol = :stock GROUP BY symbol, user_id = :id",
                                id=session["user_id"], stock=request.form.get("symbol"))

        # Ensure stock symbol exists
        if not lookup(request.form.get("symbol")):
            return apology("please use a valid stock symbol", 400)

                # Ensure shares are present and postive numbers
        elif not request.form.get("shares"):
            return apology("please use a valid number of shares", 400)

        # Ensure shares are numbers
        elif request.form.get("shares").isalpha():
            return apology("please use numbers", 400)

        # Ensure shares are whole numbers
        elif float(request.form.get("shares")) % 1 != 0:
            return apology("please use whole numbers", 400)

        # Ensure shares are positive
        elif float(request.form.get("shares")) < 1:
            return apology("please use positive numbers", 400)

        # Ensure shares are sufficient
        elif int(request.form.get("shares")) > int(sharecount[0]['total_shares']):
            return apology("you cannot sell more than you have", 400)

        # Purchase stock and update database
        else:

            userfunds = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
            stockticker = lookup(request.form.get("symbol"))
            stockcost = (int(request.form.get("shares")) * int(stockticker["price"]))
            userbalance = int(userfunds[0]["cash"]) + stockcost

            # Ensure the users portfolio is updated
            updatedshares = int(sharecount[0]['total_shares']) - int(request.form.get('shares'))
            if updatedshares == 0:
                db.execute("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?",
                           session["user_id"], request.form.get("symbol"))
            else:
                db.execute("UPDATE portfolios SET shares = shares - :share WHERE user_id = :id AND symbol = :sym",
                           id=session["user_id"], sym=stockticker['symbol'], share=updatedshares)

            # Ensure the users cash balance is updated
            db.execute("UPDATE users SET cash = ? WHERE id = ?", userbalance, session["user_id"])

            # Ensure the transaction is logged
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price, type, datetime) VALUES (?, ?, ?, ?, ?, ?)",
                       session["user_id"], stockticker['symbol'], int(request.form.get('shares')), float(stockticker['price']), "SELL", str(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")))

            # notify the user of the successful transaction
            saleConf = f"Sale Confirmation: User has sold {int(request.form.get('shares'))} units of {stockticker['symbol']} at {usd(float(stockticker['price']))} per unit totalling {usd(stockcost)}."
            return render_template("sell.html", saleConfirmation=saleConf, cashremaining=usd(userbalance))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        userportfolio = db.execute("SELECT DISTINCT symbol FROM portfolios WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", symbols=userportfolio)


@app.route("/reset", methods=["GET", "POST"])
@login_required
def reset():
    """Reset user password"""

    if request.method == "POST":

        # Ensure passwords submitted match
        if request.form.get("newpassword") != request.form.get("confirmation"):
            return apology("the supplied passwords do not match", 400)

        else:
            # Update password and notify user of success
            hashedpass = generate_password_hash(request.form.get("newpassword"))
            db.execute("UPDATE users SET hash = ? WHERE id = ?", hashedpass, session["user_id"])
            confirmation = "Your password has been reset."
            return render_template("reset.html", resetconfirmation=confirmation)

    else:
        return render_template("reset.html")