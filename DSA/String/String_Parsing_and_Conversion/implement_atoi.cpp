#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.
The algorithm for myAtoi(string s) is as follows:

1->Whitespace: Ignore any leading whitespace (" ").

2->Signedness: Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.

3->Conversion: Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. If no digits were read, then the result is 0.

4->Rounding: If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then round the integer to remain in the range. Specifically, integers less than -231 should be rounded to -231, and integers greater than 231 - 1 should be rounded to 231 - 1.
Return the integer as the final result.
*/

int myAtoi(string s) {
    int i = 0;
    int n = s.size();

    // Step 1: Skip leading whitespace
    while(i < n && s[i] == ' ') i++;
    
    // Step 2: Handle sign character if present
    int sign = 1;  // Default sign is positive
    if(i < n && (s[i] == '+' || s[i] == '-')){
        if(s[i] == '-') sign = -1;  // Set sign to negative if '-' found
        i++;  // Move past the sign character
    }

    // Step 3: Convert digits to integer
    long nums = 0;  // Use long to handle potential overflow
    while(i < n && isdigit(s[i])){
        int digit = s[i] - '0';  // Convert char to int digit

        // Step 4: Check for potential overflow at INT_MAX/10 boundary
        if(nums == INT_MAX /10){
            // When nums is exactly at INT_MAX/10, the next digit determines overflow
            if(sign == 1){
                // For positive: INT_MAX = 2,147,483,647
                // Last digit must be < 7 to avoid overflow
                if(digit >= 7){
                    return INT_MAX;  // Overflow, return INT_MAX
                }
            }else if(sign == -1){
                // For negative: INT_MIN = -2,147,483,648
                // Last digit must be < 8 to avoid overflow
                if(digit >= 8){
                    return INT_MIN;  // Overflow, return INT_MIN
                }
            }
        }
        
        // If nums already exceeds INT_MAX/10, adding any digit will overflow
        if(nums > INT_MAX /10){
            if(sign == 1){
                return INT_MAX;  // Positive overflow
            }else{
                return INT_MIN;  // Negative overflow
            }
        }
        
        // Add current digit to running total
        nums = nums * 10 + digit;
        i++;  // Move to next character
    }
    
    // Apply sign and return final result
    return (int)(nums * sign);
}
int main(){
    string s = "   -42";
    cout << myAtoi(s) << endl;  // Output: -42
    string s1 = "4193 with words";  
    cout << myAtoi(s1) << endl;  // Output: 4193
    string s2  = " -042";
    cout << myAtoi(s2) << endl;  // Output: -42
    string s3 = "1337c0d3";
    cout << myAtoi(s3) << endl;  // Output: 1337
    string s4 = "words and 987";
    cout << myAtoi(s4) << endl;  // Output: 0
    string s5 = "-91283472332";
    cout << myAtoi(s5) << endl;  // Output: -2147483648 (clamped to INT_MIN)
    return 0;
}