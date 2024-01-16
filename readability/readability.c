#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int calculate_index(int letters, int words, int sentences);
int count_letters(char text[]);
int count_words(char text[]);
int count_sentences(char text[]);

int main(void) 
{
    char text[400];

    printf("Text: ");
    fgets(text, sizeof(text), stdin);
    
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);


    int grade = calculate_index(letters, words, sentences);

    if (grade < 1) {
        printf("Before Grade 1\n");
    }
    else if (grade > 16) {
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %i\n", grade);
    }

    return 0;
}

int calculate_index(int letters, int words, int sentences)
{
    float L = (letters * 100.0 / words);
    float S = (sentences * 100.0 / words);

    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    return round(index);
}

int count_letters(char text[])
{
    int letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++) {
        if (isalpha(text[i])) {
            ++letters;
        }
    }

    return letters;
}

int count_words(char text[])
{
    int n = strlen(text);
    int words = 0;

    for (int i = 0; i < n; ++i) {
        if (isspace(text[i]) && !isspace(text[i-1])) {
            ++words;
        }
    }
    if (!isspace(text[n-1])) {
        ++words;
    }
    
    return words;
}

int count_sentences(char text[])
{
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++) {
        int ascii = text[i];
        if ((ascii == 46) || (ascii == 33) || (ascii == 63)) {
            ++sentences;
        }
    }

    return sentences;
}