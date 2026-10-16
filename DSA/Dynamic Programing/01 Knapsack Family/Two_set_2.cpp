#include <bits/stdc++.h>
using namespace std;

class Memoization {
public:
    const int MOD = 1e9 + 7;
    vector<vector<long long>> dp;

    long long subsetSumUtil(int ind, int target) {
        if (target == 0) return 1;
        if (ind == 0) return 0;

        if (dp[ind][target] != -1)
            return dp[ind][target];

        long long notTaken = subsetSumUtil(ind - 1, target);
        long long taken = 0;

        if (ind <= target)
            taken = subsetSumUtil(ind - 1, target - ind);

        return dp[ind][target] = (notTaken + taken) % MOD;
    }

    long long Partition(int n) {
        long long totSum = 1LL * n * (n + 1) / 2;

        if (totSum % 2 != 0)
            return 0;

        int target = totSum / 2;

        dp.assign(n + 1, vector<long long>(target + 1, -1));

        long long ways = subsetSumUtil(n, target);

        // Divide by 2 using modular inverse
        return ways * 500000004LL % MOD;
    }
};


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int MOD = 1e9 + 7;

    long long Partition(int n) {
        long long totSum = 1LL * n * (n + 1) / 2;

        if (totSum % 2 != 0)
            return 0;

        int target = totSum / 2;

        vector<vector<long long>> dp(n + 1, vector<long long>(target + 1, 0));

        // Base case: one way to make sum 0
        for (int i = 0; i <= n; i++)
            dp[i][0] = 1;

        // Build the DP table
        for (int ind = 1; ind <= n; ind++) {
            for (int sum = 0; sum <= target; sum++) {
                long long notTaken = dp[ind - 1][sum];
                long long taken = 0;

                if (ind <= sum)
                    taken = dp[ind - 1][sum - ind];

                dp[ind][sum] = (notTaken + taken) % MOD;
            }
        }

        long long ways = dp[n][target];

        // Divide by 2 using modular inverse
        return ways * 500000004LL % MOD;
    }
};

int main(){
    int n;
    cin>>n;
    
    Memoization obj;
    long long ans = obj.Partition(n);
    cout<<ans<<endl;

    return 0;
}