from cs50 import get_int

# mario/more

# get pyramid height
size = 0
while size > 8 or size < 1:
    size = get_int("Height of pyramid: ")


def pyragen(size):
    """ Generate a double pyramid """
    step = 1
    for i in range(size):
        print(" " * (size - step), end="")
        print("#" * step, end="")
        print("  ", end="")
        print("#" * step, end="")
        step += 1
        if step <= size:
            print("\n", end="")
    print("\n", end="")


# call the method
pyragen(size)