/*
 * Problem: Longest Valid Parentheses
 *
 * Given a string containing just '(' and ')', find the length of the
 * longest valid (well-formed) parentheses substring.
 *
 * Approach: Stack-based index tracking
 * ------------------------------------
 * Key Insight:
 *   Instead of storing characters, we store INDICES in the stack.
 *   This lets us calculate the length of valid substrings by subtracting
 *   indices: (current index) - (index at stack top after popping).
 *
 * Algorithm:
 *   1. Push -1 onto the stack as an initial "base" index.
 *      This base helps measure the length of valid substrings
 *      that start from index 0.
 *
 *   2. Traverse the string from left to right:
 *      - If '(' is found: Push its index onto the stack.
 *        (We'll match it later when we find a ')')
 *
 *      - If ')' is found: Pop the top element from the stack.
 *        - Case A: Stack becomes EMPTY after popping.
 *          This means the ')' has NO matching '(' before it.
 *          So, this ')' becomes the NEW base for future measurements.
 *          Push its index onto the stack.
 *
 *        - Case B: Stack is NOT empty after popping.
 *          This means we found a valid pair! The length of the valid
 *          substring ending at current index 'i' is:
 *              i - st.top()
 *          Update the answer with the maximum length found so far.
 *
 * Time Complexity:  O(n) - single pass through the string
 * Space Complexity: O(n) - stack can store up to n indices
 *
 * Example Walkthrough:
 *   Input:  s = "(()"
 *   i=0, s[0]='(' -> push 0.        Stack: [-1, 0]
 *   i=1, s[1]='(' -> push 1.        Stack: [-1, 0, 1]
 *   i=2, s[2]=')' -> pop 1.         Stack: [-1, 0]
 *           Stack not empty, ans = max(0, 2 - 0) = 2
 *   Output: 2  (substring "()")
 *
 *   Input:  s = ")()"
 *   i=0, s[0]=')' -> pop -1.        Stack: EMPTY
 *           Push 0 as new base.     Stack: [0]
 *   i=1, s[1]='(' -> push 1.        Stack: [0, 1]
 *   i=2, s[2]=')' -> pop 1.         Stack: [0]
 *           Stack not empty, ans = max(0, 2 - 0) = 2
 *   Output: 2  (substring "()")
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        // Stack to store indices of characters
        stack<int> st;

        // Push -1 as the initial base index.
        // This acts as a "boundary" before the start of the string,
        // so that valid substrings starting from index 0 can be measured correctly.
        // Example: For "()()", at i=1, length = 1 - (-1) = 2
        st.push(-1);

        // Variable to store the maximum length of valid parentheses found
        int ans = 0;

        // Traverse through each character of the string
        for (int i = 0; i < s.length(); i++) {

            if (s[i] == '(') {
                // Opening parenthesis found: push its index onto the stack.
                // We'll try to match it with a ')' later.
                st.push(i);
            }
            else {
                // Closing parenthesis found: pop the top element.
                // If the popped element was a '(', we found a valid pair.
                // If the popped element was -1 or a previous ')', it's a mismatch.
                st.pop();

                if (st.empty()) {
                    // Stack is empty after popping: this ')' has no matching '('.
                    // It becomes the new base/index marker for future calculations.
                    // Any valid substring in the future will be measured from this point.
                    st.push(i);
                }
                else {
                    // Stack is NOT empty: we found a valid pair!
                    // The length of the current valid substring is:
                    //   (current index) - (index at stack top)
                    // The stack top now points to the index just before
                    // the start of the current valid substring.
                    ans = max(ans, i - st.top());
                }
            }
        }

        return ans;
    }
};



int main(){
    return 0;
}