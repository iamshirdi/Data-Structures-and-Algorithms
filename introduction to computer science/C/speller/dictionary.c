// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table  is 1 initially
// to prevent unique hashing for each word while adding
const unsigned int N = 125*45*1000;

// Hash table
node *table[N];
int sz = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int w = hash(word);
    node *n = table[w];
    
    while(n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Source cs50 video simple hash function
    // This hash function adds the ASCII values of all characters in the the word together
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *p = fopen(dictionary,"r");
    if (p == NULL)
    {
        printf("memory error");
        return false;
    }
    
    char w[LENGTH+1];
    while  (fscanf(p,"%s",w) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
            return false;
        strcpy(n->word, w);
        int hash_value = hash(w);
        // stores node in that index from hash
        // weonly give 1 node in array to n.next so that if any existing value present will be linked without lost
        n->next = table[hash_value];
        table[hash_value] = n;
        sz++;
        printf("%i\n",hash_value);
        printf("%s\n",table[hash_value]->word);
        printf("%s\n",table[312]->word);

    }
    fclose(p);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sz;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            node *temp = n;
            n = n->next;
            free(temp);
        }
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    
    
    return false;
}
