/******************************************************************************
 * FILE      : cherry_pick_up.cpp
 * PROBLEM  : LeetCode 741 — Cherry Pickup (Hard)  [ 3D DP / Grid DP ]
 *
 * ============================ PROBLEM STATEMENT ============================
 * We are given an n x n grid.
 *   • grid[i][j] = number of cherries present in cell (i, j).
 *   • grid[i][j] = -1  -> that cell is a THORN (blocked / cannot be entered).
 * We must start at the top-left corner (0, 0) and reach the bottom-right
 * corner (n-1, n-1).  After reaching there we come BACK again to (0, 0)
 * (i.e. two trips: forward trip + return trip).
 * Collect the maximum possible cherries on the way.
 *
 * =========================== WHY "3D" DP ? =================================
 * A direct way is: go (0,0) -> (n-1,n-1) -> (0,0).  That would need the
 * positions of 2 travellers = 4 coordinates (r1,c1,r2,c2) = 4D DP = too slow.
 *
 * KEY OBSERVATION 1 (remove one trip):
 *   Going there and coming back is the SAME as sending TWO people together
 *   from (0,0) to (n-1,n-1).  Both people make the same kind of moves
 *   (only Down / Right), so together they cover exactly the same cells as
 *   forward + backward trip.
 *
 * KEY OBSERVATION 2 (remove 4th coordinate):
 *   Every path from (0,0) to (n-1,n-1) using only Down/Right moves takes
 *   exactly (2n-2) steps.  So for BOTH travellers at any moment:
 *          r1 + c1 == r2 + c2        (same number of steps taken)
 *   =>    c2 = r1 + c1 - r2
 *   Therefore we only need to store (r1, c1, r2)  ->  3 dimensions.
 *   The 4th coordinate c2 is always DERIVED from the other three.
 *
 * ============================ STATE DEFINITION =============================
 *   dp[r1][c1][r2] = maximum cherries collectable when
 *                    person-1 is at cell (r1, c1)  and
 *                    person-2 is at cell (r2, c2),  where c2 = r1+c1-r2,
 *                    and both of them continue to move to (n-1, n-1).
 *
 * ============================ TRANSITION ===================================
 * From any state each person has 2 choices -> 4 combined choices:
 *   1) person-1 goes Right   , person-2 goes Right  -> (r1, c1+1, r2)
 *   2) person-1 goes Right   , person-2 goes Down   -> (r1, c1+1, r2+1)
 *   3) person-1 goes Down    , person-2 goes Right  -> (r1+1, c1, r2)
 *   4) person-1 goes Down    , person-2 goes Down   -> (r1+1, c1, r2+1)
 * Take the MAX of those 4 recursive answers = "best".
 *
 *   Cherries gained in the CURRENT step:
 *        cherries = grid[r1][c1]
 *        if both persons are standing on DIFFERENT cells -> add grid[r2][c2]
 *        if both are on the SAME cell -> count it only ONCE.
 *
 *   dp[r1][c1][r2] = cherries + best
 *
 * ========================== BASE / INVALID CASES ===========================
 *   • Any coordinate out of the grid            -> invalid path, return -1
 *   • Cell contains -1 (thorn)                  -> invalid path, return -1
 *   • Person-1 reaches (n-1, n-1)               -> stop, return grid value
 *     (because then person-2 has also reached (n-1,n-1) automatically)
 *
 * =========================== SENTINEL VALUES ==============================
 *   Top-down version  : dp filled with -2  = "not computed yet"
 *                       result      -1     = "this state has no valid path"
 *   Bottom-up version : dp filled with -1  = "no valid path / not computed"
 *
 * ========================== TIME & SPACE ===================================
 *   States = O(n^3)  (r1, c1, r2 each takes n values, c2 is derived)
 *   Each state does O(1) work  ->  Time  = O(n^3)
 *   Memo table of size n x n x n -> Space = O(n^3)
 *
 * ============================ TWO SOLUTIONS ================================
 *   1) Solution (first class)  : Top-Down  MEMOIZED RECURSION  (clean & easy)
 *   2) Solution (second class) : Bottom-Up ITERATIVE DP        (no recursion)
 *
 * NOTE: Both classes are named "Solution" — only ONE of them can be used in
 *       a single compilation unit.  Rename/comment one out before compiling.
 *****************************************************************************/

#include <iostream>       // Input / output stream library (used by main())
#include <bits/stdc++.h>  // Convenience header: pulls in ALL standard libraries
                          // (vector, algorithm, max-initializer-list, etc.)
using namespace std;      // So we can write vector / cout without "std::" prefix


/*==========================================================================
 *  SOLUTION 1 : TOP-DOWN MEMOIZED RECURSION
 *==========================================================================*/
class Solution {
public:
    int n;                                     // Size of the grid (n x n).
                                                // Stored as a member so every
                                                // recursive call can use it
                                                // without passing it again.

    // Memoization table: dp[r1][c1][r2] = best answer from that state.
    // Dimensions: n (row of p1) x n (col of p1) x n (row of p2).
    // c2 is NOT stored because c2 = r1 + c1 - r2 (derived).
    vector<vector<vector<int>>> dp;

    // ---------------------------------------------------------------------
    // solve(r1, c1, r2, grid)
    //   r1, c1 -> current position of person 1
    //   r2     -> current row of person 2 (its column c2 is computed below)
    // Returns the MAXIMUM cherries both persons can collect from this state
    // until they both reach (n-1, n-1).  Returns -1 if no valid path exists.
    // ---------------------------------------------------------------------
    int solve(int r1, int c1, int r2, vector<vector<int>>& grid) {

        // STEP 1: Recover the 4th coordinate (person-2's column).
        // Because both travelled the same number of steps:
        //     r1 + c1 == r2 + c2   =>   c2 = r1 + c1 - r2
        int c2 = r1 + c1 - r2;

        // STEP 2: Boundary check — if any of the 4 coordinates goes outside
        // the grid, this direction is impossible. Return -1 = "invalid path".
        if (r1 >= n || c1 >= n || r2 >= n || c2 >= n)
            return -1;

        // STEP 3: Thorn check — if EITHER person steps on a -1 cell, the
        // whole path is illegal. Return -1 = "invalid path".
        if (grid[r1][c1] == -1 || grid[r2][c2] == -1)
            return -1;

        // STEP 4: Terminal / base case — person-1 reached bottom-right.
        // Since r1 + c1 = 2n-2 at that moment, person-2 is forced to be at
        // (n-1, n-1) too (only cell whose row+col = 2n-2). So we simply
        // return the cherries of the destination cell. No further moves.
        if (r1 == n - 1 && c1 == n - 1)
            return grid[r1][c1];

        // STEP 5: MEMO HIT — if this state was already solved before,
        // return the stored value instead of recomputing (this is what
        // converts naive exponential recursion into O(n^3)).
        // -2 is our "not computed yet" marker.
        if (dp[r1][c1][r2] != -2)
            return dp[r1][c1][r2];

        // STEP 6: RECURRENCE — try all 4 combinations of moves
        //   (p1 Right/Down) x (p2 Right/Down) and take the best.
        //   a) p1 Right + p2 Right  -> new state (r1, c1+1, r2)
        //   b) p1 Right + p2 Down   -> new state (r1, c1+1, r2+1)
        //   c) p1 Down  + p2 Right  -> new state (r1+1, c1,   r2)
        //   d) p1 Down  + p2 Down   -> new state (r1+1, c1,   r2+1)
        // max({ ... }) = maximum of an initializer list (needs <algorithm>).
        int best = max({solve(r1, c1 + 1, r2, grid), solve(r1, c1 + 1, r2 + 1, grid),
                        solve(r1 + 1, c1, r2, grid), solve(r1 + 1, c1, r2 + 1, grid)});

        // STEP 7: If EVERY one of the 4 next states is invalid (-1), then
        // there is no way to finish from here. Store -1 in memo and return it
        // so the parent call also knows this branch is dead.
        if (best == -1)
            return dp[r1][c1][r2] = -1;

        // STEP 8: Count cherries picked at the CURRENT cell(s).
        // Person-1 always picks grid[r1][c1].
        int cherries = grid[r1][c1];

        // If person-2 stands on a DIFFERENT cell, add its cherries too.
        // If both stand on the SAME cell, we must NOT double count it —
        // a cherry can be collected only once.
        if (r1 != r2 || c1 != c2)
            cherries += grid[r2][c2];

        // STEP 9: Store the answer in the memo table (this line both
        // caches the value and returns it) = current cherries + best of
        // all future moves.
        return dp[r1][c1][r2] = cherries + best;
    }

    // ---------------------------------------------------------------------
    // cherryPickup(grid) : public entry point called by the judge.
    // ---------------------------------------------------------------------
    int cherryPickup(vector<vector<int>>& grid) {
        n = grid.size();   // Grid is n x n, so size() gives n (rows = cols).

        // Allocate the 3D memo table of size n x n x n and fill it with -2
        // ("not computed yet").  assign() creates a fresh table each call so
        // multiple test cases don't share stale values.
        dp.assign(n, vector<vector<int>>(
            n, vector<int>(n, -2)
        ));

        // Start both persons together at (0, 0)  ->  state (r1=0, c1=0, r2=0).
        // max(0, ...) is a safety net: if NO valid path exists (answer -1),
        // we report 0 cherries instead of a negative number.
        return max(0, solve(0, 0, 0, grid));
    }
};


/*==========================================================================
 *  SOLUTION 2 : BOTTOM-UP ITERATIVE DP  (same logic, no recursion)
 *  States are filled from the DESTINATION backwards to the START.
 *==========================================================================*/
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();   // Grid dimension (n x n).

        // Create the 3D DP table n x n x n, initialised to -1.
        // Here -1 means "state not reachable yet / no valid path".
        // (Indices stored: dp[r1][c1][r2] — same meaning as before.)
        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(n, vector<int>(n, -1))
        );

        // BASE CASE of the bottom-up table:
        // Both persons at the destination (n-1, n-1) => collect its cherries.
        // This is the state every other state will eventually build upon.
        dp[n - 1][n - 1][n - 1] = grid[n - 1][n - 1];

        // ----- FILL THE TABLE FROM THE END TOWARDS THE START -----
        // We iterate rows/cols in DECREASING order because a state
        // (r1,c1,r2) only depends on states with LARGER indices
        // (we move Down/Right => indices increase). So those "future"
        // states must already be computed → iterate backwards.
        for (int r1 = n - 1; r1 >= 0; r1--) {          // person-1 row
            for (int c1 = n - 1; c1 >= 0; c1--) {      // person-1 column
                for (int r2 = n - 1; r2 >= 0; r2--) {  // person-2 row

                    // Derive person-2's column from the step-count invariant.
                    int c2 = r1 + c1 - r2;

                    // Skip states where person-2 would fall outside the grid
                    // (negative column or column >= n) — impossible position.
                    if (c2 < 0 || c2 >= n) continue;

                    // Skip states where either person stands on a thorn (-1).
                    if (grid[r1][c1] == -1 || grid[r2][c2] == -1) continue;

                    // The destination state (n-1, n-1) was already filled
                    // above as the base case — do not overwrite it.
                    if (r1 == n - 1 && c1 == n - 1) continue;

                    // "best" = best cherries obtainable by the NEXT move.
                    // -1 means "no valid next state found (yet)".
                    int best = -1;

                    // Move combination 1: p1 Right, p2 Right.
                    // Guard with boundary check so we never read outside dp.
                    if (c1 + 1 < n)
                        best = max(best, dp[r1][c1 + 1][r2]);

                    // Move combination 2: p1 Right, p2 Down.
                    // (c1+1 must be valid for p1, r2+1 must be valid for p2)
                    if (c1 + 1 < n && r2 + 1 < n)
                        best = max(best, dp[r1][c1 + 1][r2 + 1]);

                    // Move combination 3: p1 Down, p2 Right.
                    if (r1 + 1 < n)
                        best = max(best, dp[r1 + 1][c1][r2]);

                    // Move combination 4: p1 Down, p2 Down.
                    if (r1 + 1 < n && r2 + 1 < n)
                        best = max(best, dp[r1 + 1][c1][r2 + 1]);

                    // If none of the 4 next states is reachable, this state
                    // stays at its default -1 (dead end) → skip it.
                    if (best == -1) continue;

                    // Collect cherries at the CURRENT cells.
                    int cherries = grid[r1][c1];

                    // Both persons on different cells → count both;
                    // same cell → count only once (no double counting).
                    if (r1 != r2 || c1 != c2)
                        cherries += grid[r2][c2];

                    // Final recurrence:
                    //   dp[current] = cherries now + best from next step
                    dp[r1][c1][r2] = cherries + best;
                }
            }
        }

        // Start state is (r1=0, c1=0, r2=0). max(0, ...) converts a "-1"
        // (no valid path at all) into 0 cherries.
        return max(0, dp[0][0][0]);
    }
};



int main(){
    return 0;   // Nothing to test here; both Solution classes contain the
                // actual algorithm. Keep main minimal (compilation sanity).
}
