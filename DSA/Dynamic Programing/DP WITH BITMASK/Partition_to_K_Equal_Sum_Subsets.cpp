#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution 
{
public: 

    bool canPartitionKSubsets(vector<int>& nums, int k) 
    {
        int n = nums.size(); 

        // Calculate total sum
        int sum = 0; 

        for(int x : nums) 
        {
            sum += x; 
        }

        // Equal partition is impossible
        if(sum % k != 0) 
        {
            return false; 
        }

        // Every bucket must have this sum
        int target = sum / k; 

        // dp[mask] = current sum of the bucket
        // -1 means this state cannot be reached
        vector<int> dp(1 << n, -1); 

        // No elements used
        // Current bucket sum = 0
        dp[0] = 0; 

        // Try every subset
        for(int mask = 0; mask < (1 << n); mask++) 
        {
            // Skip unreachable states
            if(dp[mask] == -1) 
            {
                continue; 
            }

            // Try adding every unused number
            for(int i = 0; i < n; i++) 
            {
                // nums[i] is already used
                if(mask & (1 << i)) 
                {
                    continue; 
                }

                // Add nums[i] to current bucket
                int newSum = dp[mask] + nums[i]; 

                // Bucket cannot exceed target
                if(newSum > target) 
                {
                    continue; 
                }

                // Mark nums[i] as used
                int newMask = mask | (1 << i); 

                // If bucket becomes target,
                // modulo makes it 0 and starts next bucket
                dp[newMask] = newSum % target; 
            }
        }

        // All elements must be used
        // and the final bucket must also be complete
        return dp[(1 << n) - 1] == 0; 
    }
};



int main(){
    return 0;
}