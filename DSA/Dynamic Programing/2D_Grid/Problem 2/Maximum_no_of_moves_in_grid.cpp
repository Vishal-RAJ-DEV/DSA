#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
 VERSION 1 : TOP-DOWN MEMOIZATION (Recursion + dp table) - "explicit 3 branches"
================================================================================
 PROBLEM (LeetCode 2617 - Minimum Number of Moves to Reach Target with
          ... here: Maximum number of moves in grid):
   - You start at ANY cell of the FIRST column (c == 0).
   - One move = go from (r, c) to ONE of the three next-column cells:
        (r-1, c+1)  upper-right
        (r,   c+1)  right
        (r+1, c+1)  lower-right
   - A move is allowed ONLY if the target cell value > current cell value.
   - Return the MAXIMUM number of moves you can make.

 IDEA:
   Let solve(r, c) = max moves you can make STARTING from cell (r, c).
   Base case : if we are already in the last column (c == n-1) no further
               move is possible -> return 0.
   Transition: try all 3 allowed directions; if that neighbour is inside the
               grid AND its value is strictly greater, then that move gives
               1 + solve(neighbour). Take the maximum over all valid moves.
               If NO move is valid -> ans stays 0 (we are stuck).

 WHY MEMOIZATION WORKS:
   State = (r, c). There are m*n states, each computed once -> O(m*n) time.
   dp[r][c] stores the answer for state (r, c); -1 means "not computed yet".

 FINAL ANSWER:
   We may start from any row of column 0, so answer = max over r of solve(r,0).
================================================================================
*/
class Solution1 {
public:
    int m, n;                  // rows and columns of the grid
    vector<vector<int>> dp;    // dp[r][c] = max moves from (r, c), -1 = unvisited

    // Returns max moves starting from cell (r, c)
    int solve(vector<vector<int>>& grid, int r, int c) {
        // BASE CASE: last column -> cannot move further -> 0 moves
        if (c == n - 1)
            return 0;

        // MEMO: if this state was already solved, reuse it (overlapping subproblems)
        if (dp[r][c] != -1)
            return dp[r][c];

        int ans = 0;  // if no valid move exists, we are stuck -> 0

        // 1) UPPER-RIGHT move: (r-1, c+1)
        //    must stay inside rows (r-1 >= 0) and value must strictly increase
        if (r - 1 >= 0 && grid[r - 1][c + 1] > grid[r][c])
            ans = max(ans, 1 + solve(grid, r - 1, c + 1));

        // 2) RIGHT move: (r, c+1)  (always inside grid, only value check needed)
        if (grid[r][c + 1] > grid[r][c])
            ans = max(ans, 1 + solve(grid, r, c + 1));

        // 3) LOWER-RIGHT move: (r+1, c+1)
        //    must stay inside rows (r+1 < m) and value must strictly increase
        if (r + 1 < m && grid[r + 1][c + 1] > grid[r][c])
            ans = max(ans, 1 + solve(grid, r + 1, c + 1));

        // STORE the result for this state before returning (memoization)
        return dp[r][c] = ans;
    }

    int maxMoves(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        // initialize whole dp table with -1 = "not computed yet"
        dp.assign(m, vector<int>(n, -1));

        int ans = 0;

        // we may START from any cell of the FIRST column -> try all rows
        for (int r = 0; r < m; r++)
            ans = max(ans, solve(grid, r, 0));

        return ans;
    }
};

/*
================================================================================
 VERSION 2 : BOTTOM-UP 2D DP (Iterative) - "explicit 3 branches"
================================================================================
 Same 3 transitions as Version 1, but written as an ITERATIVE table fill
 instead of recursion + memo.

 KEY POINT - ORDER OF FILLING:
   dp[r][c] depends only on cells of the NEXT column (c+1), i.e. on
   dp[r-1][c+1], dp[r][c+1], dp[r+1][c+1].
   So we must fill the table from the LAST column towards the FIRST column:
        c = n-2, n-3, ... , 0
   (column n-1 is already 0 = base case, since dp is initialized with 0)

 For every cell we try the same 3 moves:
        upper-right, right, lower-right
   and take 1 + dp[neighbour] whenever the neighbour value is strictly greater.

 FINAL ANSWER = max of dp[r][0] over all rows (any starting cell of col 0).

 Complexity: O(m*n) time, O(m*n) extra space.
================================================================================
*/
class Solution2 {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[r][c] = max moves starting from (r, c)
        // initialized to 0 -> automatically handles the "last column = 0" base case
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // fill from second-last column back to the first column,
        // because dp[r][c] needs values of column c+1 (already computed)
        for (int c = n - 2; c >= 0; c--) {
            for (int r = 0; r < m; r++) {

                // Upper-right: (r-1, c+1)
                if (r - 1 >= 0 &&
                    grid[r - 1][c + 1] > grid[r][c]) {
                    dp[r][c] = max(dp[r][c],
                                   1 + dp[r - 1][c + 1]);
                }

                // Right: (r, c+1)
                if (grid[r][c + 1] > grid[r][c]) {
                    dp[r][c] = max(dp[r][c],
                                   1 + dp[r][c + 1]);
                }

                // Lower-right: (r+1, c+1)
                if (r + 1 < m &&
                    grid[r + 1][c + 1] > grid[r][c]) {
                    dp[r][c] = max(dp[r][c],
                                   1 + dp[r + 1][c + 1]);
                }
            }
        }

        int ans = 0;

        // answer = best among all possible starting cells of column 0
        for (int r = 0; r < m; r++)
            ans = max(ans, dp[r][0]);

        return ans;
    }
};

/*
================================================================================
 VERSION 3 : BOTTOM-UP DP + SPACE OPTIMIZATION (1-D rolling arrays)
             - "explicit 3 branches", same logic as Version 2
================================================================================
 OBSERVATION:
   When we are filling column c, we ONLY read from column c+1.
   Column c+1 is never modified again after that, and no other column is read.
   => The whole 2-D dp table is not needed; only TWO columns are needed at
      any moment:
            next[] -> answers for column c+1   (already computed)
            curr[] -> answers for column c     (being computed now)

 HOW THE LOOP WORKS:
   1) fill(curr, 0)            -> start column c with all zeros (base value)
   2) compute curr[r] from next[r-1], next[r], next[r+1]  (the 3 branches)
   3) next = curr              -> move one column to the left, curr becomes
                                  the "next" column for the next iteration

 After the loop finishes, c = 0 has been processed, so next[] holds the
 answers for the FIRST column, and the answer is max over next[r].

 Complexity: O(m*n) time, O(m) extra space (instead of O(m*n)).
================================================================================
*/
class Solution3 {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // next[r] = max moves starting from cell (r, c+1)
        // curr[r] = max moves starting from cell (r, c)
        vector<int> next(m, 0);
        vector<int> curr(m, 0);

        // process columns from right to left (second-last -> first)
        for (int c = n - 2; c >= 0; c--) {

            // reset current column (0 = base case for cells where no move works)
            fill(curr.begin(), curr.end(), 0);

            for (int r = 0; r < m; r++) {

                // Upper-right: uses next[r-1]  (= dp[r-1][c+1])
                if (r - 1 >= 0 &&
                    grid[r - 1][c + 1] > grid[r][c]) {
                    curr[r] = max(curr[r],
                                  1 + next[r - 1]);
                }

                // Right: uses next[r]  (= dp[r][c+1])
                if (grid[r][c + 1] > grid[r][c]) {
                    curr[r] = max(curr[r],
                                  1 + next[r]);
                }

                // Lower-right: uses next[r+1]  (= dp[r+1][c+1])
                if (r + 1 < m &&
                    grid[r + 1][c + 1] > grid[r][c]) {
                    curr[r] = max(curr[r],
                                  1 + next[r + 1]);
                }
            }

            // shift: column c is now the "already computed" column for c-1
            next = curr;
        }

        int ans = 0;

        // next[] now represents column 0 -> best starting cell
        for (int r = 0; r < m; r++)
            ans = max(ans, next[r]);

        return ans;
    }
};



/*
================================================================================
 VERSION 4 : TOP-DOWN MEMOIZATION + DIRECTION ARRAY (loop over 3 moves)
             == "another way" to write Version 1
================================================================================
 The ONLY difference from Version 1:
   Version 1 writes the 3 moves as 3 separate `if` statements.
   Version 4 stores the 3 row-offsets in an array
                dr[] = { -1, 0, +1 }   (up, same row, down)
   and always moves to column c+1 (nc = c + 1), so ONE loop covers all
   3 possible next cells. The bounds check `nr >= 0 && nr < m` replaces the
   individual `r-1 >= 0` / `r+1 < m` checks.

 WHY THIS IS BETTER:
   - Less code, no repetition.
   - Easy to extend: to allow more directions just add entries to dr[].

 Rest is exactly Version 1:
   base case  : c == n-1  -> 0
   memo       : dp[r][c] != -1 -> return stored value
   transition : max over all valid neighbours of (1 + solve(neighbour))
   answer     : max over solve(r, 0) for every row r.
================================================================================
*/
class Solution4 {
public:
    int m, n;
    vector<vector<int>> dp;

    // Returns max moves starting from cell (r, c)
    int solve(vector<vector<int>>& grid, int r, int c) {
        // BASE CASE: already in last column -> no move possible
        if (c == n - 1)
            return 0;

        // MEMO: state already computed
        if (dp[r][c] != -1)
            return dp[r][c];

        int ans = 0;  // 0 = stuck if no valid move exists

        // row offsets for the 3 allowed moves: upper-right, right, lower-right
        // column offset is always +1 (we always move to the next column)
        int dr[] = {-1, 0, 1};

        // try the 3 directions using the loop instead of 3 separate ifs
        for (int i = 0; i < 3; i++) {
            int nr = r + dr[i];   // candidate row    (r-1, r, r+1)
            int nc = c + 1;       // candidate column (always next column)

            // valid if inside the grid AND value strictly increases
            if (nr >= 0 && nr < m &&
                grid[nr][nc] > grid[r][c]) {

                ans = max(ans, 1 + solve(grid, nr, nc));
            }
        }

        // memoize and return
        return dp[r][c] = ans;
    }

    int maxMoves(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        dp.assign(m, vector<int>(n, -1));   // -1 = not computed yet

        int ans = 0;

        // start can be any cell of the first column
        for (int r = 0; r < m; r++) {
            ans = max(ans, solve(grid, r, 0));
        }

        return ans;
    }
};



/*
================================================================================
 VERSION 5 : BOTTOM-UP 2D DP + DIRECTION ARRAY (loop over 3 moves)
             == "another way" to write Version 2
================================================================================
 Combination of Version 2 (iterative 2-D table) and Version 4 (dr[] loop):
   - Same right-to-left column order (c = n-2 ... 0), because dp[r][c] only
     needs column c+1.
   - dp initialised with 0  -> last column automatically = base case 0.
   - Instead of 3 separate `if` blocks, one loop over dr[] = {-1, 0, 1}
     generates the three candidates (nr, c+1); the combined check
     `nr in range && grid[nr][nc] > grid[r][c]` does both the boundary
     check and the strictly-greater check.
   - dp[r][c] = best over all valid moves, or 0 if none is valid.
   - Final answer = max of dp[r][0] over all starting rows.

 Complexity: O(m*n) time, O(m*n) space (same as Version 2).
================================================================================
*/
class Solution5 {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[r][c] = max moves starting from (r, c); 0 = base case
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // row offsets: -1 = upper-right, 0 = right, +1 = lower-right
        int dr[] = {-1, 0, 1};

        // Last column = 0 moves
        // So start from second-last column
        for (int c = n - 2; c >= 0; c--) {

            for (int r = 0; r < m; r++) {

                int ans = 0;   // no valid move yet

                // try all 3 allowed directions in one loop
                for (int i = 0; i < 3; i++) {

                    int nr = r + dr[i];   // candidate row
                    int nc = c + 1;       // candidate column (next column)

                    // row must be inside grid AND value must increase
                    if (nr >= 0 && nr < m &&
                        grid[nr][nc] > grid[r][c]) {

                        ans = max(ans, 1 + dp[nr][nc]);
                    }
                }

                dp[r][c] = ans;
            }
        }

        int ans = 0;

        // Can start from any cell in first column
        for (int r = 0; r < m; r++) {
            ans = max(ans, dp[r][0]);
        }

        return ans;
    }
};



int main(){
    return 0;
}