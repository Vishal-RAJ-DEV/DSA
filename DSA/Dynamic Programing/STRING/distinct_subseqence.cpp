#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
You are given two strings s and t.
Return the number of distinct subsequences of s which equal t.

What is a subsequence?
- A subsequence is formed by deleting some characters from the string
  without changing the relative order of the remaining characters.

Example:
s = "babgbag"
t = "bag"

Answer = 5

Because there are 5 different ways to pick characters from s
so that the selected characters form "bag".

Core intuition:
At any position, we are deciding whether to use the current character of s
for matching t, or to skip it.

This is why the recursion splits into different paths.
Each path represents one choice pattern.
*/

/*
Memoization version

State meaning:
solve(i, j) = number of ways to form t[0...j] using s[0...i]

How paths are formed:
1. If s[i] == t[j], then we get two choices:
   - take this character
     then move to solve(i - 1, j - 1)
   - do not take this character
     then move to solve(i - 1, j)

   Total ways = take + notTake

2. If s[i] != t[j], then we cannot use s[i] for t[j]
   so only one path remains:
   solve(i - 1, j)

Base cases:
- if j < 0, it means t is fully matched
  so return 1
- if i < 0 but j >= 0, s is finished and t is not formed
  so return 0
*/
class Memoization {
public:
    long long solve(vector<vector<long long>>& dp,
                    string& s, string& t, int i, int j) {
        // We matched all characters of t successfully.
        if (j < 0) return 1;

        // s got exhausted before t could be formed.
        if (i < 0) return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (s[i] == t[j]) {
            /*
            Two paths:
            1. take s[i] as part of t[j]
            2. skip s[i]

            Both paths are valid, so add both answers.
            */
            long long take = solve(dp, s, t, i - 1, j - 1);
            long long notTake = solve(dp, s, t, i - 1, j);

            return dp[i][j] = take + notTake;
        }

        // Characters do not match, so only skipping s[i] is possible.
        return dp[i][j] = solve(dp, s, t, i - 1, j);
    }

    long long numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();

        vector<vector<long long>> dp(n, vector<long long>(m, -1));
        return solve(dp, s, t, n - 1, m - 1);
    }
};

/*
Tabulation version

How recursion is converted into tabulation:

Recursion state:
solve(i, j) = ways to form t[0...j] from s[0...i]

To avoid negative indices in table DP, we shift the meaning by 1:

dp[i][j] = ways to form first j characters of t
           using first i characters of s

That means:
- i ranges from 0 to n
- j ranges from 0 to m

Base case conversion:
1. In recursion, j < 0 returns 1
   This means empty t can always be formed.
   So in table:
   dp[i][0] = 1 for every i

2. In recursion, i < 0 and j >= 0 returns 0
   This means non-empty t cannot be formed from empty s.
   So in table:
   dp[0][j] = 0 for every j > 0

Transition conversion:
If s[i - 1] == t[j - 1]:
- take current char     -> dp[i - 1][j - 1]
- skip current char     -> dp[i - 1][j]
So:
  dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]

If s[i - 1] != t[j - 1]:
- cannot take
- only skip
So:
  dp[i][j] = dp[i - 1][j]
*/
class Tabulation {
public:
    long long numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();

        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));

        // Empty t can be formed from any prefix of s in exactly 1 way.
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }

        // Fill the table row by row.
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1]) {
                    // Two choices: take or skip.
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    // Only skip current character of s.
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return dp[n][m];
    }
};

/*
Space Optimization version

Why optimization is possible:
- In tabulation, current row i depends only on previous row i - 1
- So we do not need the entire 2D table
- We only need:
  1. prev = previous row
  2. curr = current row

Transition stays exactly the same:
if characters match:
    curr[j] = prev[j - 1] + prev[j]
else:
    curr[j] = prev[j]

Base case:
- prev[0] = 1 because empty t can always be formed
- for every new row, curr[0] must also be 1
*/
class SpaceOptimization {
public:
    long long numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();

        vector<long long> prev(m + 1, 0), curr(m + 1, 0);
        prev[0] = 1;

        for (int i = 1; i <= n; i++) {
            curr[0] = 1;

            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1]) {
                    curr[j] = prev[j - 1] + prev[j];
                } else {
                    curr[j] = prev[j];
                }
            }

            prev = curr;
            fill(curr.begin(), curr.end(), 0);
        }

        return prev[m];
    }
};

int main() {
    string s = "babgbag";
    string t = "bag";

    Memoization memo;
    Tabulation tab;
    SpaceOptimization space;

    cout << memo.numDistinct(s, t) << '\n';
    cout << tab.numDistinct(s, t) << '\n';
    cout << space.numDistinct(s, t) << '\n';

    return 0;
}
