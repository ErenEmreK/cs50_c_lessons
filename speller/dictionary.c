// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
//const unsigned int N = 26;
#define N 26
// Hash table
node *table[LENGTH + 1];
unsigned int dictionary_size = 0; 

bool compare_word_node(const char *word, node *n) {
    if (strcasecmp(n->word, word) == 0) {
        return true;
    }
    return false;
}




// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    unsigned int word_hash = hash(word);
    node *current_node = table[word_hash];

    while (current_node != NULL) {
        if (compare_word_node(word, current_node)) {
            return true;
        }
        current_node = current_node->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    
    unsigned int len = strlen(word);

    return len;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++) {
            table[i] = NULL;
    }

    FILE *dicptr = fopen(dictionary, "r");
    if (dicptr == NULL) {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dicptr, "%s", word) == 1) {
        dictionary_size++;
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            printf("Memory allocation in load function is failed.\n");
            return false;
        }


        strcpy(n->word, word);

        unsigned int word_hash = hash(word);
        if (table[word_hash] != NULL) {
            n->next = table[word_hash];
        }
        else {
            n->next = NULL;
        }

        table[word_hash] = n;
    }

    fclose(dicptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) {
        node *current_node = table[i];
        
        while(current_node != NULL) {
            node *tmp = current_node->next;
            free(current_node);
            current_node = tmp;
        }
        table[i] = NULL;
    }
    return true;
}



