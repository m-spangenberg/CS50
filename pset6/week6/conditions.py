# from cs50 import get_int
import cs50

# if you import the entire module you have to call the function insdie cs50 with dot operators
# useful when using two libraries with similar functions to avoid collisions

x = cs50.get_int("x: ")
y = cs50.get_int("y: ")

if x < y:
    print("x is less than y")

elif x > y:
    print("x is greater than y")
else:
    print("x is equal to y")