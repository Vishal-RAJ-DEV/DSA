#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:

    const int MOD = 1e9 + 7;

    int solve(int dice, int target, int k,
              vector<vector<int>>& dp) {

        // No dice left
        if (dice == 0) {
            return target == 0;
        }

        // Impossible target
        if (target < 0) {
            return 0;
        }

        // Already calculated
        if (dp[dice][target] != -1) {
            return dp[dice][target];
        }

        long long ways = 0;

        // Try every possible face of current die
        for (int face = 1; face <= k; face++) {

            ways += solve(
                dice - 1,
                target - face,
                k,
                dp
            );

            ways %= MOD;
        }

        return dp[dice][target] = ways;
    }


    int numRollsToTarget(int n, int k, int target) {

        vector<vector<int>> dp(
            n + 1,
            vector<int>(target + 1, -1)
        );

        return solve(n, target, k, dp);
    }
};


class Solution {
public:

    int numRollsToTarget(int n, int k, int target) {

        const int MOD = 1e9 + 7;

        vector<vector<int>> dp(
            n + 1,
            vector<int>(target + 1, 0)
        );

        // Base case:
        // 0 dice -> sum 0 has exactly 1 way
        dp[0][0] = 1;

        // Number of dice
        for (int dice = 1; dice <= n; dice++) {

            // Target sum
            for (int sum = 1; sum <= target; sum++) {

                // Value of current/last die
                for (int face = 1; face <= k; face++) {

                    if (sum - face >= 0) {

                        dp[dice][sum] =
                            (dp[dice][sum]
                            + dp[dice - 1][sum - face])
                            % MOD;
                    }
                }
            }
        }

        return dp[n][target];
    }
};


int main(){
    return 0;
}