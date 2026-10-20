#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int solve(int i,
              int target,
              vector<int>& stones,
              vector<vector<int>>& memo) {

        // No stones left
        if (i == stones.size()) {
            return 0;
        }

        // Already calculated
        if (memo[i][target] != -1) {
            return memo[i][target];
        }

        // Option 1: Don't take current stone
        int notTake = solve(
            i + 1,
            target,
            stones,
            memo
        );

        // Option 2: Take current stone
        int take = 0;

        if (stones[i] <= target) {
            take = stones[i] + solve(
                i + 1,
                target - stones[i],
                stones,
                memo
            );
        }

        return memo[i][target] = max(take, notTake);
    }

    int lastStoneWeightII(vector<int>& stones) {

        int total = 0;

        for (int x : stones) {
            total += x;
        }

        int target = total / 2;

        vector<vector<int>> memo(
            stones.size(),
            vector<int>(target + 1, -1)
        );

        int S2 = solve(
            0,
            target,
            stones,
            memo
        );

        return total - 2 * S2;
    }
};



class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {

        int n = stones.size();

        // 1. Calculate total sum
        int total = 0;
        for (int x : stones) {
            total += x;
        }

        // We only need subset sums up to total / 2
        int target = total / 2;

        // dp[i][j] =
        // maximum subset sum <= j
        // using first i stones
        vector<vector<int>> dp(
            n + 1,
            vector<int>(target + 1, 0)
        );

        // 2. 0/1 Knapsack
        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= target; j++) {

                // Don't take current stone
                dp[i][j] = dp[i - 1][j];

                // Take current stone if possible
                if (stones[i - 1] <= j) {

                    dp[i][j] = max(
                        dp[i][j],
                        dp[i - 1][j - stones[i - 1]]
                        + stones[i - 1]
                    );
                }
            }
        }

        // dp[n][target] = largest subset sum <= total/2
        int S2 = dp[n][target];

        // Answer = total - 2*S2
        return total - 2 * S2;
    }
};



class MemoizationVersion {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int total = accumulate(stones.begin(), stones.end(), 0);
        int target = total / 2;
        int n = stones.size();

        vector<vector<int>> dp(n, vector<int>(target + 1, -1));

        int S2 = findMaxSum(stones, n - 1, target, dp);

        return total - 2 * S2;
    }

private:
    int findMaxSum(vector<int>& stones, int ind, int target,
                   vector<vector<int>>& dp) {
        // Base case: only the first stone is available
        if (ind == 0) {
            if (stones[0] <= target) return stones[0];
            return 0;
        }

        // Return previously calculated result
        if (dp[ind][target] != -1) {
            return dp[ind][target];
        }

        // Do not pick the current stone
        int notPick = findMaxSum(stones, ind - 1, target, dp);

        // Pick the current stone if possible
        int pick = 0;
        if (stones[ind] <= target) {
            pick = stones[ind] +
                   findMaxSum(stones, ind - 1, target - stones[ind], dp);
        }

        // Store the maximum achievable sum
        return dp[ind][target] = max(pick, notPick);
    }
};




int main(){
    return 0;
}