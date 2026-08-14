// LeetCode 1081: Smallest Subsequence of Distinct Characters
// Given a string s, return the smallest lexicographical subsequence
// that contains all the distinct characters of s exactly once.
// Approach: Monotonic increasing stack with frequency counting.
// - freq[26] tracks remaining occurrences of each character
// - used[26] prevents adding the same character twice
// - While loop pops larger chars from stack if they appear later
// - Ensures lexicographically smallest result while preserving all distinct chars
//
// Dry Run Example (s = "bcabc"):
// Init: freq[a=1,b=2,c=2], stack empty
// 1. 'b': freq[b]=1, stack=[b]
// 2. 'c': freq[c]=1, stack=[b,c]
// 3. 'a': freq[a]=1, 'c' > 'a' but freq[c]=0 (can't pop),
//         'b' > 'a' and freq[b]=1>0 → pop 'b', stack=[a]
// 4. 'b': freq[b]=0, stack=[a,b]
// 5. 'c': freq[c]=0, stack=[a,b,c]
// Result: "abc" (lexicographically smallest subsequence with all distinct chars)
#include <iostream>
#include <bits/stdc++.h>
using namespace std;  // standard headers

class Solution {  // class definition
public:
    string smallestSubsequence(string s) {  // function to find smallest subsequence with all distinct characters
        
        vector<int> freq(26, 0);  // frequency array for 26 lowercase letters, initialized to 0
        vector<bool> used(26, false);  // boolean array to track characters already in the result

        for (char c : s)  // count total frequency of each character in the string
            freq[c - 'a']++;

        string st;  // result string acting as a stack (monotonic increasing stack)

        for (char c : s) {  // iterate through each character of the input string
            
            freq[c - 'a']--;  // decrement the remaining frequency of current character

            if (used[c - 'a'])  // if character is already in the stack, skip it (avoid duplicates)
                continue;

            while (!st.empty() &&  // while stack is not empty
                   st.back() > c &&  // and the top of stack is greater than current character
                   freq[st.back() - 'a'] > 0) {  // and the top character still appears later in the string
                
                used[st.back() - 'a'] = false;  // mark the popped character as unused so it can be re-added
                st.pop_back();  // remove it from the stack to maintain lexicographic order
            }

            st.push_back(c);  // push current character onto the stack
            used[c - 'a'] = true;  // mark current character as used in the result
        }

        return st;  // return the final smallest subsequence containing all distinct characters
    }
};

int main(){  // main function (empty for this problem)
    return 0;
}