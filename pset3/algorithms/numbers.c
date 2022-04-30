#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number[7] = {4,6,8,2,7,5,0};

    //linear search
    for (int i = 0; i < 7; i++)
    {
        if (numbers[i] == 0)
        printf("Found\n");
        return 0;
    }
    printf("Not found\n");
    return 1;
}