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



/*
Brute Force Algorithm for Longest Palindromic Substring

Idea:
- Generate every possible substring of the given string.
- For each substring, check whether it is a palindrome.
- If it is a palindrome and its length is greater than the current answer,
update the answer.

Steps:
1. Run a loop with i as the starting index of the substring.
2. Run another loop with j as the ending index of the substring.
3. For every substring s[i...j], check if it is palindrome.
4. If it is palindrome and longer than the previous best substring,
       store its starting index and length.
       5. Return s.substr(start, maxLen).
       
       Time Complexity:
    - O(n^3)
    - There are O(n^2) substrings, and checking each substring can take O(n).

    Space Complexity:
    - O(1), because we only use a few variables.
    */
   
bool isPalindrome(string &s, int left, int right) {

    // Check characters from both ends of the substring.
    while(left < right) {
        
        // If characters do not match, this substring is not a palindrome.
        if(s[left] != s[right]) {
            return false;
        }

        // Move both pointers toward the middle.
        left++;
        right--;
    }

    // If all matching checks passed, the substring is palindrome.
    return true;
}

string longestPalindromeBruteForce(string s) {
    
    int n = s.size();       // Length of the input string.
    int start = 0;          // Starting index of longest palindrome found.
    int maxLen = 0;         // Length of longest palindrome found.
    
    // Pick the starting index of substring.
    for(int i = 0; i < n; i++) {

        // Pick the ending index of substring.
        for(int j = i; j < n; j++) {

            // Current substring is from index i to j.
            int currLen = j - i + 1;
            
            // Check only if current substring is longer than previous answer.
            // This avoids unnecessary palindrome checks for smaller substrings.
            if(currLen > maxLen && isPalindrome(s, i, j)) {
                
                // Store this substring as the best answer so far.
                start = i;
                maxLen = currLen;
            }
        }
    }

    // Return the longest palindromic substring found by brute force.
    return s.substr(start, maxLen);
}

int main(){
    string s = "babad";
    string ans = longestPalindrome(s);  
    cout << ans << endl;
    return 0;
}








