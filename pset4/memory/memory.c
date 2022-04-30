#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = malloc(4); // if you under-allocate then valgrind will tell you
    s[0] = 'H';
    s[1] = 'I';
    s[2] = '!';
    s[3] = '\0';
    free(s); // you must always use free if you invoke malloc
}