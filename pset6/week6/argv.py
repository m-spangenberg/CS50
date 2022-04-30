from sys import argv

if len(argv) == 2:
    print(f"Hello, {argv[1]} ") # can still use square bracket notation to grab the [1] argument of argv
else:
    print("Hello, World!")