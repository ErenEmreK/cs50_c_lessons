#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char word[]);

int main(void)
{

    char word1[100];
    char word2[100];

    printf("Player 1: ");
    scanf("%s", &word1);

    printf("Player 2: ");
    scanf("%s", &word2);

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);


    if (score1 > score2) {
        printf("Player 1 Wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else {
        printf("Player 2 Wins!\n");
    }
    return 0;
}

int compute_score(char word[])
{   
    int score = 0; 
    for (int i = 0; i < strlen(word); i++) {
        int upper_char_val = toupper(word[i]);
        if ((65 <= upper_char_val) && (upper_char_val <= 90)) {
            upper_char_val -= 65;
            score += POINTS[upper_char_val];  
        } 
    }
    return score;

}
