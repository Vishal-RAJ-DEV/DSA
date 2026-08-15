// =============================================================================
// COUNT SQUARE SUBMATRICES WITH ALL ONES
// =============================================================================
// Problem: Count all square submatrices that contain only 1s
//
// ALGORITHM: Dynamic Programming
//   dp[i][j] = size of largest square with bottom-right corner at (i,j)
//
// RECURRENCE:
//   If matrix[i][j] == 0:  dp[i][j] = 0
//   If matrix[i][j] == 1:  dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
//
// KEY INSIGHT:
//   A square of size k at (i,j) requires:
//   - A square of size k-1 at (i-1,j)   [top]
//   - A square of size k-1 at (i,j-1)   [left]
//   - A square of size k-1 at (i-1,j-1) [top-left diagonal]
//
// WHY SUM ALL dp[i][j]?
//   dp[i][j] = k means there are k squares ending at (i,j):
//   - 1 square of size 1
//   - 1 square of size 2 (if k >= 2)
//   - ...
//   - 1 square of size k
//   So dp[i][j] directly counts all squares ending at (i,j)
//
// TIME: O(N * M)  |  SPACE: O(N * M)
// =============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // =========================================================================
    // APPROACH 1: DP with inline accumulation
    // =========================================================================
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        // dp[i][j] = size of largest square ending at (i,j)
        vector<vector<int>> dp(n, vector<int>(m, 0));
        int ans = 0;

        // Base case: first column
        // A single cell is a square of size 1 if it's 1
        for (int i = 0; i < n; i++) {
            dp[i][0] = matrix[i][0];
            ans += dp[i][0];
        } 

        // Base case: first row (start from j = 1 to avoid double counting dp[0][0])
        for (int j = 1; j < m; j++) { 
            dp[0][j] = matrix[0][j];
            ans += dp[0][j];
        }
        
        // DP for the rest of the matrix
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] == 1) {
                    // Take minimum of 3 neighbors and add 1
                    dp[i][j] = 1 + min({dp[i-1][j-1], dp[i][j-1], dp[i-1][j]});
                    ans += dp[i][j];
                }
            }
        }

        return ans;
    }
};

// =============================================================================
// APPROACH 2: DP with separate summation (cleaner for learning)
// =============================================================================
int countSquares(int n, int m, vector<vector<int>> &arr) {
    // DP table to store size of largest square ending at (i,j)
    vector<vector<int>> dp(n, vector<int>(m, 0));

    // Initialize first row of DP table
    for (int j = 0; j < m; j++) 
        dp[0][j] = arr[0][j];

    // Initialize first column of DP table
    for (int i = 0; i < n; i++) 
        dp[i][0] = arr[i][0];

    // Fill the rest of the DP table
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            // If current cell is 0, no square ends here
            if (arr[i][j] == 0) 
                dp[i][j] = 0;
            else {
                // Minimum of top, left, top-left + 1
                dp[i][j] = 1 + min(dp[i - 1][j],
                                   min(dp[i - 1][j - 1], dp[i][j - 1]));
            }
        }
    }

    // Sum up all values in DP table
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum += dp[i][j];
        }
    }

    // Return total count of squares
    return sum;
}

// =============================================================================
// MAIN - Test with detailed diagram
// =============================================================================
int main() {
    // Input matrix
    vector<vector<int>> arr = {
        {0, 1, 1, 1}, 
        {1, 1, 1, 1},
        {0, 1, 1, 1}
    };
    
    // Matrix dimensions
    int n = 3, m = 4;

    /*
    STEP-BY-STEP TRACE WITH DIAGRAMS:
    
    Original Matrix:
        col0  col1  col2  col3
    row0  0     1     1     1
    row1  1     1     1     1
    row2  0     1     1     1
    
    ============================================================================
    DP RECURRENCE VISUALIZATION:
    ============================================================================
    
    For each cell (i,j), dp[i][j] depends on 3 neighbors:
    
         (i-1,j-1)  (i-1,j)
              ↘       ↓
         (i,j-1)  →  (i,j)
    
    dp[i][j] = 1 + min(dp[i-1][j-1], dp[i][j-1], dp[i-1][j])
    
    ============================================================================
    DP MATRIX CONSTRUCTION:
    ============================================================================
    
    STEP 1: Initialize base cases (first row and first column)
    
    Matrix:           dp (after base cases):
    0  1  1  1        0  1  1  1
    1  1  1  1   →    1  .  .  .
    0  1  1  1        0  .  .  .
    
    STEP 2: Fill dp[1][1]
    
    Neighbors:     Calculation:
    dp[0][0]=0     dp[1][1] = 1 + min(0, 1, 1) = 1
    dp[0][1]=1     
    dp[1][0]=1     
    
    dp matrix:
    0  1  1  1
    1 [1] .  .
    0  .  .  .
    
    STEP 3: Fill dp[1][2]
    
    Neighbors:     Calculation:
    dp[0][1]=1     dp[1][2] = 1 + min(1, 1, 1) = 2
    dp[0][2]=1     
    dp[1][1]=1     
    
    dp matrix:
    0  1  1  1
    1  1 [2] .
    0  .  .  .
    
    STEP 4: Fill dp[1][3]
    
    Neighbors:     Calculation:
    dp[0][2]=1     dp[1][3] = 1 + min(1, 2, 1) = 2
    dp[0][3]=1     
    dp[1][2]=2     
    
    dp matrix:
    0  1  1  1
    1  1  2 [2]
    0  .  .  .
    
    STEP 5: Fill dp[2][1]
    
    Neighbors:     Calculation:
    dp[1][0]=1     dp[2][1] = 1 + min(1, 0, 1) = 1  (limited by dp[2][0]=0)
    dp[1][1]=1     
    dp[2][0]=0     
    
    dp matrix:
    0  1  1  1
    1  1  2  2
    0 [1] .  .
    
    STEP 6: Fill dp[2][2]
    
    Neighbors:     Calculation:
    dp[1][1]=1     dp[2][2] = 1 + min(1, 1, 2) = 2
    dp[1][2]=2     
    dp[2][1]=1     
    
    dp matrix:
    0  1  1  1
    1  1  2  2
    0  1 [2] .
    
    STEP 7: Fill dp[2][3]
    
    Neighbors:     Calculation:
    dp[1][2]=2     dp[2][3] = 1 + min(2, 2, 2) = 3  ← MAX SQUARE SIZE!
    dp[1][3]=2     
    dp[2][2]=2     
    
    FINAL dp MATRIX:
    0  1  1  1
    1  1  2  2
    0  1  2 [3]
    
    ============================================================================
    UNDERSTANDING WHY dp[i][j] = k MEANS k SQUARES:
    ============================================================================
    
    At dp[2][3] = 3, there are 3 squares ending at (2,3):
    
    Square size 1:  [2,3]           (1×1)
    Square size 2:  [1,2]-[2,3]     (2×2)
    Square size 3:  [0,1]-[2,3]     (3×3)
    
    Visual:
    col0  col1  col2  col3
    row0  .    [1]  [1] [1]     ← 3×3 square
    row1  .    [1]  [1] [1]     ← 2×2 square  
    row2  .    [1]  [1] [3]     ← 1×1 square
                    ↑
                dp[2][3] = 3
    
    ============================================================================
    FINAL ANSWER:
    ============================================================================
    
    Sum all dp values:
    0 + 1 + 1 + 1 = 3  (row 0)
    1 + 1 + 2 + 2 = 6  (row 1)
    0 + 1 + 2 + 3 = 6  (row 2)
    ─────────────────
    Total = 15 squares
    
    All 15 squares:
    Size 1×1: 9 squares (all cells with value 1)
    Size 2×2: 5 squares
    Size 3×3: 1 square
    ─────────────────
    Total = 15
    */
    
    // Call function
    int squares = countSquares(n, m, arr);

    // Print the result
    cout << "The number of squares: " << squares << "\n";

    return 0;
}