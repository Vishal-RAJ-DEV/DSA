#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/******************************************************************************
 * PROBLEM: Minimum Path Cost in a Grid
 *
 * INPUT
 *   grid[n][m]        -> value written on each cell
 *   moveCost[a][b]    -> cost of moving from a cell whose VALUE is 'a'
 *                        to a cell whose VALUE is 'b' (only next row)
 *
 * RULES
 *   - Start from ANY cell of row 0, finish at ANY cell of row n-1.
 *   - From (i, j) you may go to ANY cell of row i+1 (straight down,
 *     diagonal, anywhere - column does not matter).
 *
 * TOTAL COST OF A PATH = sum of VALUES of all cells visited
 *                         + sum of moveCost for every move made
 *
 * NOTE: the value of the starting cell is counted, but we do NOT pay
 *       any moveCost for it (we did not "move" into it).
 *
 * ONE LINE INTUITION
 *   "From this cell, try every cell of the next row, pay (my value +
 *    move cost), then recursively take the cheapest rest of the trip.
 *    Whichever next cell gives the smallest total, that is my answer."
 ******************************************************************************/

class Solution {
public:
    // ================= WAY 1 : TOP-DOWN (Recursion + Memoization) =================
    // solve(i, j) = cheapest total cost of the journey
    //               STARTING from cell (i, j) and ending in the last row.
    //
    // BASE CASE : if I am already in the last row, no move is left,
    //             so cost = only my own value = grid[i][j].
    //
    // TRANSITION: for every column k of the next row
    //             cost = grid[i][j]            (my value, counted once)
    //                    + moveCost[grid[i][j]][k]  (price to jump to value k)
    //                    + solve(i+1, k)       (cheapest rest of the trip)
    //             take the MINIMUM over all k.
    //
    // MEMO: dp[i][j] stores the answer for (i, j) so the same cell is
    //       never solved twice -> time goes from O(m^n) to O(n*m*m).
    int solve(int i, int j, vector<vector<int>>& grid,
              vector<vector<int>>& moveCost, vector<vector<int>>& dp) {

        int n = grid.size();
        int m = grid[0].size();

        // Last row
        if(i == n - 1)
            return grid[i][j];

        if(dp[i][j] != -1)
            return dp[i][j];

        int ans = INT_MAX;

        for(int k = 0; k < m; k++) {
            int cost = moveCost[grid[i][j]][k];

            ans = min(ans, grid[i][j] + cost +
                           solve(i + 1, k, grid, moveCost, dp));
        }

        return dp[i][j] = ans;
    }

    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int n = grid.size();
        int m = grid[0].size();

        // -1 means "this cell is not solved yet"
        vector<vector<int>> dp(n, vector<int>(m, -1));

        // We are allowed to start from any column of row 0,
        // so try all of them and keep the cheapest start.
        int ans = INT_MAX;

        for(int j = 0; j < m; j++) {
            ans = min(ans, solve(0, j, grid, moveCost, dp));
        }

        return ans;
    }
};



// ================= WAY 2 : BOTTOM-UP, "PULL" style =================
// Same answer as WAY 1, but no recursion - we FILL the table row by row.
//
// dp[i][j] = cheapest cost to REACH cell (i, j) from the top row.
// (In WAY 1, dp meant "cheapest cost to GO DOWN from here" - opposite direction.)
//
// "PULL" = each cell ASKS the previous row:
//   dp[i][j] = grid[i][j] + min over k of ( dp[i-1][k] + moveCost[grid[i-1][k]][j] )
//              ^^^^^^^^^^ value of the cell I landed on
//   dp[i-1][k]            cost to reach that cell above me
//   moveCost[...][j]      price of the jump from value grid[i-1][k] to value grid[i][j]
//
// Start row: dp[0][j] = grid[0][j]  (start cost = own value only).
// Answer   : min of the last row.
class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int n = grid.size();
        int m = grid[0].size();

        // start with the grid itself = row 0 is already correct
        vector<vector<int>> dp = grid;

        for(int i = 1; i < n; i++) {
            for(int j = 0; j < m; j++) {

                int minval = INT_MAX;

                // ask every cell of the previous row: "can YOU give me the cheapest way?"
                for(int k = 0; k < m; k++) {
                    int val = grid[i-1][k];
                    int cost = moveCost[val][j];

                    minval = min(minval, dp[i-1][k] + cost);
                }

                dp[i][j] = grid[i][j] + minval;
            }
        }

        int ans = INT_MAX;

        for(int j = 0; j < m; j++) {
            ans = min(ans, dp[n-1][j]);
        }

        return ans;
    }
};


// ================= WAY 3 : WAY 2 + SPACE OPTIMIZATION =================
// Logic is 100% identical to WAY 2 (still "PULL").
// Only change: the answer of row `i` depends ONLY on row `i-1`,
// so we never need the full n x m table.
//   prev  -> answer for the previous row
//   curr  -> answer for the current row
// Time  : O(n*m*m)   Space : O(m)  instead of O(n*m)
class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int n = grid.size();
        int m = grid[0].size();

        vector<int> prev = grid[0];   // row 0 = starting values

        for(int i = 1; i < n; i++) {
            vector<int> curr(m, INT_MAX);

            for(int j = 0; j < m; j++) {
                for(int k = 0; k < m; k++) {
                    int cost = moveCost[grid[i-1][k]][j];

                    curr[j] = min(curr[j],
                                  prev[k] + cost + grid[i][j]);
                }
            }

            prev = curr;              // move one row down
        }

        return *min_element(prev.begin(), prev.end());
    }
};


// ================= WAY 4 : BOTTOM-UP, "PUSH" style =================
// Written in the most readable way.
//
// HOW IS IT DIFFERENT FROM THE ABOVE WAYS?
// -----------------------------------------
// WAY 1  : Recursion + memo table.   Direction = top -> bottom, asks
//          "if I start here, how cheap can the rest be?"
// WAY 2/3: Iterative "PULL". Each cell ASKS its neighbours above:
//          "who from the previous row can reach me cheapest?"
//          dp[i][j] = my value + min( what the row above offers )
//
// WAY 4  : Iterative "PUSH". Each cell TELLS the row below:
//          "if you reach me, THIS is how cheaply you can reach each
//           of your cells."
//          dp[i+1][k] = min( dp[i+1][k] , dp[i][j] + jump cost + value of k )
//
// So:  PULL = read from the past (previous row)   -> "who can help me?"
//      PUSH = write into the future (next row)     -> "whom can I help?"
// Both give the exact same answer, PUSH just feels like Dijkstra/BFS
// where you relax the neighbours you can reach.
//
// dp[i][j] here also means "cheapest cost to REACH (i, j)" (same as WAY 2),
// so the two tables are equal - only the order of the loops differs.
class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {

        int n = grid.size();
        int m = grid[0].size();

        // 1e9 = "not reached yet / impossibly expensive"
        vector<vector<int>> dp(n, vector<int>(m, 1e9));

        // Step 1: starting row - we pay only the cell value, no move cost yet
        for (int j = 0; j < m; j++) {
            dp[0][j] = grid[0][j];
        }

        // Step 2: go row by row and PUSH the answer one row down
        for (int i = 0; i < n - 1; i++) {

            for (int j = 0; j < m; j++) {

                int choosen = grid[i][j];   // value sitting on the current cell

                // try to reach EVERY cell of the next row from here
                for (int k = 0; k < m; k++) {

                    int pick =
                        dp[i][j]              // cost to reach me
                        + moveCost[choosen][k]// price of the jump (value choosen -> value k)
                        + grid[i + 1][k];     // value of the cell I land on (paid once)

                    // keep the cheapest way found so far for that next cell
                    dp[i + 1][k] =
                        min(dp[i + 1][k], pick);
                }
            }
        }

        // Step 3: any cell of the last row can be the finishing point
        int ans = 1e9;

        for (int j = 0; j < m; j++) {
            ans = min(ans, dp[n - 1][j]);
        }

        return ans;
    }
};




int main(){
    return 0;
}