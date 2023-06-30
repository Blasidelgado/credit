#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int check_number(const char *input);
int checksum1(long int card);
int checksum2(long int card);
char *validation(int num1, int num2, long int card);

int main(void)
{
    // Prompt user to input credit card number
    char input[101];
    char *endptr;
    do
    {
        printf("Enter your credit card number: ");
        scanf("%s", input);
    }
    while (strlen(input) > 20 || !check_number(input));

    // Convert and assign input to number
    long int card_number = strtol(input, &endptr, 10);

    // Print card number
    printf("Number: %li\n", card_number);

    // Do all validations and store result
    char *card_type = validation(checksum1(card_number), checksum2(card_number), card_number);

    // Print validation result
    printf("%s\n", card_type);
}

int checksum1(long int card)
{

    int digit, checksum = 0;

    // Extract every other digit starting from second-to-last digit
    for (int i = 2; (long int) pow(10, i - 1) <= card ; i += 2)
    {

        // Store each digit
        digit = card % ((long int) pow(10, i)) / (long int) pow(10, i - 1);

        // Multiply each digit by two
        digit *= 2;

        // Split every two digited and sum eachother
        digit = digit > 9 ? digit / 10 + digit % 10 : digit;

        // Sum extracted and multiplied digits
        checksum += digit;
    }

    return checksum;
}

int checksum2(long int card)
{

    int digit, checksum = 0;

    // Extract the digits that weren't extracted in checksum1
    for (int i = 1; (long int) pow(10, i - 1) <= card ; i += 2)
    {

        // Store each digit
        digit = card % ((long int) pow(10, i)) / (long int) pow(10, i - 1);

        // Sum extracted digits
        checksum += digit;
    }

    return checksum;
}

char *validation(int sum1, int sum2, long int card)
{

    // Characters validation
    if (card < (long int) pow(10, 12))
    {
        return "INVALID";
    }

    // Checksum validation
    int final_checksum = (sum1 + sum2) % 10 == 0;
    if (final_checksum)
    {
        while (card > 99)
        {
            card /= 10;
        }

        // Creditor authentication
        switch (card)
        {
            case 34:
            case 37:
                return "AMEX";
                break;
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                return "MASTERCARD";
                break;
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
                return "VISA";
                break;
            default: // Invalid or unknown creditor
                return "INVALID";
        }
    }
    // Credit card has a valid length but does not pass Luhn's algorithm
    else
    {
        return "INVALID";
    }
}

int check_number(const char *input) {
    if (*input == '\0') // If the string is empty, it's not accepted
        return 0;

    // Check each character in the remaining string
    while (*input != '\0') {
        if (!isdigit(*input)) // If a character is not a digit, it's not an accepted number
            return 0;
        input++;
    }

    return 1; // All characters are digits, so it's accepted
}
