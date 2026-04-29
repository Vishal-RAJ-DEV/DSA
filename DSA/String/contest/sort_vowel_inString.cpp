#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isvowel(char ch) {
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
    }

    string sortVowels(string s) {
        unordered_map<char, int> freq;
        unordered_map<char, int> first_occ;
        vector<char> vowels_in_s;

        // Step 1: Gather frequencies and first occurrence positions
        for (int i = 0; i < s.length(); ++i) {
            if (isvowel(s[i])) {
                freq[s[i]]++;
                if (first_occ.find(s[i]) == first_occ.end()) {
                    first_occ[s[i]] = i;
                }
                vowels_in_s.push_back(s[i]);
            }
        }

        // Step 2: Sort the collected vowels based on the rules
        sort(vowels_in_s.begin(), vowels_in_s.end(), [&](char a, char b) {
            if (freq[a] != freq[b]) {
                return freq[a] > freq[b]; // Non-increasing frequency
            }
            return first_occ[a] < first_occ[b]; // First occurrence tie-breaker
        });

        // Step 3: Place sorted vowels back into original vowel positions
        string result = s;
        int vowel_idx = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (isvowel(s[i])) {
                result[i] = vowels_in_s[vowel_idx++];
            }
        }

        return result;
    }
};
int main(){
    Solution sol;
    string s = "hello world";
    cout << sol.sortVowels(s) << endl; // Output: "holle werld"
    return 0;
}
