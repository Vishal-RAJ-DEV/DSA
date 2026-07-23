#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ======================================================================
// PROBLEM: Maximal Square (Leetcode 221)
// Given an m x n binary matrix filled with '0's and '1's,
// find the largest square containing only '1's and return its area.
// ======================================================================

// ======================================================================
// INTUITION & ALGORITHM (Bottom-Up 2D DP):
// ======================================================================
/*
Let dp[i][j] = side length of the LARGEST square whose bottom-right
corner is at cell (i, j) and that contains all '1's.

For any cell matrix[i][j] == '1':
- If it's on the first row (i==0) or first column (j==0),
  the largest square ending here has side = 1 (just the cell itself).
- Otherwise, to form a larger square of side L ending at (i,j), we need:
    → A square of side L-1 ending at (i-1, j)   → top neighbor
    → A square of side L-1 ending at (i, j-1)   → left neighbor
    → A square of side L-1 ending at (i-1, j-1) → top-left diagonal neighbor
  The limiting factor is the MINIMUM of these three, plus 1 for the current cell.

Recurrence:
    if matrix[i][j] == '1':
        dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
    else:
        dp[i][j] = 0

Answer = max(dp[i][j])²  (area = side * side)

Example:
    matrix:     dp table:     largest square side (dp):
    1 0 1 0 0   1 0 1 0 0     1 0 1 0 0
    1 0 1 1 1   1 0 1 1 1     1 0 1 1 1
    1 1 1 1 1   1 1 1 2 2     1 1 1 2 2
    1 0 0 1 0   1 0 0 1 0     1 0 0 1 0
    → max side = 2 → area = 4

Time  : O(m * n)
Space : O(m * n)
*/
class Solution { // Bottom-Up 2D DP
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;

        int m = matrix.size(), n = matrix[0].size(), sz = 0;

        // dp[i][j] = side length of largest square ending at (i,j)
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // First row / first column / '0' cell → dp = 0 or 1
                if (i == 0 || j == 0 || matrix[i][j] == '0') {
                    dp[i][j] = matrix[i][j] - '0'; // '1'→1, '0'→0
                } else {
                    // Square = min(up, left, top-left) + 1
                    dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                }
                sz = max(sz, dp[i][j]); // track max side length
            }
        }
        return sz * sz; // area = side²
    }
};

// ======================================================================
// APPROACH 2: Top-Down DP (Recursion + Memoization)
// ======================================================================
/*
INTUITION:
- solve(i, j) returns the side length of the largest square ending at (i, j).
- Base cases: if out of bounds or matrix[i][j] == '0' → return 0.
- Recursive case: if matrix[i][j] == '1':
    → up    = solve(i-1, j)
    → left  = solve(i, j-1)
    → diag  = solve(i-1, j-1)
    → return min(up, left, diag) + 1
- We memoize results in dp[i][j].
- Global max side is tracked separately as we compute each state.

Time  : O(m * n)
Space : O(m * n)
*/
class Solution { // Top-Down Memoization
public:
    vector<vector<int>> dp;
    int maxSide;

    int solve(int i, int j, vector<vector<char>>& matrix) {
        // Out of bounds or cell is '0' → no square ends here
        if (i < 0 || j < 0 || matrix[i][j] == '0')
            return 0;

        // Already computed
        if (dp[i][j] != -1)
            return dp[i][j];

        // Largest squares ending at neighbor positions
        int up   = solve(i - 1, j, matrix);
        int left = solve(i, j - 1, matrix);
        int diag = solve(i - 1, j - 1, matrix);

        // Current square side = min(neighbors) + 1
        dp[i][j] = min({up, left, diag}) + 1;

        maxSide = max(maxSide, dp[i][j]); // track global max

        return dp[i][j];
    }

    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;

        int m = matrix.size(), n = matrix[0].size();
        dp.assign(m, vector<int>(n, -1));
        maxSide = 0;

        // Compute for every cell (bottom-right corners)
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                solve(i, j, matrix);

        return maxSide * maxSide;
    }
};

// ======================================================================
// APPROACH 3: Space Optimized DP (1D Array)
// ======================================================================
/*
INTUITION:
- dp[i][j] only depends on:
    → dp[i-1][j]   (previous row, same col) — "above"
    → dp[i][j-1]   (same row, prev col)     — "left"
    → dp[i-1][j-1] (previous row, prev col) — "diagonal"
- We can replace the full 2D table with a single 1D array of size n.
- dp[j]        = current row's dp for column j (being computed)
- prev         = dp[j-1] before update → holds dp[i][j-1] (left)
- dp[j] (old)  = holds dp[i-1][j]      (above)
- We need to save old dp[j] before updating it to use as diagonal for next column.

State per cell:
    temp = dp[j];               // save old dp[j] = dp[i-1][j]
    dp[j] = min(prev, dp[j], dp[j-1]) + 1   // where dp[j] = above, dp[j-1] = left (already updated)
    prev = temp;                // becomes diagonal for next column

Time  : O(m * n)
Space : O(n)
*/
class Solution { // Space Optimized 1D DP
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;

        int m = matrix.size(), n = matrix[0].size(), sz = 0;

        // dp[j] = side of largest square ending at current row, column j
        vector<int> dp(n, 0);

        for (int i = 0; i < m; i++) {

            int prev = 0; // dp[i-1][j-1] — diagonal from previous row

            for (int j = 0; j < n; j++) {

                int temp = dp[j]; // save current dp[j] (will become diagonal for next col)

                if (i == 0 || j == 0 || matrix[i][j] == '0') {
                    dp[j] = matrix[i][j] - '0';
                } else {
                    // dp[j] (old) = above, dp[j-1] (updated) = left, prev = diagonal
                    dp[j] = min({prev, dp[j], dp[j - 1]}) + 1;
                }

                sz = max(sz, dp[j]);
                prev = temp; // diagonal for next column = old dp[j] of this column
            }
        }
        return sz * sz;
    }
};


int main(){
    return 0;
}
