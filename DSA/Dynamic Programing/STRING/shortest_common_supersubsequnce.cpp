#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    We need the Shortest Common Supersequence (SCS) of two strings.

    Supersequence means:
    - The final string must contain s1 as a subsequence.
    - The final string must also contain s2 as a subsequence.

    Shortest means:
    - Among all possible common supersequences, return the one with minimum length.

    Key idea:
    The common characters that already appear in the same relative order in
    both strings should be written only once.

    That common ordered part is the LCS (Longest Common Subsequence).

    So:
    - LCS characters are shared by both strings and can be written once.
    - Non-LCS characters are still required and must also be included.

    Because of that:
    SCS length = s1.length + s2.length - LCS length

    dp[i][j] stores the LCS length of:
    - first i characters of s1
    - first j characters of s2

    Reconstruction intuition:
    - If s1[i - 1] == s2[j - 1], this character is common, so store it once.
    - Otherwise move toward the bigger LCS value.
      Why? That path preserves more shared characters, which helps keep the
      final supersequence shorter.

    Difference from Print LCS:
    - In Print LCS, when characters do not match, we only move in dp.
    - In SCS, when characters do not match, we still store one character,
      because the final answer must contain both strings completely as
      subsequences, not only their common part.

    Why reverse at the end?
    - Backtracking starts from the ends of the strings.
    - So we store characters from right to left.
    - Reverse gives the correct final order.
*/

class Solution {
public:
    // Function to return the shortest common supersequence of two strings
    string shortestSupersequence(string s1, string s2) {

        // Get the lengths of the two strings
        int n = s1.size();
        int m = s2.size();

        // Create a 2D DP table to store lengths of LCS
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Initialize base cases: when either string is empty
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }
        for (int i = 0; i <= m; i++) {
            dp[0][i] = 0;
        }

        // Fill the DP table using bottom-up approach
        for (int ind1 = 1; ind1 <= n; ind1++) {
            for (int ind2 = 1; ind2 <= m; ind2++) {

                // If characters match, take diagonal + 1
                if (s1[ind1 - 1] == s2[ind2 - 1])
                    dp[ind1][ind2] = 1 + dp[ind1 - 1][ind2 - 1];

                // Otherwise, take max from left or top
                else
                    dp[ind1][ind2] = max(dp[ind1 - 1][ind2], dp[ind1][ind2 - 1]);
            }
        }

        // Start from bottom-right and backtrack to build the SCS.
        // This is similar to Print LCS, but here unmatched characters are
        // also stored because they are needed in the final supersequence.
        int i = n;
        int j = m;
        string ans = "";

        // Traverse the table in reverse to find the supersequence
        while (i > 0 && j > 0) {

            // Same character in both strings:
            // store it once because this single character can represent both.
            if (s1[i - 1] == s2[j - 1]) {
                ans += s1[i - 1];
                i--;
                j--;
            }

            // Characters are different.
            // Move toward the side with larger LCS value so we keep the path
            // with more common characters available for merging.
            else if (dp[i - 1][j] > dp[i][j - 1]) {

                // s1[i - 1] is not matched with s2[j - 1], but it still must
                // appear in the SCS so that s1 remains a subsequence.
                ans += s1[i - 1];
                i--;
            } else {

                // s2[j - 1] is also required for the same reason:
                // s2 must remain a subsequence of the final answer.
                ans += s2[j - 1];
                j--;
            }
        }

        // If s2 is exhausted, all remaining characters of s1 are compulsory.
        while (i > 0) {
            ans += s1[i - 1];
            i--;
        }

        // If s1 is exhausted, all remaining characters of s2 are compulsory.
        while (j > 0) {
            ans += s2[j - 1];
            j--;
        }

        // We built the answer from end to start while backtracking.
        reverse(ans.begin(), ans.end());

        // Return the final shortest supersequence
        return ans;
    }
};

// Driver code
int main() {

    // Define input strings
    string s1 = "brute";
    string s2 = "groot";

    // Create object of Solution class
    Solution obj;

    // Call the function and print result
    cout << "The Shortest Common Supersequence is " << obj.shortestSupersequence(s1, s2);

    return 0;
}
