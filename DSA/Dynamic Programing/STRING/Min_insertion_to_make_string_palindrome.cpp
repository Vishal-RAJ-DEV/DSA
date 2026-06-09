#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//lEETCODE 1312. Minimum Insertion Steps to Make a String Palindrome

class Solution {
public:
    /*
        Intuition:

        We want the minimum number of insertions needed to make the string a palindrome.

        Instead of directly thinking about where to insert characters, think like this:

        - If some characters are already forming a palindromic subsequence,
          we do not need to change those characters.
        - The only characters that cause trouble are the ones that are NOT part
          of the longest palindromic subsequence.

        So:
        - Let LPS = length of Longest Palindromic Subsequence
        - Then the remaining characters = n - LPS
        - Each of those remaining characters must be balanced by inserting
          matching characters at proper places

        Therefore:
            Minimum Insertions = n - LPS

        Now the next question is:
        How do we find LPS?

        Key observation:
        - LPS of a string s is equal to the LCS of:
              s
              reverse(s)

        Why?
        - A palindrome reads the same from left to right and right to left.
        - So if a subsequence appears in s and also appears in reverse(s),
          that common subsequence can represent a palindromic pattern.

        Example:
        s = "mbadm"
        reverse(s) = "mdabm"

        Longest Palindromic Subsequence = "mam" or "mbm", length = 3
        String length = 5

        Minimum insertions = 5 - 3 = 2

        One possible palindrome after 2 insertions:
        "mbdadbm"

        So this problem becomes:
        1. Find LCS(s, reverse(s))
        2. Return n - LCS

        Time Complexity: O(n * n)
        Space Complexity: O(n * n)
    */

    int solve(string s) {
        int n = s.size();

        string rev = s;
        reverse(rev.begin(), rev.end());

        // dp[i][j] = LCS length between:
        // first i characters of s
        // first j characters of rev
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Row 0 and column 0 stay 0 because LCS with an empty string is 0.
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

        // This is the LPS length because LPS = LCS(s, reverse(s)).
        return dp[n][n];
    }

    int minInsertions(string s) {
        // Characters already present in the longest palindromic subsequence
        // are kept as they are.
        // Every other character needs support through insertion.
        return s.size() - solve(s);
    }
};

int main() {
    Solution obj;

    string s = "mbadm";

    cout << "Minimum insertions to make palindrome: "
         << obj.minInsertions(s) << endl;

    return 0;
}
