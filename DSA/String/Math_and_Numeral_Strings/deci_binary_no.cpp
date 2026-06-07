/*
 * Problem: Partitioning Into Minimum Number Of Deci-Binary Numbers
 * 
 * A deci-binary number is a number that contains only digits 0 and 1.
 * Examples: 1, 10, 11, 101, 110, 1010, etc.
 * 
 * Given a string n representing a positive decimal integer,
 * find the minimum number of positive deci-binary numbers that sum to n.
 * 
 * Example 1:
 * Input: n = "32"
 * Output: 3
 * Explanation: 32 = 10 + 11 + 11 (3 deci-binary numbers)
 * 
 * Example 2:
 * Input: n = "82734"
 * Output: 8
 * Explanation: We need 8 deci-binary numbers. The digit 8 appears in the number,
 * and each deci-binary number can contribute at most 1 to any digit position.
 * 
 * Key Insight: The answer is the maximum digit in the string.
 * Why? Each deci-binary number can add at most 1 to each digit position.
 * To reach the maximum digit value, we need that many deci-binary numbers.
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minPartitions(string n) {
        // Strategy: Find the maximum digit in the input string
        // 
        // Why this works:
        // - Each deci-binary number contains only 0s and 1s
        // - At any digit position, a deci-binary number can contribute at most 1
        // - To build a digit with value 'd', we need at least 'd' deci-binary numbers
        // - Therefore, the minimum count = maximum digit in the string
        // 
        // Example: n = "82734"
        // - Digit 8 requires 8 deci-binary numbers
        // - All other digits (2,7,3,4) can be formed with ≤ 8 numbers
        // - So minimum needed = 8
        
        char maxDigit = '0';  // Track the maximum digit character
        
        // Scan through all digits to find the maximum
        for(char digit : n) {
            maxDigit = max(maxDigit, digit);
        }

        // Convert character to integer and return
        return maxDigit - '0';
    }
};

int main() {
    // Test case: Find minimum deci-binary numbers for "82734"
    string n = "82734";
    
    cout << "Input: " << n << endl;
    cout << "Maximum digit in " << n << " is: ";
    
    char maxChar = '0';
    for(char c : n) {
        maxChar = max(maxChar, c);
    }
    cout << maxChar << endl;
    
    Solution obj;
    int result = obj.minPartitions(n);
    
    cout << "Minimum deci-binary numbers needed: " << result << endl;
    
    cout << "\nExplanation:" << endl;
    cout << "Since the maximum digit is " << maxChar << ", we need " << result;
    cout << " deci-binary numbers." << endl;
    cout << "Each deci-binary number can contribute at most 1 to each position." << endl;

    return 0;
}
