#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];  // Array to store child nodes
    bool isEndOfWord;  // Flag to mark the end of a word
};

// Function to create a new Trie node
struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (node) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
        node->isEndOfWord = false;
    }
    return node;
}

// Function to insert a word into the Trie
void insert(struct TrieNode* root, const char* word) {
    for (int level = 0; word[level] != '\0'; level++) {
        int index = word[level] - 'a';
        if (!root->children[index]) {
            root->children[index] = createNode();
        }
        root = root->children[index];
    }
    root->isEndOfWord = true;
}

// Function to search for a word in the Trie
bool search(struct TrieNode* root, const char* word) {
    for (int level = 0; word[level] != '\0'; level++) {
        int index = word[level] - 'a';
        if (!root->children[index]) {
            return false;  // If a node is not found, the word is not in the Trie
        }
        root = root->children[index];
    }
    return root != NULL && root->isEndOfWord;
}

// Function to check if a word is in the dictionary
bool isInDictionary(struct TrieNode* root, const char* word) {
    return search(root, word);
}

// Main function
int main() {
    struct TrieNode* root = createNode();  // Create the root of the Trie

    // Insert words from the dictionary
    const char* dictionary[] = {
        "abalones", "abamp", "abampere", "abandon", "abandoned", 
        "abandonee", "abandoner", "abandoning", "abandonment", 
        "abandonments", "abandons", "abase", "abased", "abasement", 
        "abasements", "abaser", "abases", "abash", "abashed", 
        "abashes", "abashing"
    };
    for (int i = 0; i < sizeof(dictionary) / sizeof(dictionary[0]); i++) {
        insert(root, dictionary[i]);  // Insert each word into the Trie
    }

    // Spell check a word
    const char* targetWord = "abandn";
    printf("%s is %sspelled correctly.\n", targetWord, isInDictionary(root, targetWord) ? "" : "mis");

    // Don't forget to free the allocated memory for the Trie nodes
    // (Omitted for simplicity in this example)

    return 0;
}
