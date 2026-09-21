#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===========================================================================
PROBLEM: Minimum Area Rectangle to Enclose All 1s
===========================================================================
Given a 2D binary grid containing 0s and 1s, find the area of the
smallest axis-aligned rectangle that fully encloses all the 1s.

The rectangle must:
  - Be aligned with the grid axes (no rotation)
  - Contain ALL cells that have value 1
  - Have minimum possible area

If there are no 1s, the area is 0.

Example:
  grid = {
      {0, 0, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 1, 0, 0}
  }

  1s are at positions: (0,2), (1,1), (1,2), (3,1)

  Bounding box:
    Topmost row with 1:    row 0        → minRow = 0
    Bottommost row with 1: row 3        → maxRow = 3
    Leftmost col with 1:   col 1        → minCol = 1
    Rightmost col with 1:  col 2        → maxCol = 2

  Width  = maxCol - minCol + 1 = 2 - 1 + 1 = 2
  Height = maxRow - minRow + 1 = 3 - 0 + 1 = 4
  Area   = 2 × 4 = 8

  (The "+1" is because indices are 0-based; e.g., cols 1 and 2
   span 2 columns, not 1.)
===========================================================================

===========================================================================
LOGIC: BOUNDARY TRACKING
===========================================================================

Intuition:
  The minimum rectangle enclosing all 1s is simply the "bounding box"
  defined by:
    - The topmost row containing a 1 (minRow)
    - The bottommost row containing a 1 (maxRow)
    - The leftmost column containing a 1 (minCol)
    - The rightmost column containing a 1 (maxCol)

  We scan the entire grid, and every time we see a 1, we update
  these four boundaries. At the end, the area is computed from them.

Initialization:
  minRow = m (start at largest possible, will shrink downward)
  maxRow = -1 (start at smallest possible, will grow downward)
  minCol = n (start at largest possible, will shrink rightward)
  maxCol = -1 (start at smallest possible, will grow rightward)

  This ensures any valid 1 found will update all four bounds.

DRY RUN for grid = {
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 1, 0, 0}
}

  m=4, n=4
  minRow=4, maxRow=-1, minCol=4, maxCol=-1

  Scan (0,0)=0, (0,1)=0, (0,2)=1 → minRow=0, maxRow=0, minCol=2, maxCol=2
          (0,3)=0
  Scan (1,0)=0, (1,1)=1 → minRow=0, maxRow=1, minCol=1, maxCol=2
          (1,2)=1 → no change (all bounds already cover this)
          (1,3)=0
  Scan (2,0)=0, (2,1)=0, (2,2)=0, (2,3)=0 → no 1s found
  Scan (3,0)=0, (3,1)=1 → minRow=0, maxRow=3, minCol=1, maxCol=2
          (3,2)=0, (3,3)=0

  Final: minRow=0, maxRow=3, minCol=1, maxCol=2
  Width  = 2 - 1 + 1 = 2
  Height = 3 - 0 + 1 = 4
  Area   = 2 × 4 = 8 ✓

TIME:  O(m × n) — single pass through the grid
SPACE: O(1) — only four boundary variables
===========================================================================

*/

int minimumArea(vector<vector<int>> &grid)
{
    int m = grid.size();
    int n = grid[0].size();

    // Initialize boundaries to extreme values
    // minRow starts at m (largest possible) so any row with a 1 will be smaller
    // maxRow starts at -1 so any row with a 1 will be larger
    // Same logic for minCol and maxCol
    int maxCol = -1;
    int maxRow = -1;
    int minCol = n;
    int minRow = m;

    // Scan entire grid to find the bounding box of all 1s
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 1)
            {
                // Update all four boundaries whenever we find a 1
                maxCol = max(maxCol, j);   // rightmost column with a 1
                maxRow = max(maxRow, i);   // bottommost row with a 1
                minCol = min(minCol, j);   // leftmost column with a 1
                minRow = min(minRow, i);   // topmost row with a 1
            }
        }
    }

    // Compute area of the bounding box
    // +1 because indices are 0-based: cols 1 to 2 span 2 columns, not 1
    return (maxCol - minCol + 1) * (maxRow - minRow + 1);
}

int main()
{
    vector<vector<int>> grid = {
        {0, 0, 1, 0},  // 1 at (0,2)
        {0, 1, 1, 0},  // 1s at (1,1), (1,2)
        {0, 0, 0, 0},  // no 1s
        {0, 1, 0, 0}   // 1 at (3,1)
    };
    cout << minimumArea(grid) << endl;  // Output: 8
    return 0;
}
