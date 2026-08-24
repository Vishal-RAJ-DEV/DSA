/*
================================================================================
PROBLEM: Longest Increasing Path in a Matrix
================================================================================

Given an m x n matrix, find the length of the longest strictly increasing
path. You can move up, down, left, or right. You cannot move diagonally
or wrap around.

Example: matrix = [[9,9,4],[6,6,8],[2,1,1]]
  Path: 1 -> 2 -> 6 -> 9  (length 4)
  Answer: 4

================================================================================
APPROACH 1: DFS + MEMOIZATION (THIS FILE)
================================================================================

IDEA:
  For each cell (i,j), use DFS to find the longest increasing path
  starting from that cell. Memoize results so each cell is computed once.

  dp[i][j] = length of longest increasing path starting from (i,j)

  dp[i][j] = 1 + max(dp[nr][nc]) for all neighbors (nr,nc) where
              matrix[nr][nc] > matrix[i][j]

  If no larger neighbor exists, dp[i][j] = 1 (just the cell itself).

WHY DFS WORKS:
  The matrix forms a DAG (Directed Acyclic Graph):
    - Nodes = cells
    - Edge from (r1,c1) to (r2,c2) if they are adjacent AND matrix[r2][c2] > matrix[r1][c1]
  - No cycles because edges only go from SMALLER to LARGER values
  - DFS explores all paths from a cell, memoization avoids recomputation

RECURSION TREE for cell (2,0) in [[9,9,4],[6,6,8],[2,1,1]]:
  matrix[2][0] = 1

  dfs(2,0): neighbors > 1 -> (2,1)=2, (1,0)=6
    |
    +-- dfs(2,1): value=2, neighbors > 2 -> (2,0)=1 NO, (1,1)=6, (2,2)=1 NO
    |     |
    |     +-- dfs(1,1): value=6, neighbors > 6 -> (0,0)=9, (0,1)=9
    |           |
    |           +-- dfs(0,0): value=9, no neighbor > 9 -> return 1
    |           +-- dfs(0,1): value=9, no neighbor > 9 -> return 1
    |           return 1 + max(1,1) = 2
    |     return 1 + 2 = 3
    |
    +-- dfs(1,0): value=6, neighbors > 6 -> (0,0)=9
          |
          +-- dfs(0,0): already computed -> return 1
          return 1 + 1 = 2

  return 1 + max(3, 2) = 4

  dp[2][0] = 4  (path: 1->2->6->9)

CROSS-REFERENCE:
  This problem can ALSO be solved using Topological Sort (Kahn's BFS).
  See: D:\\Data Structure and Algrothim\\DSA\\GRAPH\\TOPO_SORT_PROBLEM\\
       Lonest_increasing_path_in_matrix.cpp

  Both approaches are O(m*n) time and space, but work differently:
    - DFS: Recursion from each cell, memoize results
    - Topological: Process cells level-by-level using BFS (Kahn's algorithm)

TIME:  O(m * n) - each cell visited once due to memoization
SPACE: O(m * n) for dp array + O(m*n) recursion stack worst case
================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class DFS {
public:
    int m, n;

    // -----------------------------------------------------------------------
    // DFS: Find longest increasing path starting from (row, col)
    // -----------------------------------------------------------------------
    // Returns the length of the longest increasing path from this cell.
    //
    // LOGIC:
    //   1. If dp[row][col] already computed, return it (memoization)
    //   2. Check all 4 neighbors (up, down, left, right)
    //   3. If neighbor is LARGER, recursively explore from that neighbor
    //   4. Take the MAX across all valid neighbors
    //   5. Result = 1 (current cell) + max from neighbors
    //
    // WHY ans starts at 1:
    //   The path must include at least the current cell itself.
    //   If no larger neighbor exists, the path is just [matrix[row][col]].
    //
    // VISUAL: dfs(2,0) for matrix:
    //   ┌───┬───┬───┐
    //   │ 9 │ 9 │ 4 │
    //   ├───┼───┼───┤
    //   │ 6 │ 6 │ 8 │
    //   ├───┼───┼───┤
    //   │ 1 │ 2 │ 1 │
    //   └───┴───┴───┘
    //
    //   Start at (2,0)=1. Neighbors > 1: (2,1)=2, (1,0)=6
    //   dfs(2,0) = 1 + max(dfs(2,1), dfs(1,0))
    //            = 1 + max(3, 2) = 4
    // -----------------------------------------------------------------------
    int dfs(int row, int col, vector<vector<int>>& matrix,
            vector<vector<int>>& dp) {

        // Already computed -> return cached answer
        if (dp[row][col] != -1) {
            return dp[row][col];
        }

        int ans = 1;  // path includes at least the current cell

        // 4 directions: up, down, left, right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int k = 0; k < 4; k++) {

            int nr = row + dr[k];
            int nc = col + dc[k];

            // Check bounds AND increasing condition
            if (nr >= 0 && nr < m &&
                nc >= 0 && nc < n &&
                matrix[nr][nc] > matrix[row][col]) {

                // Take the best path from all valid neighbors
                ans = max(
                    ans,
                    1 + dfs(nr, nc, matrix, dp)
                );
            }
        }

        // Cache and return
        return dp[row][col] = ans;
    }

    // -----------------------------------------------------------------------
    // MAIN: Try DFS from every cell, return the overall maximum
    // -----------------------------------------------------------------------
    // We must try starting from EVERY cell because the longest path
    // might start anywhere (not necessarily from the minimum value).
    //
    // VISUAL: dp table for [[9,9,4],[6,6,8],[2,1,1]]:
    //   ┌───┬───┬───┐
    //   │ 1 │ 1 │ 2 │   dp[0][2]=2 because 4->8
    //   ├───┼───┼───┤
    //   │ 2 │ 2 │ 1 │   dp[1][0]=2 because 6->9
    //   ├───┼───┼───┤
    //   │ 4 │ 3 │ 1 │   dp[2][0]=4 because 1->2->6->9
    //   └───┴───┴───┘
    //
    //   Answer = max of all = 4
    // -----------------------------------------------------------------------
    int longestIncreasingPath(vector<vector<int>>& matrix) {

        m = matrix.size();
        n = matrix[0].size();

        // dp[i][j] = longest increasing path starting from (i,j)
        // -1 means "not computed yet"
        vector<vector<int>> dp(m, vector<int>(n, -1));

        int result = 0;

        // Try starting from every cell
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                result = max(
                    result,
                    dfs(i, j, matrix, dp)
                );
            }
        }

        return result;
    }
};


int main(){
    return 0;
}