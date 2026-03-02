#include <bits/stdc++.h>
using namespace std;


//time complexity : O(n) because we are traversing the height array once and for each index we are doing constant work
//space complexity : O(n) because we are using a dp array of size n to store
class MemoizationSolution {
public:
    // Solve function using recursion with memoization
    // ind -> current index the frog needs to reach
    // height -> vector of heights
    // dp -> memo table where dp[i] stores min cost to reach i
    int solve(int ind, const vector<int>& height, vector<int>& dp) {
        // If at the first stone, cost is 0
        if (ind == 0) return 0;

        // Return memoized result if already computed
        if (dp[ind] != -1) return dp[ind];

        // Initialize jumpTwo with a large value
        int jumpTwo = INT_MAX;

        // Compute cost when jumping from previous stone (ind - 1)
        int jumpOne = solve(ind - 1, height, dp) + abs(height[ind] - height[ind - 1]);

        // Compute cost when jumping from two stones back (ind - 2) if possible
        if (ind > 1) {
            jumpTwo = solve(ind - 2, height, dp) + abs(height[ind] - height[ind - 2]);
        }

        // Memoize and return the minimum of the two choices
        return dp[ind] = min(jumpOne, jumpTwo);
    }

    // Helper to handle edge cases and start recursion
    int frogJump(const vector<int>& height) {
        // Handle empty input
        if (height.empty()) return 0;

        // Prepare dp with -1 indicating uncomputed states
        int n = (int)height.size();
        vector<int> dp(n, -1);

        // Start from the last index
        return solve(n - 1, height, dp);
    }
};

//time complexity : O(n) because we are traversing the height array once and for each index we are doing constant work
//space complexity : O(n) because we are using a dp array of size n to store
class TabulationSolution {
public:
    // Computes minimum energy to reach last index using bottom-up DP
    int frogJump(const vector<int>& height) {
        // Handle empty input
        if (height.empty()) return 0;

        // Fetch size of the input
        int n = (int)height.size();

        // Create dp array where dp[i] = min energy to reach i
        vector<int> dp(n, INT_MAX);

        // Base case: cost to stand on first stone is zero
        dp[0] = 0;

        // Iterate over stones from index 1 to n-1
        for (int ind = 1; ind < n; ind++) {
            // Compute cost for a jump from ind-1
            int jumpOne = dp[ind - 1] + abs(height[ind] - height[ind - 1]);

            // Initialize jumpTwo with large value
            int jumpTwo = INT_MAX;

            // If possible, compute cost for a jump from ind-2
            if (ind > 1) {
                jumpTwo = dp[ind - 2] + abs(height[ind] - height[ind - 2]);
            }

            // Take the minimum of the two options
            dp[ind] = min(jumpOne, jumpTwo);
        }

        // Return min energy to reach last stone
        return dp[n - 1];
    }
};


//time complexity : O(n) because we are traversing the height array once and for each index we are doing constant work
//space complexity : O(1) because we are using only constant space to store the previous
class SpaceOptimizedSolution {
public:
    // Computes minimum energy to reach the last stone using O(1) space
    int frogJump(const vector<int>& height) {
        // Handle empty input
        if (height.empty()) return 0;

        // Fetch number of stones
        int n = (int)height.size();

        // Handle single stone case
        if (n == 1) return 0;

        // Initialize the cost to reach i-1 (prev) and i-2 (prev2)
        int prev = 0;
        int prev2 = 0;

        // Iterate through stones from index 1 to n-1
        for (int i = 1; i < n; i++) {
            // Initialize jumpTwo with large value
            int jumpTwo = INT_MAX;

            // Compute cost for jumping from i-1
            int jumpOne = prev + abs(height[i] - height[i - 1]);

            // If possible, compute cost for jumping from i-2
            if (i > 1) {
                jumpTwo = prev2 + abs(height[i] - height[i - 2]);
            }

            // Determine minimal cost to reach current stone
            int cur_i = min(jumpOne, jumpTwo);

            // Shift window: update prev2 and prev
            prev2 = prev;
            prev = cur_i;
        }

        // Return minimal cost to reach last stone
        return prev;
    }
};


int main() {
    // Define the heights array
    vector<int> height{30, 10, 60, 10, 60, 50};

    // Create MemoizationSolution instance
    MemoizationSolution memoSol;
    // Create TabulationSolution instance
    TabulationSolution tabSol;
    // Create SpaceOptimizedSolution instance
    SpaceOptimizedSolution spaceOptSol;

    // Compute and print the minimum energy
    cout << memoSol.frogJump(height) << endl; // Expected: 40
    cout << tabSol.frogJump(height) << endl;  // Expected: 40
    cout << spaceOptSol.frogJump(height) << endl;  // Expected: 40

    return 0;
}
