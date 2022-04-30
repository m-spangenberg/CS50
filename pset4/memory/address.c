#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;
    printf("%p\n", p);

    // A single ampersand find the data in memmory - address of operator
    // %p (pointer) is used to print ot the address in hexadecimal
    // A asterisk looks inside the address in memmory - dereference operator
    // printf("%i\n", *&n);
    // A pointer is just a variable that stores the address of some value int *p = &n
}