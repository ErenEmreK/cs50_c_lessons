#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//American Express : 15-digit, swith 34 or 37
//MasterCard : 16-digit, swith 51 52, 53, 54, 55
//Visa 13 and 16 digit, swith 4 


int calculate_luhn(long long int number);
int is_ae(long long int number);
int is_mc(long long int number);
int is_visa(long long int number);
int calculate_digit(long long int number);

int main(void) 
{
    
    char input[50];
    long long int card;
    char *endptr;

    while (1) {
        printf("Type a valid card number: ");
        fgets(input, sizeof(input), stdin);

        card = strtoll(input, &endptr, 10);

        if ((input[0] != '\n' && *endptr == '\n') && 
        !(card == LLONG_MIN || card == LLONG_MAX) && endptr != input) {
            break;
        } 

    }


    if (calculate_luhn(card)) {

        if (is_ae(card)) {
            printf("AMERICAN EXPRESS");
            return 0;
        }
        if (is_mc(card)) {
            printf("MASTERCARD");
            return 0;
        }
        if (is_visa(card)) {
            printf("VISA");
            return 0;
        }
        printf("VALID OTHER");
        return 0;
    }

    printf("INVALID");
    return 0;
}

int calculate_luhn(long long int number)

{
    int sum_of_luhn = 0;
    long long int n = number;
    long long int m = number;
    int digits = calculate_digit(number);

    while (n > 10) {
        n /= 10;
        int mod_2_times = (n % 10) * 2;
        if (mod_2_times > 9) {
            int second_digit = mod_2_times % 10;
            mod_2_times /= 10;
            mod_2_times += second_digit;  
        }

        sum_of_luhn += mod_2_times;
        n /= 10;      
    }

    while (m > 10) {
        int mod_1_times = m % 10;
        sum_of_luhn += mod_1_times;
        m /= 100;
        
    }

    if (digits % 2 != 0) {
        sum_of_luhn += m;
    }

    if (sum_of_luhn % 10 == 0) {
        return 1;
    }
    return 0;
    
}

int calculate_digit(long long int number) {
    int count = 0;
    while (number > 0) {
        number /= 10;
        count++;
    }

    return count;
}

int is_ae(long long int number) {
    int digits = calculate_digit(number);

    while (number > 99) {
        number /= 10;
    }
    
    if ((digits == 15) && ((number == 34) || (number == 37))) {
        return 1;
    }
    return 0;

}

int is_mc(long long int number) {
    int digits = calculate_digit(number);

    while (number > 99) {
        number /= 10;
    }

    if (digits == 16) {
        for (int i = 51; i < 56; i++) {
            if (i == number) {
                return 1;
            }
            
        }
    }

    
    
    return 0;
}

int is_visa(long long int number) {

    int digits = calculate_digit(number);

    while (number > 9) {
        number /= 10;
    }

    if ((number == 4) && ((digits == 13) || (digits == 16))) {
        return 1;
    }
    return 0;
}
