#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool matches(char s, char p) {
        return p == '.' || s == p;
    }

    bool solve(int i, int j, string &s, string &p,
               vector<vector<int>>& dp) {

        // Both string and pattern are exhausted
        if (i == 0 && j == 0) return true;

        // Pattern exhausted, but string remains
        if (j == 0) return false;

        // Check memoization
        if (dp[i][j] != -1) return dp[i][j];

        // Current pattern character is '*'
        if (p[j - 1] == '*') {

            // '*' matches zero occurrences of preceding element
            bool zero = solve(i, j - 2, s, p, dp);

            // '*' matches one or more occurrences
            bool multiple = false;

            if (i > 0 && matches(s[i - 1], p[j - 2])) {
                multiple = solve(i - 1, j, s, p, dp);
            }

            return dp[i][j] = zero || multiple;
        }

        // Normal character or '.'
        if (i > 0 && matches(s[i - 1], p[j - 1])) {
            return dp[i][j] = solve(i - 1, j - 1, s, p, dp);
        }

        return dp[i][j] = false;
    }

    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        return solve(n, m, s, p, dp);
    }
};



class Solution {
public:
    bool matches(char s, char p) {
        return p == '.' || s == p;
    }

    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        // Both string and pattern are empty
        dp[0][0] = true;

        // Empty string matches patterns like a*, a*b*, a*b*c*
        for (int j = 2; j <= m; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {

                // Current pattern character is '*'
                if (p[j - 1] == '*') {

                    // '*' matches zero occurrences
                    dp[i][j] = dp[i][j - 2];

                    // '*' matches one or more occurrences
                    if (matches(s[i - 1], p[j - 2])) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }

                // Normal character or '.'
                else if (matches(s[i - 1], p[j - 1])) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }

        return dp[n][m];
    }
};




int main(){
    return 0;
}