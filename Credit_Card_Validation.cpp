#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

void testNumber(long long num);
int digitCount(long long num);
void cardType(long long num);
int getDigit(long long num, int position);

int main()
{
    while (true) {
        // take input(credit card number) from user
        string userInput = "";
        long long creditCardNumber = 0;
        do {
            cout << "Credit Card Number: ";
            cin >> userInput;
            cout << "\n";

            // exit program
            if (userInput == "exit") return 0;

            // check if user input is a number
            bool ok = false;
            for (char character : userInput) {
                if (!isdigit(character)) {
                    ok = true;
                }
            }
            if (ok) {
                cout << "Must be a number or 'exit' to quit" << "\n";
                continue;
            }

            creditCardNumber = stoll(userInput);
            cout << creditCardNumber << "\n";
        } while (creditCardNumber <= 0);

        // test whether this is a valid credit card number
        testNumber(creditCardNumber);
    }
}

void testNumber(long long num) {
    // check how many digits are in the number
    int digits = digitCount(num);

    // process of adding digits
    long long tempNum = num;
    long sum = 0;
    for (int i = 0; i < digits; i++) {
        int digit = tempNum % 10;
        tempNum /= 10;
        if (i % 2 == 0) {
            sum += digit;
        }
        else {
            digit *= 2;
            if (digit > 9) {
                sum += digit % 10;
                sum += digit / 10;
            }
            else {
                sum += digit;
            }
        }
    }

    if (sum % 10 != 0) {
        cout << "Invalid Card" << "\n" << "\n";
    }
    else {
        cardType(num);
    }
}

void cardType(long long num) {
    int digits = digitCount(num);
    
    // get first and second digit
    int firstDigit = getDigit(num, 1);
    int secondDigit = getDigit(num, 2);

    if (digits == 15 && firstDigit == 3 && (secondDigit == 4 || secondDigit == 7)) {
        // check for American Express
        cout << "American Express" << "\n";
    }
    else if (digits == 16 && ((firstDigit == 5 && secondDigit > 0 && secondDigit < 6) || firstDigit == 2)) {
        // check for MasterCard
        cout << "MasterCard" << "\n";
    }
    else if ((digits == 13 || digits == 16) && firstDigit == 4) {
        // check for Visa
        cout << "Visa" << "\n";
    }
    else if (digits == 16 && firstDigit == 6) {
        // check for Discover
        cout << "Discover" << "\n";
    }
    else {
        cout << "Invalid or other brand" << "\n";
    }
    cout << "\n";
}

int getDigit(long long num, int position) {
    int digits = digitCount(num);
    for (int i = position; i < digits; i++) {
        num /= 10;
    }
    return num % 10;
}

int digitCount(long long num) {
    int count = 0;
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}