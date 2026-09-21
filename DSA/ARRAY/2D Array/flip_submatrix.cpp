#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===========================================================================
PROBLEM: Reverse (Flip) a K×K Submatrix Vertically
===========================================================================
Given:
  - A 2D grid of integers
  - (x, y) = top-left corner of the submatrix
  - k = size of the k×k submatrix

Task: Reverse the rows of the k×k submatrix. The first row of the
submatrix swaps with the last row, second with second-last, etc.

Elements outside the submatrix remain unchanged.

Example:
  grid =                    submatrix at (1,1) k=2:
  [1,  2,  3,  4]           [6,  7]
  [5,  6,  7,  8]     →     [10, 11]  (reversed vertically)
  [9,  10, 11, 12]
  [13, 14, 15, 16]

  Result:
  [1,  2,  3,  4]
  [5,  10, 11, 8]    ← rows 1-2, cols 1-2 flipped
  [9,  6,  7, 12]
  [13, 14, 15, 16]
===========================================================================

===========================================================================
LOGIC: TWO-POINTER ROW SWAP (Top ↔ Bottom)
===========================================================================

Intuition:
  To "reverse" the rows of the submatrix, we swap the top row with
  the bottom row, then move inward — exactly like reversing an array
  using two pointers.

  top = x                (first row of submatrix)
  bottom = x + k - 1     (last row of submatrix)

  While top < bottom:
      For each column i from y to y+k-1:
          swap(grid[top][i], grid[bottom][i])
      top++       (move top row down)
      bottom--    (move bottom row up)

  This is identical to reversing a 1D array, but applied row-by-row
  across the k columns of the submatrix.

DRY RUN for grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
                    x=1, y=1, k=2

  Submatrix (rows 1-2, cols 1-2):
      [6,  7]
      [10, 11]

  top = 1, bottom = 2

  Iteration 1 (top=1 < bottom=2):
    Swap row 1 ↔ row 2, columns 1 to 2:
      swap(grid[1][1], grid[2][1])  → swap(6, 10)  → grid[1][1]=10, grid[2][1]=6
      swap(grid[1][2], grid[2][2])  → swap(7, 11)  → grid[1][2]=11, grid[2][2]=7
    top = 2, bottom = 1

  top(2) >= bottom(1) → STOP

  Result grid:
      [1,  2,  3,  4]
      [5, 10, 11,  8]    ← submatrix row 0: [10,11]
      [9,  6,  7, 12]    ← submatrix row 1: [6,7]
      [13, 14, 15, 16]

  Original submatrix was [6,7; 10,11], now it's [10,11; 6,7] ✓

TIME:  O(k²) — we visit each element in the submatrix once
SPACE: O(1) — in-place swaps
===========================================================================

*/

class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        // top = first row of the k×k submatrix
        // bottom = last row of the k×k submatrix
        int top = x;
        int bottom = x + k - 1;

        // Two-pointer approach: swap top row with bottom row,
        // then move inward until pointers meet
        while (top < bottom) {
            // Swap all k elements in columns [y, y+k-1] between row top and row bottom
            for (int i = y; i < y + k; i++) {
                swap(grid[top][i], grid[bottom][i]);
            }
            top++;      // move top pointer down
            bottom--;   // move bottom pointer up
        }

        return grid;
    }
};



int main(){
    Solution sol;
    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int x = 1, y = 1, k = 2;
    vector<vector<int>> ans = sol.reverseSubmatrix(grid, x, y, k);
    cout << "Reversed Submatrix:" << endl;
    for (const auto& row : ans) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    return 0;
}
