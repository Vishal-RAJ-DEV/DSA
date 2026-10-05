#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
 VERSION 1 : RECURSION + MEMOIZATION  ->  score is computed DIRECTLY
             ("one function does everything")
================================================================================
 PROBLEM (LeetCode 3148 - Maximum Difference Score in a Grid):
   - From a cell you may move to ANY other cell that is strictly BELOW it
     (same column, bigger row) or strictly to the RIGHT of it (same row,
     bigger column). The destination does NOT have to be adjacent.
   - Score of one move  c1 -> c2  is  c2 - c1.
   - You start at any cell and MUST make at least one move.
   - Return the maximum total score.

 KEY MATH INSIGHT (telescoping sum):
   Path: a -> b -> c -> ...
   total = (b - a) + (c - b) + ... = LAST - FIRST
   => the score of a whole path depends ONLY on its first and last cell,
      never on the cells in between.
   => problem becomes: pick two cells (start, end), end reachable from start
      (end not above and not left of start, and end != start),
      maximize  grid[end] - grid[start].

 WHAT solve(i, j) MEANS HERE:
   The best TOTAL SCORE of a path that starts exactly at cell (i, j)
   (i.e. best over all reachable "end" cells of grid[end] - grid[i][j]).
   Note: the subtraction of grid[i][j] happens INSIDE this function.

 HOW IT WORKS:
   Every reachable "end" cell is reached through some first hop, and the
   first hop is in one of 3 groups:
     1) same column, lower row      (loop "Go down")
     2) same row,   right column    (loop "Go right")
     3) lower row AND right column  (double loop "diagonal")
        - a diagonal cell is NOT a legal single move, but going
          down-then-right reaches it and, by telescoping, gives the SAME
          total score. So treating it as one hop is valid.
   For each candidate (x, y):
       ans = max(ans, grid[x][y] - grid[i][j])              -> stop after 1 move
       ans = max(ans, grid[x][y] - grid[i][j] + solve(x, y)) -> keep going
   (the 2nd line is just grid[end] - grid[i][j] for whatever end the
    sub-path from (x,y) ends at)

 BASE / DEAD END:
   If no hop is possible (bottom row + last column combination) ans stays
   INT_MIN -> "there is no path starting from this cell". That value is
   harmless: it can never beat a real answer.

 IMPORTANT - THE OVERFLOW GUARD:
   `grid[x][y] - grid[i][j] + next` is only legal when next != INT_MIN.
   If next were INT_MIN, the addition wraps around (signed overflow / UB) and
   produces huge garbage values like 2147483647. So every continuation is
   guarded with `if (next != INT_MIN)` - the "stop after this move" line
   above already covers the case where the sub-path cannot continue.

 ANSWER: max over ALL cells (i, j) of solve(i, j)  (start may be anywhere).

 COMPLEXITY: O(m*n) states, but every state scans O(m + n + m*n) cells
             -> about O(m^2 * n^2). Correct but slow (can TLE).
================================================================================
*/
class Solution1 {
public:
    int solve(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
        // MEMO: INT_MIN = "not computed yet" (also the natural dead-end value)
        if (dp[i][j] != INT_MIN)
            return dp[i][j];

        int m = grid.size();
        int n = grid[0].size();

        int ans = INT_MIN;   // INT_MIN = no path exists from (i, j)

        // Go down : first hop to (x, j) with x > i  (same column, below)
        for (int x = i + 1; x < m; x++) {
            // path of exactly one move: score = grid[x][j] - grid[i][j]
            ans = max(ans, grid[x][j] - grid[i][j]);

            // or continue the path from (x, j) onwards
            // (guard: next == INT_MIN means nothing is reachable from (x, j),
            //  adding it would overflow int -> MUST skip it)
            int next = solve(x, j, grid, dp);
            if (next != INT_MIN)
                ans = max(ans, grid[x][j] - grid[i][j] + next);
        }

        // Go right : first hop to (i, y) with y > j  (same row, right side)
        for (int y = j + 1; y < n; y++) {
            ans = max(ans, grid[i][y] - grid[i][j]);

            // (guard: skip when nothing is reachable from (i, y), avoids overflow)
            int next = solve(i, y, grid, dp);
            if (next != INT_MIN)
                ans = max(ans, grid[i][y] - grid[i][j] + next);
        }

        // Go diagonally / lower-right : (x, y) with x > i AND y > j
        // (reachable with 2 legal moves; telescoping makes it equivalent)
        for (int x = i + 1; x < m; x++) {
            for (int y = j + 1; y < n; y++) {
                ans = max(ans, grid[x][y] - grid[i][j]);

                int next = solve(x, y, grid, dp);
                if (next != INT_MIN)   // guard: avoid INT_MIN overflow
                    ans = max(ans, grid[x][y] - grid[i][j] + next);
            }
        }

        // memoize the best score of a path starting at (i, j)
        return dp[i][j] = ans;
    }

    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // INT_MIN everywhere = "uncomputed" / "no path"
        vector<vector<int>> dp(m, vector<int>(n, INT_MIN));

        int ans = INT_MIN;

        // we may START at any cell of the grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans = max(ans, solve(i, j, grid, dp));
            }
        }

        return ans;
    }
};


/*
================================================================================
 VERSION 2 : RECURSION + MEMOIZATION  ->  stores the best reachable VALUE
             ("two-step: find best value, subtract outside")
             THIS IS THE SMARTER RECURSION - how it differs from VERSION 1
================================================================================
 MAIN DIFFERENCE FROM VERSION 1
 --------------------------------------------------------------------------
                        VERSION 1                  VERSION 2
 --------------------------------------------------------------------------
 what dp[i][j] stores    best SCORE                 best grid VALUE that is
                        = best_end - grid[i][j]     reachable from (i, j)
 where grid[i][j] is     INSIDE solve()              OUTSIDE, in maxScore()
 is subtracted
 directions tried        down + right + diagonal     only down + right
 work per state          O(m + n + m*n)             O(1)
 total time              O(m^2 * n^2)               O(m * n)
 --------------------------------------------------------------------------
 WHY ONLY "down" AND "right" ARE ENOUGH HERE:
   solve(i, j) only asks "what is the largest grid value among cells that
   are below-or-right of (i, j), excluding (i, j) itself?".
   The best such cell is either:
        - the direct neighbour below            grid[i+1][j]
        - something reachable from below        solve(i+1, j)
        - the direct neighbour right            grid[i][j+1]
        - something reachable from the right    solve(i, j+1)
   The diagonal case is automatically covered: a diagonal cell is reachable
   from (i+1, j) (it is to its right) so solve(i+1, j) already includes it.
   So no nested loop is needed -> O(1) work per cell.

 HOW IT WORKS
   1) solve(i, j) = max value reachable from (i, j) in one or more moves
        base: dead end (bottom-right cell) -> INT_MIN = "nothing reachable"
   2) in maxScore(), for every cell that CAN make a move:
        candidate score = solve(i, j) - grid[i][j]
      and take the maximum over all start cells.
      (telescoping again: score = grid[end] - grid[start])

 SENTINELS
   - dp is filled with -1 = "not computed yet". Safe because grid values are
     >= 1, so a real answer is never -1 (a dead end gives INT_MIN, not -1).
   - INT_MIN inside solve() = "no cell reachable from here".
   - the cell (m-1, n-1) has no move at all -> skipped in maxScore().

 COMPLEXITY: O(m*n) time, O(m*n) space.
================================================================================
*/
class Solution2 {
public:
    // returns the MAXIMUM grid value reachable from (i, j) (1 move or more)
    int solve(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
        int m = grid.size();
        int n = grid[0].size();

        // MEMO: -1 = not computed yet (grid values are positive, so -1 is safe)
        if (dp[i][j] != -1)
            return dp[i][j];

        int best = INT_MIN;   // INT_MIN = no cell is reachable from (i, j)

        // Go down : cell below, or anything reachable from that cell
        if (i + 1 < m) {
            best = max(best, grid[i + 1][j]);          // stop right below
            best = max(best, solve(i + 1, j, grid, dp)); // or go further
        }

        // Go right : cell on the right, or anything reachable from it
        if (j + 1 < n) {
            best = max(best, grid[i][j + 1]);          // stop right beside
            best = max(best, solve(i, j + 1, grid, dp)); // or go further
        }

        // memoize the best reachable VALUE from (i, j)
        return dp[i][j] = best;
    }

    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, -1));   // -1 = uncomputed

        int ans = INT_MIN;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // bottom-right cell can never move -> it cannot be a start
                if (i == m - 1 && j == n - 1)
                    continue;

                int best = solve(i, j, grid, dp);  // best value reachable from here

                // score = reachable value - starting value
                ans = max(ans, best - grid[i][j]);
            }
        }

        return ans;
    }
};


/*
================================================================================
 VERSION 3 : TABULATION (bottom-up 2-D DP)  =  iterative version of VERSION 2
================================================================================
 SAME DEFINITION AS VERSION 2:
   dp[i][j] = the maximum grid VALUE reachable from cell (i, j)
              (looking only below / right, never at (i, j) itself).
   answer   = max over cells of  dp[i][j] - grid[i][j].

 WHY THE LOOP RUNS BACKWARDS:
   dp[i][j] needs dp[i+1][j] (row below) and dp[i][j+1] (column to the right),
   so we fill from the BOTTOM-RIGHT corner towards the TOP-LEFT corner:
        for i = m-1 ... 0
          for j = n-1 ... 0
   When we are at (i, j) both required cells are already computed.

 INITIAL VALUE:
   dp is created with INT_MIN = "nothing reachable yet".
   The bottom-right cell has no down/right neighbour, so it keeps INT_MIN
   (it is the base / dead-end case) - exactly what recursion returned.

 TRANSITION (for every cell):
   DOWN   : consider grid[i+1][j]  (end the path right below)
            consider dp[i+1][j]    (best value reachable from that cell)
   RIGHT  : consider grid[i][j+1]  (end the path right beside)
            consider dp[i][j+1]    (best value reachable from there)
   dp[i][j] = maximum of everything considered; stays INT_MIN if neither
              branch exists (last row AND last column handled by the ifs).

 ANSWER:
   Whenever dp[i][j] != INT_MIN the cell can make at least one move, so
   dp[i][j] - grid[i][j] is a valid candidate score. Take the max.
   (Skipping the INT_MIN cells is the "you must make at least one move"
    rule of the problem.)

 COMPLEXITY: O(m*n) time, O(m*n) space. No recursion / no stack overflow.
================================================================================
*/
class Solution3 {
public:
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j] = best VALUE reachable from (i, j); INT_MIN = nothing yet
        vector<vector<int>> dp(m, vector<int>(n, INT_MIN));

        int ans = INT_MIN;

        // bottom-up: dependencies are (i+1, j) and (i, j+1) -> go reverse
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                // Down: value right below, or best reachable from there
                if (i + 1 < m) {
                    dp[i][j] = max(dp[i][j], grid[i + 1][j]);
                    dp[i][j] = max(dp[i][j], dp[i + 1][j]);
                }

                // Right: value right beside, or best reachable from there
                if (j + 1 < n) {
                    dp[i][j] = max(dp[i][j], grid[i][j + 1]);
                    dp[i][j] = max(dp[i][j], dp[i][j + 1]);
                }

                // If there is at least one valid move
                if (dp[i][j] != INT_MIN) {
                    ans = max(ans, dp[i][j] - grid[i][j]);
                }
            }
        }

        return ans;
    }
};


/*
================================================================================
 VERSION 4 : TABULATION + SPACE OPTIMIZATION  (single 1-D array of size n)
================================================================================
 WHY 2-D DP IS NOT NEEDED:
   To compute the cell (i, j) we only ever read TWO values:
        dp[i+1][j]  -> the row BELOW   (next row of the table)
        dp[i][j+1]  -> the cell to the RIGHT in the SAME row
   So at any moment we only need:
        - the whole "row below"   (i.e. row i+1 already computed)
        - the part of the "current row" (i) that is already computed

 ONE ARRAY IS ENOUGH  (classic 1-D DP for grids):
   dp[] is reused for every row:
        dp[j]     -> on ENTRY it still holds the value of cell (i+1, j)
                     (written during the previous row's pass)
                     and after we finish cell (i, j) we OVERWRITE it with
                     the value of cell (i, j), ready for row i-1.
        dp[j + 1] -> already overwritten in this pass, so it holds the value
                     of cell (i, j+1)  (the "right" neighbour)  ✔
   This works because we scan j from RIGHT to LEFT (n-1 -> 0), so dp[j+1]
   is refreshed before dp[j] is needed, and dp[j] (the "down" neighbour)
   is refreshed only after it has been read.

 WHAT HAPPENS AT THE LAST ROW (i = m-1):
   dp[] starts as all INT_MIN = "row m does not exist" -> down branch is
   guarded by `i + 1 < m`, so those INT_MIN entries are simply never used
   as a "down" value.

 TRANSITION (identical meaning to Version 3):
        best = INT_MIN
        if down exists : best = max(best, grid[i+1][j], dp[j])   // dp[j] = (i+1, j)
        if right exists: best = max(best, grid[i][j+1], dp[j+1]) // dp[j+1] = (i, j+1)
        dp[j] = best                      // store for the row above
        if best != INT_MIN: ans = max(ans, best - grid[i][j])

 COMPLEXITY: O(m*n) time, O(n) space (was O(m*n)).
================================================================================
*/
class Solution4 {
public:
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[j] = best value reachable from cell (current_row + 1, j)
        //         = "row below" while we are inside a row pass
        // INT_MIN = nothing reachable (fills in for the imaginary row m)
        vector<int> dp(n, INT_MIN);

        int ans = INT_MIN;

        // bottom-up row by row, right to left inside each row
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                int best = INT_MIN;   // best VALUE reachable from (i, j)

                // Down: cell below (grid) + best reachable from it (dp[j])
                //       dp[j] still holds row i+1 because it is not yet overwritten
                if (i + 1 < m) {
                    best = max(best, grid[i + 1][j]);
                    best = max(best, dp[j]);
                }

                // Right: cell beside (grid) + best reachable from it (dp[j+1])
                //        dp[j+1] was already updated in this pass -> it is cell (i, j+1)
                if (j + 1 < n) {
                    best = max(best, grid[i][j + 1]);
                    best = max(best, dp[j + 1]);
                }

                dp[j] = best;   // overwrite: dp[j] now = value for cell (i, j)

                if (best != INT_MIN) {
                    ans = max(ans, best - grid[i][j]);
                }
            }
        }

        return ans;
    }
};



int main(){
    return 0;
}