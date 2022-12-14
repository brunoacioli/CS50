// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1500;

//Count the number of words in the dictionary
unsigned int count;

// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int aux = hash(word);
    node *tmp = table[aux];
    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int index = 0;
    int a = strlen(word);
    int b = 2;
    char aux[a + 1];
    for (int i = 0; i < a; i++)
    {
        aux[i] = tolower(word[i]);
    }
    for (int i = 0; i < a; i++)
    {
        
        index += aux[i] * b;
        b++;
    }
    index = index % N;
    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char aux[LENGTH + 1];
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }
    while (fscanf(dic, "%s", aux) != EOF)
    {

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, aux);
        unsigned int index = hash(n->word);
        if (table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;
            count++;

        }
        else
        {
            n->next = table[index];
            table[index] = n;
            count++;
        }
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;

        }
    }
    return true;
}
