#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

// prototypes
int count_letters(string prompt);
int count_words(string prompt);
int count_sentences(string prompt);

int main(void)
{
    string prompt = get_string("Text: ");

    float total_letters = count_letters(prompt);
    float total_words = count_words(prompt);
    float total_sentences = count_sentences(prompt);

    // L is the average number of letters per 100 words
    float L = (total_letters / total_words) * 100;
    // S is the average number of sentences per 100 words
    float S = (total_sentences / total_words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    /*
    debug
    printf("Letters:  %f\n", total_letters);
    printf("Words:  %f\n", total_words);
    printf("Sentences:  %f\n", total_sentences);
    printf("L:  %f\n", L);
    printf("S:  %f\n", S);
    */

    // print the grade
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.f\n", index);
    }

}

// count letters from the input prompt
int count_letters(string prompt)
{
    int letter_count = 0;
    // get the total length of the string
    for (int i = 0, text_count = strlen(prompt); i < text_count; i++)
    {
        // filter out non alphabetical characters
        if (isalpha(prompt[i]))
        {
            letter_count ++;
        }
    }
    return letter_count;
}

// count breaks in alphabetic chars to infer words
int count_words(string prompt)
{
    int word_count = 1;
    // get the total length of the string
    for (int i = 0, text_count = strlen(prompt); i < text_count; i++)
    {
        // count text as a word when unbroken by non alphabetical chars.
        if (isspace(prompt[i]))
        {
            word_count ++;
        }
    }
    return word_count;
}

// count '.', '!' and '?' as sentence boundaries
int count_sentences(string prompt)
{
    int sentence_count = 0;
    // get the total length of the string
    for (int i = 0, text_count = strlen(prompt); i < text_count; i++)
    {
        // count a sentence when encountering the following ASCII chars.
        if ((prompt[i] == '.') || (prompt[i] == '!') || (prompt[i] == '?'))
        {
            sentence_count ++;
        }
    }
    return sentence_count;
}