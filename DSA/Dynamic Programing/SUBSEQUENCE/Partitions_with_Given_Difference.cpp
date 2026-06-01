#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
        Count the number of ways to split the array into two groups such that
        the difference between their sums is equal to diff.

    Main logic:
        Let the first group sum be S1.
        Let the second group sum be S2.

        We need:
            S1 - S2 = diff

        We also know:
            S1 + S2 = totalSum

        Add both equations:

            S1 - S2 = diff
            S1 + S2 = totalSum
            -------------------
            2 * S1 = diff + totalSum

        So:
            S1 = (diff + totalSum) / 2

        This means the partition problem is converted into:

            Count subsets whose sum is S1.

        Required target:
            target = (diff + totalSum) / 2

    Before applying DP, check impossible cases:

        1. If diff > totalSum:
               Difference cannot be bigger than the total sum.
               So no valid partition is possible.

        2. If (diff + totalSum) is odd:
               target = (diff + totalSum) / 2 will not be an integer.
               Since subset sum must be an integer, no valid partition exists.

    After these checks:
        The problem becomes exactly the same as:

            Count Subsets with Sum K

        where:
            K = target
*/

class Solution {
  public:
    int solve(int idx, int target, vector<int>& arr, vector<vector<int>>& dp) {
        /*
            Base case:
                When idx == 0, only arr[0] is available.

            If target == 0 and arr[0] == 0:
                There are two subsets:
                    {} and {0}
                Both have sum 0, so return 2.

            If target == 0:
                Empty subset {} makes sum 0, so return 1.

            If arr[0] == target:
                Subset {arr[0]} makes the target, so return 1.

            Otherwise:
                No subset can make target, so return 0.
        */
        if (idx == 0) {
            if (target == 0 && arr[0] == 0) return 2;
            if (target == 0 || arr[0] == target) return 1;
            return 0;
        }

        if (dp[idx][target] != -1) return dp[idx][target];

        // Do not include arr[idx] in the subset.
        int notTake = solve(idx - 1, target, arr, dp);

        // Include arr[idx] only when it is not greater than target.
        int take = 0;
        if (arr[idx] <= target) {
            take = solve(idx - 1, target - arr[idx], arr, dp);
        }

        return dp[idx][target] = take + notTake;
    }

    int countPartitions(vector<int>& arr, int diff) {
        int n = arr.size();
        int totalSum = accumulate(arr.begin(), arr.end(), 0);

        // Impossible: required difference cannot be bigger than total sum.
        if (diff > totalSum) return 0;

        // Impossible: S1 = (diff + totalSum) / 2 must be an integer.
        if ((totalSum + diff) % 2 != 0) return 0;

        int target = (diff + totalSum) / 2;

        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        return solve(n - 1, target, arr, dp);
    }
};

class Tabulation {
  public:
    int countPartitions(vector<int>& arr, int diff) {
        int n = arr.size();
        int totalSum = accumulate(arr.begin(), arr.end(), 0);

        /*
            We convert the partition problem into subset count:

                S1 - S2 = diff
                S1 + S2 = totalSum

            Adding them:
                2 * S1 = diff + totalSum

            So:
                target = S1 = (diff + totalSum) / 2

            Now we count subsets whose sum is target.
        */
        if (diff > totalSum) return 0;
        if ((totalSum + diff) % 2 != 0) return 0;

        int target = (diff + totalSum) / 2;

        /*
            dp[idx][sum] means:
                Number of subsets from arr[0...idx] whose sum is exactly sum.
        */
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));

        /*
            Base case initialization:

            This is the tabulation form of the recursion base case idx == 0.
            At idx = 0, only arr[0] is available.

            Case 1:
                arr[0] == 0

                Sum 0 can be formed in two ways:
                    {} and {0}

                So:
                    dp[0][0] = 2

            Case 2:
                arr[0] != 0

                Sum 0 can be formed only by empty subset:
                    {}

                So:
                    dp[0][0] = 1
        */
        if (arr[0] == 0)
            dp[0][0] = 2;
        else
            dp[0][0] = 1;

        /*
            If arr[0] is non-zero and arr[0] <= target:
                Subset {arr[0]} forms sum arr[0].

            So:
                dp[0][arr[0]] = 1

            We check arr[0] != 0 because if arr[0] is 0, then dp[0][0]
            must remain 2, not become 1.
        */
        if (arr[0] != 0 && arr[0] <= target)
            dp[0][arr[0]] = 1;

        /*
            Fill the DP table.

            For every arr[idx], we have two choices:

                notTake:
                    Do not include arr[idx].
                    The required sum stays the same.

                take:
                    Include arr[idx].
                    The remaining sum becomes sum - arr[idx].

            Total ways:
                dp[idx][sum] = notTake + take
        */
        for (int idx = 1; idx < n; idx++) {
            for (int sum = 0; sum <= target; sum++) {
                int notTake = dp[idx - 1][sum];

                int take = 0;
                if (arr[idx] <= sum) {
                    take = dp[idx - 1][sum - arr[idx]];
                }

                dp[idx][sum] = take + notTake;
            }
        }

        return dp[n - 1][target];
    }
};

class SpaceOptimization {
  public:
    int countPartitions(vector<int>& arr, int diff) {
        int n = arr.size();
        int totalSum = accumulate(arr.begin(), arr.end(), 0);

        /*
            Same conversion:

                S1 - S2 = diff
                S1 + S2 = totalSum

            Therefore:
                S1 = (diff + totalSum) / 2

            Count subsets whose sum is S1.
        */
        if (diff > totalSum) return 0;
        if ((totalSum + diff) % 2 != 0) return 0;

        int target = (diff + totalSum) / 2;

        /*
            In tabulation, every row depends only on the previous row.

            So instead of storing:
                dp[n][target + 1]

            We store only:
                prev[target + 1]
                curr[target + 1]

            prev[sum] means:
                Number of subsets from previous processed elements
                whose sum is exactly sum.
        */
        vector<int> prev(target + 1, 0);

        /*
            Base case for row 0:
                prev represents dp[0].

            If arr[0] == 0:
                prev[0] = 2 because {} and {0} both make sum 0.

            Else:
                prev[0] = 1 because only {} makes sum 0.
        */
        if (arr[0] == 0)
            prev[0] = 2;
        else
            prev[0] = 1;

        /*
            If arr[0] is non-zero, subset {arr[0]} makes sum arr[0].
        */
        if (arr[0] != 0 && arr[0] <= target)
            prev[arr[0]] = 1;

        /*
            Build each next row using only the previous row.
        */
        for (int idx = 1; idx < n; idx++) {
            vector<int> curr(target + 1, 0);

            for (int sum = 0; sum <= target; sum++) {
                int notTake = prev[sum];

                int take = 0;
                if (arr[idx] <= sum) {
                    take = prev[sum - arr[idx]];
                }

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
