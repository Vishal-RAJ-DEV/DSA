#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*242. Valid Anagram
Given two strings s and t, return true if t is an anagram of s, and false otherwise.
Example 1:

Input: s = "anagram", t = "nagaram"
Output: true

Example 2:
Input: s = "rat", t = "car"
Output: false*/

bool isAnagram(string s, string t) {
    if(s.size() != t.size()) return false;

    unordered_map<char,int> mpp;

    for(char c : s) {
        mpp[c]++;
    }

    for(char c : t) {
        if(mpp.count(c)) {
            mpp[c]--;
        }
    }

    for(auto &p : mpp) {
        if(p.second != 0) return false;
    }

    return true;
}

int main(){
    string s = "anagram";
    string t = "nagaram";

    if(isAnagram(s, t)){
        cout << "The strings are anagrams." << endl;
    } else {
        cout << "The strings are not anagrams." << endl;
    }

    return 0;
}