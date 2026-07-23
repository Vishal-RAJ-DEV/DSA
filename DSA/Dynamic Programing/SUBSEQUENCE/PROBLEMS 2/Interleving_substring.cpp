#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ======================================================================
// PROBLEM: Interleaving String (Leetcode 97)
// Given strings s1, s2, s3, check if s3 is formed by an interleaving of s1 and s2.
//
// "Interleaving" means we merge s1 and s2 by taking characters alternately
// while preserving the relative order of characters within each string.
//
// Example: s1 = "aab", s2 = "axy", s3 = "aaxaby" -> true
//          s3 = a(a from s1) a(x from s2) x(a from s2) a(b from s1) b(y from s2) y
//          Order preserved: s1-> a..a..b , s2-> ..a..x..y
// ======================================================================

// ======================================================================
// APPROACH 1: Top-Down DP (Recursion + Memoization)
// ======================================================================
/* 
INTUITION:
- We have two pointers i (in s1) and j (in s2) deciding how much of each we've used.
- At each step, the next character to form is s3[i+j] (since we've used i chars from s1 and j from s2).
- We can take from s1 if s1[i] == s3[i+j], OR from s2 if s2[j] == s3[i+j].
- If either leads to a solution, return true.
- This is a decision tree; we memoize (i,j) states to avoid recomputation.

STATES: (n+1)*(m+1) — each pair (i,j) represents using first i chars of s1 and first j chars of s2.

Time  : O(n * m)
Space : O(n * m)
*/
class Solution {
public:
    int n, m;
    vector<vector<int>> dp;

    bool solve(int i, int j, string &s1, string &ss2, string &s3) {

        // Base Case:
        // If we've used all characters from both strings,
        // then we've successfully formed s3.
        if (i == n && j == m)
            return true;

        // Already computed
        if (dp[i][j] != -1)
            return dp[i][j];

        bool ans = false;

        // Current index in s3 = total characters used so far
        int k = i + j;

        // Option 1: Try matching next character from s1
        if (i < n && s1[i] == s3[k]) {
            ans |= solve(i + 1, j, s1, ss2, s3);
        }

        // Option 2: Try matching next character from s2
        if (j < m && ss2[j] == s3[k]) {
            ans |= solve(i, j + 1, s1, ss2, s3);
        }

        return dp[i][j] = ans;
    }

    bool isInterleave(string s1, string s2, string s3) {

        n = s1.size();
        m = s2.size();

        // Quick check: lengths must add up
        if (n + m != s3.size())
            return false;

        dp.assign(n + 1, vector<int>(m + 1, -1)); // -1 = unvisited, 0 = false, 1 = true

        return solve(0, 0, s1, s2, s3);
    }
};

// ======================================================================
// APPROACH 2: Bottom-Up 2D DP (Tabulation)
// ======================================================================
/*
INTUITION:
- dp[i][j] = true if the first i chars of s1 and first j chars of s2
  can interleave to form the first i+j chars of s3.
- dp[0][0] = true (empty strings form empty string)
- To reach dp[i][j], we must reach it from:
    → dp[i-1][j] if s1[i-1] == s3[i+j-1] (came from using s1 char)
    → dp[i][j-1] if s2[j-1] == s3[i+j-1] (came from using s2 char)
- dp[i][j] = (from_s1_possible) OR (from_s2_possible)

Time  : O(n * m)
Space : O(n * m)
*/
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {

        int n = s1.size();
        int m = s2.size();

        if (n + m != s3.size())
            return false;

        // dp[i][j] = can interleave s1[0..i-1] and s2[0..j-1] to form s3[0..i+j-1]
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        dp[0][0] = true; // empty + empty = empty

        for (int i = 0; i <= n; i++) {          // iterate over s1 prefix length
            for (int j = 0; j <= m; j++) {      // iterate over s2 prefix length

                // Try coming from dp[i-1][j] by using s1[i-1] as the last matched char
                if (i > 0 && s1[i - 1] == s3[i + j - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }

                // Try coming from dp[i][j-1] by using s2[j-1] as the last matched char
                if (j > 0 && s2[j - 1] == s3[i + j - 1]) {
                    dp[i][j] = dp[i][j] || dp[i][j - 1];
                }
            }
        }

        return dp[n][m];
    }
};

// ======================================================================
// APPROACH 3: Bottom-Up 1D DP (Space Optimized)
// ======================================================================
/*
INTUITION:
- In the 2D approach, dp[i][j] only depends on:
    → dp[i-1][j]  (previous row, same column) — "from above"
    → dp[i][j-1]  (same row, previous column) — "from left"
- So we can compress the 2D table into a single 1D array of size (m+1).
- dp[j] represents the current row's state for column j.
- When processing row i:
    → dp[j] (before update) corresponds to dp[i-1][j] (from above) — since it holds previous row's value
    → dp[j-1] (already updated) corresponds to dp[i][j-1] (from left)
- We first initialize dp for row 0 (using only s2 to match prefix of s3).
- Then for each row i (1..n), we update dp[0] for the first column, then dp[1..m].

Time  : O(n * m)
Space : O(m)  — only one row of DP table stored
*/
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {

        int n = s1.size();
        int m = s2.size();

        if (n + m != s3.size())
            return false;

        // dp[j] = can interleave processed prefix of s1 (rows so far) and s2[0..j-1]
        vector<bool> dp(m + 1, false);

        // --- Initialize row 0: using ONLY s2 (i=0) ---
        dp[0] = true; // empty + empty
        // dp[j] = can first j chars of s2 alone form first j chars of s3?
        for (int j = 1; j <= m; j++) {
            dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);
        }

        // --- Process rows for i = 1..n ---
        for (int i = 1; i <= n; i++) {

            // First column: using ONLY s1 (j=0)
            // dp[0] currently holds previous row's dp[0]. Update it for current row.
            dp[0] = dp[0] && (s1[i - 1] == s3[i - 1]);

            for (int j = 1; j <= m; j++) {

                // dp[j] (old)  = dp[i-1][j]  → came from above (use s1)
                // dp[j-1] (new) = dp[i][j-1]  → came from left (use s2)
                dp[j] =
                    (dp[j] && s1[i - 1] == s3[i + j - 1]) ||   // from above: use s1[i-1]
                    (dp[j - 1] && s2[j - 1] == s3[i + j - 1]); // from left:  use s2[j-1]
            }
        }

        return dp[m];
    }
};


int main(){
    return 0;
}
