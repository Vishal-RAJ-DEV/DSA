#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
                    MAIN LOGIC
===========================================================

We need to count all CONTIGUOUS subarrays having at least
3 elements where every consecutive difference is equal.

Example:

    nums = [1,2,3,4]

Arithmetic subarrays are:

    [1,2,3]
    [2,3,4]
    [1,2,3,4]

Answer = 3


---------------------- DP DEFINITION ----------------------

The most important thing:

    dp[i] = number of arithmetic subarrays
            that END EXACTLY at index i.

It does NOT mean total arithmetic subarrays
from 0 to i.


Example:

    nums = [1,2,3,4]

At i = 2:

    [1,2,3]

Only one arithmetic subarray ends at index 2.

    dp[2] = 1


At i = 3:

    [2,3,4]
    [1,2,3,4]

Two arithmetic subarrays end at index 3.

    dp[3] = 2


Therefore:

    dp = [0,0,1,2]

And total answer:

    1 + 2 = 3


------------------- HOW DO WE CHECK? ----------------------

To know whether an arithmetic subarray can end at i,
we only need to check the last 3 elements:

    nums[i-2], nums[i-1], nums[i]

Their differences must be equal:

    nums[i] - nums[i-1]
            ==
    nums[i-1] - nums[i-2]


Example:

    [1,2,3]

    2 - 1 = 1
    3 - 2 = 1

So they form an arithmetic slice.


------------------- WHY +1? ------------------------------

Suppose:

    nums = [1,2,3,4]

At i = 2:

    [1,2,3]

There is one arithmetic slice:

    dp[2] = 1


Now i = 3.

The last 3 elements are:

    [2,3,4]

They are also arithmetic.

We get a NEW slice:

    [2,3,4]

But we can ALSO extend every arithmetic slice
that ended at i-1:

    [1,2,3]
          ↓ add 4
    [1,2,3,4]

So:

    previous slices = dp[i-1]
    new 3-element slice = 1

Therefore:

    dp[i] = dp[i-1] + 1


------------------- WHY 0? -------------------------------

Suppose:

    nums = [1,2,3,5]

At i = 3:

    3 - 2 = 1
    5 - 3 = 2

Differences are different.

Therefore no arithmetic subarray can END at index 3.

So:

    dp[3] = 0

Notice that [1,2,3] is still an arithmetic slice,
but it ends at index 2, not index 3.


------------------- FINAL ANSWER --------------------------

For every index i:

    ans += dp[i]

because dp[i] represents all arithmetic slices
ending at that particular index.


===========================================================
*/


// =========================================================
// 1. MEMOIZATION / TOP-DOWN
// =========================================================

class SolutionMemoization {
public:

    /*
        solve(i) returns:

        Number of arithmetic subarrays
        ending exactly at index i.
    */
    int solve(vector<int>& nums, vector<int>& dp, int i) {

        // Less than 3 elements cannot form a slice
        if (i < 2)
            return 0;

        // Already calculated -> return stored value
        if (dp[i] != -1)
            return dp[i];

        /*
            Check whether the last 3 elements
            form an arithmetic sequence.

            Example:

                [1,2,3]

                2 - 1 = 1
                3 - 2 = 1

            Therefore they are arithmetic.
        */
        if (nums[i] - nums[i - 1] ==
            nums[i - 1] - nums[i - 2]) {

            /*
                Why +1?

                We always get one new 3-element slice:

                    [nums[i-2], nums[i-1], nums[i]]

                And all arithmetic slices ending at i-1
                can be extended by nums[i].

                Therefore:

                    dp[i] = dp[i-1] + 1
            */
            return dp[i] = solve(nums, dp, i - 1) + 1;
        }

        /*
            Last 3 elements are not arithmetic,
            so no arithmetic slice can end at i.
        */
        return dp[i] = 0;
    }


    int numberOfArithmeticSlices(vector<int>& nums) {

        int n = nums.size();

        // Need at least 3 elements
        if (n < 3)
            return 0;

        /*
            dp[i] stores the answer for index i.

            -1 means we have not calculated it yet.
        */
        vector<int> dp(n, -1);

        int ans = 0;

        /*
            Start from index 2 because that is
            the first index where 3 elements exist.

            solve(i) tells us how many arithmetic
            slices end at i.

            Add them to the total answer.
        */
        for (int i = 2; i < n; i++) {
            ans += solve(nums, dp, i);
        }

        return ans;
    }
};


// =========================================================
// 2. TABULATION / BOTTOM-UP
// =========================================================

class SolutionTabulation {
public:

    int numberOfArithmeticSlices(vector<int>& nums) {

        int n = nums.size();

        // Need at least 3 elements
        if (n < 3)
            return 0;

        /*
            dp[i] = number of arithmetic subarrays
                    ending exactly at i.

            Initially all values are 0 because
            no calculations have been done.
        */
        vector<int> dp(n, 0);

        int ans = 0;

        /*
            Start from index 2 because we need
            at least 3 elements.
        */
        for (int i = 2; i < n; i++) {

            /*
                Check whether:

                    nums[i-2], nums[i-1], nums[i]

                form an arithmetic sequence.
            */
            if (nums[i] - nums[i - 1] ==
                nums[i - 1] - nums[i - 2]) {

                /*
                    We have:

                    1 new 3-element slice
                    +
                    all slices ending at i-1
                    can be extended.

                    Therefore:

                        dp[i] = dp[i-1] + 1
                */
                dp[i] = dp[i - 1] + 1;

                /*
                    dp[i] contains all arithmetic
                    slices ending at i.

                    Add them to total answer.
                */
                ans += dp[i];
            }

            /*
                If the condition is false,
                dp[i] remains 0.

                This means no arithmetic slice
                ends at i.
            */
        }

        return ans;
    }
};


// =========================================================
// 3. SPACE OPTIMIZATION
// =========================================================

class Solution {
public:

    int numberOfArithmeticSlices(vector<int>& nums) {

        int n = nums.size();

        // Need at least 3 elements
        if (n < 3)
            return 0;

        /*
            In tabulation we had:

                dp[i] = dp[i-1] + 1

            Notice that to calculate dp[i],
            we only need dp[i-1].

            We don't need the entire dp array.

            Therefore:

                prev = dp[i-1]
                curr = dp[i]

            This reduces space from O(n) to O(1).
        */
        int prev = 0;

        int ans = 0;

        /*
            Start from index 2 because
            3 elements are required.
        */
        for (int i = 2; i < n; i++) {

            /*
                curr represents dp[i].

                Start with 0 because if the last
                3 elements are not arithmetic,
                no slice ends at i.
            */
            int curr = 0;

            /*
                Check whether the last 3 elements
                have the same difference.
            */
            if (nums[i] - nums[i - 1] ==
                nums[i - 1] - nums[i - 2]) {

                /*
                    Same logic as dp:

                        curr = prev + 1

                    prev = dp[i-1]
                    curr = dp[i]

                    +1 represents the new
                    3-element arithmetic slice.
                */
                curr = prev + 1;
            }

            /*
                curr contains all arithmetic
                slices ending at i.

                Add them to total answer.
            */
            ans += curr;

            /*
                Move to the next index.

                Current dp becomes previous dp.
            */
            prev = curr;
        }

        return ans;
    }
};


int main() {
    return 0;
}