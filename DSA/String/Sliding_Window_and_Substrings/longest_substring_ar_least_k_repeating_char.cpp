#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int solve(string& s, int left, int right, int k) {

        // If substring length is smaller than k,
        // no character can appear at least k times.
        if (right - left + 1 < k) {
            return 0;
        }

        // Count frequency in current substring
        vector<int> freq(26, 0);

        for (int i = left; i <= right; i++) {
            freq[s[i] - 'a']++;
        }

        // Find a character whose frequency is < k
        for (int i = left; i <= right; i++) {

            if (freq[s[i] - 'a'] < k) {

                // This character cannot be part
                // of any valid substring.

                int next = i + 1;

                // Skip consecutive invalid characters
                while (next <= right &&
                       freq[s[next] - 'a'] < k) {
                    next++;
                }

                // Divide into two parts
                int leftPart = solve(s, left, i - 1, k);
                int rightPart = solve(s, next, right, k);

                return max(leftPart, rightPart);
            }
        }

        // Every character occurs at least k times
        return right - left + 1;
    }


    int longestSubstring(string s, int k) {

        return solve(s, 0, s.size() - 1, k);
    }
};


int main(){
    return 0;
}