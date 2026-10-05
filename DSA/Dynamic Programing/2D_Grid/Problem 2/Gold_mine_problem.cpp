#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/******************************************************************************
 * PROBLEM: Gold Mine
 *
 *   mat[n][m] = gold kept in each cell.
 *   A miner starts from ANY cell of the FIRST column (j = 0)
 *   and from a cell (i, j) he may move to only 3 places
 *   (all in the NEXT column j+1):
 *
 *          (i-1, j+1)   up-right diagonal      \   |   /
 *          ( i , j+1)   straight right         -- cell --
 *          (i+1, j+1)   down-right diagonal     /   |   \
 *
 *   Goal: collect the MAXIMUM gold = max sum of visited cells.
 *   He stops when he reaches the last column (no more columns).
 *
 * ONE LINE INTUITION
 *   "Gold I can collect from (i,j) = my gold + the BEST of the 3
 *    next cells.  Last column = only my gold (journey ends)."
 *
 * The file contains 4 versions of the same solution:
 *   WAY 1 : top-down recursion + memoization
 *   WAY 2 : bottom-up 2D dp table   (right -> left columns)
 *   WAY 3 : bottom-up with only 2 rows (space optimized)
 *   WAY 4 : bottom-up IN-PLACE      (no extra dp at all)
 ******************************************************************************/

// ================= WAY 1 : TOP-DOWN (Recursion + Memoization) =================
// solve(i, j) = MAX gold the miner can collect
//               STARTING from cell (i, j) and going right till the end.
//
// BASE CASE : if I am already in the last column, journey stops,
//             so gold = only mat[i][j].
//
// TRANSITION: mat[i][j] + best of (up-right, right, down-right)
//             missing directions (top row / bottom row) are simply 0.
//
// MEMO: dp[i][j] caches the answer -> each cell solved only once,
//       time O(n*m) instead of 3^(m) paths.
class Solution {
public:
    int n, m;
    vector<vector<int>> dp;

    int solve(int i, int j, vector<vector<int>>& mat) {
        // journey ends at the last column
        if (j == m - 1)
            return mat[i][j];

        // already solved this cell?
        if (dp[i][j] != -1)
            return dp[i][j];

        // 0 = that direction does not exist, so it contributes nothing
        int up = 0, right = 0, down = 0;

        // Diagonal up-right
        if (i - 1 >= 0)
            up = solve(i - 1, j + 1, mat);

        // Right
        right = solve(i, j + 1, mat);

        // Diagonal down-right
        if (i + 1 < n)
            down = solve(i + 1, j + 1, mat);

        // my gold + best of the three possible next moves
        return dp[i][j] = mat[i][j] + max({up, right, down});
    }

    int maxGold(vector<vector<int>>& mat) {
        n = mat.size();
        m = mat[0].size();

        dp.assign(n, vector<int>(m, -1));

        int ans = 0;

        // Miner can start from any row in column 0
        for (int i = 0; i < n; i++) {
            ans = max(ans, solve(i, 0, mat));
        }

        return ans;
    }
};


// ================= WAY 2 : BOTTOM-UP 2D DP =================
// Same formula as WAY 1, but no recursion - we FILL a table.
//
// DIRECTION: last column first, then move RIGHT -> LEFT.
//   (WAY 1 depended on column j+1, so here also column j+1 must be
//    ready BEFORE we compute column j - hence the reverse loop.)
//
// dp[i][j] = max gold collectable STARTING from cell (i, j).
//   dp[i][j] = mat[i][j] + max( dp[i-1][j+1],  dp[i][j+1],  dp[i+1][j+1] )
//                            up-right          right        down-right
//
// Answer = max over the FIRST column (that is where we may start).
class Solution {
public:
    int maxGold(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        vector<vector<int>> dp(n, vector<int>(m, 0));

        // Last column: no move left, gold = own value only
        for (int i = 0; i < n; i++) {
            dp[i][m - 1] = mat[i][m - 1];
        }

        // Move from right to left
        for (int j = m - 2; j >= 0; j--) {
            for (int i = 0; i < n; i++) {

                int up = 0;
                int right = dp[i][j + 1];
                int down = 0;

                if (i - 1 >= 0)
                    up = dp[i - 1][j + 1];

                if (i + 1 < n)
                    down = dp[i + 1][j + 1];

                dp[i][j] = mat[i][j] + max({up, right, down});
            }
        }

        // Can start from any row in first column
        int ans = 0;

        for (int i = 0; i < n; i++) {
            ans = max(ans, dp[i][0]);
        }

        return ans;
    }
};


// ================= WAY 3 : WAY 2 + SPACE OPTIMIZATION =================
// Logic is 100% same as WAY 2 (still right -> left).
//
// Observation: to compute column j we ONLY need column j+1.
//   next[i] -> dp value of column j+1 (already known)
//   curr[i] -> dp value of column j  (being built now)
// So the full n x m table is NOT needed, only 2 columns.
//
// Time  : O(n*m)     Space : O(n)   instead of O(n*m)
class Solution {
public:
    int maxGold(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        vector<int> next(n);
        vector<int> curr(n);

        // Last column
        for (int i = 0; i < n; i++) {
            next[i] = mat[i][m - 1];
        }

        // Process columns from right to left
        for (int j = m - 2; j >= 0; j--) {

            for (int i = 0; i < n; i++) {

                int up = 0;
                int right = next[i];
                int down = 0;

                if (i - 1 >= 0)
                    up = next[i - 1];

                if (i + 1 < n)
                    down = next[i + 1];

                curr[i] = mat[i][j] + max({up, right, down});
            }

            // Current column becomes next column
            next = curr;
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            ans = max(ans, next[i]);
        }

        return ans;
    }
};


// ================= WAY 4 : BOTTOM-UP, IN-PLACE (no extra dp) =================
// HOW IS THIS DIFFERENT FROM THE OTHER THREE?
// --------------------------------------------
// WAY 1 : extra dp table + recursion stack.
// WAY 2 : extra dp table, filled right -> left.
// WAY 3 : no full table, but still 2 extra arrays of size n.
// WAY 4 : NO extra space at all - we OVERWRITE mat itself with the dp values.
//
// WHY IS OVERWRITING SAFE?
//   mat[i][j] is read in only 2 places:
//     (1) mat[i][j] += ...  while computing THIS cell  -> the original
//         value is consumed exactly here, before being overwritten.
//     (2) as "right / up-right / down-right" by the cells of column j-1
//         -> by that time column j already holds dp values, which is
//         EXACTLY what those cells need.
//   So the original value of every cell is used exactly once, and only
//   by its own cell. Nothing is lost.
//
// HOW THE LOOP WORKS, STEP BY STEP:
//   1) j = m-2 : column m-1 already has the raw gold (journey end).
//      For every row i we write into mat[i][m-2]:
//          mat[i][m-2] = original mat[i][m-2]
//                        + max( right/up-right/down-right from column m-1 )
//      Now column m-2 holds "best gold if you START at (i, m-2)".
//   2) j = m-3 : same, but it reads the already-computed column m-2.
//      Repeat till j = 0.
//   3) After the loops, mat[i][0] = best gold if the miner starts
//      from row i of the first column.
//   4) Answer = max over mat[i][0]  (start row is our choice).
//
// Time O(n*m), Space O(1).
class Solution {
public:
    int maxGold(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        // Start from second-last column and move right to left
        for (int j = m - 2; j >= 0; j--) {
            for (int i = 0; i < n; i++) {

                int up = 0;
                // mat[*][j+1] is no longer raw gold - it already stores
                // the best gold from that cell onwards (dp value)
                int right = mat[i][j + 1];
                int down = 0;

                if (i - 1 >= 0)
                    up = mat[i - 1][j + 1];

                if (i + 1 < n)
                    down = mat[i + 1][j + 1];

                // original value of this cell + best of the 3 moves
                mat[i][j] += max({up, right, down});
            }
        }

        // Maximum gold starting from any row of first column
        int ans = 0;

        for (int i = 0; i < n; i++) {
            ans = max(ans, mat[i][0]);
        }

        return ans;
    }
};


int main(){
    return 0;
}