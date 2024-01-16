#include <stdio.h>

int main(void)
{
    int start_size = 0;
    int ending_size = 0;
    int years = 0;

    // TODO: Prompt for start size
    do {
        printf("Type a start size: \n");
        scanf("%d", &start_size);
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    do {
        printf("Type a ending size: \n");
        scanf("%d", &ending_size);
    }
    while (ending_size < start_size);
   
    // TODO: Calculate number of years until we reach threshold
    do {
        start_size = start_size + (start_size / 3) - (start_size / 4);
        ++years;
    }
    while (start_size < ending_size);

    // TODO: Print number of years
    printf("%d", years);
}