#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // Do not pass
    // negative numbers
    // words or letters
    // zero or null input
    // numbers over 8

    int height;
    do
    {
        height = get_int("Height:\n");
    }
    while (height > 8 || height < 1);

    // print newline
    for (int pyramid_y = 1; pyramid_y <= height; pyramid_y++)
    {
        // print periods
        int space_x = 0;
        while (space_x < (height - pyramid_y))
        {
            printf(" ");
            space_x++;
        }

        // print pound symbol
        for (int pyramid_x = 0; pyramid_x < pyramid_y; pyramid_x++)
        {
            printf("#");
        }

        if (pyramid_y > 0)
        {
            printf("\n");
        }

    }
}