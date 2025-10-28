#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
🧠 Algorithm (Step-by-Step)

1.Initialize:
start = 0, maxLen = 0 — to store the best palindrome found so far.

2.Loop through each character in s:
Treat i as the center.
Expand around it for both cases:
Odd length: center at i
Even length: center between i and i+1

3.Expansion logic:
From the center, move:
left-- and right++ while s[left] == s[right]
When expansion stops, we have found the palindrome boundaries.
Calculate the length: len = right - left - 1
Update maxLen and start ad the left if this palindrome is longer.

4.Return the substring:
Finally, return s.substr(start, maxLen).
*/
string longestPalindrome(string s) {
    int start = 0;                        // Starting index of the longest palindrome found
    int maxlen = 1;                       // Length of the longest palindrome (initialized to 1 since single char is palindrome)
    int n = s.size();                     // Length of input string
    
    for(int i = 0; i < n; i++) {          // Loop through each character as potential center
        // Case 1: Check for odd-length palindromes with center at position i
        int l = i;                        // Initialize left pointer at center
        int r = i;                        // Initialize right pointer at center
        while(l >= 0 && r < n && s[l] == s[r]) {
            // Valid palindrome found - check if it's longer than our current best
            if(r - l + 1 > maxlen) {
                maxlen = r - l + 1;       // Update maximum length
                start = l;                // Update starting position
            }
            l--;                          // Expand left
            r++;                          // Expand right
        }

        // Case 2: Check for even-length palindromes with center between i and i+1
        l = i;                            // Reset left pointer to current position
        r = i + 1;                        // Right pointer starts at next position
        while(l >= 0 && r < n && s[l] == s[r]) {
            // Valid palindrome found - check if it's longer than our current best
            if(r - l + 1 > maxlen) {
                maxlen = r - l + 1;       // Update maximum length
                start = l;                // Update starting position
            }
            l--;                          // Expand left
            r++;                          // Expand right
        }
    }
    
    return s.substr(start, maxlen);       // Extract and return the longest palindromic substring
}


int main(){
    string s = "babad";
    string ans = longestPalindrome(s);  
    cout << ans << endl;
    return 0;
}