# define main so code remains readable
def main():
    meow(3)

def meow(n):
    for i in range(n):
        print("meow")

# call main at the bottom
# if __name__ == "__main__": <- achieves the same goal with your own libraries
main()