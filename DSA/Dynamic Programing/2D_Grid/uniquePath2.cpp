/*
Unique Paths II
-->same as unique path but with obstacles in the grid denoted by 1 and empty cells denoted by 0 , we have to find the ignore the blocked cells and find the number of unique paths from top left to bottom right cell
-->we can move only right and down
Example 1:
Input:
 matrix = [[0, 0, 0], [0, 1, 0], [0, 0, 0]]
Output:
 2
Explanation:

The two possible paths to reach the bottom-right cell are:
1) down → down → right → right
2) right → right → down → down
Thus, the number of paths is 2.

Example 2:
Input:
 matrix = [[0, 0, 0], [0, 0, 1], [0, 1, 0]]
Output:
 0
Explanation:
 There is no valid path to reach the bottom-right cell due to blocked cells (represented by 1).
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// code will be same as unique path but with some changes in the base case and the recursive calls
//time complexity : O(m*n) and space complexity : O(m*n) where m is the number of rows and n is the number of columns in the grid
class Memozation
{
private:
    // Function to solve the problem using memoization
    int func(int i, int j, vector<vector<int>> &matrix, vector<vector<int>> &dp)
    {
        // Base cases
        //when the cell is blocked or we go out of bounds then there is no way to reach the destination so that we can return 0 meaning no path
        if (i < 0 || j < 0 || matrix[i][j] == 1)  //also add the condition for the blocked cell where we can not go through it
            return 0;
        else if (i == 0 && j == 0)
            return 1;

        // If the result is already computed, return it
        if (dp[i][j] != -1)
            return dp[i][j];

        /* Calculate the number of ways by
        moving up and left recursively.*/
        int up = func(i - 1, j, matrix, dp);
        int left = func(i, j - 1, matrix, dp);

        // Return the total ways
        return dp[i][j] = up + left;
    }

public:
    /*Function to find all unique paths to reach
    matrix[m-1][n-1] form matrix[0][0] with obstacles*/
    int uniquePathsWithObstacles(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        // Initialize DP table to memoize results
        vector<vector<int>> dp(m, vector<int>(n, -1));

        // Return the total number of paths
        return func(m - 1, n - 1, matrix, dp);
    }
};

//time complexity : O(m*n) and space complexity : O(m*n) where m is the number of rows and n is the number of columns in the grid
class Tabulation {
private:
    // Function to solve the problem using tabulation
    int func(int m, int n, vector<vector<int>>& matrix, vector<vector<int>>& dp) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                // Base conditions
                if (matrix[i][j] == 1) {
                    /* If there's an obstacle at the 
                    cell, no paths can pass through it*/
                    dp[i][j] = 0;
                    continue;
                }
                if (i == 0 && j == 0) {
                    /* If we are at the starting 
                    point, there is one path to it*/
                    dp[i][j] = 1;
                    continue;
                }

                int up = 0;
                int left = 0;

                /* Check if we can move up and left 
                (if not at the edge of the maze)*/
                if (i > 0)
                    up = dp[i - 1][j];
                if (j > 0)
                    left = dp[i][j - 1];

                /* Total number of paths to reach (i, j)
                is the sum of paths from above and left*/
                dp[i][j] = up + left;
            }
        }

        /* The final result is stored in dp[m-1][n-1],
        which represents the destination*/
        return dp[m - 1][n - 1];
    }

public:
    /* Function to find all unique paths to reach 
    matrix[m-1][n-1] from matrix[0][0] with obstacles*/
    int uniquePathsWithObstacles(vector<vector<int>>& matrix) {
        int m = matrix.size();   
        int n = matrix[0].size(); 

        // Initialize DP table to memoize results
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // Return the total number of paths
        return func(m, n, matrix, dp);
    }
};


//time complexity : O(m*n) and space complexity : O(n) where m is the number of rows and n is the number of columns in the grid
class SpaceOptimization {
private:
    // Function to solve the problem using tabulation
    int func(int m, int n, vector<vector<int>>& matrix) {
        
        vector<int> prev(n, 0), curr(n, 0);
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                // Base conditions
                if (matrix[i][j] == 1) {
                    /* If there's an obstacle at the 
                    cell, no paths can pass through it*/
                    //SO THAT CELL CAN NOT BE USED TO REACH THE DESTINATION SO WE CAN MARK IT AS 0 MEANING NO PATH CAN PASS THROUGH IT
                    curr[j] = 0;
                    continue;
                }
                if (i == 0 && j == 0) {
                    /* If we are at the starting 
                    point, there is one path to it*/
                    curr[j] = 1;
                    continue;
                }

                int up = 0;
                int left = 0;

                /* Check if we can move up and left 
                (if not at the edge of the maze)*/
                if (i > 0)
                    up = prev[j];
                if (j > 0)
                    left = curr[j - 1];

                /* Total number of paths to reach (i, j)
                is the sum of paths from above and left*/
                curr[j] = up + left;
            }
            
            prev = curr;
        }

        /* The final result is stored in dp[m-1][n-1],
        which represents the destination*/
        return prev[n-1];
    }

public:
    /* Function to find all unique paths to reach 
    matrix[m-1][n-1] from matrix[0][0] with obstacles*/
    int uniquePathsWithObstacles(vector<vector<int>>& matrix) {
        int m = matrix.size();   
        int n = matrix[0].size(); 

        // Return the total number of paths
        return func(m, n, matrix);
    }
};

int main()
{
        vector<vector<int>> matrix = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
        Tabulation tab;
        cout << "Number of unique paths with obstacles: " << tab.uniquePathsWithObstacles(matrix) << endl;  
    return 0;
}