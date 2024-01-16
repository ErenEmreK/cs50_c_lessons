#include <stdio.h>



typedef struct
{
    int winner;
    int loser;
    int margin;
} pair;
pair pairs[10];



void sort_pairs(pair pairs[], int low, int high)
{
    
    int pivot, value1, value2, temp_margin, temp_winner, temp_loser;

    if (low < high) {
        pivot = low;
        value1 = low;
        value2 = high;

        while (value1 < value2) {
            while (pairs[value1].margin >= pairs[pivot].margin && value1 <= high) {
                value1++;
            }
            while (pairs[value2].margin < pairs[pivot].margin && value2 >= low) {
                value2--;
            }
            if (value1 < value2) {
                temp_margin = pairs[value1].margin;
                pairs[value1].margin = pairs[value2].margin;
                pairs[value2].margin = temp_margin;

                temp_winner = pairs[value1].winner;
                pairs[value1].winner = pairs[value2].winner;
                pairs[value2].winner = temp_winner;

                temp_loser = pairs[value1].loser;
                pairs[value1].loser = pairs[value2].loser;
                pairs[value2].loser = temp_loser;
            }
        }
        temp_margin = pairs[value2].margin;
        pairs[value2].margin = pairs[pivot].margin;
        pairs[pivot].margin = temp_margin;

        temp_winner = pairs[value2].winner;
        pairs[value2].winner = pairs[pivot].winner;
        pairs[pivot].winner = temp_winner;

        temp_loser = pairs[value2].loser;
        pairs[value2].loser = pairs[pivot].loser;
        pairs[pivot].loser = temp_loser;

        sort_pairs(pairs, low, value2 - 1);
        sort_pairs(pairs, value2 + 1, high);
    
    }
    return;
}


int main(void) {

    pairs[0].margin = 5;
    pairs[0].winner = 1;
    pairs[0].loser = 0;

    pairs[1].margin = 9;
    pairs[1].winner = 6;
    pairs[1].loser = 3;

    pairs[2].margin = 3;
    pairs[2].winner = 3;
    pairs[2].loser = 1;

    pairs[3].margin = 1;
    pairs[3].winner = 2;
    pairs[3].loser = 8;

    pairs[4].margin = 8;
    pairs[4].winner = 2;
    pairs[4].loser = 1;

    printf("%i %i %i\n", pairs[0].margin, pairs[1].margin, pairs[2].margin);
    sort_pairs(pairs, 0, 4);

    printf("%i %i %i\n", pairs[0].winner, pairs[1].winner, pairs[2].winner);
 
}


void quicksort_method(int element_list[], int low, int high)
{
    int pivot, value1, value2, temp;

    if (low < high) {
        pivot = low;
        value1 = low;
        value2 = high;

        while (value1 < value2) {
            while (element_list[value1] >= element_list[pivot] && value1 <= high) {
                value1++;
            }
            while (element_list[value2] < element_list[pivot] && value2 >= low) {
                value2--;
            }
            if (value1 < value2) {
                temp = element_list[value1];
                element_list[value1] = element_list[value2];
                element_list[value2] = temp;
            }
        }
        temp = element_list[value2];
        element_list[value2] = element_list[pivot];
        element_list[pivot] = temp;

        quicksort_method(element_list, low, value2 - 1);
        quicksort_method(element_list, value2 + 1, high);
    }
}