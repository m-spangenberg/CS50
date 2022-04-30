// Implements a dictionary's functionality

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = ((LENGTH * 26) + LENGTH);

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // look through hashtable bucket at hashed word's location
    for (node *cursor = table[hash(word)]; cursor != NULL; cursor = cursor->next)
    {
        // see if hashed word is in bucket
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // my simple rolling alphabetical hash
    // 134K words into 1215 buckets = avg. 110 words per bucket, index to n - 1 (1214)
    int hashed = 0;
    int letter_count = 0;
    char first_letter = '\0';

    // get the total length of the string
    for (int i = 0, text_count = strlen(word); i < text_count; i++)
    {
        // only pass alphabetical characters
        if (isalpha(word[i]))
        {
            letter_count ++;
        }
    }

    // get first letter in string
    for (int z = 0, text_count = strlen(word); z < text_count; z++)
    {
        if (isalpha(word[z]))
        {
            first_letter = word[z];
            break;
        }
    }

    // first letter of word roling over strlen(word) eg:apple = aaaaa = bucket 5
    hashed = (((tolower(first_letter) - 'a') * LENGTH) + letter_count) - 1;

    return hashed;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // allocate some memory for a word buffer
    char *dictionary_word = malloc(sizeof(char) * (LENGTH + 1));

    // set table[heads] to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // open dictionary file
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        fclose(dictionary_file);
        return false;
    }

    // read strings from file one at a time till the end of file
    while (fscanf(dictionary_file, "%s", dictionary_word) != EOF)
    {
        // create a new node for each word
        node *dictionary_node = malloc(sizeof(node));

        if (dictionary_node != NULL)
        {
            strcpy(dictionary_node->word, dictionary_word);
            dictionary_node->next = NULL;

            // hash word to obtain hash value
            int head = hash(dictionary_word);

            dictionary_node->next = table[head];
            table[head] = dictionary_node;
        }

    }

    fclose(dictionary_file);
    free(dictionary_word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int word_count = 0;
    // for ever bucket in the hashtable
    for (int i = 0; i < N; i++)
    {
        // for every word in i-th bucket
        for (node *cursor = table[i]; cursor != NULL; cursor = cursor->next)
        {
            word_count++;
        }
    }

    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor = table[0];

    int count = 0;
    // check every bucket in the hashtable
    for (int i = 0; i < N; i++)
    {
        // free all the things!
        while (table[i] != NULL)
        {
            cursor = table[i]->next;
            free(table[i]);
            table[i] = cursor;
        }
        count++;
    }

    free(cursor);
    free(table[0]);

    if (count == N)
    {
        return true;
    }
    else
    {
        return false;
    }
}