#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char *s = get_string("s: "); // getting a string from the user

    char *t = malloc(strlen(s) + 1); // copying the string to another char variable pointer while alocating memory with malloc

    if (t == NULL) // check for out of memmory condition by checking for NULL (absense of addresses)
    {
        return 1;
    }

    for (int i = 0, n = strlen(s); i <= n; i++) // using a for loop copy the contents of s to t
    {
        t[i] = s[i];
    }

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]); // taking the first character in the new string and converting it to uppercase
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t); // if you allocate memmory, you need to give it back using free
}

// strcpy handles the above for the user, but you must still use free