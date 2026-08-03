#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
                        Intuition
===============================================================================

The Count and Say sequence is built by repeatedly "reading" the previous string.

We start with:

    countAndSay(1) = "1"

To generate the next string, we scan the current string from left to right.

For every group of consecutive identical characters:
    1. Count how many times the character appears consecutively.
    2. Append:
            <count> + <character>
       to the new string.

Example:

Current String:
    "1211"

Groups:
    "1"   -> one 1  -> "11"
    "2"   -> one 2  -> "12"
    "11"  -> two 1s -> "21"

Concatenate:
    "11" + "12" + "21"
    = "111221"

This becomes the next string.

We repeat this process until we generate the nth string.


===============================================================================
                        Algorithm
===============================================================================

1. Initialize:
       curr = "1"

2. Repeat from i = 2 to n:

       Create an empty string 'next'.

       Traverse the current string using pointer 'j'.

       While j is inside the string:

           a) Store current character.

           b) Count how many consecutive times this character appears.

           c) Append:
                  count + character
              into 'next'.

       Replace:
           curr = next

3. Return curr.


===============================================================================
                        Time Complexity
===============================================================================

Let L be the length of the generated string.

Each iteration scans the current string exactly once.

Time  : O(L)
Space : O(L)

Since n <= 30, the maximum string length remains small, making this solution
efficient.
===============================================================================
*/

class Solution {
public:
    string countAndSay(int n) {

        // Base string (countAndSay(1))
        string curr = "1";

        // Generate strings from 2nd to nth
        for (int i = 2; i <= n; i++) {

            // Stores the next generated string
            string next = "";

            // Pointer used to traverse the current string
            int j = 0;

            // Process every group of consecutive characters
            while (j < curr.size()) {

                // Current character whose frequency we are counting
                char ch = curr[j];

                // Count of consecutive occurrences
                int cnt = 0;

                // Count all consecutive identical characters
                while (j < curr.size() && curr[j] == ch) {
                    cnt++;
                    j++;
                }

                // Append:
                // first the frequency,
                // then the character itself.
                //
                // Example:
                // cnt = 3, ch = '2'
                // Append "32"
                next += to_string(cnt);
                next += ch;
            }

            // The generated string becomes the current string
            // for the next iteration.
            curr = next;
        }

        // After generating all strings, return the nth string.
        return curr;
    }
};


int main(){
    return 0;
}