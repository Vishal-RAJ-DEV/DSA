#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
QUESTION (Leetcode 1901 - Find a Peak Element II):
A peak element in a 2D grid is an element that is STRICTLY GREATER than
all its 4 neighbors: top, bottom, left, and right (diagonal doesn't count).
If a neighbor doesn't exist (edge), ignore it.

Find ANY peak element in the given matrix and return its [row, col].
The matrix has no two adjacent cells with the same value.

EXAMPLE:
mat = [
  [10, 20, 15],
  [21, 30, 14],
  [7 , 16, 32]
]
Peaks: 30 at (1,1), 32 at (2,2). Return any one.

---

ALGORITHM EXPLANATION (Binary Search on Columns):

We know a peak always exists (guaranteed by problem).
Instead of scanning all elements O(n*m), we use binary search on columns.

The flow is:
  Binary Search on columns (low=0, high=m-1)
  |
  Choose middle column (mid)
  |
  Find maximum element in that column (call it mat[row][mid])
  |
  Compare only left and right neighbors
  (we don't need to check top/bottom because mat[row][mid] is the
   column max, so it's already >= top and bottom)
  |
  ┌─────────────────────────────────────────────┐
  │  if left < current > right                  │
  │      → current is a peak → Return (row,mid) │
  ├─────────────────────────────────────────────┤
  │  else if left > current → Search LEFT       │
  │      (peak must exist on left side)         │
  ├─────────────────────────────────────────────┤
  │  else (right > current) → Search RIGHT      │
  │      (peak must exist on right side)        │
  └─────────────────────────────────────────────┘

WHY THIS WORKS:
- The max element of a column is guaranteed >= its top and bottom.
- So we only need to compare left and right.
- If the column max has a larger left neighbor, there MUST be a peak
  on the left side (by a 1D peak argument along that row).
- Similarly for a larger right neighbor.
- This narrows our search space by half each time → O(n log m).

ALGORITHM STEPS:
1. Set low = 0 (first column), high = m-1 (last column).
2. While low <= high:
   a. mid = low + (high - low) / 2
   b. Find the row index of the maximum element in column mid.
   c. Get left neighbor value (-1 if out of bounds).
   d. Get right neighbor value (-1 if out of bounds).
   e. If current > left AND current > right → PEAK FOUND, return {row, mid}.
   f. Else if left > current → peak is on left side, set high = mid - 1.
   g. Else (right > current) → peak is on right side, set low = mid + 1.
3. Return {-1, -1} (shouldn't reach here as a peak always exists).
*/

class Solution {
public:

    // Find row index of the maximum element in a given column
    int search(int col, vector<vector<int>>& mat, int rows) {

        int rowIdx = 0;

        for (int row = 1; row < rows; row++) {
            if (mat[row][col] > mat[rowIdx][col])
                rowIdx = row;
        }

        return rowIdx;
    }

    vector<int> findPeakGrid(vector<vector<int>>& mat) {

        int n = mat.size();      // rows
        int m = mat[0].size();   // columns

        int low = 0;
        int high = m - 1;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            // Step 1: Find max element in middle column
            int row = search(mid, mat, n);

            // Step 2: Get left and right neighbors
            int left = (mid == 0) ? -1 : mat[row][mid - 1];
            int right = (mid == m - 1) ? -1 : mat[row][mid + 1];

            // Step 3: Check if current is a peak
            if (mat[row][mid] > left && mat[row][mid] > right)
                return {row, mid};

            // Step 4: Move towards the larger neighbor
            else if (left > mat[row][mid])
                high = mid - 1;
            else
                low = mid + 1;
        }

        return {-1, -1};
    }
};

int main(){
    return 0;
}