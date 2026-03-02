#include <bits/stdc++.h>
using namespace std;
class memoization
{

public:
    // Function to find the minimum cost to reach index 'ind' using at most 'k' jumps
    int solveUtil(int ind, vector<int> &height, vector<int> &dp, int k)
    {
        // Base case: starting point has zero cost
        if (ind == 0)
            return 0;

        // Return already computed result
        if (dp[ind] != -1)
            return dp[ind];

        // Initialize minimum steps as large value
        int mmSteps = INT_MAX;

        // Try all possible jumps from 1 to k
        for (int j = 1; j <= k; j++)
        {
            // Ensure jump does not go out of bounds
            if (ind - j >= 0)
            {
                // Cost of taking the jump
                int jump = solveUtil(ind - j, height, dp, k) + abs(height[ind] - height[ind - j]);
                // Store the minimum cost
                mmSteps = min(jump, mmSteps);
            }
        }
        // Save the result in dp array
        return dp[ind] = mmSteps;
    }

    // Function to get minimum cost to reach end
    int solve(int n, vector<int> &height, int k)
    {
        // DP array initialized to -1
        vector<int> dp(n, -1);
        // Start recursion from last index
        return solveUtil(n - 1, height, dp, k);
    }
};

class tabulation
{
    public:
    // Function to compute the minimum cost to reach the end using at most 'k' jumps
    int solveUtil(int n, vector<int> &height, vector<int> &dp, int k)
    {
        // Base case: cost to reach the first stone is 0
        dp[0] = 0;

        // Iterate over each stone
        for (int i = 1; i < n; i++)
        {
            // Initialize the minimum cost for this stone as large value
            int mmSteps = INT_MAX;

            // Try all possible jump lengths from 1 to k
            for (int j = 1; j <= k; j++)
            {
                // Ensure jump doesn't go out of bounds
                if (i - j >= 0)
                {
                    // Cost of jumping from (i - j) to i
                    int jump = dp[i - j] + abs(height[i] - height[i - j]);
                    // Keep track of the minimum cost
                    mmSteps = min(mmSteps, jump);
                }
            }

            // Store the computed minimum cost for this stone
            dp[i] = mmSteps;
        }

        // The last element of dp stores the answer
        return dp[n - 1];
    }

    // Main function to solve the problem
    int solve(int n, vector<int> &height, int k)
    {
        // Initialize DP array with -1
        vector<int> dp(n, -1);
        // Fill DP array iteratively
        return solveUtil(n, height, dp, k);
    }
};
// Driver code
int main()
{
    // Heights of stones
    vector<int> height{30, 10, 60, 10, 60, 50};
    int n = height.size();
    int k = 2;

    memoization sol;
    // Get minimum cost to reach the end
    cout << sol.solve(n, height, k) << endl;

    tabulation sol2;
    // Get minimum cost to reach the end using tabulation
    cout << sol2.solve(n, height, k) << endl;


    return 0;
}
