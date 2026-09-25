#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
PROBLEM: Delete and Earn (LeetCode 740)
--------------------------------------------------------------------------------
You are given an integer array `nums`.

Operation: Pick any `nums[i]` and delete it to earn `nums[i]` points.
After that, you must delete EVERY element equal to `nums[i] - 1` and every
element equal to `nums[i] + 1` (you get NO points for those forced deletions).

Repeat until array is empty. Return the maximum points you can earn.

Example 1: nums = [3, 4, 2]
  - Delete 4 to earn 4, then delete 3. Remaining [2]. Delete 2 to earn 2.
  - Total = 6. This is optimal.

Example 2: nums = [2, 2, 3, 3, 3, 4]
  - Delete 3 three times to earn 3+3+3 = 9, then all 2s and 4s are auto-deleted.
  - Total = 9. (If you took 2s and 4s instead: 2+2+4 = 8, which is worse.)

CONSTRAINTS: 1 <= nums.length <= 2*10^4, 1 <= nums[i] <= 10^4.
================================================================================

================================================================================
MAIN LOGIC / CORE IDEA: Convert it into "House Robber" problem
--------------------------------------------------------------------------------
KEY OBSERVATION 1 - All same numbers must be taken together:
  If you decide to take value `v`, you might as well take ALL copies of `v`
  at once. Why? Taking one `v` deletes `v-1` and `v+1`, but does NOT delete
  other `v`s. So the second, third copy of `v` is still available and gives
  free extra points with no extra penalty. There is never a reason to take
  only some of the `v`s and leave others.
  => Decision is per DISTINCT VALUE, not per index: either take ALL `v`s
     or take NONE of them.

KEY OBSERVATION 2 - Taking `v` forbids taking `v-1` and `v+1`:
  This is EXACTLY like House Robber where robbing house `i` forbids robbing
  house `i-1` and `i+1` (adjacent houses). Here "houses" are VALUES
  0, 1, 2, ..., max(nums), placed in a line in sorted order.

STEP 1 - Build `points` array (frequency * value aggregation):
  maxi = max(nums)                                  // biggest value present
  points[v] = (count of v in nums) * v              // total reward if we
                                                    // take ALL copies of v
  Example: [2,2,3,3,3,4] -> points = [0, 0, 4, 9, 4]
                                             idx:  0  1  2  3  4
  If a value never appears, points[v] = 0 (taking it gives 0, but still
  blocks neighbours, so the DP will learn to skip it).

  After this step, the original UNSORTED array problem is gone. We now have
  a LINEAR 1D array `points[0..maxi]` and the rule:
    "Pick a subset of indices with no two adjacent, to maximize sum."
  That is precisely House Robber.

STEP 2 - Run House-Robber DP on `points`:
  Let solve(x) = max points earnable considering values 0..x only.
  For value `x` we have exactly 2 choices:

    a) SKIP x: earn nothing from x, answer = best from 0..x-1
           skip = solve(x-1)

    b) TAKE x: earn points[x] (take all x's), but x-1 becomes forbidden,
       so we can only add best from 0..x-2
           take = points[x] + solve(x-2)

    solve(x) = max(skip, take)

  Base: solve(x <= 0) = 0 (no values to consider, zero earning).
        solve(1) = points[1] (only choice: take value 1 or nothing; since
                  points[1] >= 0, taking is always >= skipping).

  Answer = solve(maxi) = best considering ALL values.

DRY RUN on points = [0, 0, 4, 9, 4]  ([2,2,3,3,3,4] case):
  solve(0) = 0
  solve(1) = points[1] = 0
  x=2: skip = solve(1) = 0, take = 4 + solve(0) = 4  -> max = 4  (take 2s)
  x=3: skip = 4,           take = 9 + solve(1) = 9  -> max = 9  (take 3s, drop 2s)
  x=4: skip = 9,           take = 4 + solve(2)=4+4=8 -> max = 9  (skip 4, keep 3s)
  Answer 9. Matches expected.

WHY x-2 AND NOT x-1 IN "take"? Because taking x deletes x-1 (adjacent value),
so x-1 is no longer available. The remaining allowed prefix ends at x-2.
That is the whole "delete neighbours" rule encoded as "no adjacent picks".

COMPLEXITY:
  Building points: O(n + maxi) time, O(maxi) space.
  DP: O(maxi) time. maxi <= 10^4, so this is fine.
================================================================================
*/

class Solution {
public:
    // -------------------------------------------------------------------------
    // APPROACH 1: Recursion + Memoization (Top-Down)
    // -------------------------------------------------------------------------
    // solve(x, points, dp) returns max earning using values 0..x only.
    //  - if x <= 0: base case, nothing to earn -> 0.
    //  - if dp[x] already computed, return it (memo).
    //  - Otherwise:
    //      skip = solve(x-1)            // ignore value x completely
    //      take = points[x] + solve(x-2)// take ALL x's, x-1 becomes blocked
    //      dp[x] = max(skip, take)
    // TC: O(maxi) states x 1 work each. SC: O(maxi) dp + O(maxi) stack.
    // -------------------------------------------------------------------------
    int solve(int x, vector<int>& points, vector<int>& dp) {
        // Base case: no values left to consider (x = 0 means only value 0,
        // whose points[0] is always 0, so earning is 0; x < 0 is empty prefix).
        if (x <= 0) return 0;

        // Memo check: if we already solved prefix 0..x, reuse it.
        if (dp[x] != -1) return dp[x];

        // Choice 1 - SKIP value x: best of prefix 0..x-1 carries over.
        int skip = solve(x - 1, points, dp);

        // Choice 2 - TAKE value x: collect points[x] now, but value x-1 is
        // deleted, so we can only extend the best of prefix 0..x-2.
        int take = points[x] + solve(x - 2, points, dp);

        // Store and return the better of the two choices.
        return dp[x] = max(skip, take);
    }

    // Main driver for Approach 1.
    // Steps: 1) find maxi, 2) build points[], 3) memo-DFS from maxi downwards.
    int deleteAndEarnMemo(vector<int>& nums) {
        // 1) Find maximum value -> defines the size of points[] line.
        int maxi = 0;
        for (int x : nums) {
            maxi = max(maxi, x);
        }

        // 2) Aggregate: points[v] = total reward for taking ALL v's.
        //    e.g. three 3's -> points[3] = 3+3+3 = 9.
        vector<int> points(maxi + 1, 0);
        for (int x : nums) {
            points[x] += x;
        }

        // 3) Top-down DP over value-prefixes 0..maxi.
        vector<int> dp(maxi + 1, -1); // -1 = unsolved (points are >= 0)

        return solve(maxi, points, dp); // answer = best over ALL values
    }

    // -------------------------------------------------------------------------
    // APPROACH 2: Tabulation (Bottom-Up) - same logic, iterative
    // -------------------------------------------------------------------------
    // dp[x] = max earning using values 0..x.
    //  dp[0] = 0            (value 0 earns nothing)
    //  dp[1] = points[1]    (only value 1 available)
    //  dp[x] = max(dp[x-1],            // skip x
    //              points[x]+dp[x-2])  // take x, x-1 blocked
    // TC: O(maxi), SC: O(maxi).
    // -------------------------------------------------------------------------
    int deleteAndEarnTabulation(vector<int>& nums) {
        // 1) Find maximum value.
        int maxi = 0;
        for (int x : nums) {
            maxi = max(maxi, x);
        }

        // 2) Build aggregated points array (House Robber houses).
        vector<int> points(maxi + 1, 0);
        for (int x : nums) {
            points[x] += x;
        }

        // 3) Bottom-up: solve small prefixes first, grow to maxi.
        vector<int> dp(maxi + 1, 0);

        dp[0] = 0; // base: prefix {0} earns 0

        if (maxi >= 1) {
            dp[1] = points[1]; // base: prefix {0,1} -> best is take value 1
        }

        for (int x = 2; x <= maxi; x++) {
            int skip = dp[x - 1];            // ignore value x
            int take = points[x] + dp[x - 2];// take x, jump over x-1

            dp[x] = max(skip, take); // best of the two choices
        }

        return dp[maxi]; // best over full range 0..maxi
    }

    // -------------------------------------------------------------------------
    // APPROACH 3: Space Optimization - only 2 previous states needed
    // -------------------------------------------------------------------------
    // OBSERVATION: dp[x] needs only dp[x-1] and dp[x-2]. So instead of a full
    // array, keep two rolling variables:
    //   prev2 = dp[x-2] (best up to value before previous)
    //   prev1 = dp[x-1] (best up to previous value)
    //   current = max(prev1, points[x] + prev2)
    // then slide: prev2 = prev1, prev1 = current.
    // TC: O(maxi), SC: O(maxi) for points + O(1) for DP.
    // (points[] itself can also be a hashmap if maxi is huge, but here
    //  maxi <= 1e4 so array is fine.)
    // -------------------------------------------------------------------------
    int deleteAndEarnSpaceOpt(vector<int>& nums) {
        // 1) Find maximum value.
        int maxi = 0;
        for (int x : nums) {
            maxi = max(maxi, x);
        }

        // Edge case: empty reasoning guard. If maxi == 0 (e.g. nums empty or
        // only zeros), there is nothing to earn. Prevents points[1] OOB below.
        if (maxi == 0) return 0;

        // 2) Build aggregated points array.
        vector<int> points(maxi + 1, 0);
        for (int x : nums) {
            points[x] += x;
        }

        // Edge case: only value 0/1 present -> answer is points[1] directly,
        // loop below would not run.
        if (maxi == 1) return points[1];

        // 3) Rolling DP: prev2 = dp[0], prev1 = dp[1] to start.
        int prev2 = 0;          // dp[0] = 0
        int prev1 = points[1];  // dp[1] = points[1]

        for (int x = 2; x <= maxi; x++) {
            int take = points[x] + prev2; // take x + best up to x-2
            int skip = prev1;             // skip x, keep best up to x-1

            int current = max(take, skip); // dp[x]

            // Slide window forward for next x+1:
            // old prev1 becomes the new "x-1" (i.e. prev2), current becomes prev1.
            prev2 = prev1;
            prev1 = current;
        }

        return prev1; // after loop prev1 = dp[maxi]
    }

    // -------------------------------------------------------------------------
    // LeetCode entry point (keeps original function name/signature).
    // Delegates to the space-optimized version (fastest in memory).
    // Change to deleteAndEarnMemo / deleteAndEarnTabulation to test others.
    // -------------------------------------------------------------------------
    int deleteAndEarn(vector<int>& nums) {
        return deleteAndEarnSpaceOpt(nums);
    }
};



int main(){
    Solution s;
    vector<int> nums1 = {3, 4, 2};
    vector<int> nums2 = {2, 2, 3, 3, 3, 4};
    cout << "Memo [3,4,2]: " << s.deleteAndEarnMemo(nums1) << " (expected 6)" << endl;
    cout << "Tab  [3,4,2]: " << s.deleteAndEarnTabulation(nums1) << " (expected 6)" << endl;
    cout << "Opt  [3,4,2]: " << s.deleteAndEarnSpaceOpt(nums1) << " (expected 6)" << endl;
    cout << "Memo [2,2,3,3,3,4]: " << s.deleteAndEarnMemo(nums2) << " (expected 9)" << endl;
    cout << "Tab  [2,2,3,3,3,4]: " << s.deleteAndEarnTabulation(nums2) << " (expected 9)" << endl;
    cout << "Opt  [2,2,3,3,3,4]: " << s.deleteAndEarnSpaceOpt(nums2) << " (expected 9)" << endl;
    return 0;
}
