/*
================================================================================
                       DUNGEON GAME  (LeetCode 174)
================================================================================

PROBLEM
-------
Given an m x n grid `dungeon`:
  - Knight starts at cell (0, 0)   -> top-left
  - Princess is locked at cell (m-1, n-1) -> bottom-right
  - dungeon[i][j] > 0  -> a health potion  (health increases)
  - dungeon[i][j] < 0  -> a demon/Trap    (health decreases)
  - dungeon[i][j] = 0  -> nothing
Knight can only move RIGHT or DOWN.
Find the MINIMUM initial health so that the knight's health is ALWAYS >= 1
at every point of the chosen path, and he still reaches the princess.

KEY INSIGHT / REAL LOGIC
------------------------
Forward DP (start -> end) DOES NOT WORK, because:
  "current health" depends on the path taken so far, and we must guarantee
  health never drops below 1 ANYWHERE. Many different health values can reach
  the same cell, and future cells care about the WORST (lowest) health seen.

So we think BACKWARDS (end -> start):
  Define dp[i][j] = minimum health required JUST BEFORE entering cell (i,j)
                    so that the knight can reach the princess alive.

  At cell (i, j) the knight:
    1. must survive this cell   -> health after this cell >= 1
    2. must survive the rest    -> needs `nextHealth` after this cell,
                                   where nextHealth = best (minimum) requirement
                                   of the two possible next cells (right / down)
  So:  health after  = nextHealth
       health before = nextHealth - dungeon[i][j]   (dungeon may heal or hurt)
  But health can never be < 1, so clamp with max(1, ...):

        dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j])

  BASE CASE (princess cell, bottom-right):
        There is no "next" cell. Just need to survive this cell:
        dp[m-1][n-1] = max(1, 1 - dungeon[m-1][n-1])
        (if demon of -5 : need 1-(-5) = 6 before, so after losing 5 -> 1)
        (if potion of +5 : need max(1, 1-5) = 1  -> already safe)

  WHY min() of the two directions?
        The knight CHOOSES the path that needs the LEAST initial HP,
        so from two candidate next cells we take the smaller requirement.

  ANSWER = dp[0][0]  (minimum health to start with at the entry cell)

================================================================================
  THREE APPROACHES  (all O(m*n) time, differ in space / style)
--------------------------------------------------------------------------------
  1) TOP-DOWN MEMOIZATION   : recursion from (0,0), dp table + call stack
  2) BOTTOM-UP TABULATION   : separate dp table, filled from (m-1,n-1) -> (0,0)
  3) BOTTOM-UP IN-PLACE     : reuse `dungeon` itself as the dp table, O(1) extra

  NOTE: All three classes are named `Solution`. Keep only ONE uncommented
        at a time to compile (rename others, e.g. Solution1/Solution2/Solution3).
================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------------------
// APPROACH 1 : TOP-DOWN MEMOIZATION (recursive + dp table)
// -----------------------------------------------------------------------------
// How it works:
//   solve(i, j) answers: "min health needed to enter (i,j) and reach princess"
//   * Base cases
//       - out of grid      -> return 1e9 (a "never chosen" large value, so that
//                             min(right, down) at the border ignores the
//                             invalid direction automatically)
//       - princess cell    -> max(1, 1 - dungeon[i][j])  (same as DP base case)
//   * Transition
//       right = solve(i, j+1)     -> go right
//       down  = solve(i+1, j)     -> go down
//       nextHealth = min(right, down)          // knight picks cheaper path
//       dp[i][j] = max(1, nextHealth - dungeon[i][j])   // survive this cell
//   * Memo: dp[i][j] != -1 means already computed -> return it (avoid re-work)
//   * Start: solve(0,0)
// Time  : O(m*n)  - each cell computed once
// Space : O(m*n)  - dp table + O(m+n) recursion stack depth
// -----------------------------------------------------------------------------
class Solution1 {
public:
    int m, n;
    vector<vector<int>> dp;

    int solve(int i, int j, vector<vector<int>>& dungeon) {
        // Outside the grid = impossible path, huge value so min() skips it
        if (i >= m || j >= n)
            return 1e9;

        // Princess cell (base case): only need to survive this one cell
        if (i == m - 1 && j == n - 1)
            return max(1, 1 - dungeon[i][j]);

        // Memoization: already solved this subproblem
        if (dp[i][j] != -1)
            return dp[i][j];

        // Requirements of the two possible NEXT cells
        int right = solve(i, j + 1, dungeon);
        int down = solve(i + 1, j, dungeon);

        // Knight takes the path needing the least health
        int nextHealth = min(right, down);

        // Health needed BEFORE this cell: survive cell (>=1) + afford next path
        return dp[i][j] = max(1, nextHealth - dungeon[i][j]);
    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        m = dungeon.size();
        n = dungeon[0].size();

        // -1 = "not computed yet"
        dp.assign(m, vector<int>(n, -1));

        return solve(0, 0, dungeon);
    }
};

// -----------------------------------------------------------------------------
// APPROACH 2 : BOTTOM-UP TABULATION (iterative, separate dp table)
// -----------------------------------------------------------------------------
// How it works:
//   Same recurrence as Approach 1, but filled ITERATIVELY from the princess
//   cell backwards, so NO recursion is needed.
//   Order of filling (reverse of travel direction):
//     1) dp[m-1][n-1] = base case (princess cell)
//     2) last ROW   : only one way to move -> RIGHT neighbour exists
//     3) last COLUMN: only one way to move -> DOWN  neighbour exists
//     4) remaining cells (i = m-2..0, j = n-2..0): both neighbours ready
//   Because we fill bottom-right -> top-left, dp[i+1][j] and dp[i][j+1]
//   are ALWAYS already computed when we need them (no dependency problem).
//   Answer = dp[0][0]
// Time  : O(m*n)
// Space : O(m*n) for the dp table
// -----------------------------------------------------------------------------
class Solution2 {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();

        vector<vector<int>> dp(m, vector<int>(n));

        // Princess cell: just survive it
        dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1]);

        // Last row: can only move RIGHT, so nextHealth = dp of right cell
        for (int j = n - 2; j >= 0; j--) {
            dp[m - 1][j] = max(1, dp[m - 1][j + 1] - dungeon[m - 1][j]);
        }

        // Last column: can only move DOWN, so nextHealth = dp of cell below
        for (int i = m - 2; i >= 0; i--) {
            dp[i][n - 1] = max(1, dp[i + 1][n - 1] - dungeon[i][n - 1]);
        }

        // Remaining cells: choose min(right, down), then adjust by this cell
        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                int nextHealth = min(dp[i + 1][j], dp[i][j + 1]);

                dp[i][j] = max(1, nextHealth - dungeon[i][j]);
            }
        }

        // Minimum initial health at the starting cell
        return dp[0][0];
    }
};

// -----------------------------------------------------------------------------
// APPROACH 3 : BOTTOM-UP IN-PLACE (reuse the dungeon grid itself)
// -----------------------------------------------------------------------------
// How it works:
//   EXACTLY the same logic as Approach 2, but instead of allocating a new
//   dp table we OVERWRITE dungeon[i][j] with the dp value.
//   This is safe because when we process cell (i,j) we only READ
//   dungeon[i+1][j] and dungeon[i][j+1] (already converted to dp values)
//   and WRITE dungeon[i][j] (never needed again in its original form).
//   Final answer is left sitting in dungeon[0][0].
// Time  : O(m*n)
// Space : O(1) extra  (only loop variables) -> best space complexity
// -----------------------------------------------------------------------------
class Solution3 {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();

        // Princess cell becomes its own dp value
        dungeon[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1]);

        // Last row (only RIGHT is possible)
        for (int j = n - 2; j >= 0; j--) {
            dungeon[m - 1][j] = max(1, dungeon[m - 1][j + 1] - dungeon[m - 1][j]);
        }

        // Last column (only DOWN is possible)
        for (int i = m - 2; i >= 0; i--) {
            dungeon[i][n - 1] = max(1, dungeon[i + 1][n - 1] - dungeon[i][n - 1]);
        }

        // Interior cells: min of the two next cells, then fix current cell
        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                int nextHealth = min(dungeon[i + 1][j], dungeon[i][j + 1]);

                dungeon[i][j] = max(1, nextHealth - dungeon[i][j]);
            }
        }

        // dungeon[0][0] now holds the minimum initial HP
        return dungeon[0][0];
    }
};

/*
================================================================================
  QUICK COMPARISON
  --------------------------------------------------------------------------------
  | Approach        | Time   | Extra Space | Notes                              |
  |-----------------|--------|-------------|------------------------------------|
  | 1. Memoization  | O(m*n) | O(m*n)+stack| Easiest to derive, recursive       |
  | 2. Tabulation   | O(m*n) | O(m*n)      | No recursion, clearest structure   |
  | 3. In-place     | O(m*n) | O(1)        | Reuses input grid, space optimal   |
  --------------------------------------------------------------------------------

  DRY RUN (small grid):
      dungeon = [ [-2, -3,  3],
                  [-5, -10, 1],
                  [10,  30, -5] ]

      Step 1 (base): dp[2][2] = max(1, 1-(-5)) = 6
      Step 2 (last row):
          dp[2][1] = max(1, 6 - 30)  = 1
          dp[2][0] = max(1, 1 - 10)  = 1
      Step 3 (last col):
          dp[1][2] = max(1, 6 - 1)   = 5
          dp[0][2] = max(1, 5 - 3)   = 2
      Step 4 (interior):
          dp[1][1] = min(dp[1][2], dp[2][1]) = min(5,1) = 1
                     max(1, 1 - (-10)) = 11
          dp[1][0] = min(dp[1][1], dp[2][0]) = min(11,1) = 1
                     max(1, 1 - (-5))  = 6
          dp[0][1] = min(dp[0][2], dp[1][1]) = min(2,11) = 2
                     max(1, 2 - (-3))  = 5
          dp[0][0] = min(dp[0][1], dp[1][0]) = min(5,6)  = 5
                     max(1, 5 - (-2))  = 7
      Answer = 7  -> start with 7 HP, path: (0,0)->(0,1)->(0,2)->(1,2)->(2,2)
================================================================================
*/

int main(){
    return 0;
}
