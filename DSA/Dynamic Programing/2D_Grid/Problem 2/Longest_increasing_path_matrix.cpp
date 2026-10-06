#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
 APPROACH 1 : DFS + MEMOIZATION  (top-down DP)   LeetCode 329
================================================================================
 PROBLEM:
   Matrix of integers. A path moves only UP / DOWN / LEFT / RIGHT (4-neighbour)
   and every step must go to a STRICTLY GREATER value.
   Return the length (number of cells) of the longest such path.

 WHY RECURSION TERMINATES (important intuition):
   Values strictly increase along a path, so you can never come back to a
   cell you already visited -> there are NO cycles -> the DFS always ends
   (at a cell that has no bigger neighbour).

 DEFINITION / RECURRENCE:
   Let dfs(r, c) = length of the longest increasing path that STARTS at (r, c)
                   and includes (r, c) itself.
        base value = 1  (the path consisting of only this cell)
   Transition:
        dfs(r, c) = 1 + max( dfs(neighbour) )   over all 4-neighbours with
                                                 matrix[neighbour] > matrix[r][c]
        if no bigger neighbour exists, the max loop never runs and the answer
        stays 1 (path of just this single cell).

 HOW THE CODE WORKS:
   dr[] / dc[] = the 4 direction offsets (-1,0) (1,0) (0,-1) (0,1),
                 so one loop replaces 4 copy-pasted if-blocks.
   For each neighbour: check it is inside the grid AND strictly greater,
   then take 1 + dfs(neighbour) and keep the maximum.
   dp[r][c] caches the result; -1 = "not computed yet", so every cell is
   solved only once (this is what turns exponential recursion into O(m*n)).

 WHY MEMOIZATION IS LEGAL HERE:
   The value of dfs(r, c) depends only on the cells reachable FROM (r, c),
   never on how we got here → the subproblem is well-defined and reusable.

 FINAL ANSWER:
   A longest path can start at ANY cell, so try every (i, j) and keep the
   global maximum of dfs(i, j).

 COMPLEXITY: O(m*n) time (m*n states x 4 neighbours), O(m*n) extra space.
================================================================================
*/
class Solution1 {
public:
    int m, n;

    // returns the length of the longest increasing path STARTING at (r, c)
    int dfs(int r, int c, vector<vector<int>>& matrix, vector<vector<int>>& dp) {

        // MEMO: cell already solved -> reuse the stored length
        if (dp[r][c] != -1)
            return dp[r][c];

        int ans = 1;   // the path that contains only this cell

        // 4 directions: up, down, left, right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int k = 0; k < 4; k++) {

            int nr = r + dr[k];
            int nc = c + dc[k];

            // neighbour must be inside the matrix AND strictly greater
            // (strictly greater also guarantees no cycles)
            if (nr >= 0 && nr < m &&
                nc >= 0 && nc < n &&
                matrix[nr][nc] > matrix[r][c]) {

                // best path from here = 1 (this cell) + best path from neighbour
                ans = max(ans, 1 + dfs(nr, nc, matrix, dp));
            }
        }

        // store and return the answer for this cell
        return dp[r][c] = ans;
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {

        m = matrix.size();
        n = matrix[0].size();

        vector<vector<int>> dp(m, vector<int>(n, -1));   // -1 = uncomputed

        int ans = 0;

        // the path may start at any cell -> try all of them
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans = max(ans, dfs(i, j, matrix, dp));
            }
        }

        return ans;
    }
};

/*
================================================================================
 APPROACH 2 : SORT CELLS BY VALUE  (bottom-up DP, no recursion at all)
================================================================================
 KEY IDEA - CHANGE THE POINT OF VIEW:
   Approach 1 asked: "how long a path can I build going FORWARD from here?"
   Approach 2 asks : "how long a path can END at this cell?"
        dp[r][c] = length of the longest increasing path that ENDS at (r, c)
                 = 1 + max( dp[smaller neighbour] ),   at least 1 (itself)

 WHY PROCESSING IN SORTED ORDER MAKES IT CORRECT:
   A path that ends at (r, c) can only come from neighbours with a SMALLER
   value. If we visit all cells from the SMALLEST value to the LARGEST value,
   then when we reach (r, c) every smaller neighbour already has its FINAL
   dp value → dp[r][c] is computed correctly in one shot.
   (Cells with EQUAL value are never allowed as predecessors because the
    path needs strictly increasing values, so their relative order in the
    sort does not matter.)

 DATA STRUCTURE:
   cells = list of tuples (value, row, col) for every cell;
   sort(cells) sorts by value first (tuple comparison) → ascending order.

 HOW THE LOOP WORKS:
   For the current (smallest-not-yet-processed) cell (r, c):
      dp[r][c] is already final (all its predecessors were processed before).
      Now PUSH the result forward to its 4 bigger neighbours:
            dp[nr][nc] = max(dp[nr][nc], dp[r][c] + 1)
      i.e. "a path ending here can be extended by one more cell there".
   Answer = maximum dp value seen (also tracked while looping).

 NOTE ON DIRECTION OF THE UPDATE:
   We UPDATE THE BIGGER NEIGHBOUR (forward propagation) instead of reading
   from smaller neighbours, precisely because going upwards in value all
   required information is already available.

 COMPLEXITY: O(m*n log(m*n)) for the sort + O(m*n) for the scan,
             O(m*n) space. Iterative → no recursion / stack overflow risk.
================================================================================
*/
class Solution2 {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {

        int m = matrix.size();
        int n = matrix[0].size();

        // (value, row, col) for every cell -> will be sorted by value
        vector<tuple<int, int, int>> cells;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cells.push_back({matrix[i][j], i, j});
            }
        }

        // ascending by value: smallest cells first (their dp is trivially 1)
        sort(cells.begin(), cells.end());

        // dp[r][c] = length of the longest increasing path ENDING at (r, c)
        vector<vector<int>> dp(m, vector<int>(n, 1));

        int ans = 1;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (auto it : cells) {
            // get<0>(it) = cell value (only used as the sort key),
            // get<1>/get<2> = row / column of the cell
            int r = get<1>(it);
            int c = get<2>(it);

            // dp[r][c] is FINAL here (all smaller cells were processed earlier)
            // extend the path by one cell into every strictly bigger neighbour
            for (int k = 0; k < 4; k++) {

                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < m &&
                    nc >= 0 && nc < n &&
                    matrix[nr][nc] > matrix[r][c]) {

                    dp[nr][nc] = max(dp[nr][nc], dp[r][c] + 1);
                }
            }

            // final value of this cell can only contribute to the answer now
            ans = max(ans, dp[r][c]);
        }

        return ans;
    }
};

/*
================================================================================
 APPROACH 3 : TOPOLOGICAL SORT (Kahn's algorithm / BFS on the DAG levels)
================================================================================
 GRAPH MODEL:
   Make every cell a NODE.
   Draw a DIRECTED EDGE  (r, c) -> (nr, nc)  when the neighbour is inside
   the grid and matrix[nr][nc] > matrix[r][c]  (a legal path step).
   Because values strictly increase, this graph is a DAG (no cycles).

   In this graph the answer is simply the length of the LONGEST PATH,
   and a classic way to get it is level-by-level topological BFS.

 INDEGREE:
   indegree[r][c] = number of NEIGHBOURS THAT ARE STRICTLY SMALLER
                  = number of edges coming INTO (r, c)
                  = how many predecessors must be "finished" before (r, c)
                    can be placed on its path layer.
   indegree == 0  →  local minimum  →  it can START a path (layer 1).

 HOW THE BFS LEVELS ENCODE THE ANSWER:
   The queue initially holds ALL indegree-0 cells = all local minima.
        length = 1 after we process them   (a path of 1 cell)
   Processing ONE whole queue-level at a time:
        - remove those cells (they are "locked" as the current layer),
        - for every bigger neighbour decrement its indegree,
        - whenever an indegree reaches 0 the neighbour becomes a member of
          the NEXT layer (all its smaller predecessors are done).
   Each level = one more cell on the path → length++ per level.
   When the queue empties, the number of levels processed = length of the
   longest increasing path.

   Why is the level of a cell = longest path ending there? Because a cell
   enters the queue only after ALL smaller neighbours have been processed,
   i.e. it waits for the slowest (longest) predecessor chain → its level is
   1 + max(level of predecessors), which is exactly the recurrence.

 IMPLEMENTATION DETAILS:
   - The outer `while (!q.empty())` processes one layer; `size = q.size()`
     snapshots how many cells are in that layer.
   - `length++` happens once per layer, BEFORE draining the layer.
   - The edge direction in the indegree loop is reversed (we count smaller
     neighbours) while the BFS follows forward edges (bigger neighbours).

 COMPLEXITY: O(m*n) time (each cell/edge looked at a constant number of
             times), O(m*n) space. Fully iterative.
================================================================================
*/
class Solution3 {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {

        int m = matrix.size();
        int n = matrix[0].size();

        // indegree[r][c] = how many neighbours are STRICTLY SMALLER than (r, c)
        vector<vector<int>> indegree(m, vector<int>(n, 0));

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // Calculate indegree (count incoming edges = smaller neighbours)
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {

                for (int k = 0; k < 4; k++) {

                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr >= 0 && nr < m &&
                        nc >= 0 && nc < n &&
                        matrix[nr][nc] < matrix[r][c]) {

                        indegree[r][c]++;
                    }
                }
            }
        }

        queue<pair<int, int>> q;

        // Cells having indegree 0 = local minima = start of every path (layer 1)
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {

                if (indegree[r][c] == 0) {
                    q.push({r, c});
                }
            }
        }

        int length = 0;

        while (!q.empty()) {

            int size = q.size();

            // One BFS level = one path length
            length++;

            // drain the whole current layer
            while (size--) {

                auto it = q.front();
                int r = it.first;
                int c = it.second;
                
                q.pop();

                // walk the FORWARD edges: to every strictly bigger neighbour
                for (int k = 0; k < 4; k++) {

                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr >= 0 && nr < m &&
                        nc >= 0 && nc < n &&
                        matrix[nr][nc] > matrix[r][c]) {

                        // one predecessor of (nr, nc) has been processed
                        indegree[nr][nc]--;

                        // all predecessors done -> it belongs to the next layer
                        if (indegree[nr][nc] == 0) {
                            q.push({nr, nc});
                        }
                    }
                }
            }
        }

        // number of processed layers = length of the longest increasing path
        return length;
    }
};



int main(){
    return 0;
}