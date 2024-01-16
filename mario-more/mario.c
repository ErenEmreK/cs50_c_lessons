#include <stdio.h>

int main(void) 
{   
    int height = 0;
    while (height < 1) {
        printf("Type a number: ");
        scanf("%d", &height);
    }

    for (int i = 1; i < height + 1; i++) {
        for (int j = height - i; j > 0; j--) {
            printf(" ");
        }
        for (int k = 0; k < i; k++) {
            printf("#");
        }

        printf(" ");

        for (int l = 0; l < i; l++) {
            printf("#");
        }
        printf("\n");
    }
    
}