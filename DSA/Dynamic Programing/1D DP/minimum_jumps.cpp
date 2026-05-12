#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//  Bottom-Up DP + Tabulation Approach
class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();
        // dp array to store max jumps till index i
        vector<int> dp(n, -1);

        // First index is reachable with 0 jumps
        dp[0]=0;

        for(int i=1; i<n; i++) {
            for(int j=0; j<i; j++) {
                // Check if the condition holds true and prev index was visited
                if(abs(nums[i]-nums[j]) <= target && dp[j]>-1) {
                    dp[i] = max(dp[i], 1+dp[j]);
                }
            }
        }

        return dp[n-1];
    }
};


//  Top-Down DP + Memoization Approach

class Solution {
public:
    int n;

    // Recursive function to find maximum jumps from index i
    int solve(int i, vector<int>& nums, int target, vector<int>& dp) {

        // If we reach last index, no more jumps needed
        if(i == n - 1)
            return 0;

        // Return already computed result
        if(dp[i] != -2)
            return dp[i];

        int ans = -1;

        // Try all possible next jumps
        for(int j = i + 1; j < n; j++) {

            // Check jump condition
            if(abs(nums[j] - nums[i]) <= target) {

                int temp = solve(j, nums, target, dp);

                // Update maximum jumps
                if(temp != -1) {
                    ans = max(ans, 1 + temp);
                }
            }
        }

        // Store and return answer
        return dp[i] = ans;
    }

    int maximumJumps(vector<int>& nums, int target) {

        n = nums.size();

        // -2 means not calculated yet
        vector<int> dp(n, -2);

        return solve(0, nums, target, dp);
    }
};


int main(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int target;
    cin >> target;
    Solution sol;
    cout << sol.maximumJumps(nums, target) << endl;
    return 0;
}
