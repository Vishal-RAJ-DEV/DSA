#include <bits/stdc++.h>
using namespace std;
/*

Input :s = "aababbcaacc" , k = 2
Output :6
Explanation :The longest substring with at most two distinct characters is "aababb".
The length of the string 6


Input : s = "abcddefg" , k = 3
Output : 4
Explanation : The longest substring with at most three distinct characters is "bcdd".
The length of the string 4.
*/
class Solution1 {
public:
    // Function to find the length of the longest substring with at most K distinct characters
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        // Store the maximum length of valid substring
        int maxLength = 0;

        // Try every possible substring
        for (int i = 0; i < s.size(); i++) {
            // Use set/map to track distinct characters in current substring
            unordered_map<char, int> freq;

            for (int j = i; j < s.size(); j++) {
                // Add current character to map and update frequency
                freq[s[j]]++;

                // If number of distinct characters exceeds k, break
                if (freq.size() > k) break;

                // Update maximum length if valid
                maxLength = max(maxLength, j - i + 1);
            }
        }

        // Return the maximum valid substring length
        return maxLength;
    }
};
class Solution {
public:
    // Function to find longest substring with at most K distinct characters
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        // Edge case: if k is 0 or string is empty
        if (k == 0 || s.empty()) return 0;

        // Hash map to store frequency of characters in current window
        unordered_map<char, int> freq;

        // Initialize left pointer of sliding window
        int left = 0;

        // Initialize variable to store maximum length
        int maxLen = 0;

        // Loop through the string using right pointer
        for (int right = 0; right < s.length(); right++) {
            // Include current character into frequency map
            freq[s[right]]++;

            // Shrink window if number of distinct characters exceeds k
            while (freq.size() > k) {
                freq[s[left]]--;

                // If character count becomes zero, erase from map
                if (freq[s[left]] == 0) {
                    freq.erase(s[left]);
                }

                // Move left pointer ahead
                left++;
            }

            // Update maxLen with current valid window size
            maxLen = max(maxLen, right - left + 1);
        }

        // Return the final answer
        return maxLen;
    }
};

// Driver code
int main() {
    Solution sol;
    string s = "eceba";
    int k = 2;
    cout << sol.lengthOfLongestSubstringKDistinct(s, k) << endl;
    return 0;
}
