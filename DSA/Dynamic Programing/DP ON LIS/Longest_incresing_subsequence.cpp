#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ==========================================================================
 *  PROBLEM: Longest Increasing Subsequence (LeetCode 300)
 *  ==========================================================================
 *  Given an integer array nums, return the length of the longest strictly
 *  increasing subsequence.
 *
 *  This file contains 4 different approaches, each building on the previous
 *  in terms of optimisation or viewpoint.
 * ========================================================================== */



/* ==========================================================================
 *  APPROACH 1 — Binary Search (Patience Sorting)   [MOST OPTIMAL]
 *  ==========================================================================
 *  Intuition:
 *    This is based on the "patience sorting" card game. Imagine you have
 *    piles of cards. You can only place a card on the leftmost pile whose
 *    top card is >= the card you are holding. If no such pile exists, start
 *    a new pile to the right. At the end, the number of piles equals the
 *    LIS length.
 *
 *  Key Idea:
 *    Maintain an array `tails` where `tails[i]` = the smallest possible
 *    ending value of an increasing subsequence of length (i+1).
 *
 *    For each number x:
 *      - Find the first element in tails that is >= x using lower_bound.
 *      - If no such element (x > all), append x → we found a longer LIS.
 *      - Otherwise, replace that element with x → this keeps the ending
 *        as small as possible for that length, which is "better" because
 *        a smaller ending gives more room to extend later.
 *
 *    The length of `tails` at the end is the LIS length.
 *
 *  Important:
 *    `tails` itself is NOT the actual LIS, only its length is correct.
 *    The array stores optimal *endings* for each length, not the actual
 *    subsequence elements.
 *
 *  Example: nums = [10, 9, 2, 5, 3, 7, 101, 18]
 *    tails evolves: [10] → [9] → [2] → [2,5] → [2,3] → [2,3,7]
 *                   → [2,3,7,101] → [2,3,7,18]   => LIS length = 4
 *
 *  Time  Complexity: O(n log n)
 *  Space Complexity: O(n)
 * ========================================================================== */

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {

        vector<int> tails;

        for (int x : nums) {

            /* Find the first element >= x  (returns iterator) */
            auto it = lower_bound(tails.begin(), tails.end(), x);

            if (it == tails.end()) {
                /* x is larger than everything seen → extend longest LIS */
                tails.push_back(x);
            } else {
                /* Replace the ending with a smaller value for same length */
                *it = x;
            }
        }

        return tails.size();
    }
};



/* ==========================================================================
 *  APPROACH 2 — Classic DP (Bottom-Up / Tabulation)
 *  ==========================================================================
 *  Intuition:
 *    The LIS ending at any index `i` can be built by extending the LIS
 *    ending at some earlier index `j` (where j < i and nums[j] < nums[i]).
 *    We try all possible `j` and take the best one.
 *
 *  DP Definition:
 *    dp[i] = length of the LIS that ends at index i.
 *
 *  Recurrence:
 *    dp[i] = 1 + max{ dp[j] | 0 <= j < i  and  nums[j] < nums[i] }
 *    Base: dp[i] = 1 (every element alone is an LIS of length 1)
 *
 *  Answer:
 *    max(dp[0], dp[1], ..., dp[n-1])
 *
 *  Example: nums = [10, 9, 2, 5, 3, 7]
 *    dp = [1, 1, 1, 2, 2, 3]   → LIS = 3
 *
 *  Time  Complexity: O(n²)  — two nested loops
 *  Space Complexity: O(n)   — dp array
 * ========================================================================== */

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();

    vector<int> dp(n, 1);     // each element is an LIS of length 1 by itself
    int ans = 1;

    for (int i = 0; i < n; i++) {

        /* Check all previous elements to extend their subsequence */
        for (int j = 0; j < i; j++) {

            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        ans = max(ans, dp[i]);   // keep track of overall maximum
    }

    return ans;
}



/* ==========================================================================
 *  APPROACH 3 — Recursive DP with Memoisation (LIS ending at i)
 *  ==========================================================================
 *  Intuition:
 *    Same as Approach 2, but expressed recursively. We compute the LIS
 *    ending at index `i` by recursively asking: what is the best LIS
 *    ending at each previous index `j`?
 *
 *  Solve function:
 *    solve(i, nums, dp) = length of LIS ending at index i.
 *
 *  Recurrence:
 *    solve(i) = 1 + max{ solve(j) | 0 <= j < i  and  nums[j] < nums[i] }
 *
 *  Memoisation:
 *    dp[i] caches the result so we never recompute the same subproblem.
 *
 *  Answer:
 *    max(solve(i)) for all i, because the LIS can end at any index.
 *
 *  Note:
 *    -1 in dp means "not yet computed".
 *
 *  Time  Complexity: O(n²)
 *  Space Complexity: O(n)  — recursion stack + dp array
 * ========================================================================== */

class Solution {
public:
    int solve(int i, vector<int>& nums, vector<int>& dp) {

        if (dp[i] != -1)
            return dp[i];

        dp[i] = 1;                       // element alone

        for (int j = 0; j < i; j++) {

            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], solve(j, nums, dp) + 1);
            }
        }

        return dp[i];
    }

    int lengthOfLIS(vector<int>& nums) {

        int n = nums.size();
        vector<int> dp(n, -1);

        int ans = 1;

        /* LIS can end at any index — try every possible ending position */
        for (int i = 0; i < n; i++) {
            ans = max(ans, solve(i, nums, dp));
        }

        return ans;
    }
};



/* ==========================================================================
 *  APPROACH 4 — Take / Not Take DP with Memoisation (index + prev)
 *  ==========================================================================
 *  Intuition:
 *    Instead of defining dp as "LIS ending at i", we walk through the
 *    array from left to right and at each index decide whether to TAKE
 *    the current element (if it respects the increasing order) or SKIP it.
 *
 *  State:
 *    solve(i, prev) where:
 *      - i    = current index we are deciding on
 *      - prev = index of the last taken element (-1 means none taken yet)
 *
 *  Choices at index i:
 *    1. NOT TAKE: skip nums[i], move to i+1, keep same prev.
 *    2. TAKE: only allowed if prev == -1 or nums[i] > nums[prev].
 *       If we take, the new prev becomes i and length increases by 1.
 *
 *  Recurrence:
 *    solve(i, prev) = max( notTake, take )
 *      where:
 *        notTake = solve(i+1, prev)
 *        take    = (prev == -1 || nums[i] > nums[prev])
 *                  ? 1 + solve(i+1, i)
 *                  : 0
 *
 *  Base case:
 *    solve(n, prev) = 0   (no elements left to process)
 *
 *  DP Table:
 *    dp[i][prev+1] — we shift prev by +1 to handle the -1 sentinel case
 *    (prev = -1 becomes index 0 in the 2nd dimension).
 *
 *  Time  Complexity: O(n²)
 *  Space Complexity: O(n²) — dp table of size n × (n+1)
 *
 *  Note:
 *    This approach is the most general form of DP for subsequence problems
 *    (it directly follows the "take / not take" pattern used in knapsack
 *    and similar problems). However, it is overkill for LIS since the
 *    simpler "LIS ending at i" (Approach 2/3) works with O(n) space.
 * ========================================================================== */

class Solution {
public:

    int solve(int i, int prev, vector<int>& nums,
              vector<vector<int>>& dp) {

        /* No elements left to process */
        if (i == nums.size())
            return 0;

        /* Return memoised result (prev+1 handles the -1 offset) */
        if (dp[i][prev + 1] != -1)
            return dp[i][prev + 1];

        /* Option 1: Skip the current element */
        int notTake = solve(i + 1, prev, nums, dp);

        /* Option 2: Take the current element if it keeps the sequence increasing */
        int take = 0;
        if (prev == -1 || nums[i] > nums[prev]) {
            take = 1 + solve(i + 1, i, nums, dp);
        }

        return dp[i][prev + 1] = max(take, notTake);
    }

    int lengthOfLIS(vector<int>& nums) {

        int n = nums.size();

        /* dp[i][prev+1] — second dimension is n+1 because prev ranges from -1 to n-1 */
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));

        return solve(0, -1, nums, dp);
    }
};

int main(){
    return 0;
}