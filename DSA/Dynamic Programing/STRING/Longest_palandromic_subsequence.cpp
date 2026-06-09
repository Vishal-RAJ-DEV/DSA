#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Memoization {
public:
    /*
        Algorithm: Longest Palindromic Subsequence using Recursion + Memoization

        A palindrome reads the same forward and backward.
        A subsequence does not need to be continuous, so we are allowed to skip
        characters while keeping the relative order same.

        Core idea:
        - Longest Palindromic Subsequence (LPS) of a string s is the same as the
          Longest Common Subsequence (LCS) between:
              s
              reverse(s)

        Why this works:
        - A palindromic subsequence appears in the same order in the original
          string and in reverse order in the reversed string.

        Meaning of solve(i, j):
        - It returns the LCS length between:
              s[0...i] and rev[0...j]

        Recurrence:
        1. If s[i] == rev[j], this character can be part of the answer:
              1 + solve(i - 1, j - 1)

        2. If s[i] != rev[j], we try skipping one character from either side:
              max(solve(i - 1, j), solve(i, j - 1))

        Memoization:
        - dp[i][j] stores the answer for the state (i, j).
        - This avoids recalculating the same subproblem many times.

        Time Complexity: O(n * n)
        Space Complexity: O(n * n) for dp + O(n) recursion stack
    */

    int solve(int i, int j, const string &s, const string &rev,
              vector<vector<int>> &dp) {

        // If either string part is exhausted, no subsequence is possible.
        if (i < 0 || j < 0)
            return 0;

        // If already computed, return stored value.
        if (dp[i][j] != -1)
            return dp[i][j];

        // If current characters match, include them and move diagonally.
        if (s[i] == rev[j]) {
            return dp[i][j] = 1 + solve(i - 1, j - 1, s, rev, dp);
        }

        // If they do not match, skip one character from either string
        // and keep the better answer.
        return dp[i][j] = max(
            solve(i - 1, j, s, rev, dp),
            solve(i, j - 1, s, rev, dp)
        );
    }

    int longestPalindromeSubseq(string s) {
        int n = s.size();
        string rev = s;
        reverse(rev.begin(), rev.end());

        vector<vector<int>> dp(n, vector<int>(n, -1));

        return solve(n - 1, n - 1, s, rev, dp);
    }
};

class Tabulation {
public:
    /*
        Algorithm: Longest Palindromic Subsequence using Bottom-Up DP

        We again convert the problem into LCS:
        - original string s
        - reversed string rev

        Meaning of dp[i][j]:
        - dp[i][j] stores the LCS length between:
              first i characters of s
              first j characters of rev

        Why dp is of size (n + 1) * (n + 1):
        - Row 0 means first string is empty.
        - Column 0 means second string is empty.
        - LCS with an empty string is always 0.

        Transition:
        - If s[i - 1] == rev[j - 1]:
              dp[i][j] = 1 + dp[i - 1][j - 1]

        - Else:
              dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

        Final answer:
        - dp[n][n] gives the LPS length.

        Time Complexity: O(n * n)
        Space Complexity: O(n * n)
    */

    int longestPalindromeSubseq(string s) {
        int n = s.size();
        string rev = s;
        reverse(rev.begin(), rev.end());

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // i and j start from 1 because row 0 and column 0 are base cases.
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {

                // Since dp is shifted by 1, compare s[i - 1] and rev[j - 1].
                if (s[i - 1] == rev[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[n][n];
    }
};

class SpaceOptimized {
public:
    /*
        Algorithm: Longest Palindromic Subsequence using Space Optimization

        In the full 2D DP table:
        - dp[i][j] depends only on:
              dp[i - 1][j - 1]
              dp[i - 1][j]
              dp[i][j - 1]

        So instead of storing all rows, we only keep:
        - prev -> previous row
        - curr -> current row

        Meaning:
        - prev[j] represents dp[i - 1][j]
        - curr[j] represents dp[i][j]

        Transition:
        - If characters match:
              curr[j] = 1 + prev[j - 1]

        - Else:
              curr[j] = max(prev[j], curr[j - 1])

        After finishing one row, copy curr into prev.

        Time Complexity: O(n * n)
        Space Complexity: O(n)
    */

    int longestPalindromeSubseq(string s) {
        int n = s.size();
        string rev = s;
        reverse(rev.begin(), rev.end());

        vector<int> prev(n + 1, 0);
        vector<int> curr(n + 1, 0);

        for (int i = 1; i <= n; i++) {

            // For each new row, column 0 stays 0 because LCS with empty string is 0.
            curr[0] = 0;

            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == rev[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                }
                else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }

            prev = curr;
        }

        return prev[n];
    }
};

int main() {
    string s = "bbbab";

    Memoization obj1;
    cout << "Longest Palindromic Subsequence (Memoization): "
         << obj1.longestPalindromeSubseq(s) << endl;

    Tabulation obj2;
    cout << "Longest Palindromic Subsequence (Tabulation): "
         << obj2.longestPalindromeSubseq(s) << endl;

    SpaceOptimized obj3;
    cout << "Longest Palindromic Subsequence (Space Optimized): "
         << obj3.longestPalindromeSubseq(s) << endl;

    return 0;
}
