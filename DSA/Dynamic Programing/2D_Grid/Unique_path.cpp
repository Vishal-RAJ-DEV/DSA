/*Example 1:
Input:
 m = 3, n = 2  
Output:
 3  
Explanation:
 There are 3 unique ways to go from the top-left to the bottom-right cell:
1) right → down → down  
2) down → right → down  
3) down → down → right  

Example 2:
Input:
 m = 2, n = 4  
Output:
 4  
Explanation:
 There are 4 unique ways to go from the top-left to the bottom-right cell:
1) down → right → right → right  
2) right → down → right → right  
3) right → right → down → right  
4) right → right → right → down
*/

#include <bits/stdc++.h>
using namespace std;

class Memozationn {
private:
    //Function to solve the problem using recursion
    int func(int i, int j, vector<vector<int>>& dp){
        // Base case
        if (i == 0 && j == 0)  return 1;

        /* If we go out of bounds or reach 
        a blocked cell, there are no ways.*/
        if (i < 0 || j < 0)  return 0;
        
        /* If we have already computed the number 
        of ways for this cell, return it.*/
        if (dp[i][j] != -1)  return dp[i][j];

        /* Calculate the number of ways by
        moving up and left recursively.*/
        int up = func(i - 1, j, dp);
        int left = func(i, j - 1, dp);

        // Store the result in dp table and return it.
        return dp[i][j] = up + left;
    }
public:
    /*Function to count the total ways
    to reach (0,0) from (m-1,n-1)*/
    int uniquePaths(int m, int n) {
        /* Initialize a memoization table (dp) to
        store the results of subproblems.*/
        vector<vector<int>> dp(m, vector<int>(n, -1));
        
        //Return the total count(0 based indexing)
        return func(m-1,n-1, dp);
    }
};

class Tabulation {
private:
    //Function to solve the problem using tabulation
    int func(int m, int n, vector<vector<int>>& dp){
        // Loop through the grid using two nested loops
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
            // Base condition
            if (i == 0 && j == 0) {
                dp[i][j] = 1;
                /* Skip the rest of the loop and 
                continue with the next iteration.*/
                continue; 
            }

            /* Initialize variables to store the number 
            of ways from cell above (up) and left (left)*/
            int up = 0;
            int left = 0;

            /* If we are not at first row (i > 0), update 
            'up' with the value from the cell above.*/
            if (i > 0)
                up = dp[i - 1][j];

            /* If we are not at the first column (j > 0),
            update 'left' with value from the cell to left.*/
            if (j > 0)
                left = dp[i][j - 1];

            /* Calculate the number of ways to reach the 
            current cell by adding 'up' and 'left'.*/
            dp[i][j] = up + left;
        }
    }

    // The result is stored in bottom-right cell (m-1, n-1).
    return dp[m - 1][n - 1];
}
public:
    /*Function to count the total ways
    to reach (0,0) from (m-1,n-1)*/
    int uniquePaths(int m, int n) {
        /* Initialize a memoization table (dp) to
        store the results of subproblems.*/
        vector<vector<int>> dp(m, vector<int>(n, -1));
        
        //Return the total count(0 based indexing)
        return func(m, n, dp);
    }
};


class SpaceOptimization {
private:
    //Function to solve the problem using space optimization.
    int func(int m, int n){
        /* Initialize a vector to represent 
        the previous row of the grid.*/
        vector<int> prev(n, 0);

        // Iterate through the rows of the grid.
        for (int i = 0; i < m; i++) {
            /* Create a temporary vector to
            represent the current row.*/
            vector<int> temp(n, 0);

            for (int j = 0; j < n; j++) {
                // Base case
                if (i == 0 && j == 0) {
                    temp[j] = 1; //base case initialized with 1 because there is only one way to reach the starting cell (0,0) which is to stay there.
                    continue;
                }

            /* Initialize variables to store the number
            of ways from the cell above (up) and left (left).*/
            int up = 0;
            int left = 0;

            /* If we are not at the first row (i > 0), update
            'up' with the value from the previous row.*/
            if (i > 0)
                up = prev[j];

            /* If we are not at the first column (j > 0),
            update 'left' with the value from current row.*/
            if (j > 0)
                left = temp[j - 1];

            /* Calculate the number of ways to reach the
            current cell by adding 'up' and 'left'.*/
            temp[j] = up + left;
        }

        /* Update the previous row with values 
        calculated for the current row.*/
        prev = temp;
    }

    /* The result is stored in the last
    cell of the previous row (n-1).*/
    return prev[n - 1];
}
public:
    /*Function to count the total ways
    to reach (0,0) from (m-1,n-1)*/
    int uniquePaths(int m, int n) {
        
        //Return the total count(0 based indexing)
        return func(m, n);
    }
};


int main() {
    int m = 3;
    int n = 2;
    
    //Create an instance of Solution class
    Memozationn sol;
    
    // Call the countWays function and print the result.
    cout << "Number of ways: " << sol.uniquePaths(m, n) << endl;

    return 0;
}