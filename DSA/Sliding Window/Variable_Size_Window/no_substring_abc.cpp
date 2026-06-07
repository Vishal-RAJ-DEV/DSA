#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 
Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 
Example 3:

Input: s = "abc"
Output: 1
*/
int numberOfSubstrings(string s)
{
    int n = s.size();                      // Get length of input string
    int left = 0;                          // Left pointer of sliding window
    int right = 0;                         // Right pointer of sliding window
    int maxLen = 0;                        // Total count of valid substrings (note: variable name is misleading, should be 'count')
    unordered_map<int, int> mpp;           // Map to store frequency of characters 'a', 'b', 'c'
                                           // Key: 0 for 'a', 1 for 'b', 2 for 'c'
    int satisfes = 0;                      // Count of distinct characters (a, b, c) in current window
    
    while (right < n)                      // Expand window by moving right pointer
    {
        // Check if this character is appearing for the first time in current window
        if (mpp[s[right] - 'a'] == 0)      
            satisfes++;                    // Increment count of distinct characters
        
        mpp[s[right] - 'a']++;             // Increment frequency of current character
                                           // s[right] - 'a' converts: 'a'→0, 'b'→1, 'c'→2
        
        // When we have all three characters (a, b, c) in current window
        while (satisfes == 3)              
        {
            // KEY INSIGHT: If substring from [left...right] contains all 3 chars,
            // then ALL substrings from [left...right], [left...right+1], ... [left...n-1]
            // also contain all 3 chars
            maxLen += (n - right);         // Add count of all such valid substrings
            
            mpp[s[left] - 'a']--;          // Reduce frequency of leftmost character
            
            // If frequency becomes 0, we no longer have this character in window
            if (mpp[s[left] - 'a'] == 0)   
                satisfes--;                // Decrement count of distinct characters
            
            left++;                        // Shrink window from left
        }
        
        right++;                           // Move right pointer to next position
    }
    
    return maxLen;                         // Return total count of valid substrings
}
int main()
{
    string s = "abcabc";
    cout << numberOfSubstrings(s) << endl; // Output: 10

    return 0;
}
