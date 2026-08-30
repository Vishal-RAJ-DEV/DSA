#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * PROBLEM: Count Battleships on a Board
 *
 * Given an m x n board where:
 *   'X' = part of a battleship
 *   '.' = empty water
 *
 * Rules:
 *   - Battleships are placed ONLY horizontally or vertically
 *     (never diagonally).
 *   - Battleships do NOT touch each other (guaranteed by input).
 *
 * GOAL: Count the number of battleships.
 *
 * EXAMPLE:
 *   board = [
 *     "X..X",
 *     "...X",
 *     "...X"
 *   ]
 *
 *   Battleship 1: (0,0)
 *   Battleship 2: (0,3) -> (1,3) -> (2,3)   (vertical)
 *   Answer: 2
 *
 * ========================================================================
 * APPROACH 1: Count Top-Left Heads (Optimal)
 * ========================================================================
 *
 * KEY OBSERVATION:
 *   Every battleship is a contiguous line of 'X's (horizontal or vertical).
 *   The TOP-LEFT cell of each ship is the ONLY cell that satisfies:
 *     - board[i][j] == 'X'
 *     - NO 'X' directly ABOVE it   (i == 0 or board[i-1][j] == '.')
 *     - NO 'X' directly to the LEFT (j == 0 or board[i][j-1] == '.')
 *
 *   Why?
 *     - For a horizontal ship: only the leftmost cell has no 'X' to the left.
 *     - For a vertical ship: only the topmost cell has no 'X' above.
 *     - The top-left cell of any ship satisfies BOTH conditions.
 *
 * VISUAL:
 *     .  X  .  X
 *     .  .  .  X
 *     .  .  .  X
 *
 *     Cell (0,1): X, no X above (i=0), no X to left (. at (0,0)) → HEAD ✓
 *     Cell (0,3): X, no X above (i=0), X to left (X at (0,2)?) → no, (0,2)='.'
 *                 Actually (0,3): X, no X above, no X left → HEAD ✓
 *     Cell (1,3): X, X above at (0,3) → NOT a head
 *     Cell (2,3): X, X above at (1,3) → NOT a head
 *
 *     Count = 2 battleships ✓
 *
 * TIME:  O(m * n) — single pass through the board
 * SPACE: O(1)    — only a counter, no extra data structures
 *
 * ========================================================================
 * APPROACH 2: DFS / Flood Fill (Connected Components)
 * ========================================================================
 *
 * This is the STANDARD graph approach:
 *   - Treat each 'X' as a node, connect adjacent 'X's (4-directional).
 *   - Count connected components — each component = one battleship.
 *   - Use DFS to explore and mark an entire component when found.
 *
 * WHY USE DFS?
 *   - General technique that works for ANY connected component problem.
 *   - Doesn't rely on the "battleship" structure (works even if ships
 *     could be L-shaped, T-shaped, etc.).
 *   - Good practice for flood-fill problems.
 *
 * TIME:  O(m * n) — each cell visited at most once
 * SPACE: O(m * n) — visited matrix + recursion stack (worst case O(m*n))
 *
 * ========================================================================
 * COMPARISON TABLE
 * ========================================================================
 *
 * +---------------------+--------------------+---------------------+
 * |     Metric          |  Approach 1        |  Approach 2         |
 * |                     |  (Top-Left Head)   |  (DFS Flood Fill)   |
 * +---------------------+--------------------+---------------------+
 * | Time Complexity     |  O(m * n)          |  O(m * n)           |
 * | Space Complexity    |  O(1)              |  O(m * n)           |
 * | Modifies Board?     |  No                |  No (uses visited)  |
 * | Extra Data Structure|  None              |  visited[][] matrix |
 * | Recursion?          |  No (iterative)    |  Yes (DFS stack)    |
 * | Generalizable?      |  No (ships only)   |  Yes (any shape)    |
 * | Best For            |  Interviews/optimal|  General graph probs |
 * +---------------------+--------------------+---------------------+
 */

// ========================================================================
// APPROACH 1: Count Top-Left Heads (Optimal — O(1) space)
// ========================================================================
class Solution1 {
public:
    int countBattleships(vector<vector<char>>& board) {

        int m = board.size();
        int n = board[0].size();

        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Skip water cells — not part of any battleship
                if (board[i][j] == '.') {
                    continue;
                }

                // If there's an 'X' directly ABOVE this cell,
                // this cell is part of a ship we already counted
                // (it's not the head) → skip.
                if (i > 0 && board[i - 1][j] == 'X') {
                    continue;
                }

                // If there's an 'X' directly to the LEFT of this cell,
                // this cell is part of a ship we already counted
                // (it's not the head) → skip.
                if (j > 0 && board[i][j - 1] == 'X') {
                    continue;
                }

                // This cell has no 'X' above and no 'X' to the left.
                // It MUST be the top-left head of a new battleship.
                count++;
            }
        }

        return count;
    }
};

// ========================================================================
// APPROACH 2: DFS Flood Fill (Connected Components)
// ========================================================================
class Solution2 {
public:

    // DFS: explore all 4 directions from cell (i, j) and mark
    // every cell in this battleship as visited.
    void dfs(int i, int j, vector<vector<char>>& board,
             vector<vector<bool>>& visited) {

        int m = board.size();
        int n = board[0].size();

        // Base case: out of bounds → stop
        if (i < 0 || i >= m || j < 0 || j >= n) {
            return;
        }

        // Base case: already visited or water cell → stop
        if (visited[i][j] || board[i][j] == '.') {
            return;
        }

        // Mark this cell as visited (part of current battleship)
        visited[i][j] = true;

        // Recurse in all 4 directions to explore the entire ship
        dfs(i + 1, j, board, visited); // down
        dfs(i - 1, j, board, visited); // up
        dfs(i, j + 1, board, visited); // right
        dfs(i, j - 1, board, visited); // left
    }

    int countBattleships(vector<vector<char>>& board) {

        int m = board.size();
        int n = board[0].size();

        // Visited matrix to avoid counting the same cell twice
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Found an unvisited 'X' — this is the start of a new ship
                if (board[i][j] == 'X' && !visited[i][j]) {

                    // DFS marks every cell in this ship as visited
                    dfs(i, j, board, visited);

                    // One DFS call = one complete battleship explored
                    count++;
                }
            }
        }

        return count;
    }
};



int main(){
    return 0;
}