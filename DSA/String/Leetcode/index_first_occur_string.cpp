#include <iostream>
#include <bits/stdc++.h>

/*
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

 

Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
*/
using namespace std;

    int strStr(string haystack, string needle) {
        int n = haystack.size();        // Get length of haystack string
        int m = needle.size();          // Get length of needle string

        if(m == 0) return 0;            // Edge case: empty needle is found at index 0
        
        // Loop through potential starting positions in haystack
        for(int i = 0; i <= n - m; i++){ 
            // n-m ensures we don't go out of bounds:
            // e.g., if haystack.length=9 and needle.length=3,
            // we only need to check starting positions 0 to 6,
            // since positions 7 and 8 don't have enough characters left
            
            // Extract substring of length m starting at position i,
            // then compare with needle
            if(haystack.substr(i, m) == needle) 
                return i;   // If match found, return current position
        }
        return -1;                      // If no match found, return -1
    }
int main(){
    string haystack = "hello";
    string needle = "ll";
    cout << strStr(haystack, needle) << endl; // Output: 2  
    return 0;
}
