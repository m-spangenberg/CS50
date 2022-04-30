#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size;
    int end_size;
    int year_count = 0;

    // Prompt for start size larger than 9
    do
    {
        start_size = get_int("Start size: \n");
    }
    while (start_size < 9);

    // Prompt for end size larger than starting size
    do
    {
        end_size = get_int("End size: \n");
    }
    while (end_size < start_size);

    // Calculate number of years until we reach threshold
    while (start_size < end_size)
    {
        year_count ++;
        start_size = start_size + (start_size / 3) - (start_size / 4);
    }

    // Print number of years needed to reach end population size.
    printf("Years: %i", year_count);
}