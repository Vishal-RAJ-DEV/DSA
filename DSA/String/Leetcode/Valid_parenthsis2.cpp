/*20. Valid Parentheses
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

Example 1:

Input: s = "()"

Output: true

Example 2:

Input: s = "()[]{}"

Output: true

*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

bool isValid(string s) {
    int n = s.size();                // Store the length of input string
    stack<char> st;                  // Create a stack to keep track of opening brackets
    
    for(int i = 0; i < n; i++) {     // Loop through each character in the string
        if(s[i] == '(' || s[i] == '{' || s[i] == '[') {
                                     // If the character is an opening bracket
            st.push(s[i]);           // Push it onto the stack
        }
        else {                       // If the character is a closing bracket
            if(st.empty()) return false;
                                     // If stack is empty, there's no matching opening bracket
                                     // Return false immediately
            
            char c = st.top();       // Get the top element from the stack (most recent opening bracket)
            st.pop();                // Remove it from the stack
            
            // Check if the current closing bracket matches the top opening bracket
            if((c == '(' && s[i] != ')') ||  // If '(' should be matched with ')'
               (c == '{' && s[i] != '}') ||  // If '{' should be matched with '}'
               (c == '[' && s[i] != ']')     // If '[' should be matched with ']'
            ) return false;          // If any mismatch, return false
        }
    }
    
    return st.empty();               // If stack is empty, all brackets were matched
                                     // Otherwise, some opening brackets weren't matched
}
    
int main(){
    string s = "()[]{}";
    cout << isValid(s) << endl;  // Output: 1 (true)  
    return 0;
}
