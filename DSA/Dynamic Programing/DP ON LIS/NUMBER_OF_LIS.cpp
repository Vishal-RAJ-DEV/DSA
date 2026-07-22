/* ==========================================================================
 *  PROBLEM: Number of Longest Increasing Subsequences (LeetCode 673)
 *  ==========================================================================
 *  Given an integer array nums, return the NUMBER of longest strictly
 *  increasing subsequences (not the length — how many distinct LIS exist).
 *
 *  Example: nums = [1, 3, 5, 4, 7]
 *    LIS length = 4  (max LIS length).
 *    All LIS of length 4:  [1, 3, 5, 7]  and  [1, 3, 4, 7]
 *    So answer = 2.
 *
 * ==========================================================================
 *  ALGORITHM OVERVIEW — DP with count tracking
 * ==========================================================================
 *  We maintain TWO arrays:
 *
 *    dp[i]    = length of the LIS that ENDS at index i.
 *    count[i] = NUMBER of distinct LIS of length dp[i] that end at i.
 *
 *  Initialisation:
 *    dp[i] = 1      (every element alone is an LIS of length 1)
 *    count[i] = 1   (there is exactly 1 way: just {nums[i]})
 *
 *  For each i, scan all j < i:
 *    If nums[j] < nums[i], we can EXTEND the LIS ending at j by appending i.
 *      ┌─────────────────────────────────────────────────────────────┐
 *      │  CASE A: dp[j] + 1  >  dp[i]                               │
 *      │    We found a LONGER LIS ending at i.                      │
 *      │    → dp[i] = dp[j] + 1                                     │
 *      │    → count[i] = count[j]   ← all ways that reached j       │
 *      │      now reach i by appending nums[i] at the end.          │
 *      └─────────────────────────────────────────────────────────────┘
 *      ┌─────────────────────────────────────────────────────────────┐
 *      │  CASE B: dp[j] + 1 == dp[i]                                │
 *      │    We found ANOTHER way to get the SAME max length at i.   │
 *      │    → count[i] += count[j]   ← add the new ways             │
 *      └─────────────────────────────────────────────────────────────┘
 *
 *  After the loop, maxi = max(dp[0..n-1]) = the LIS length.
 *
 *  Answer = sum of count[i] for all i where dp[i] == maxi.
 *
 * ==========================================================================
 *  HOW count[i] WORKS — DETAILED WALKTHROUGH
 * ==========================================================================
 *  count[i] tracks the NUMBER of distinct LIS that end at i.
 *
 *  When we find a LONGER sequence (Case A):
 *    count[i] is REPLACED by count[j]. Why?
 *    - Every distinct LIS that ended at j can now be EXTENDED by adding
 *      nums[i] at the end. This creates a NEW distinct LIS ending at i.
 *    - None of the previous LIS ending at i (with shorter length) matter
 *      anymore because we only care about the LONGEST length so far.
 *    - So we reset count[i] = count[j].
 *
 *  When we find ANOTHER sequence of SAME length (Case B):
 *    count[i] is ACCUMULATED (added to). Why?
 *    - We already had some number of LIS of length dp[i] ending at i
 *      (from earlier j's). Now we discovered more ways (through a new j)
 *      to achieve that same length, so we add count[j] to the existing count.
 *
 *  Example: nums = [1, 3, 5, 4, 7]
 *
 *    i=0 (val=1): dp[0]=1, count[0]=1, maxi=1
 *
 *    i=1 (val=3):
 *      j=0: 1<3, dp[0]+1=2 > dp[1]=1  →  dp[1]=2, count[1]=count[0]=1
 *      maxi=2
 *      State: dp=[1,2], count=[1,1]   (LIS ending at 1: [1,3])
 *
 *    i=2 (val=5):
 *      j=0: 1<5, dp[0]+1=2 > dp[2]=1  →  dp[2]=2, count[2]=count[0]=1
 *      j=1: 3<5, dp[1]+1=3 > dp[2]=2  →  dp[2]=3, count[2]=count[1]=1
 *      maxi=3
 *      State: dp=[1,2,3], count=[1,1,1]   (LIS ending at 2: [1,3,5])
 *
 *    i=3 (val=4):
 *      j=0: 1<4, dp[0]+1=2 > dp[3]=1  →  dp[3]=2, count[3]=count[0]=1
 *      j=1: 3<4, dp[1]+1=3 > dp[3]=2  →  dp[3]=3, count[3]=count[1]=1
 *      j=2: 5<4?  No
 *      maxi=3
 *      State: dp=[1,2,3,3], count=[1,1,1,1]   (LIS ending at 3: [1,3,4])
 *
 *    i=4 (val=7):
 *      j=0: 1<7, dp[0]+1=2 > dp[4]=1  →  dp[4]=2, count[4]=count[0]=1
 *      j=1: 3<7, dp[1]+1=3 > dp[4]=2  →  dp[4]=3, count[4]=count[1]=1
 *      j=2: 5<7, dp[2]+1=4 > dp[4]=3  →  dp[4]=4, count[4]=count[2]=1
 *        ↑ CASE A: 4 > 3, so we replace count[4] = count[2] = 1
 *      j=3: 4<7, dp[3]+1=4 == dp[4]=4 →  count[4] += count[3] = 1+1 = 2
 *        ↑ CASE B: same length (4), so we ADD count[3] to count[4]
 *      maxi=4
 *      State: dp=[1,2,3,3,4], count=[1,1,1,1,2]
 *
 *    Answer: sum count[i] where dp[i]==maxi(4) → count[4] = 2
 *
 *    The two LIS of length 4:
 *      Through j=2 (val=5): [1,3,5,7]   (count[2]=1 way)
 *      Through j=3 (val=4): [1,3,4,7]   (count[3]=1 way)
 *      Total = count[4] = 2  ✓
 *
 * ==========================================================================
 *  KEY INSIGHT — Why count[i] = count[j] and not 1?
 * ==========================================================================
 *  When we extend j→i to form a longer LIS, the number of distinct LIS
 *  that now end at i equals the number that ended at j, because each one
 *  can be extended by appending nums[i]. For example, if there were 3
 *  different LIS ending at j, there will be 3 different LIS ending at i
 *  (just with nums[i] tacked on). So count[i] = count[j], not count[j] + 1.
 *
 *  count is NOT about length — it's about NUMBER OF DISTINCT SEQUENCES.
 *
 *  Time  Complexity: O(n²)
 *  Space Complexity: O(n)
 * ========================================================================== */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {

        int n = nums.size();

        /* dp[i] = length of LIS ending at index i (minimum = 1) */
        vector<int> dp(n, 1);

        /* count[i] = number of distinct LIS of length dp[i] that end at i */
        vector<int> count(n, 1);

        int maxi = 1;   // tracks the maximum LIS length seen so far

        /* ---------- Compute dp[i] and count[i] for every i ---------- */
        for (int i = 0; i < n; i++) {

            /* Check every previous element that can be extended */
            for (int j = 0; j < i; j++) {

                /* Can nums[i] come after nums[j] in an increasing sequence? */
                if (nums[j] < nums[i]) {

                    /* ----- CASE A: Extending j produces a LONGER LIS ----- */
                    if (dp[j] + 1 > dp[i]) {

                        dp[i] = dp[j] + 1;

                        /* All distinct LIS that ended at j can now be
                         * extended by adding nums[i].
                         * Replace count[i] with the number of ways from j. */
                        count[i] = count[j];
                    }

                    /* ----- CASE B: Same length found through another j ----- */
                    else if (dp[j] + 1 == dp[i]) {

                        /* We already had some ways to reach i with this length.
                         * Now we found MORE ways through j. Add them. */
                        count[i] += count[j];
                    }
                }
            }

            /* Update the global maximum LIS length */
            maxi = max(maxi, dp[i]);
        }

        /* ---------- Sum counts of all indices having the max LIS length ---------- */
        int ans = 0;

        for (int i = 0; i < n; i++) {

            if (dp[i] == maxi)
                ans += count[i];
        }

        return ans;
    }
};



int main(){
    return 0;
}