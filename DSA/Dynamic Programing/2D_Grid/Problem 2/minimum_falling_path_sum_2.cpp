#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Minimum Falling Path Sum II

    We are given an n x n grid.
    We need to choose exactly one element from each row.

    Rule:
    - From one row to the next row, we are NOT allowed to choose the same column.
    - Example:
        If we choose column 2 in row 0, then in row 1 we can choose any column
        except column 2.

    Goal:
    - Find the minimum possible sum after choosing one valid cell from every row.

    DP idea:
    - Let dp[row][col] mean:
        Minimum sum of a valid falling path that ends at grid[row][col].

    Transition:
    - To reach grid[row][col], the previous cell must come from row - 1.
    - But previous column cannot be equal to col.
    - So:
        dp[row][col] = grid[row][col] + minimum dp[row - 1][prevCol]
                       where prevCol != col

    Base case:
    - For row 0, there is no previous row.
    - So dp[0][col] = grid[0][col].

    Important C++ note:
    - This file currently contains three classes named Solution.
    - C++ will not compile multiple classes with the same name in the same file.
    - These are three different approaches for learning.
    - While submitting/running, keep only one Solution class active, or rename the others.
*/

/*
    Approach 1: Recursion + Memoization

    This is a top-down DP solution.
    We start from a cell in the last row and ask:
    "What is the minimum valid path sum ending at this cell?"

    The recursive function solve(row, col, grid) returns:
    - minimum valid path sum ending at grid[row][col]

    Because the same state solve(row, col) can be needed many times,
    we store already computed answers in dp[row][col].
*/
class Solution {
public:
    // n stores the size of the square grid.
    int n;

    /*
        dp[row][col] stores the answer for solve(row, col).

        dp[row][col] = -1 means:
        - this state has not been calculated yet.

        Once calculated:
        - dp[row][col] stores the minimum valid path sum ending at grid[row][col].
    */
    vector<vector<int>> dp;

    int solve(int row, int col, vector<vector<int>>& grid) {
        /*
            Base case:
            If we are at the first row, the path starts here.
            There is no previous row to add.

            So the minimum sum ending at grid[0][col] is simply grid[0][col].
        */
        if (row == 0) {
            return grid[0][col];
        }

        /*
            Memoization check:
            If dp[row][col] is not -1, it means we have already solved this state.
            Return the stored answer instead of recalculating it.
        */
        if (dp[row][col] != -1) {
            return dp[row][col];
        }

        /*
            ans will store the minimum path sum from the previous row.
            We initialize it with INT_MAX because we are looking for a minimum.
        */
        int ans = INT_MAX;

        /*
            Try every possible column from the previous row.

            To reach grid[row][col], we can come from:
            - grid[row - 1][0]
            - grid[row - 1][1]
            - ...
            - grid[row - 1][n - 1]

            But we cannot come from the same column.
            So if prevCol == col, we skip it.
        */
        for (int prevCol = 0; prevCol < n; prevCol++) {
            if (prevCol == col) {
                continue;
            }

            /*
                solve(row - 1, prevCol, grid) gives the minimum path sum ending
                at the previous row and prevCol.

                We take the minimum among all valid previous columns.
            */
            ans = min(ans, solve(row - 1, prevCol, grid));
        }

        /*
            Now ans contains the best valid path sum from the previous row.

            To end at grid[row][col], we add the current cell value.
            Store it in dp[row][col] before returning.
        */
        return dp[row][col] = grid[row][col] + ans;
    }

    int minFallingPathSum(vector<vector<int>>& grid) {
        // Since the grid is n x n, number of rows and columns both are n.
        n = grid.size();

        /*
            Create an n x n dp table and fill it with -1.
            -1 means no state has been computed yet.
        */
        dp.assign(n, vector<int>(n, -1));

        /*
            Final answer can end at any column in the last row.
            So we try every last-row column and take the minimum.
        */
        int ans = INT_MAX;

        for (int col = 0; col < n; col++) {
            ans = min(ans, solve(n - 1, col, grid));
        }

        return ans;
    }
};

/*
    Approach 2: Bottom-Up Tabulation

    This builds the dp table from the first row to the last row.

    dp[i][j] means:
    - minimum valid path sum ending at cell grid[i][j]

    Instead of using recursion, we fill dp row by row.
*/
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();

        /*
            dp has the same size as grid.
            dp[i][j] will store the minimum valid falling path sum ending at
            grid[i][j].
        */
        vector<vector<int>> dp(n, vector<int>(n));

        /*
            Base case:
            For the first row, there is no previous row.
            So each dp[0][j] is equal to grid[0][j].
        */
        for (int j = 0; j < n; j++) {
            dp[0][j] = grid[0][j];
        }

        /*
            Fill the table row by row starting from row 1.

            For every cell grid[i][j], we search the previous row for the
            smallest dp[i - 1][prevCol], where prevCol is not equal to j.
        */
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {

                /*
                    best stores the minimum path sum from the previous row
                    that can legally come to column j.
                */
                int best = INT_MAX;

                /*
                    Check all columns in the previous row.
                    We skip prevCol == j because choosing the same column in
                    two adjacent rows is not allowed.
                */
                for (int prevCol = 0; prevCol < n; prevCol++) {
                    if (prevCol == j) {
                        continue;
                    }

                    // Keep the smallest valid previous path sum.
                    best = min(best, dp[i - 1][prevCol]);
                }

                /*
                    The best path ending at grid[i][j] is:
                    current cell value + best valid path from previous row.
                */
                dp[i][j] = grid[i][j] + best;
            }
        }

        /*
            The path must end somewhere in the last row.
            Since any column in the last row is allowed as the ending point,
            the answer is the minimum value in dp[n - 1].
        */
        int ans = INT_MAX;

        for (int j = 0; j < n; j++) {
            ans = min(ans, dp[n - 1][j]);
        }

        return ans;
    }
};

/*
    Approach 3: Space Optimized Bottom-Up DP

    In Approach 2, to calculate the current row, we only need the previous row.
    We do not need the entire dp table.

    So instead of dp[n][n], we use:
    - prev: stores DP values of the previous row
    - curr: stores DP values of the current row

    Space reduces from O(n^2) to O(n).
*/
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();

        /*
            prev[j] means:
            - minimum valid path sum ending at column j of the previous row.

            Initially, previous row is row 0.
        */
        vector<int> prev(n);

        /*
            Base case:
            For the first row, path sum is just the cell value itself.
        */
        for (int j = 0; j < n; j++) {
            prev[j] = grid[0][j];
        }

        /*
            Process each remaining row.
            For every row i, we build curr using values from prev.
        */
        for (int i = 1; i < n; i++) {

            /*
                curr[j] will store the minimum valid path sum ending at
                grid[i][j] for the current row.
            */
            vector<int> curr(n);

            for (int j = 0; j < n; j++) {

                /*
                    best stores the minimum value from prev except prev[j],
                    because we cannot choose the same column in adjacent rows.
                */
                int best = INT_MAX;

                /*
                    Search the previous row for the minimum valid column.
                    prevCol == j is skipped because same-column movement is not
                    allowed.
                */
                for (int prevCol = 0; prevCol < n; prevCol++) {
                    if (prevCol == j) {
                        continue;
                    }

                    // Choose the smallest valid previous path sum.
                    best = min(best, prev[prevCol]);
                }

                /*
                    Add the current grid value to the best valid previous path.
                    This gives the minimum path sum ending at grid[i][j].
                */
                curr[j] = grid[i][j] + best;
            }

            /*
                After finishing row i, curr becomes the previous row for the
                next iteration.
            */
            prev = curr;
        }

        /*
            After processing all rows, prev stores the DP values for the last row.
            The answer is the minimum value in prev.
        */
        int ans = INT_MAX;

        for (int j = 0; j < n; j++) {
            ans = min(ans, prev[j]);
        }

        return ans;
    }
};



int main(){
    return 0;
}
