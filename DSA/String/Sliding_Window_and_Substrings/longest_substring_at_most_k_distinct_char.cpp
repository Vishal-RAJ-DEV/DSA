#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Longest Substring with At Most K Distinct Characters
    Given a string s and an integer k, find the length of the longest
    substring that contains at most k distinct characters.

    Example:
    s = "eceba", k = 2
    Output: 3
    Explanation: "ece" has 2 distinct characters (e, c)

    ================================================================
    INTUITION: SLIDING WINDOW TECHNIQUE
    ================================================================

    This problem can be solved efficiently using the SLIDING WINDOW
    technique. The key insight is:

    1. We maintain a window [left, right] that always has at most k
       distinct characters.

    2. We expand the window by moving 'right' pointer forward.

    3. When we exceed k distinct characters, we shrink the window
       from the left until we have exactly k again.

    4. At each step with exactly k distinct characters, we update
       our answer with the window size.

    WHY SLIDING WINDOW WORKS:
    - If a window [L, R] is valid (≤ k distinct), all its subwindows
      are also valid (removing characters can only reduce distinct count)
    - So we only need to find the maximum valid window
    - We don't need to check all substrings!

    VISUAL EXAMPLE:
    s = "eceba", k = 2

    Step 1: [e] - distinct = 1, window = 1
    Step 2: [e,c] - distinct = 2, window = 2 ✓
    Step 3: [e,c,e] - distinct = 2, window = 3 ✓ (max so far)
    Step 4: [e,c,e,b] - distinct = 3 > k! Shrink...
            [c,e,b] - distinct = 3 > k! Shrink...
            [e,b] - distinct = 2, window = 2
    Step 5: [e,b,a] - distinct = 3 > k! Shrink...
            [b,a] - distinct = 2, window = 2

    Answer: 3 ("ece")
*/

// ==========================================
// Approach 1: Sliding Window (Optimal)
// Time: O(n) - single pass
// Space: O(1) - fixed size array (26 chars)
// ==========================================
class SlidingWindow {
public:
    int longestKSubstr(string &s, int k) {

        // Frequency array to count characters in current window
        vector<int> freq(26, 0);

        int left = 0;          // Left pointer of window
        int distinct = 0;      // Number of distinct characters in window
        int ans = -1;          // Maximum length found

        // Expand window by moving right pointer
        for (int right = 0; right < s.size(); right++) {

            // Add current character to window
            int index = s[right] - 'a';

            // If this character was not in window, we have a new distinct char
            if (freq[index] == 0) {
                distinct++;
            }

            freq[index]++;

            // Shrink window from left while we have too many distinct chars
            while (distinct > k) {

                int leftIndex = s[left] - 'a';

                freq[leftIndex]--;

                // If count becomes 0, this character is no longer in window
                if (freq[leftIndex] == 0) {
                    distinct--;
                }

                left++;  // Shrink window
            }

            // If we have exactly k distinct characters, update answer
            if (distinct == k) {
                ans = max(ans, right - left + 1);
            }
        }

        return ans;
    }
};

// ==========================================
// Approach 2: Prefix Sum
// Time: O(n * 26) ≈ O(n) - for each substring, count distinct in O(26)
// Space: O(n * 26) - prefix sum array
// ==========================================
/*
    INTUITION:
    - Precompute prefix sums for each character
    - For any substring [l, r], we can count how many of each character
      using prefix sums: count = prefix[r+1][ch] - prefix[l][ch]
    - Then count distinct characters by checking which characters have
      count > 0

    WHY USE PREFIX SUM?
    - Without prefix sum, counting distinct in a substring takes O(length)
    - With prefix sum, it takes O(26) = O(1) per substring
    - This helps in the brute force approach but still O(n^2) overall
*/
class PrefixSum {
public:
    int longestKSubstr(string &s, int k) {
        int n = s.size();

        // prefix[i][ch] = count of character ch in s[0..i-1]
        vector<vector<int>> prefix(n + 1, vector<int>(26, 0));

        // Build prefix sum array
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i];              // Copy previous counts
            prefix[i + 1][s[i] - 'a']++;            // Increment current char
        }

        int ans = -1;

        // Try all possible substrings [l, r]
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {

                // Count distinct characters in substring [l, r]
                int distinct = 0;
                for (int ch = 0; ch < 26; ch++) {
                    // Count of character ch in s[l..r]
                    int count =
                        prefix[r + 1][ch] - prefix[l][ch];

                    if (count > 0) {
                        distinct++;
                    }
                }

                // Update answer if exactly k distinct
                if (distinct == k) {
                    ans = max(ans, r - l + 1);
                }
            }
        }

        return ans;
    }
};

// ==========================================
// Approach 3: Brute Force
// Time: O(n^3) - for each substring, count distinct in O(n)
// Space: O(1) - just a frequency array
// ==========================================
/*
    INTUITION:
    - Check ALL possible substrings
    - For each substring, count distinct characters
    - Keep track of maximum length with exactly k distinct

    WHY THIS IS SLOW:
    - O(n^2) substrings to check
    - For each substring, O(n) to count distinct characters
    - Total: O(n^3)

    This is the simplest approach but least efficient.
    Used here for comparison with better approaches.
*/
class BruteForce {
public:
    int longestKSubstr(string &s, int k) {
        int n = s.size();
        int ans = -1;

        // Try all possible starting positions
        for (int i = 0; i < n; i++) {

            // Reset frequency array for each new substring
            vector<int> freq(26, 0);
            int distinct = 0;

            // Try all possible ending positions
            for (int j = i; j < n; j++) {

                int index = s[j] - 'a';

                // If this character was not in substring, new distinct char
                if (freq[index] == 0) {
                    distinct++;
                }

                freq[index]++;

                // Update answer if exactly k distinct
                if (distinct == k) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};

/*
    COMPARISON OF ALL APPROACHES:
    ============================

    Approach          Time        Space     Notes
    ─────────────────────────────────────────────────
    Sliding Window    O(n)        O(1)      Best! Single pass
    Prefix Sum        O(n*26)     O(n*26)   Precomputation helps
    Brute Force       O(n^3)      O(1)      Check all substrings

    KEY INSIGHT:
    - Sliding window is optimal because we only need to track the
      maximum valid window, not check all substrings
    - When we exceed k distinct, we shrink from left
    - When we have exactly k distinct, we try to expand

    EDGE CASES:
    - If k > 26: Return -1 (can't have more than 26 distinct lowercase chars)
    - If k == 0: Return -1 (need at least 1 distinct char)
    - If string length < k: Return -1 (not enough characters)
*/

int main(){
    return 0;
}
