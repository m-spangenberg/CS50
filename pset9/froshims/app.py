import os
import re

from flask import Flask, render_template, request
from flask_mail import Mail, Message

app = Flask(__name__)

# Requires that "Less secure app access" be on
# https://support.google.com/accounts/answer/6010255
app.config["MAIL_DEFAULT_SENDER"] = os.environ["MAIL_DEFAULT_SENDER"]
app.config["MAIL_PASSWORD"] = os.environ["MAIL_PASSWORD"]
app.config["MAIL_PORT"] = 587
app.config["MAIL_SERVER"] = "smtp.gmail.com"
app.config["MAIL_USE_TLS"] = True
app.config["MAIL_USERNAME"] = os.environ["MAIL_USERNAME"]
mail = Mail(app)


db = SQL("sqlite:///froshims.db")

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee"
]


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():

    # Validate submission
    name = request.form.get("name")
    email = request.form.get("email")
    sport = request.form.get("sport")
    if not name or not email or sport not in SPORTS:
        return render_template("failure.html")

    # Send email
    message = Message("You are registered!", recipients=[email])
    mail.send(message)

    # Confirm registration
    return render_template("success.html")


@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", registrants=registrants)


@app.route("/deregister", methods=["POST"])
def deregister():

    # Forget registrant
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")