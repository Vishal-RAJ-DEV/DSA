// Problem: Maximum Length Substring with at Most Two Occurrences
// https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/
//
// APPROACH: Variable Size Sliding Window
//
// KEY INSIGHT:
// We need the longest substring where NO character appears more than 2 times.
// Use two pointers (left, right) to maintain a valid window.
//
// ALGORITHM:
// 1. Expand window by moving right pointer, updating character frequencies
// 2. When any character count exceeds 2, shrink from left until valid again
// 3. Track maximum valid window size throughout
//
// EXAMPLE: s = "eceba"
//   right=0: 'e' -> window="e",     freq={e:1},         len=1
//   right=1: 'c' -> window="ec",    freq={e:1,c:1},     len=2
//   right=2: 'e' -> window="ece",   freq={e:2,c:1},     len=3
//   right=3: 'b' -> window="eceb",  freq={e:2,c:1,b:1}, len=4
//   right=4: 'a' -> window="eceba", freq={e:2,c:1,b:1,a:1}, len=5
//   Answer: 3 ("ece")
//
// TIME COMPLEXITY: O(n) - each element is visited at most twice (once by right, once by left)
// SPACE COMPLEXITY: O(k) where k = number of distinct characters (at most 26 for lowercase)

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();

        // Frequency map to track count of each character in current window
        unordered_map<char , int>freq;

        int left = 0;    // Left boundary of sliding window
        int ans = 0;     // Maximum valid window size found

        // Expand window by moving right pointer
        for(int right = 0 ; right < n ; right++){
            // Add right character to window
            freq[s[right]]++;

            // Shrink window from left while constraint is violated
            // (any character appears more than 2 times)
            while(freq[s[right]] > 2){
                freq[s[left]]--;  // Remove left character from window
                left++;           // Move left pointer forward
            }

            // Update maximum length of valid window
            // Window size = right - left + 1
            ans = max(ans , right - left + 1);
        }

        return ans;
    }
};


int main(){
    return 0;
}