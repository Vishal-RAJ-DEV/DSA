#include <bits/stdc++.h>
using namespace std;


/*
Backtracking through the DP table reconstructs one Longest Common
Subsequence.

Why do we first fill the dp table and then track the LCS?

The dp table tells us the length of the best LCS possible for every pair
of prefixes of the two strings. After this table is ready, we can start
from dp[n][m] and know exactly which direction keeps us on an optimal path.

If characters match, we know that character is part of one LCS and we move
diagonally.

If characters do not match, we cannot simply choose any one side randomly.
We must know whether moving up or moving left gives the longer subsequence.
That information comes from the already-filled dp table:
    dp[i - 1][j] tells the answer after skipping text1[i - 1]
    dp[i][j - 1] tells the answer after skipping text2[j - 1]

Why not directly use one simple recursion and print whenever characters
match?

A direct recursion can find matching characters, but when characters do
not match, it has two choices:
    1. Move in text1
    2. Move in text2

Without dp, recursion does not know which choice will finally produce the
longest subsequence. Printing characters immediately during such recursion
can print a common subsequence, but not necessarily the longest one.

Example:
For some positions, one path may give length 2 and another path may give
length 5. If we print while exploring the wrong path first, the printed
answer can become incorrect.

So the safe approach is:
1. First fill dp to know the best LCS length for all states.
2. Then backtrack/recursively track through dp to collect only the
   characters that belong to an optimal LCS.

Starting from dp[n][m], each cell represents the answer for prefixes
text1[0...i-1] and text2[0...j-1].

1. If text1[i-1] == text2[j-1], this character contributed to the LCS.
   Add it to the answer and move diagonally to (i-1,j-1).

2. Otherwise, the current value came from either the upper cell
   dp[i-1][j] or the left cell dp[i][j-1]. Move toward the cell with
   the larger value, since that path produced the optimal subsequence.

Since traversal proceeds from the end of the strings toward the
beginning, characters are collected in reverse order. Reverse the
result at the end to obtain the correct LCS.
*/


// Solution class for LCS with reconstruction using tabulation
class Solution {
public:
    // Function to return the LCS string of text1 and text2
    string longestCommonSubsequence(string &text1, string &text2) {
        int n = text1.size();
        int m = text2.size();

        // Create DP table to store lengths of LCS for all substrings
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Fill dp table bottom-up
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    // Characters match: increase length by 1
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    // Characters don't match: take max of left and top
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // Reconstruct LCS string from dp table
        int i = n, j = m;
        string lcs = "";

        // Traverse dp table from bottom-right to top-left
        while (i > 0 && j > 0) {
            if (text1[i - 1] == text2[j - 1]) {
                // Characters match, add to result and move diagonally
                lcs += text1[i - 1];
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                // Move up if top cell has greater value
                i--;
            } else {
                // Move left otherwise
                j--;
            }
        }

        // Reverse string since it was built backwards
        reverse(lcs.begin(), lcs.end());

        return lcs;
    }
};

/*
    Recursive way to print/reconstruct the LCS string.

    First we create the same dp table that stores the length of LCS.
    Then instead of using a while loop to move through the table, we use
    recursion.

    Logic of recursive buildLCS(i, j):
    - i and j are current positions in the dp table.
    - If text1[i - 1] == text2[j - 1], that character is part of the LCS.
      So we store that character in ans and move diagonally to i - 1, j - 1.
    - If characters do not match, we move toward the bigger value between
      dp[i - 1][j] and dp[i][j - 1].

    Since recursion starts from the end of both strings, matched characters
    are stored in reverse order. So we reverse ans at the end.
*/
class RecursiveSolution {
public:
    void buildLCS(int i,
                  int j,
                  string &text1,
                  string &text2,
                  vector<vector<int>> &dp,
                  string &ans) {

        // Base case: if any string becomes empty, stop recursion.
        if(i == 0 || j == 0) return;

        // If characters match, store the matched character.
        if(text1[i - 1] == text2[j - 1]) {
            ans += text1[i - 1];

            // Move diagonally because both characters are used.
            buildLCS(i - 1, j - 1, text1, text2, dp, ans);
        }

        // If characters do not match, move to the side that has larger LCS.
        else if(dp[i - 1][j] > dp[i][j - 1]) {
            buildLCS(i - 1, j, text1, text2, dp, ans);
        }
        else {
            buildLCS(i, j - 1, text1, text2, dp, ans);
        }
    }

    string longestCommonSubsequence(string &text1, string &text2) {
        int n = text1.size();
        int m = text2.size();

        // dp[i][j] stores LCS length of first i characters of text1
        // and first j characters of text2.
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Fill the LCS length table.
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        string ans = "";

        // Start recursion from the bottom-right cell.
        buildLCS(n, m, text1, text2, dp, ans);

        // ans is built from end to start, so reverse it.
        reverse(ans.begin(), ans.end());

        return ans;
    }
};

/* ==========================================================================
 *  ALL LCS — Find every Longest Common Subsequence in lexicographical order
 * ==========================================================================
 *
 *  Algorithm:
 *    1. Compute the standard LCS length DP table (same as above).
 *    2. Use DFS backtracking from dp[n][m] to dp[0][*] / dp[*][0].
 *    3. At each step:
 *       - If text1[i-1] == text2[j-1] : this character IS in the LCS,
 *         append it, move diagonally to (i-1, j-1).
 *       - If characters differ, move to ANY neighbour whose dp value
 *         equals dp[i][j] (may be up, left, or BOTH when tied).
 *    4. When i == 0 || j == 0, the path has accumulated exactly LCS length
 *       characters. Reverse the string (built backwards) and store in a set.
 *    5. Convert the set to a vector<string> for the return value.
 *       The set automatically keeps strings sorted lexicographically.
 *
 *  Time  Complexity: O(n * m + L) where L = total length of all LCS strings
 *        (can be exponential in worst case, e.g. strings with all same
 *         characters like "aaa" and "aaa" produce C(n, n/2) LCS strings)
 *  Space Complexity: O(n * m + L)
 * ========================================================================== */

class AllLCS {
public:
    vector<string> findAllLCS(string &text1, string &text2) {
        int n = text1.size(), m = text2.size();

        /* ----- Step 1: Standard LCS length DP table ----- */
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (text1[i - 1] == text2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        int lcsLen = dp[n][m];
        set<string> resultSet;          // automatically sorts lexicographically
        string current = "";

        /* ----- Step 2: Backtrack to collect ALL optimal paths ----- */
        function<void(int, int)> backtrack = [&](int i, int j) {

            /* Base case: one string exhausted */
            if (i == 0 || j == 0) {
                if ((int)current.size() == lcsLen) {
                    string rev = current;
                    reverse(rev.begin(), rev.end());
                    resultSet.insert(rev);
                }
                return;
            }

            if (text1[i - 1] == text2[j - 1]) {
                /* Characters match — this char belongs to the LCS */
                current.push_back(text1[i - 1]);
                backtrack(i - 1, j - 1);
                current.pop_back();          // backtrack
            } else {
                /* Characters differ — explore every direction that
                 * still leads to an optimal solution */
                if (dp[i - 1][j] == dp[i][j])
                    backtrack(i - 1, j);     // move up
                if (dp[i][j - 1] == dp[i][j])
                    backtrack(i, j - 1);     // move left
            }
        };

        backtrack(n, m);

        return vector<string>(resultSet.begin(), resultSet.end());
    }
};



int main() {
    string s1 = "abcde";
    string s2 = "ace";

    Solution sol;
    cout << "Single LCS: " << sol.longestCommonSubsequence(s1, s2) << endl;

    AllLCS all;
    vector<string> allLcs = all.findAllLCS(s1, s2);

    cout << "\nAll LCS (" << allLcs.size() << " found):" << endl;
    for (auto &str : allLcs)
        cout << "  \"" << str << "\"" << endl;

    /* ----- Test with multiple LCS (tied paths) ----- */
    string s3 = "abc", s4 = "acb";
    vector<string> res2 = all.findAllLCS(s3, s4);

    cout << "\nLCS of \"abc\" and \"acb\" (" << res2.size() << " found):" << endl;
    for (auto &str : res2)
        cout << "  \"" << str << "\"" << endl;

    return 0;
}
