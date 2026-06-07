/*1249. Minimum Remove to Make Valid Parentheses
Medium
Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
 */

//  Example 1:
// Input: s = "lee(t(c)o)de)"
// Output: "lee(t(c)o)de"
// Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
string minRemoveToMakeValid(string s)
{
    int n = s.size(); // Store the length of input string
    string result;    // Create first result string
    int bal = 0;      // Balance counter for parentheses

    // First pass: Process the string from left to right
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
        {                           // If character is opening parenthesis
            bal++;                  // Increment balance counter
            result.push_back(s[i]); // Add '(' to result
        }
        else if (s[i] == ')')
        { // If character is closing parenthesis
            if (bal > 0)
            {                           // If we have at least one unmatched '('
                bal--;                  // Decrement balance counter
                result.push_back(s[i]); // Add ')' to result
            }
            // Skip adding ')' if no matching '(' is available
        }
        else
        {                           // If character is not a parenthesis
            result.push_back(s[i]); // Add it to result
        }
    }

    // At this point, 'result' has no extra closing parentheses
    // But it may have extra opening parentheses

    string finalRes = ""; // Create final result string
    int openpar = bal;    // Count of extra opening parentheses

    // Second pass: Process the first result from right to left
    for (int i = result.size() - 1; i >= 0; i--)
    {
        if (result[i] == '(' && openpar > 0)
        {              // If character is '(' and we have extra ones
            openpar--; // Skip this '(' by not adding to finalRes
        }
        else
        {                                  // Otherwise
            finalRes.push_back(result[i]); // Add character to finalRes
        }
    }

    // finalRes is built in reverse order, so we need to reverse it
    reverse(finalRes.begin(), finalRes.end());

    return finalRes; // Return the valid string
}
int main()
{
    string s = "lee(t(c)o)de)";
    cout << minRemoveToMakeValid(s) << endl; // Output: lee(t(c)o)de
    return 0;
}
