#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {

        int freq[26] = {};

        // Step 1: Count frequency of every character
        for (char c : s) {
            freq[c - 'a']++;
        }

        // Step 2: Find the first character occurring once
        for (int i = 0; i < s.length(); i++) {
            if (freq[s[i] - 'a'] == 1) {
                return i;
            }
        }

        return -1;
    }
};




int main(){
    return 0;
}