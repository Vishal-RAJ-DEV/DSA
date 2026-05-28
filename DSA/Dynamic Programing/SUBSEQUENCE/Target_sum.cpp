#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
        Problem Intuition:
        For every number in nums, we have exactly two choices:
        1. Put a '+' sign before it.
        2. Put a '-' sign before it.

        Example:
        nums = [1, 1, 1], target = 1

        Some possible expressions:
        +1 +1 -1 = 1
        +1 -1 +1 = 1
        -1 +1 +1 = 1

        We need to count how many different sign combinations can make target.

        What does idx mean?
        idx tells us which element we are deciding right now.

        If idx = 0, we are deciding sign for nums[0].
        If idx = 1, we are deciding sign for nums[1].
        If idx = 2, we are deciding sign for nums[2].

        Every recursive call moves to idx + 1 because after choosing '+' or '-'
        for the current number, we go to the next number.

        What does sum mean?
        sum stores the current value made by all signs chosen so far.

        Example:
        nums = [1, 2, 3]

        If we choose:
        +1, then sum = 1
        +1 -2, then sum = -1
        +1 -2 +3, then sum = 2

        Why totalSum is taken?
        The current sum can become negative also.

        Example:
        nums = [1, 2, 3]
        totalSum = 1 + 2 + 3 = 6

        Minimum possible sum = -6, when we take every number as negative.
        Maximum possible sum =  6, when we take every number as positive.

        So possible sums are from -totalSum to +totalSum.

        But array indexes cannot be negative.
        We cannot write dp[idx][-3].

        That is why we shift every sum by totalSum:
        real sum = -6  -> dp index = -6 + 6 = 0
        real sum =  0  -> dp index =  0 + 6 = 6
        real sum =  6  -> dp index =  6 + 6 = 12

        So dp[idx][sum + totalSum] safely stores negative and positive sums.
    */
    int solve( vector<int>&nums , int & target , int idx , int sum ,vector<vector<int>>&dp , int& totalsum){
        //base case 
        // If idx reached nums.size(), it means we have assigned signs
        // to all numbers. Now we check whether the final sum is target.
        if( sum == target && idx == nums.size()) return 1;

        // If all elements are used but sum is not target, this path is invalid.
        if( idx >= nums.size()) return 0;

        //return overlapping subproblem 
        // sum can be negative, so we use sum + totalsum as the valid DP index.
        if( dp[idx][ sum + totalsum] != -1) return dp[idx][sum + totalsum];

        // Choice 1: Put '+' before nums[idx].
        // Then current sum increases by nums[idx].
        int postive = solve(nums , target , idx + 1 , sum + nums[idx] , dp , totalsum);

        // Choice 2: Put '-' before nums[idx].
        // Then current sum decreases by nums[idx].
        int negative = solve( nums, target , idx + 1 , sum - nums[idx] , dp , totalsum);

        // Total ways from this state = ways from positive choice + negative choice.
        return dp[idx][sum + totalsum] = postive + negative;
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int totalsum = 0;
        //get the total sum of the nums 
        for( int i =0 ; i < n ; i++){
            totalsum += nums[i];
        }
        //here size is 2* totalsum + 1 beacuse if we take negative value -5 then -5+5 = 0th index 
        // and at 5+5 = 10th index , so total size is 2*5+1 = 11 size elements 
        // DP columns represent all possible sums from -totalsum to +totalsum.
        // Since that range has 2 * totalsum + 1 values, this is the required size.
        vector<vector<int>>dp(nums.size() , vector<int>( 2*totalsum + 1, -1));

        // Start from index 0 with current sum 0 because no number has been used yet.
        return solve( nums , target , 0 , 0 , dp , totalsum);
    }
};
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {

        int n = nums.size();

        int totalSum = 0;

        for(int num : nums) {
            totalSum += num;
        }

        /*
            Tabulation Intuition:

            dp[i][sum + totalSum] means:
            using the first i elements, how many ways can we create "sum"?

            Here i is not the actual array index.
            i means "how many elements have been processed".

            i = 0 means no elements are used.
            i = 1 means nums[0] is used.
            i = 2 means nums[0] and nums[1] are used.

            That is why the current element is nums[i - 1].

            Why totalSum is used again?
            Because sum can be negative, but vector index cannot be negative.
            So we store sum at index sum + totalSum.

            Example:
            totalSum = 5

            sum = -5 is stored at index 0.
            sum =  0 is stored at index 5.
            sum =  5 is stored at index 10.
        */

        // Edge case:
        // target outside possible range

        if(abs(target) > totalSum)
            return 0;

        int range = 2 * totalSum + 1;

        // dp[i][sum + totalSum]
        // = number of ways to reach 'sum'
        // using first i elements

        vector<vector<int>> dp(n + 1,
                               vector<int>(range, 0));

        // Base Case:
        // Using 0 elements,
        // only sum 0 is possible in 1 way

        // sum 0 is stored at index 0 + totalSum.
        dp[0][totalSum] = 1;

        // Process elements one by one

        for(int i = 1; i <= n; i++) {

            // Since i means first i elements, the new element added now is nums[i - 1].
            int curr = nums[i - 1];

            for(int sum = -totalSum;
                sum <= totalSum;
                sum++) {

                int ways =
                    dp[i - 1][sum + totalSum];

                if(ways > 0) {

                    // Positive sign

                    // If old sum was "sum", then adding +curr makes sum + curr.
                    int positiveSum = sum + curr;

                    dp[i][positiveSum + totalSum]
                        += ways;

                    // Negative sign

                    // If old sum was "sum", then adding -curr makes sum - curr.
                    int negativeSum = sum - curr;

                    dp[i][negativeSum + totalSum]
                        += ways;
                }
            }
        }

        return dp[n][target + totalSum];
    }
};

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {

        int n = nums.size();

        int totalSum = 0;

        for(int num : nums) {
            totalSum += num;
        }

        // If target is outside possible range

        if(abs(target) > totalSum)
            return 0;

        int range = 2 * totalSum + 1;

        /*
            Space Optimization Intuition:

            In tabulation, dp[i] depends only on dp[i - 1].
            So instead of storing the full 2D table, we keep only one previous row.

            prev[sum + totalSum] means:
            before processing the current number, how many ways can we make "sum"?

            curr[sum + totalSum] means:
            after processing the current number, how many ways can we make "sum"?

            The index shift using totalSum is still needed because sums can be negative.
        */

        // prev[sum + totalSum]
        // = number of ways to make 'sum'

        vector<int> prev(range, 0);

        // Base case:
        // Sum 0 possible in 1 way

        prev[totalSum] = 1;

        for(int i = 0; i < n; i++) {

            vector<int> curr(range, 0);

            // Try every sum that was possible before using nums[i].
            for(int sum = -totalSum;
                sum <= totalSum;
                sum++) {

                int ways =
                    prev[sum + totalSum];

                if(ways > 0) {

                    // Take positive sign

                    // Put '+' before nums[i].
                    int positiveSum =
                        sum + nums[i];

                    curr[positiveSum + totalSum]
                        += ways;

                    // Take negative sign

                    // Put '-' before nums[i].
                    int negativeSum =
                        sum - nums[i];

                    curr[negativeSum + totalSum]
                        += ways;
                }
            }

            // Current row becomes previous row for the next element.
            prev = curr;
        }

        return prev[target + totalSum];
    }
};

int main(){
    Solution sol;
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    cout << sol.findTargetSumWays(nums, target) << endl;
    return 0;
}
