from cs50 import get_string

# closer to english than c is
# uses 'or' instead of ||
if s == "Y" or s == "y":
    print("Agreed.")
elif s == "N" or s == "n":
    print("Not Agreed.")

# more succinct approach
if s in ["Y", "y"]:
    print("Agreed.")