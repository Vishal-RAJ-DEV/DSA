#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
You are given two strings:
- s = original string
- p = pattern string

Pattern rules:
- '?' matches exactly one character
- '*' matches any sequence of characters, including empty string

Return true if the pattern p matches the entire string s.
Otherwise return false.

Example:
s = "adceb"
p = "*a*b"

Answer = true

Because:
- first '*' can match empty or some characters
- 'a' matches 'a'
- second '*' can match "dce"
- 'b' matches 'b'

Core idea:
We compare the string and pattern from the end.
At each step, the current pattern character decides what paths are possible.
*/

/*
Memoization version

State meaning:
solve(i, j) = can s[0...i] be matched by p[0...j]?

How pattern characters behave:

1. Normal character:
   If s[i] == p[j], both must match directly.
   So move both pointers left.

2. '?':
   '?' must match exactly one character.
   So we consume one character from s and one from p.
   Move both pointers left.

3. '*':
   '*' is the most important part.
   It can behave in 2 ways:

   Path 1: '*' matches empty string
   - ignore '*' from pattern
   - move pattern pointer left
   - solve(i, j - 1)

   Path 2: '*' matches one or more characters
   - use '*' to absorb current character of s
   - move string pointer left, but keep '*' at same pattern position
   - solve(i - 1, j)

Why keep j same in Path 2?
- Because '*' may still absorb more characters after matching one.

Base cases explained one by one:

1. if i < 0 and j < 0:
   - both string and pattern are finished
   - exact full match happened
   - return true

2. if i >= 0 and j < 0:
   - string still has characters left
   - pattern is already finished
   - no way to match remaining string
   - return false

3. if i < 0 and j >= 0:
   - string is finished
   - pattern still remains
   - this is only valid if all remaining pattern characters are '*'
   - because only '*' can match empty string
*/
class Memoization {
public:
    bool checkPattern(string& p, int j) {
        // Check whether p[0...j] contains only '*'
        for (int i = 0; i <= j; i++) {
            if (p[i] != '*') return false;
        }
        return true;
    }

    bool solve(int i, int j, string& s, string& p, vector<vector<int>>& dp) {
        // Base 1: both string and pattern are exhausted.
        if (i < 0 && j < 0) return true;

        // Base 2: pattern exhausted, string still left.
        if (i >= 0 && j < 0) return false;

        // Base 3: string exhausted, pattern still left.
        if (i < 0 && j >= 0) {
            return checkPattern(p, j);
        }

        if (dp[i][j] != -1) return dp[i][j];

        // Direct character match.
        if (s[i] == p[j]) {
            return dp[i][j] = solve(i - 1, j - 1, s, p, dp);
        }

        // '?' matches exactly one character.
        if (p[j] == '?') {
            return dp[i][j] = solve(i - 1, j - 1, s, p, dp);
        }

        if (p[j] == '*') {
            /*
            '*' creates two paths:

            1. solve(i, j - 1)
               '*' acts like empty string

            2. solve(i - 1, j)
               '*' matches current character of s and may match more later
            */
            return dp[i][j] = solve(i, j - 1, s, p, dp) || solve(i - 1, j, s, p, dp);
        }

        // No match possible.
        return dp[i][j] = false;
    }

    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(n - 1, m - 1, s, p, dp);
    }
};

/*
Tabulation version

How recursion converts into tabulation:

Recursion state:
solve(i, j) = match s[0...i] with p[0...j]

To avoid negative indices, shift state by 1:

dp[i][j] = can first i characters of s match first j characters of p?

So:
- i ranges from 0 to n
- j ranges from 0 to m

Meaning:
- dp[0][0] = empty string matches empty pattern

Base conversion:
1. recursion (i < 0 && j < 0) => dp[0][0] = true
2. recursion (i >= 0 && j < 0) => dp[i][0] = false for i > 0 -> this is handled by default initialization to false
3. recursion (i < 0 && j >= 0) => dp[0][j] is true only if p[0...j-1] are all '*' -> we need to fill first row accordingly

Transition conversion:

If s[i - 1] == p[j - 1] or p[j - 1] == '?'
    dp[i][j] = dp[i - 1][j - 1]

If p[j - 1] == '*'
    Path 1: '*' matches empty      => dp[i][j - 1]
    Path 2: '*' matches characters => dp[i - 1][j]
    so:
    dp[i][j] = dp[i][j - 1] || dp[i - 1][j]

Else
    dp[i][j] = false
*/
class Tabulation {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;

        // Fill first row: empty string vs pattern prefix.
        for (int j = 1; j <= m; j++) {
            bool allStar = true;
            for (int k = 1; k <= j; k++) {
                if (p[k - 1] != '*') {
                    allStar = false;
                    break;
                }
            }
            dp[0][j] = allStar;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                } else {
                    dp[i][j] = false;
                }
            }
        }

        return dp[n][m];
    }
};

/*
Space Optimization version

Why space optimization works:
- In tabulation, dp[i][j] depends only on:
  1. dp[i - 1][j - 1]  -> previous row
  2. dp[i - 1][j]      -> previous row
  3. dp[i][j - 1]      -> current row, previous column

So we only need:
- prev = previous row
- curr = current row

Transition remains same:
- direct match or '?' => prev[j - 1]
- '*' => curr[j - 1] || prev[j]

Notice carefully for '*':
- curr[j - 1] means '*' matches empty
- prev[j] means '*' matches current character of s
*/
class SpaceOptimization {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();

        vector<bool> prev(m + 1, false), curr(m + 1, false);
        prev[0] = true;

        // Initialize first row for empty string.
        for (int j = 1; j <= m; j++) {
            bool allStar = true;
            for (int k = 1; k <= j; k++) {
                if (p[k - 1] != '*') {
                    allStar = false;
                    break;
                }
            }
            prev[j] = allStar;
        }

        for (int i = 1; i <= n; i++) {
            curr[0] = false;

            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                    curr[j] = prev[j - 1];
                } else if (p[j - 1] == '*') {
                    curr[j] = curr[j - 1] || prev[j];
                } else {
                    curr[j] = false;
                }
            }

            prev = curr;
            fill(curr.begin(), curr.end(), false);
        }

        return prev[m];
    }
};

int main() {
    string s = "adceb";
    string p = "*a*b";

    Memoization memo;
    Tabulation tab;
    SpaceOptimization space;

    cout << memo.isMatch(s, p) << '\n';
    cout << tab.isMatch(s, p) << '\n';
    cout << space.isMatch(s, p) << '\n';

    return 0;
}
