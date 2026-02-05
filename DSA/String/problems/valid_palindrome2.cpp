#include <iostream>
#include <bits/stdc++.h>
/*
Description
You are given a string s, return true if the s can be a palindrome after deleting at most one character from it.

A palindrome is a string that reads the same forward and backward.

Note: Alphanumeric characters consist of letters (A-Z, a-z) and numbers (0-9).

Example 1:

Input: s = "aca"

Output: true
Explanation: "aca" is already a palindrome.
*/
using namespace std;

//brute force approach by generating all the substrings by removing one character at a time
//time complexity : O(n^2)
//space complexity : O(n)
class Solution {
public:
    bool validPalindrome(string s) {
        if (isPalindrome(s)) {
            return true;
        }

        for (int i = 0; i < s.size(); i++) {
            string newS = s.substr(0, i) + s.substr(i + 1);
            if (isPalindrome(newS)) {
                return true;
            }
        }

        return false;
    }

private:
    bool isPalindrome(const string& s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};
//optimal approach with passsing substring in the helper function
//tiem complexity : O(n)
//space complexity : o(n) beacuse of the substring
class Solution {
public:
    bool validPalindrome(string s) {
        int l = 0, r = s.size() - 1;

        while (l < r) {
            if (s[l] != s[r]) {
                return isPalindrome(s.substr(0, l) + s.substr(l + 1)) ||
                       isPalindrome(s.substr(0, r) + s.substr(r + 1));
            }
            l++;
            r--;
        }

        return true;
    }

private:
    bool isPalindrome(string s) {
        int l = 0, r = s.length() - 1;
        while (l < r) {
            if (s[l] != s[r]) {
                return false;
            }
            l++;
            r--;
        }
        return true;
    }
};

//optimal approach using two pointer technique without passing the substring
//time complexity : o(n)
//space complexity : o(1)
class Solution {
public:
    bool isPalindrome( string &s , int l , int r){
        while( l<=r){
            if( s[l] != s[r]){
                return false;
            }
            l++;
            r--;
        }
        return true;
    }
    bool validPalindrome(string s) {
        int l = 0 ; 
        int r = s.length() - 1;

        while( l<=r){
            if( s[l] != s[r]){
                return isPalindrome(s, l + 1 , r ) || //skip the left charcater and check 
                       isPalindrome( s , l , r -1);  //skip the right character 
            }
            //if matches then simply increse the pointer 
            l++;
            r--;
        }
        return true;
    }
};
int main(){
    return 0;
}