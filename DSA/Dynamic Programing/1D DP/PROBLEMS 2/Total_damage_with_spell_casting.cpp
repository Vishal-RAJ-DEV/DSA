#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ============================================================================
 * PROBLEM: Maximum Total Damage With Spell Casting (LeetCode 3186)
 * ----------------------------------------------------------------------------
 * STATEMENT:
 *   You are given array `power`, where power[i] = damage of i-th spell.
 *   If you cast a spell with damage value `x = power[i]`, then you CANNOT
 *   cast any spell whose damage value is in {x-2, x-1, x+1, x+2}.
 *   Each spell can be used at most once.
 *   Return the maximum total damage sum you can get.
 *
 * EXAMPLES:
 *   Ex1: power = [1,1,3,4]  -> 6
 *        Take both 1's (1+1=2) + 4 = 6. Can't take 3 because 3 is within
 *        2 of 1 (3-1=2, conflict). So {1,1,4} is optimal.
 *
 *   Ex2: power = [7,1,6,6]  -> 13
 *        Take 1 + 6 + 6 = 13. Skip 7 because 7 conflicts with 6 (|7-6|=1).
 *
 * CONSTRAINTS:
 *   1 <= power.length <= 1e5, 1 <= power[i] <= 1e9
 *   Answer can exceed 32-bit int, so use `long long`.
 *
 * ----------------------------------------------------------------------------
 * CORE IDEA (Same for all 3 solutions below):
 * ----------------------------------------------------------------------------
 * This is a "Delete and Earn / House Robber on value-axis" 1D DP problem.
 *
 * Step 1 - COMPRESS BY VALUE:
 *   Same damage value must be taken together or skipped together.
 *   Why? If you decide to take value `x`, taking one `x` bans x-2..x+2,
 *   but does NOT ban another `x`. So there is never a reason to take only
 *   some copies of `x`. Take all of them to get gain = x * freq(x).
 *   Example: [1,1,3,4] -> unique sorted values = [1,3,4]
 *                         gain = [1*2=2, 3*1=3, 4*1=4]
 *
 *   After compression, `values[]` is strictly increasing (via map).
 *
 * Step 2 - 1D DP WITH CONFLICT JUMP (Take / Skip):
 *   Process unique values in sorted order. For values[i] = x:
 *
 *     SKIP i : answer = best answer using values[0..i-1]
 *     TAKE i : answer = gain[i] + best answer using values <= x-3
 *              (because any value in [x-2, x-1] conflicts with x)
 *     dp[i]  = max(SKIP, TAKE)
 *
 *   To find "last compatible index" (largest j with values[j] <= x-3),
 *   use binary search: lower_bound(values[0..i), x-2) gives first index
 *   `j` with values[j] >= x-2. So indices [0..j-1] are compatible.
 *
 * TIME:  O(n log n) due to map/sort + binary search per state.
 * SPACE: O(n) for values/gain/dp.
 * ----------------------------------------------------------------------------
 * THREE VERSIONS BELOW ARE THE SAME LOGIC, DIFFERENT DP STYLE:
 *   1. Top-Down Memoization (recursion + dp array)
 *   2. Bottom-Up Tabulation (iterative dp array)
 *   3. Bottom-Up Optimized (only store best-per-value, no full array)
 * ============================================================================
 */

// ============================================================================
// APPROACH 1: TOP-DOWN MEMOIZATION (Recursion + Memo)
// Time: O(n log n), Space: O(n) for dp + O(n) recursion stack
// ============================================================================
class SolutionMemo {
public:
    vector<long long> values; // sorted unique damage values
    vector<long long> gain;   // gain[i] = values[i] * frequency
    vector<long long> dp;     // dp[i] = max damage using values[0..i], -1 = uncomputed

    // Returns max damage we can get considering unique values[0..i]
    long long solve(int i) {
        // BASE CASE: No values left to consider
        if (i < 0)
            return 0;

        // MEMO CHECK: Already solved this subproblem, reuse it
        if (dp[i] != -1)
            return dp[i];

        // OPTION 1 - SKIP: Don't cast values[i], answer comes from [0..i-1]
        long long skip = solve(i - 1);

        // Find first index `j` in [0..i) with values[j] >= values[i]-2.
        // All indices before `j` have value <= values[i]-3, hence compatible.
        // lower_bound is binary search because values[] is sorted.
        auto it = lower_bound(values.begin(), values.begin() + i, values[i] - 2);

        // Convert iterator to index: number of values before `it`
        int j = it - values.begin();

        // OPTION 2 - TAKE: Take ALL copies of values[i] + best from [0..j-1]
        // solve(j-1) is 0 when j==0 (no compatible element).
        long long take = gain[i] + solve(j - 1);

        // Store and return best of Take vs Skip
        return dp[i] = max(skip, take);
    }

    long long maximumTotalDamage(vector<int>& power) {
        map<long long, long long> mp;

        // COUNT FREQUENCY: mp[x] = how many spells have damage x.
        // map keeps keys sorted automatically.
        for (long long x : power) {
            mp[x]++;
        }

        // BUILD COMPRESSED ARRAYS: values[] and gain[]
        for (auto& val : mp) {
            long long x = val.first;    // unique damage value
            long long freq = val.second; // its count
            values.push_back(x);
            gain.push_back(x * freq);   // total damage if we take all x's
        }

        int n = values.size();

        // dp[i] = -1 means "not computed yet" (answers are >= 0, so -1 is safe)
        dp.assign(n, -1);

        // Solve for full range [0..n-1]
        return solve(n - 1);
    }
};


// ============================================================================
// APPROACH 2: BOTTOM-UP TABULATION (Iterative DP)
// Same recurrence as Approach 1, but no recursion.
// dp[i] = max damage using first i unique values (i from 0..n).
// ============================================================================
class SolutionTabulation {
public:
    long long maximumTotalDamage(vector<int>& power) {
        map<long long, long long> mp;

        // COUNT FREQUENCY (sorted by value due to map)
        for (long long x : power) {
            mp[x]++;
        }

        vector<long long> values; // sorted unique values
        vector<long long> gain;   // gain[i] = values[i] * freq

        // COMPRESS: one entry per distinct damage
        for (auto& val : mp) {
            long long x = val.first;
            long long freq = val.second;
            values.push_back(x);
            gain.push_back(x * freq);
        }

        int n = values.size();

        // dp[0] = 0 (no values considered).
        // dp[i] = answer using first i values (values[0..i-1]).
        vector<long long> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            // Current unique value (1-based dp -> 0-based arrays)
            long long x = values[i - 1];

            // Find first index `j` in [0..i-1) with values[j] >= x-2.
            // Indices [0..j-1] are compatible (value <= x-3).
            // dp[j] already stores best answer for first j values.
            auto it = lower_bound(
                values.begin(),
                values.begin() + (i - 1),
                x - 2
            );

            int j = it - values.begin();

            // OPTION 1 - SKIP current value: carry forward previous best
            long long skip = dp[i - 1];

            // OPTION 2 - TAKE current value: gain + best compatible prefix
            long long take = gain[i - 1] + dp[j];

            // Best of Take vs Skip
            dp[i] = max(skip, take);
        }

        return dp[n]; // answer using all n unique values
    }
};


// ============================================================================
// APPROACH 3: OPTIMIZED BOTTOM-UP (Best-map, no dp array / no binary search
//             on array — uses ordered map to query prefix best)
// Idea: iterate values in increasing order, maintain:
//   ans      = best answer considering all values processed so far
//   best[x]  = ans right after processing value x (prefix best up to x)
// For current x, compatible best = best answer for values <= x-3, which is
// found by best.upper_bound(x-3) then stepping one iterator back.
// ============================================================================
class SolutionOptimized {
public:
    long long maximumTotalDamage(vector<int>& power) {
        map<long long, long long> freq;

        // COUNT FREQUENCY
        for (long long x : power) {
            freq[x]++;
        }

        // best[key] = prefix-best answer up to damage value `key`.
        // Since we insert keys in increasing order, map stays sorted.
        map<long long, long long> best;

        // ans = global best over all processed values so far (= skip option)
        long long ans = 0;

        for (auto& val : freq) {
            long long x = val.first;     // current damage value
            long long count = val.second; // its frequency

            // Total damage if we take all copies of x
            long long gain = x * count;

            // Find best answer using only values <= x-3 (compatible part).
            // upper_bound(x-3) = first key > x-3, so step back once to get
            // last key <= x-3. If none exists, compatible = 0.
            auto it = best.upper_bound(x - 3);

            long long compatible = 0;

            if (it != best.begin()) {
                --it;
                compatible = it->second;
            }

            // OPTION TAKE: gain of x + best compatible prefix
            long long take = gain + compatible;

            // OPTION SKIP: keep previous global best
            long long skip = ans;

            // Best up to current x
            ans = max(skip, take);

            // Record prefix best at x for future larger values to query
            best[x] = ans;
        }

        return ans;
    }
};




int main(){
    // Quick manual test:
    // power = [1,1,3,4] -> expected 6
    // power = [7,1,6,6] -> expected 13
    SolutionTabulation s;
    vector<int> p1 = {1,1,3,4};
    vector<int> p2 = {7,1,6,6};
    cout << s.maximumTotalDamage(p1) << endl; // 6
    cout << s.maximumTotalDamage(p2) << endl; // 13
    return 0;
}
