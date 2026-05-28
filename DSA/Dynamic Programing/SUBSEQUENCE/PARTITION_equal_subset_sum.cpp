#include <bits/stdc++.h>
using namespace std;

/*
    Main Logic / Intuition:

    We need to check whether the array can be divided into two subsets
    such that both subsets have equal sum.

    Suppose:
    subset1 sum = S1
    subset2 sum = S2

    For equal partition:
    S1 == S2

    Also, all elements are used in either subset1 or subset2, so:
    S1 + S2 = totalSum

    Since S1 and S2 are equal:
    S1 + S1 = totalSum
    2 * S1 = totalSum
    S1 = totalSum / 2

    That means the problem becomes:
    Can we find any subset whose sum is totalSum / 2?

    If yes:
    The remaining elements will automatically also have sum totalSum / 2,
    because totalSum - totalSum / 2 = totalSum / 2.

    Example:
    arr = [2, 3, 3, 4]
    totalSum = 12
    half = 6

    If we find subset [2, 4] with sum 6,
    then remaining subset [3, 3] also has sum 6.
    So equal partition is possible.

    Why odd total sum is impossible?
    If totalSum is odd, it cannot be divided into two equal integer sums.

    Example:
    totalSum = 11
    half = 5.5

    We cannot make two subsets with sum 5.5 using integer array elements.
    So we directly return false.
*/

class Memoization
{
public:
    /*
        Time Complexity: O(n * k)
        Here n = number of elements, and k = totalSum / 2.

        Reason:
        The DP state is dp[ind][target].
        ind can have n values, and target can have k + 1 values.
        So at most n * k unique states are solved.

        Space Complexity: O(n * k) + O(n)
        O(n * k) is for the DP table.
        O(n) is for the recursion stack.
    */

    // Function to check if it's possible to partition the array into two subsets with equal sum
    bool subsetSumUtil(int ind, int target, vector<int> &arr, vector<vector<int>> &dp)
    {
        // Base case: If the target sum is 0, we found a valid partition
        if (target == 0)
            return true;

        // Base case: If we have considered all elements and the target is still not 0, return false
        if (ind == 0)
            return arr[0] == target;

        // If the result for this state is already calculated, return it
        if (dp[ind][target] != -1)
            return dp[ind][target];

        // Recursive cases
        // 1. Exclude the current element
        bool notTaken = subsetSumUtil(ind - 1, target, arr, dp);

        // 2. Include the current element if it doesn't exceed the target
        bool taken = false;
        if (arr[ind] <= target)
            taken = subsetSumUtil(ind - 1, target - arr[ind], arr, dp);

        // Store the result in the DP table and return
        return dp[ind][target] = notTaken || taken;
    }

    // Function to check if the array can be partitioned into two equal subsets
    bool canPartition(int n, vector<int> &arr)
    {
        int totSum = 0;

        // Calculate the total sum of the array
        for (int i = 0; i < n; i++)
        {
            totSum += arr[i];
        }

        // If the total sum is odd, it cannot be partitioned into two equal subsets
        if (totSum % 2 == 1)
            return false;
        else
        {
            int k = totSum / 2;

            // Create a DP table with dimensions n x k+1 and initialize with -1
            vector<vector<int>> dp(n, vector<int>(k + 1, -1));

            // Call the subsetSumUtil function to check if it's possible to partition
            return subsetSumUtil(n - 1, k, arr, dp);
        }
    }
};

class Solution
{
public:
    /*
        Time Complexity: O(n * targetSum)
        targetSum = totalSum / 2.

        Reason:
        We fill a DP table of size n x (targetSum + 1).
        For every index, we try every possible target from 1 to targetSum.

        Space Complexity: O(n * targetSum)
        Reason:
        We store the full 2D DP table.
    */

    // Determines if the given array can be split into two subsets
    // whose sums are equal using a tabulation DP approach
    bool canPartition(int n, vector<int> &arr)
    {

        // Step 1: Calculate the total sum
        int totalSum = 0;
        for (int i = 0; i < n; i++)
        {
            totalSum += arr[i];
        }

        // Step 2: If total sum is odd, partition is impossible
        if (totalSum % 2 != 0)
        {
            return false;
        }

        // Step 3: Determine the target sum for each subset
        int targetSum = totalSum / 2;

        // Step 4: Create DP table and initialize
        vector<vector<bool>> dp(n, vector<bool>(targetSum + 1, false));

        // Step 5: Base case: sum 0 is always possible
        for (int i = 0; i < n; i++)
        {
            dp[i][0] = true;
        }

        // Step 6: Initialize first row
        if (arr[0] <= targetSum)
        {
            dp[0][arr[0]] = true;
        }

        // Step 7: Fill DP table
        for (int index = 1; index < n; index++)
        {
            for (int target = 1; target <= targetSum; target++)
            {
                bool notTaken = dp[index - 1][target];
                bool taken = false;
                if (arr[index] <= target)
                {
                    taken = dp[index - 1][target - arr[index]];
                }
                dp[index][target] = notTaken || taken;
            }
        }

        // Step 8: Return result
        return dp[n - 1][targetSum];
    }
};

class SpaceOptimized
{
public:
    /*
        Time Complexity: O(n * k)
        Here k = totalSum / 2.

        Reason:
        We still process every element and every target from 1 to k.
        Space optimization reduces memory, not the number of calculations.

        Space Complexity: O(k)
        Reason:
        Instead of storing the full n x k DP table, we only store:
        prev row and current row.
    */

    // Function to check if it's possible to partition the array into two subsets with equal sum
    bool canPartition(int n, vector<int> &arr)
    {
        int totSum = 0;

        // Calculate the total sum of the array
        for (int i = 0; i < n; i++)
        {
            totSum += arr[i];
        }

        // If the total sum is odd, it cannot be partitioned into two equal subsets
        if (totSum % 2 == 1)
            return false;
        else
        {
            int k = totSum / 2;

            // Create a vector to represent the previous row of the DP table
            vector<bool> prev(k + 1, false);

            // Base case: If the target sum is 0, it can be achieved by not selecting any elements
            prev[0] = true;

            // Initialize the first row based on the first element of the array
            if (arr[0] <= k)
                prev[arr[0]] = true;

            // Fill in the DP table using a bottom-up approach
            for (int ind = 1; ind < n; ind++)
            {
                // Create a vector to represent the current row of the DP table
                vector<bool> cur(k + 1, false);
                cur[0] = true;

                for (int target = 1; target <= k; target++)
                {
                    // Exclude the current element
                    bool notTaken = prev[target];

                    // Include the current element if it doesn't exceed the target
                    bool taken = false;
                    if (arr[ind] <= target)
                        taken = prev[target - arr[ind]];

                    // Update the current row of the DP table
                    cur[target] = notTaken || taken;
                }

                // Set the current row as the previous row for the next iteration
                prev = cur;
            }

            // The final result is in the last cell of the previous row of the DP table
            return prev[k];
        }
    }
};

int main()
{
    vector<int> arr = {2, 3, 3, 3, 4, 5};
    int n = arr.size();

    Solution solution;
    if (solution.canPartition(n, arr))
        cout << "The Array can be partitioned into two equal subsets";
    else
        cout << "The Array cannot be partitioned into two equal subsets";

    return 0;
}
