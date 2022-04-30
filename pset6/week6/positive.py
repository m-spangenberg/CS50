from cs50 import get_int

def main():
    i = get_postive_int()
    print(i)

def get_postive_int():
    # do-while is gone but scope is no longer an issue
    # a declared variable remains until the end of the function
    # so it remains accesible and means you don't have to declare outside the function
    # it is scoped to the function, but not globaly
    while True:
        n = get_int("Positive Integer: ")
        if n > 0:
            break
    return n