#include <cs50.h>
#include <stdio.h>
#include <math.h>

int checksum1(long int card);
int checksum2(long int card);
string validation(int num1, int num2, long int card);

int main(void)
{
    // Prompt user to input credit card number
    long int card_number;
    do
    {

        card_number = get_long("Enter your credit card number: ");

    }
    while (!card_number);

    // Print card number
    printf("Number: %li\n", card_number);

    // Do all validations and store result
    string card_type = validation(checksum1(card_number), checksum2(card_number), card_number);

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

string validation(int sum1, int sum2, long int card)
{

    // Characters validation
    if (card < (long int) pow(10, 12))
    {
        return "INVALID";
    }

    // Checksum validation
    bool final_checksum = (sum1 + sum2) % 10 == 0;
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
