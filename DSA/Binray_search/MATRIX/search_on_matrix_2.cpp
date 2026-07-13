#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: 240. Search a 2D Matrix II

    Write an efficient algorithm that searches for a target value in an
    m x n integer matrix. The matrix has the following properties:
        - Integers in each row are sorted in ascending order from left to right.
        - Integers in each column are sorted in ascending order from top to bottom.

    Example:
        Matrix:
        [ 1,  4,  7, 11, 15]
        [ 2,  5,  8, 12, 19]
        [ 3,  6,  9, 16, 22]
        [10, 13, 14, 17, 24]
        [18, 21, 23, 26, 30]

        Input: target = 5  -> Output: true
        Input: target = 20 -> Output: false

    NOTE: This problem is different from "Search a 2D Matrix I" (LeetCode 74)
    where the entire matrix is strictly row-major sorted. Here, only individual
    rows and columns are sorted, NOT the entire matrix in a linear sense.
    So binary search on the flattened matrix does NOT work here.
*/


// =========================================================
// APPROACH 1: Staircase Search (Row/Column Elimination) — O(n + m)
// =========================================================
/*
    THE KEY INSIGHT:
        The matrix is sorted both row-wise and column-wise. If we stand at
        the top-right corner (row=0, col=m-1), we have a unique property:
            - Moving DOWN (row++) increases the value (since columns are
              sorted top-to-bottom).
            - Moving LEFT (col--) decreases the value (since rows are
              sorted left-to-right).
        This creates a decision tree where each comparison eliminates an
        entire row or an entire column.

    LOGIC:
        1. Start from the top-right corner: row = 0, col = m - 1.
        2. While row is within bounds (row < n) and col is within bounds (col >= 0):
            a. If matrix[row][col] == target  -> return true.
            b. If matrix[row][col] < target:
               -> All elements in the current row to the left of (row, col)
                  are even smaller (since row is sorted left-to-right).
                  So this entire row cannot contain the target.
                  Move DOWN (row++) to the next row for larger values.
            c. If matrix[row][col] > target:
               -> All elements in the current column below (row, col)
                  are even larger (since column is sorted top-to-bottom).
                  So this entire column cannot contain the target.
                  Move LEFT (col--) to the previous column for smaller values.
        3. If we exit the loop, target is not in the matrix.

    WHY THIS WORKS:
        The matrix has a "Young tableau" property. At any point, the element
        at (row, col) acts as a pivot:
        - The region BELOW and to the RIGHT has larger elements.
        - The region ABOVE and to the LEFT has smaller elements.
        - By starting at top-right, each step cleanly eliminates one row or
          one column from consideration.

    DRY RUN:
        Matrix = [[1,4,7,11,15],
                  [2,5,8,12,19],
                  [3,6,9,16,22]], target = 6

        Step 1: row=0, col=3, matrix[0][3]=11 > 6  -> col-- (col=2)
        Step 2: row=0, col=2, matrix[0][2]=7  > 6  -> col-- (col=1)
        Step 3: row=0, col=1, matrix[0][1]=4  < 6  -> row++ (row=1)
        Step 4: row=1, col=1, matrix[1][1]=5  < 6  -> row++ (row=2)
        Step 5: row=2, col=1, matrix[2][1]=6 == 6  -> return true

    TIME COMPLEXITY:
        - In the worst case, we traverse at most n rows and m columns.
        - Each iteration either increments row or decrements col.
        - row goes from 0 to at most n-1 (max n increments).
        - col goes from m-1 to at most 0 (max m decrements).
        - Total iterations ≤ n + m.
        - Overall: O(n + m) — linear in the dimensions of the matrix.

    SPACE COMPLEXITY:
        - Only a few integer variables used: O(1).
*/


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();

        // Start from top-right corner
        int row = 0;
        int col = m - 1;

        while (row < n && col >= 0) {

            if (matrix[row][col] == target)
                return true;

            else if (matrix[row][col] < target)
                row++;  // Current element is too small, move down
            else
                col--;  // Current element is too large, move left
        }

        return false;
    }
};


/*
    ALTERNATIVE APPROACHES:

    APPROACH 2: Binary Search on Each Row — O(n log m)
        - For each row, apply standard binary search.
        - Since rows are sorted, binary search works on each row.
        - Time: O(n log m), Space: O(1)
        - Slower than staircase when n and m are comparable.

    APPROACH 3: Divide & Conquer (Quadrant Elimination) — O(n^1.58)
        - Recursively divide the matrix into 4 quadrants.
        - Compare target with the center element to eliminate one quadrant.
        - Time: O(n^1.58) using Master Theorem.
        - More complex, rarely used in practice.

    The staircase approach (Approach 1) is the most intuitive and optimal
    for this problem's specific constraints.
*/


int main(){
    return 0;
}
