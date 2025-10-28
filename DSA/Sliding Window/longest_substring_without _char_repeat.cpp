#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
3. Longest Substring Without Repeating Characters

Given a string s, find the length of the longest substring without duplicate characters

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/
// optimal approach: Sliding Window with HashSet
// Time Complexity: O(n)
//here the basic idea is the traverse the string with two pointers left and right and keep track of the characters in the current window using a hashset
//if the character is already present in the hashset then we will move the left pointer to the right until the character is not present in the hashset
//if the character is not present in the hashset then we will add the character to the hashset and update the maximum length of the substring


int lengthOfLongestSubstring(string s)
{
    vector<int> map(256, -1);    // Array to store last seen index of each character (ASCII)
    int left = 0;                // Left boundary of current window
    int right = 0;               // Right boundary of current window  
    int n = s.size();            // Length of input string
    int len = 0;                 // Maximum length found so far
    
    while (right < n)            // Iterate through string with right pointer
    {
        // Check if current character was seen before in current window
        if (map[s[right]] != -1)
        {
            // Move left pointer to position after last occurrence of current character
            // Use max to ensure left never moves backward
            left = max((map[s[right]] + 1), left);
        }
        
        map[s[right]] = right;              // Update last seen index of current character
        len = max(right - left + 1, len);   // Update maximum length if current window is larger
        right++;                            // Move right pointer forward
    }
    return len;                             // Return maximum length found
}


int lengthOfLongestSubstring1(string s)
{
    unordered_set<char> charset; // Set to track characters in current window
    int left = 0;                // Left pointer of sliding window
    int maxlen = 0;              // Track maximum length found so far

    for (int right = 0; right < s.size(); right++)
    {
        // If character already exists in current window, shrink window from left
        while (charset.find(s[right]) != charset.end())
        {
            charset.erase(s[left]); // Remove leftmost character from set
            left++;                 // Move left pointer forward
        }

        charset.insert(s[right]);                 // Add current character to the set
        maxlen = max(maxlen, (right - left + 1)); // Update maximum length
    }
    return maxlen; // Return the final maximum length
}
int main()
{
    string s = "abcabcbb";
    cout << lengthOfLongestSubstring(s) << endl; // Output: 3
    return 0;
}

/*
Start: left=0, right=0, charset={}, maxlen=0

Iteration 1: Process 'a'

Add 'a' to charset
No duplicates, window = "a"
maxlen = max(0, 1) = 1
Iteration 2: Process 'b'

Add 'b' to charset
No duplicates, window = "ab"
maxlen = max(1, 2) = 2
Iteration 3: Process 'c'

Add 'c' to charset
No duplicates, window = "abc"
maxlen = max(2, 3) = 3
Iteration 4: Process 'a'

'a' already in charset
Remove 'a' from charset, increment left (window = "bc")
Add 'a' to charset (window = "bca")
maxlen = max(3, 3) = 3
Iteration 5: Process 'b'

'b' already in charset
Remove 'b' from charset, increment left (window = "ca")
Add 'b' to charset (window = "cab")
maxlen = max(3, 3) = 3
Iteration 6: Process 'c'

'c' already in charset
Remove 'c' from charset, increment left (window = "ab")
Add 'c' to charset (window = "abc")
maxlen = max(3, 3) = 3
Iteration 7 & 8: Process 'b', 'b'

Similar process with duplicates
Final maxlen = 3

4. Complexity Analysis
Time Complexity: O(n) where n is the length of the string
Each character is processed at most twice (once by right pointer, once by left)

Space Complexity: O(min(m, n))
m is the size of the character set (at most 26 for lowercase letters)
n is the string length*/