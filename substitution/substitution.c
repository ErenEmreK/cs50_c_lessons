#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *to_ciphertext(char key[], char text[]);
int is_valid_key(char key[]);



int main(int argc, char *argv[]) 
{
    
    if (argc == 2) {
        char key[50];
        strcpy(key, argv[1]);

        if (is_valid_key(key)) {
            char plaintext[100];
            printf("Text: ");
            fgets(plaintext, sizeof(plaintext), stdin);

            char *ciphertext = to_ciphertext(key, plaintext);
            printf("Ciphered text: %s", ciphertext);
            free(ciphertext);

            return 0;
        }
        printf("Not a valid key.\n");
        return 1;
    } else {
        printf("Usage : %s <key>\n", argv[0]);
        return 1;
    }    
}

char *to_ciphertext(char key[], char text[])
{   
    char upper_key[27];
    for (int i = 0, n = strlen(key); i < n; i++) {
        upper_key[i] = toupper(key[i]); 
    }

    int suffixes[27];
    for (int i = 0; i < 27; i++) {
        suffixes[i] = (int)upper_key[i] - (65 + i);
    }

    char *ciphered_text = (char *)malloc(strlen(text) + 1);
    if (ciphered_text == NULL) {
        printf("Memory Fail\n");
        return NULL;
    }


    for (int i = 0, n = strlen(text); i < n; i++) {
        int character = text[i];
        int ciphered_char = character;

        if (isupper(character)) {            
            int suffix = suffixes[character - 65];
            ciphered_char = character + suffix;
        }
        else if (islower(character)) {
            int suffix = suffixes[character - 97];
            ciphered_char = character + suffix;
        }
        ciphered_text[i] = (char)ciphered_char; 

    }
   
    ciphered_text[strlen(text)] = '\0';
    return ciphered_text;
}

int is_valid_key(char key[]) 
{
    int length = strlen(key);
    char upper_key[27];
    for (int i = 0, n = strlen(key); i < n; i++) {
        upper_key[i] = toupper(key[i]); 
    }

    if (length != 26) {
        return 0;
    }

    for (int i = 0; i < length; i++ ) {
        if (!isalnum(upper_key[i])) {
            return 0;
        }
        for (int j = 0; j < length; j++) {
            if ((upper_key[i] == upper_key[j]) && (i != j)) {
                return 0;
            }
        }
    }
    return 1;
}











