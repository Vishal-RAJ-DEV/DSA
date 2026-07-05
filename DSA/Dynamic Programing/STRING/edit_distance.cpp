#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Edit Distance

    We want the minimum number of operations needed to convert s1 into s2.

    Allowed operations:
    1. Insert a character
    2. Delete a character
    3. Replace a character

    Very important intuition:
    We do NOT actually keep changing the string in code.

    Why?
    Because DP only needs the minimum count of operations, not the final edited
    string itself.

    So instead of building a new answer string, we only ask:
    "From these current positions, what is the minimum cost required now?"

    That is why this problem is different from:
    - Print LCS
    - Shortest Common Supersequence reconstruction

    In those problems we were asked to build/print a string.
    Here we are only asked for the minimum number of operations, so storing an
    integer answer in DP is enough.
*/

class Memoization {
public:
    /*
        solve(i, j) means:
        minimum operations needed to convert
            s1[0...i]
        into
            s2[0...j]

        We start from the last characters and move backward.

        Base cases:
        - If i < 0, s1 is exhausted.
          Then we must insert all remaining (j + 1) characters of s2.

        - If j < 0, s2 is exhausted.
          Then we must delete all remaining (i + 1) characters of s1.

        Choice logic when characters are different:

        1. Replace:
           Replace s1[i] with s2[j].
           Cost = 1 + solve(i - 1, j - 1)

        2. Delete:
           Delete s1[i].
           Cost = 1 + solve(i - 1, j)

        3. Insert:
           Insert s2[j] into s1.
           After inserting, s2[j] is matched, but s1[i] is still not processed.
           Cost = 1 + solve(i, j - 1)

        We take the minimum of these three choices.

        If characters already match:
        - no operation is needed for this pair
        - just move diagonally to smaller prefixes
    */
    int solve(int i,
              int j,
              const string &s1,
              const string &s2,
              vector<vector<int>> &dp) {

        if (i < 0) return j + 1;
        if (j < 0) return i + 1;

        if (dp[i][j] != -1) return dp[i][j];

        if (s1[i] == s2[j]) {
            return dp[i][j] = solve(i - 1, j - 1, s1, s2, dp);
        }

        int replaceCost = solve(i - 1, j - 1, s1, s2, dp);
        int deleteCost = solve(i - 1, j, s1, s2, dp);
        int insertCost = solve(i, j - 1, s1, s2, dp);

        return dp[i][j] = 1 + min(replaceCost, min(deleteCost, insertCost));
    }

    int editDistance(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(n - 1, m - 1, s1, s2, dp);
    }
};

class Tabulation {
public:
    /*
        dp[i][j] means:
        minimum operations needed to convert
            first i characters of s1
        into
            first j characters of s2

        Why dp size is (n + 1) x (m + 1)?
        - Row 0 means s1 is empty
        - Column 0 means s2 is empty

        Base filling intuition:

        1. dp[0][j] = j
           If s1 is empty and we want to make first j characters of s2,
           the only way is to insert j characters.

        2. dp[i][0] = i
           If s2 is empty and s1 has i characters,
           the only way is to delete i characters.

        This base row and base column are the tabulation version of the
        recursion base cases:
        - i < 0  -> need insertions
        - j < 0  -> need deletions

        Transition:
        If s1[i - 1] == s2[j - 1]:
            no new operation needed
            dp[i][j] = dp[i - 1][j - 1]

        Else take best of 3 operations:
        - replace -> dp[i - 1][j - 1]
        - delete  -> dp[i - 1][j]
        - insert  -> dp[i][j - 1]

        Then add 1 for the current operation.
    */
    int editDistance(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 0; i <= n; i++) {
            dp[i][0] = i;
        }

        for (int j = 0; j <= m; j++) {
            dp[0][j] = j;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    int replaceCost = dp[i - 1][j - 1];
                    int deleteCost = dp[i - 1][j];
                    int insertCost = dp[i][j - 1];

                    dp[i][j] = 1 + min(replaceCost, min(deleteCost, insertCost));
                }
            }
        }

        return dp[n][m];
    }
};

class SpaceOptimization {
public:
    /*
        In tabulation, dp[i][j] depends only on:
        - dp[i - 1][j - 1]  -> previous row, previous column
        - dp[i - 1][j]      -> previous row
        - dp[i][j - 1]      -> current row, previous column

        So we do not need the full 2D table.
        We keep only:
        - prev = previous row
        - cur  = current row

        Meaning here:
        - prev[j] acts like dp[i - 1][j]
        - cur[j] acts like dp[i][j]

        Base setup:
        - prev[j] = j means converting empty s1 to first j chars of s2
          needs j insertions.
        - For every new row i, cur[0] = i means converting first i chars of s1
          to empty s2 needs i deletions.

        Choice logic stays exactly the same as normal tabulation.
        Only the storage is reduced.
    */
    int editDistance(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();

        vector<int> prev(m + 1, 0);
        vector<int> cur(m + 1, 0);

        for (int j = 0; j <= m; j++) {
            prev[j] = j;
        }

        for (int i = 1; i <= n; i++) {
            cur[0] = i;

            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    cur[j] = prev[j - 1];
                } else {
                    int replaceCost = prev[j - 1];
                    int deleteCost = prev[j];
                    int insertCost = cur[j - 1];

                    cur[j] = 1 + min(replaceCost, min(deleteCost, insertCost));
                }
            }

            prev = cur;
        }

        return prev[m];
    }
};

int main() {
    string s1 = "horse";
    string s2 = "ros";

    Memoization memo;
    Tabulation tab;
    SpaceOptimization so;

    cout << "Memoization: " << memo.editDistance(s1, s2) << endl;
    cout << "Tabulation: " << tab.editDistance(s1, s2) << endl;
    cout << "Space Optimization: " << so.editDistance(s1, s2) << endl;

    return 0;
}
