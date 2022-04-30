#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

// prototypes
int verifyCard(long last_two_digits, int end_digit, int digit_count);
int everyOther(int end_digit, int switch_number);
int calcSecondNumbers(int end_digit, int second_number_total);
int calcCheck(int first_number_total, int second_number_total);

int main(void)
{
    int digit_count = 0;
    int end_digit;
    long last_two_digits;
    long remaining_digits;
    int switch_number = 0;
    int first_number_total = 0;
    int second_number_total = 0;

    // ask for a card number from the user
    long card_number = get_long("Number: ");

    //find the last two digits in the number
    last_two_digits = card_number;
    while (last_two_digits >= 100)
    {
        last_two_digits /= 10;
    }

    // get the last digit in the number using a modulo operator and the
    // iterate through the number in reverse by a factor of ten each step
    while (card_number != 0)
    {
        end_digit = card_number % 10;
        switch_number = everyOther(end_digit, switch_number);
        digit_count++;

        // for every index position + 1 starting at 0 sum the output
        if (switch_number == 1)
        {
            first_number_total = first_number_total + end_digit;
        }
        else
        {
            second_number_total = calcSecondNumbers(end_digit, second_number_total);
        }

        card_number /= 10;
    }

    // check all conditions and verify the card
    if (card_number == 0 && calcCheck(first_number_total, second_number_total) == true)
    {
        verifyCard(last_two_digits, end_digit, digit_count);
    }
    else
    {
        printf("INVALID\n");
    }
}

// verify the card vendor
int verifyCard(long last_two_digits, int end_digit, int digit_count)
{
    // check for AMEX
    if (last_two_digits == 34 || last_two_digits == 37)
    {
        if (digit_count == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // check for MASTERCARD
    else if (last_two_digits == 51 || last_two_digits == 52 || last_two_digits == 53 || last_two_digits == 54 || last_two_digits == 55)
    {
        if (digit_count == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (end_digit == 4)
    {
        // check for VISA
        if (digit_count == 13 || digit_count == 16)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}

// sort the incoming numbers from our while loop by [index position]+1
int everyOther(int end_digit, int switch_number)
{
    if (switch_number == 0)
    {
        switch_number++;
    }
    else
    {
        switch_number--;
    }
    return switch_number;
}

// calculate the total of all the second numbers
int calcSecondNumbers(int end_digit, int second_number_total)
{
    int second_number = 0;
    int check_second_number;

    second_number = end_digit * 2;

    // check for numbers larger than 2 digits and sum their individual values
    if (second_number > 9)
    {
        check_second_number = second_number % 10;

        if (second_number >= 10)
        {
            second_number /= 10;
            second_number += check_second_number;
        }

    }
    return second_number_total += second_number;
}

// check if the last digit's value is 0
int calcCheck(int first_number_total, int second_number_total)
{
    bool checkvalue;
    if ((first_number_total + second_number_total) % 10 == 0)
    {
        checkvalue = true;
    }
    else
    {
        checkvalue = false;
    }
    return checkvalue;
}