#include <iostream>
#include <bits/stdc++.h>
using namespace std;

string reverseWords(string s) {
    /*
    Algorithm:
    1. Traverse the string from left to right.
    2. Build the current word in `temp`.
    3. Whenever we hit a space:
       - if `temp` is not empty, one full word is ready
       - place that word at the front of `result`
       - clear `temp` for the next word
    4. After the loop, add the last word if present.
    5. Return the final result.

    Intuition:
    We want to reverse the order of words, not the characters inside each word.
    So instead of reversing the whole string, we read one word at a time
    and keep attaching it in front of the answer.

    Example:
    Input:  "Hello World Coding"
    Build "Hello"  -> result = "Hello"
    Build "World"  -> result = "World Hello"
    Build "Coding" -> result = "Coding World Hello"
    */

    int left = 0;
    int right = s.size() - 1;

    string temp = "";
    string result = "";

    while (left <= right) {
        char ch = s[left];

        // If current character is not a space,
        // keep building the current word.
        if (ch != ' ') {
            temp += ch;
        } else {
            // We reached the end of one word.
            // Only use temp if it is non-empty,
            // so multiple spaces are ignored.
            if (!temp.empty()) {
                // Put the finished word at the front of result.
                if (!result.empty()) result = temp + " " + result;
                else result = temp;

                // Clear temp to start the next word.
                temp.clear();
            }
        }
        left++;
    }

    // After traversal, the last word may still remain in temp.
    if (!temp.empty()) {
        if (!result.empty()) result = temp + " " + result;
        else result = temp;
    }

    return result;
}

int main() {
    string s = "Hello World";
    cout << reverseWords(s) << endl;
    return 0;
}
