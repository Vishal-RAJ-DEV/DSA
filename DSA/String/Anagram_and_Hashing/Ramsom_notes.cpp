// LeetCode 383 - Ransom Note: https://leetcode.com/problems/ransom-note/
// Given two strings ransomNote and magazine, return true if ransomNote can be
// constructed using the letters from magazine (each letter used at most once).

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {

        int freq[26] = {};

        for (char c : magazine) {
            freq[c - 'a']++;
        }

        for (char c : ransomNote) {
            if (freq[c - 'a'] == 0)
                return false;

            freq[c - 'a']--;
        }

        return true;
    }
};



int main(){
    return 0;
}