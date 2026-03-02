#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * Problem: Minimum Falling Path Sum
 * We can move from any position (i, j) to (i+1, j-1), (i+1, j), or (i+1, j+1)
 * Goal: Find the minimum sum path from any position in first row to any position in last row
 */

class memoization
{
public:
    // Recursive function with memoization
    // i: current row, j: current column
    int solve(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        // Base case: if we're at the first row, return the current cell value
        if (i == 0)
            return grid[i][j];
        
        // If already computed, return the cached result
        if (dp[i][j] != -1)
            return dp[i][j];
        
        // From current position (i,j), we can come from three possible positions in previous row:
        // 1. Directly above: (i-1, j)
        int up = grid[i][j] + solve(i - 1, j, grid, dp);
        
        // 2. Left diagonal: (i-1, j-1) - Check if j-1 is within bounds
        int left_diagonal = INT_MAX;  // Initialize with max value to indicate invalid path
        if (j - 1 >= 0)  // Check left boundary: column index shouldn't go below 0
            left_diagonal = grid[i][j] + solve(i - 1, j - 1, grid, dp);
        
        // 3. Right diagonal: (i-1, j+1) - Check if j+1 is within bounds
        int right_diagonal = INT_MAX;  // Initialize with max value to indicate invalid path
        if (j + 1 < grid[0].size())  // Check right boundary: column index shouldn't exceed matrix width
            right_diagonal = grid[i][j] + solve(i - 1, j + 1, grid, dp);
        
        // Store and return the minimum of all three possible paths
        return dp[i][j] = min(up, min(left_diagonal, right_diagonal));
    }
    int minFallingPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();    // Number of rows
        int m = grid[0].size(); // Number of columns
        
        // Initialize DP table with -1 (indicating uncomputed states)
        vector<vector<int>> dp(n, vector<int>(m, -1));
        
        int ans = INT_MAX;
        // Try starting from each position in the last row and find minimum
        //every last row call the solve function for all the columns and find the minimum value among them which will be our answer
        for (int j = 0; j < m; j++)
        {
            ans = min(ans, solve(n - 1, j, grid, dp));
        }
        return ans;
    }
};

class Tabulation
{
public:
    // Bottom-up approach using 2D DP table
    int minFallingPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();    // Number of rows
        int m = grid[0].size(); // Number of columns
        
        // DP table where dp[i][j] = minimum path sum to reach position (i,j)
        vector<vector<int>> dp(n, vector<int>(m, 0));
        
        // Base case: First row values are same as grid values
        for (int j = 0; j < m; j++)
        {
            dp[0][j] = grid[0][j];
        }
        
        // Fill the DP table row by row from top to bottom
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                // Current cell value + minimum path sum from directly above
                int up = grid[i][j] + dp[i - 1][j];
                
                // Current cell value + minimum path sum from left diagonal
                int left_diagonal = INT_MAX;  // Default to max (invalid path)
                if (j - 1 >= 0)  // Check if left diagonal is within bounds (not out of left edge)
                    left_diagonal = grid[i][j] + dp[i - 1][j - 1];
                
                // Current cell value + minimum path sum from right diagonal
                int right_diagonal = INT_MAX;  // Default to max (invalid path)
                if (j + 1 < m)  // Check if right diagonal is within bounds (not out of right edge)
                    right_diagonal = grid[i][j] + dp[i - 1][j + 1];
                
                // Store the minimum of all three possible paths
                dp[i][j] = min(up, min(left_diagonal, right_diagonal));
            }
        }
        
        // Find the minimum value in the last row (any ending position)
        //here last row have all the minimum path sums from the first row to the last row by trying all the possible paths and we need to find the minimum value in the last row which will be our answer
        int ans = INT_MAX;
        for (int j = 0; j < m; j++)
        {
            ans = min(ans, dp[n - 1][j]);
        }
        return ans;
    }
};

class Space_Optimization
{
public:
    // Space optimized approach using only two 1D arrays instead of 2D DP table
    // Space Complexity: O(m) instead of O(n*m)
    int minFallingPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();    // Number of rows
        int m = grid[0].size(); // Number of columns
        
        // Only store the previous row's minimum path sums
        vector<int> prev(m, 0);
        
        // Initialize with first row values
        for (int j = 0; j < m; j++)
        {
            prev[j] = grid[0][j];
        }
        
        // Process each row from second row onwards
        for (int i = 1; i < n; i++)
        {
            // Current row's minimum path sums
            vector<int> curr(m, 0);
            
            for (int j = 0; j < m; j++)
            {
                // Path from directly above
                int up = grid[i][j] + prev[j];
                
                // Path from left diagonal - check bounds to avoid accessing negative index
                int left_diagonal = INT_MAX;  // Default to max (out of bounds)
                if (j - 1 >= 0)  // Ensure we don't access prev[-1] (out of bounds)
                    left_diagonal = grid[i][j] + prev[j - 1];
                
                // Path from right diagonal - check bounds to avoid array overflow
                int right_diagonal = INT_MAX;  // Default to max (out of bounds)
                if (j + 1 < m)  // Ensure we don't access prev[m] or beyond (out of bounds)
                    right_diagonal = grid[i][j] + prev[j + 1];
                
                // Store minimum of all valid paths
                curr[j] = min(up, min(left_diagonal, right_diagonal));
            }
            
            // Move current row to previous for next iteration
            prev = curr;
        }
        
        //now the prev array contain all the minimum path sums for the last row to the 1st row by trying all the possible paths and we need to find the minimum value in the prev array which will be our answer
        // Find minimum value in the last processed row
        int ans = INT_MAX;
        for (int j = 0; j < m; j++)
        {
            ans = min(ans, prev[j]);
        }
        return ans;
    }
};

int main()
{
    /*
     * Test case: {{2, 1, 3}, 
     *            {6, 5, 4}, 
     *            {7, 8, 9}}
     * 
     * Optimal path: 1 -> 5 -> 7 = 13
     * Path explanation:
     * Start at (0,1) with value 1
     * Move to (1,1) with value 5  [total: 1+5 = 6]
     * Move to (2,0) with value 7  [total: 6+7 = 13]
     */
    vector<vector<int>> grid = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    
    // Test all three approaches - they should give the same result
    memoization m;
    cout << "Minimum Falling Path Sum (Memoization): " << m.minFallingPathSum(grid) << endl;
    
    Tabulation t;
    cout << "Minimum Falling Path Sum (Tabulation): " << t.minFallingPathSum(grid) << endl;
    
    Space_Optimization s; 
    cout << "Minimum Falling Path Sum (Space Optimized): " << s.minFallingPathSum(grid) << endl;
    
    return 0;
}
