#include <iostream> // standard I/O
#include <bits/stdc++.h> // convenience header for STL
using namespace std; // use standard namespace


// Algorithm steps:
// 1) Initialize count to 0.
// 2) For each number from 1 to n:
//    a) Check digits one by one.
//    b) If any digit is 3, 4, or 7 -> invalid, stop checking this number.
//    c) If any digit is 2, 5, 6, or 9 -> mark that rotation changes the number.
//    d) If valid and changed -> increment count.
// 3) Return the count.
class Solution { // solution wrapper class
public: // public access specifier
    int rotatedDigits(int n) { // count good rotated numbers in [1, n]
        int cnt = 0; // count of valid rotated digits

        for (int i = 1; i <= n; i++) { // iterate through each number
            int num = i; // copy current number
            bool isValid = true; // assume valid until proven otherwise
            bool hasChange = false; // track if any digit changes on rotation

            while (num > 0) { // process all digits
                int digit = num % 10; // extract last digit

                if (digit == 3 || digit == 4 || digit == 7) { // invalid digits
                    isValid = false; // mark invalid
                    break; // stop checking this number
                }

                if (digit == 2 || digit == 5 || digit == 6 || digit == 9) { // digits that change
                    hasChange = true; // at least one digit changes on rotation
                }

                num /= 10; // remove last digit
            }

            if (isValid && hasChange) { // valid and changed after rotation
                cnt++; // increment count
            }
        }

        return cnt; // return final count
    } // end function
}; // end class


int main() { // program entry point
    int n = 10; // sample input
    Solution sol; // create solution instance
    cout << "Count of valid rotated digits: " << sol.rotatedDigits(n) << endl; // run and print
    return 0; // exit status
} // end main
