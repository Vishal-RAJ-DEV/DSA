#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * PROBLEM: Given a target string, find the path on an alphabet board to spell it.
     *          The board is:
     *
     *            a b c d e
     *            f g h i j
     *            k l m n o
     *            p q r s t
     *            u v w x y
     *                        z (special: row 5, col 0)
     *
     *          Start at 'a'. Use U/D/L/R to move, '!' to select current letter.
     *          Return the path string.
     *
     * EXAMPLE: target = "zaz"
     *   'a' → 'z': path from (0,0) to (5,0) = "DDDDD!" (5 downs)
     *   'z' → 'a': path from (5,0) to (0,0) = "UUUUU!" (5 ups)
     *   'a' → 'z': path from (0,0) to (5,0) = "DDDDD!" (5 downs)
     *   Answer: "DDDDD!UUUUU!DDDDD!"
     *
     * HOW TO RECOGNIZE THIS PATTERN:
     * -------------------------
     * This is a "GRID NAVIGATION + PATH RECONSTRUCTION" problem.
     *
     * Recognize this pattern when:
     *   1. You have a 2D grid with labeled positions (here: alphabet)
     *   2. You need to move between positions step by step
     *   3. Each move is one unit in 4 directions (U/D/L/R)
     *   4. You need to output the PATH, not just count moves
     *   5. Positions can be computed from values (here: 'a'=0, 'b'=1, etc.)
     *
     * Similar problems:
     *   - Robot navigation on a grid
     *   - Remote control navigation
     *   - Any "spell word on custom keyboard" problem
     *
     * KEY INSIGHT: Greedy Manhattan distance
     * -------------------------
     * We DON'T need BFS/shortest path algorithms because:
     *   - All moves have equal cost (1 step)
     *   - We want shortest path = Manhattan distance
     *   - No obstacles on the board
     *   - We can move independently in X and Y axes
     *
     * So we just move greedily:
     *   - If above target → move Down
     *   - If below target → move Up
     *   - If left of target → move Right
     *   - If right of target → move Left
     *
     * ORDER MATTERS (U, L, D, R):
     * -------------------------
     * We move UP and LEFT first, then DOWN and RIGHT.
     * Why? Because 'z' is at bottom-left. If we move Down first,
     * we might go out of bounds (off the board) when trying to reach 'z'.
     * Moving Up/Left first is always safe because the board extends
     * upward and leftward from any position.
     *
     * Board layout:
     *   Row 0: a b c d e
     *   Row 1: f g h i j
     *   Row 2: k l m n o
     *   Row 3: p q r s t
     *   Row 4: u v w x y
     *   Row 5: z
     *
     *   - Rows 0-4 have 5 columns each
     *   - Row 5 has only 1 column (z at col 0)
     */

    string alphabetBoardPath(string target) {
        string ans = "";

        // Start at 'a' (top-left corner: row 0, col 0)
        int currentRow = 0;
        int currentCol = 0;

        // Process each character in target string
        for (char ch : target) {

            // STEP 1: Find target character's position on the board
            // Formula: index = ch - 'a' (0 for 'a', 1 for 'b', ..., 25 for 'z')
            // Row = index / 5 (integer division gives the row)
            // Col = index % 5 (remainder gives the column)
            int targetRow = (ch - 'a') / 5;
            int targetCol = (ch - 'a') % 5;

            // STEP 2: Move UP first (if currently below target)
            // Why UP before DOWN? See explanation above about board bounds
            while (currentRow > targetRow) {
                ans += 'U';
                currentRow--;
            }

            // STEP 3: Move LEFT (if currently right of target)
            while (currentCol > targetCol) {
                ans += 'L';
                currentCol--;
            }

            // STEP 4: Move DOWN (if currently above target)
            while (currentRow < targetRow) {
                ans += 'D';
                currentRow++;
            }

            // STEP 5: Move RIGHT (if currently left of target)
            while (currentCol < targetCol) {
                ans += 'R';
                currentCol++;
            }

            // STEP 6: Select the character (press '!')
            ans += '!';
        }

        return ans;
    }
};


int main(){
    return 0;
}