from cs50 import get_string

# answer = input("What's your name? ") <- without the CS50 training wheels.
answer = get_string("What's your name? ")

# I love f-strings!
print(f"Hello {answer}")