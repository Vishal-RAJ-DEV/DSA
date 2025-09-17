#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int converthexatodecimal(string s)
{
    int base = 1;  // Initialize base value
    int decimalValue = 0;  // Initialize decimal value

    // Loop through the string in reverse
    for (int i = s.length() - 1; i >= 0; i--) {
        char ch = s[i];
        int digit;

        // Convert hex character to decimal digit
        if (ch >= '0' && ch <= '9') {
            digit = ch - '0';
        } else if (ch >= 'A' && ch <= 'F') {
            digit = ch - 'A' + 10;
        } else {
            cerr << "Invalid hexadecimal character: " << ch << endl;
            return -1;  // Error case
        }

        // Update decimal value
        decimalValue += digit * base;
        base *= 16;  // Increase base for next digit
    }

    return decimalValue;
}

int main(){
    string hexString;
    cout << "Enter a hexadecimal number: ";
    cin >> hexString;

    int decimalValue = converthexatodecimal(hexString);
    if (decimalValue != -1) {
        cout << "Decimal value: " << decimalValue << endl;
    }

    return 0;
}

// Initialize variables

// hexNum = "1A3"

// decimalNum = 0

// base = 1 // represents powers of 16 (1, 16, 256, ...)

// Loop starts from last character to first
// First iteration (i = 2)

// Current char: '3'

// '3' is between '0' and '9' → numeric value = 3

// decimalNum += 3 * base = 0 + 3 * 1 = 3

// Update base: base *= 16 → base = 16

// Second iteration (i = 1)

// Current char: 'A'

// 'A' is between 'A' and 'F' → numeric value = 10

// decimalNum += 10 * base = 3 + 10 * 16 = 3 + 160 = 163

// Update base: base *= 16 → base = 256

// Third iteration (i = 0)

// Current char: '1'

// '1' is between '0' and '9' → numeric value = 1

// decimalNum += 1 * base = 163 + 1 * 256 = 163 + 256 = 419

// Update base: base *= 16 → base = 4096 (not used further as loop ends)

// Loop ends

// Final decimalNum = 419