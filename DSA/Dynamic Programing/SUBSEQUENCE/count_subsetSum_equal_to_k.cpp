#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
        Count how many subsets of arr have sum exactly equal to target.

    Core DP idea:
        For every index idx and every sum target, we ask:

            How many subsets can be formed from arr[0...idx]
            whose sum is exactly target?

        For each element arr[idx], we have two choices:

            1. Do not take arr[idx]
               Count remains the same target:
                   solve(idx - 1, target)

            2. Take arr[idx]
               Then arr[idx] contributes to the sum, so the remaining
               sum must be:
                   target - arr[idx]
               Count becomes:
                   solve(idx - 1, target - arr[idx])

        Final answer:
            take + notTake

    Important zero case:
        Zero is special because it does not change the sum.

        Example:
            arr[0] = 0, target = 0

        Possible subsets using only arr[0]:
            {}      -> sum 0
            {0}     -> sum 0

        So the answer is 2, not 1.
*/

// Approach 1: Recursion + Memoization
class Solution {
  public:

    int solve(int idx, int target, vector<int>& arr, vector<vector<int>>& dp) {
        /*
            Base case:
                When idx == 0, only one element is available: arr[0].

            We need to count how many subsets from this one element can make
            the required target.

            Case 1:
                target == 0 and arr[0] == 0

                There are two valid subsets:
                    {}      -> sum 0
                    {0}     -> sum 0

                So return 2.

            Case 2:
                target == 0

                Empty subset {} makes sum 0.
                So return 1.

            Case 3:
                arr[0] == target

                Subset {arr[0]} makes the target.
                So return 1.

            Case 4:
                None of the above is true.
                No subset can make the target.
                So return 0.
        */
        if (idx == 0) {
            if (target == 0 && arr[0] == 0) return 2;
            if (target == 0 || arr[0] == target) return 1;
            return 0;
        }

        if (dp[idx][target] != -1) return dp[idx][target];

        // Choice 1: Do not include arr[idx].
        int notTake = solve(idx - 1, target, arr, dp);

        // Choice 2: Include arr[idx], only if it does not exceed target.
        int take = 0;
        if (arr[idx] <= target) {
            take = solve(idx - 1, target - arr[idx], arr, dp);
        }

        return dp[idx][target] = take + notTake;
    }

    int perfectSum(vector<int>& arr, int target) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));

        return solve(n - 1, target, arr, dp);
    }
};

// Approach 2: Tabulation
class Solution {
public:

    int perfectSum(vector<int>& arr, int target) {
        int n = arr.size();

        /*
            dp[idx][sum] means:
                Number of subsets from arr[0...idx] whose sum is exactly sum.
        */
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));

        /*
            Converting recursion base case into tabulation initialization:

            In recursion, the base case was:

                if idx == 0:
                    if target == 0 and arr[0] == 0 -> return 2
                    if target == 0 or arr[0] == target -> return 1
                    otherwise -> return 0

            In tabulation, idx == 0 means the first row:

                dp[0][sum]

            This row stores answers using only arr[0].
        */

        /*
            Base case conversion 1:
                If arr[0] == 0, then dp[0][0] = 2.

            Why?
                Using only arr[0] = 0, sum 0 can be formed in two ways:
                    {} and {0}
        */
        if (arr[0] == 0)
            dp[0][0] = 2;

        /*
            Base case conversion 2:
                If arr[0] != 0, then dp[0][0] = 1.

            Why?
                Sum 0 can be formed only by taking the empty subset {}.
                We cannot take arr[0], because arr[0] is non-zero.
        */
        else
            dp[0][0] = 1;

        /*
            Base case conversion 3:
                If arr[0] is not zero and arr[0] <= target,
                then dp[0][arr[0]] = 1.

            Why?
                Using only the first element, the subset {arr[0]} forms
                sum arr[0] exactly once.

            Why arr[0] != 0 is checked?
                If arr[0] == 0, dp[0][0] is already 2 because both {} and {0}
                are valid. Setting it to 1 again would destroy that answer.
        */
        if (arr[0] != 0 && arr[0] <= target)
            dp[0][arr[0]] = 1;

        /*
            Fill the remaining rows.

            For each idx and sum:
                notTake = number of subsets that make sum without arr[idx]
                take    = number of subsets that make sum after taking arr[idx]

            Total ways:
                dp[idx][sum] = take + notTake
        */
        for (int idx = 1; idx < n; idx++) {
            for (int sum = 0; sum <= target; sum++) {
                int notTake = dp[idx - 1][sum];

                int take = 0;
                if (arr[idx] <= sum)
                    take = dp[idx - 1][sum - arr[idx]];

                dp[idx][sum] = take + notTake;
            }
        }

        return dp[n - 1][target];
    }
};

// Approach 3: Space Optimization
class Solution {
public:

    int perfectSum(vector<int>& arr, int target) {
        int n = arr.size();

        /*
            We only need the previous row to calculate the current row.

            prev[sum] means:
                Number of subsets from the processed previous elements
                whose sum is exactly sum.
        */
        vector<int> prev(target + 1, 0);

        /*
            Same base case conversion as tabulation, but instead of filling
            dp[0][sum], we fill prev[sum].

            prev represents row 0 at the beginning.
        */
        if (arr[0] == 0)
            prev[0] = 2;
        else
            prev[0] = 1;

        if (arr[0] != 0 && arr[0] <= target)
            prev[arr[0]] = 1;

        for (int idx = 1; idx < n; idx++) {
            vector<int> curr(target + 1, 0);

            for (int sum = 0; sum <= target; sum++) {
                int notTake = prev[sum];

                int take = 0;
                if (arr[idx] <= sum)
                    take = prev[sum - arr[idx]];

                curr[sum] = take + notTake;
            }

            prev = curr;
        }

        return prev[target];
    }
};

int main() {
    return 0;
}
