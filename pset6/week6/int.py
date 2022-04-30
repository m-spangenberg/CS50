# in c this infinite loop will eventually exceed the 4 byte limit of an integer
# integer overflow is not an issue in python, but floating point imprecision is still an issue

i = 1
while:
    print(i)
    i += 1