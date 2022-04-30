import sys

if len(sys.argv) != 2:
    print("Missing command-line argument")
    sys.exit(1) # have to prefix with sys. because you did a global import of sys

print(f"Hello, {sys.argv[1]}")