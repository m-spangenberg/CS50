#include <stdio.h>

int main(void)
{
    int x;
    // char s[4]; no need to use alloc and free, gives 4 bytes on the stack
    // char *s = malloc(4); this is on heap and requires you to use free after
    printf("x: ");
    scanf("%i", &x); // no type or error checking
    printf("x: %i\n", x);
}