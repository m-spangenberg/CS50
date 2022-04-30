#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Comments are useful, but don't be superfluous!
    string name = get_string("What is your name?\n");
    printf("Hello, %s\n", name);
}
