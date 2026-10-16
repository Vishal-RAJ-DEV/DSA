#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Memozation {
    static constexpr long long NEG = -(1LL << 60);
    vector<vector<long long>> dp;

    long long solve(int i, int rem, vector<int>& nums) {
        if (i == nums.size()) {
            return rem == 0 ? 0 : NEG;
        }
        if (dp[i][rem] != -1) return dp[i][rem];

        // Choice 1: Skip the current number.
        long long skip = solve(i + 1, rem, nums);

        // Choice 2: Pick the current number and update the remainder.
        int newRem = (rem + nums[i]) % 3;
        long long next = solve(i + 1, newRem, nums);
        long long pick = (next == NEG) ? NEG : nums[i] + next;

        return dp[i][rem] = max(pick, skip);
    }

public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        dp.assign(n, vector<long long>(3, -1));
        return (int)solve(0, 0, nums);
    }
};

class Tabulation {
    static constexpr long long NEG = -(1LL << 60);
    vector<vector<long long>> dp;

public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();

        dp.assign(n + 1, vector<long long>(3, NEG));

        // Base case: all elements have been processed.
        dp[n][0] = 0;
        dp[n][1] = NEG;
        dp[n][2] = NEG;

        // Fill the DP table from right to left.
        for (int i = n - 1; i >= 0; i--) {
            for (int rem = 0; rem < 3; rem++) {

                // Choice 1: Skip the current number.
                long long skip = dp[i + 1][rem];

                // Choice 2: Pick the current number.
                int newRem = (rem + nums[i]) % 3;
                long long next = dp[i + 1][newRem];

                long long pick = (next == NEG)
                                 ? NEG
                                 : nums[i] + next;

                // Same recurrence relation as memoization.
                dp[i][rem] = max(pick, skip);
            }
        }

        return (int)dp[0][0];
    }
};



class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        const long long NEG = -(1LL << 60);

        // dp[r] = maximum sum whose remainder is r.
        vector<long long> dp(3, NEG);
        dp[0] = 0; // An empty selection has sum 0.

        for (int x : nums) {
            // Start by skipping x, preserving all existing states.
            vector<long long> next = dp;

            // Try adding x to each previously achievable remainder.
            for (int r = 0; r < 3; r++) {
                if (dp[r] == NEG) continue;

                int newRem = (r + x) % 3;
                next[newRem] = max(next[newRem], dp[r] + x);
            }

            dp = next; // Move to the states after processing x.
        }

        return (int)dp[0]; // Largest sum divisible by 3.
    }
};




int main(){
    return 0;
}