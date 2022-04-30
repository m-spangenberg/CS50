#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

// prototypes
int numCheck(string user_string);
int encipher(string user_string, string plain_text);

// pass command-line arguments diretly to the main function
int main(int argc, string argv[])
{
    int failure = 0;

    // Use the last argument in the array, from the back
    string user_string = argv[argc - 1];

    // check to see if there is more than one argument
    if (argc > 2)
    {
        printf("Usage: ./caesar key\n");
        failure = 1;
    }
    else if (numCheck(user_string))
    {
        string plain_text = get_string("plaintext: ");
        encipher(user_string, plain_text);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        failure = 1;
    }

    // Check if the program fails, return 1 if so
    if (failure == 1)
    {
        return 1;
    }

}

// Check that the supplied argument is a positive number and not a word
int numCheck(string user_string)
{
    bool input_check;

    // Check for uppercase, lowercase, spaces, blanks and digits
    for (int i = 0, user_input = strlen(user_string); i < user_input; i++)
    {
        if (isalpha(user_string[i]) || isspace(user_string[i]) || isblank(user_string[i]))
        {
            input_check = false;
        }
        else if (isdigit(user_string[i]) && isspace(user_string[i]))
        {
            input_check = false;
        }
        else if (isdigit(user_string[i]) && atoi(user_string) > 0)
        {
            input_check = true;
        }
    }
    return input_check;
}

// Encipher the supplied plaintext
int encipher(string user_string, string plain_text)
{
    int cipher_index = atoi(user_string);
    char cipher_text[(strlen(plain_text))];

    // count throught the string's array and perform the encryption on each item in the array
    for (int i = 0; i < strlen(plain_text); i++)
    {
        char x = '\0';

        // change the upper and lowercase letters, pass the rest unchanged
        if (isspace(plain_text[i]) || isdigit(plain_text[i]))
        {
            x = plain_text[i];
            cipher_text[i] = x;
        }
        else if (isupper(plain_text[i]))
        {
            x = (((plain_text[i] - 65) + cipher_index) % 26) + 65;
            cipher_text[i] = x;
        }
        else if (islower(plain_text[i]))
        {
            x = (((plain_text[i] - 97) + cipher_index) % 26) + 97;
            cipher_text[i] = x;
        }
        else
        {
            x = plain_text[i];
            cipher_text[i] = x;
        }
    }
    cipher_text[(strlen(plain_text))] = '\0';
    printf("ciphertext: %s\n", cipher_text);
    return 0;
}