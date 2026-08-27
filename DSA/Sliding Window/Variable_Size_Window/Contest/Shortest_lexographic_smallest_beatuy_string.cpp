#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * PROBLEM: Find the shortest substring with exactly k ones.
     *          If multiple have same length, pick the lexicographically smallest.
     *
     * "Beautiful" substring = substring containing exactly k ones.
     *
     * EXAMPLE: s = "10101", k = 2
     *   Substrings with exactly 2 ones:
     *     "101"   (indices 0-2) → length 3
     *     "10101" (indices 0-4) → length 5
     *     "101"   (indices 2-4) → length 3
     *   Shortest = length 3, lex smallest among them = "101"
     *
     * INTUITION:
     * -------------------------
     * We use a VARIABLE SIZE SLIDING WINDOW to find the shortest window
     * with exactly k ones.
     *
     * Key observations:
     * 1. We want to MINIMIZE length → shrink window when we have k ones
     * 2. Leading zeros don't help (they only make substring longer)
     *    → remove leading zeros when we have k ones
     * 3. Among same-length candidates, pick lex smallest (string comparison)
     *
     * WHY THIS WORKS:
     * - Sliding window guarantees we explore ALL valid windows
     * - After finding k ones, we shrink from left to get shortest
     * - Removing leading zeros makes substring as short as possible
     * - String comparison handles lex order naturally
     */

    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();

        int left = 0;      // Left boundary of sliding window
        int ones = 0;      // Count of '1's in current window [left, right]

        string ans = "";   // Best answer found so far

        // EXPAND: move right pointer one step at a time
        for (int right = 0; right < n; right++) {

            // Include s[right] in window
            if (s[right] == '1')
                ones++;

            // SHRINK: if we have MORE than k ones, window is too large
            // Move left forward until we have exactly k ones again
            while (ones > k) {
                if (s[left] == '1')
                    ones--;     // Removing a '1' reduces count

                left++;         // Shrink window from left
            }

            // VALID WINDOW: exactly k ones found
            if (ones == k) {

                // OPTIMIZATION: Remove leading zeros
                // Why? If s[left] == '0', removing it keeps k ones
                // but makes substring SHORTER (better answer)
                // Example: "001001" → remove leading "00" → "1001"
                while (left < right && s[left] == '0') {
                    left++;
                }

                // Extract current candidate substring
                string cur = s.substr(left, right - left + 1);

                // UPDATE ANSWER if current is better:
                //   1. No answer yet (ans == "")
                //   2. Shorter length (cur.size() < ans.size())
                //   3. Same size but lex smaller (cur < ans)
                if (ans == "" ||
                    cur.size() < ans.size() ||
                    (cur.size() == ans.size() && cur < ans)) {

                    ans = cur;
                }
            }
        }

        return ans;
    }
};



int main(){
    return 0;
}