#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ============================================================================
   QUESTION EXPLAINED : MIN COST / MIN STEPS TO REACH TARGET
   ----------------------------------------------------------------------------
   Problem Statement:
     You are given:
       1. An integer `target`  -> the exact score/distance/amount to reach
          starting from 0.
       2. A vector<int> `ways` -> allowed moves. In one move you can add
          any one value from `ways` to your current sum.
          Each value can be used UNLIMITED times (unbounded / infinite supply).

     Goal:
       Reach EXACTLY `target` using minimum number of moves.

       If it is impossible, return -1 (your current code returns INT_MAX,
       we fix that in the new functions below).

     This is exactly the classic:
       "Coin Change - Minimum Coins" (LeetCode 322)
       "Min Cost to Reach N with jumps of size ways[i]"

   Examples:
     Ex1: target = 7, ways = [1, 3, 5]
          Options: 5+1+1 = 3 moves, 3+3+1 = 3 moves, 1*7 = 7 moves
          Answer = 3

     Ex2: target = 11, ways = [2, 3, 5]
          Options: 5+3+3 = 3 moves, 5+2+2+2 = 4 moves
          Answer = 3

     Ex3: target = 7, ways = [2, 4]
          No combination makes 7.
          Answer = -1 (impossible)

   Recurrence (heart of DP):
     Let f(t) = min moves to reach sum `t`.
     Base: f(0) = 0  (already at 0, 0 moves needed)
     For t > 0:
       f(t) = 1 + min { f(t - way) }  over all way in `ways` where way <= t
              and f(t-way) is reachable.
       If no such way is reachable, f(t) = INF (impossible).

     Why +1? Because we take one last jump `way` to go from (t-way) -> t.

   Time Complexity (all versions): O(target * ways.size())
     For each t = 1..target, we try every way.
   ============================================================================ */

vector<int> memo;

// ----------------------------------------------------------------------------
// 1. MEMOIZATION (Top-Down Recursion + DP array)
// ----------------------------------------------------------------------------
// Logic: solve(t) tries every `way <= t`, recursively asks "what is best
//        for (t-way)?" and adds 1 for current jump.
// memo[t] stores already computed answer for t, so we don't recompute.
// Time : O(target * K) where K = ways.size()
// Space: O(target) for memo[] + O(target) recursion stack in worst case.
int solve(int target, vector<int>& ways) {
    if (target == 0)
        return 0; // base: 0 moves to reach 0

    if (memo[target] != -1)
        return memo[target]; // already solved -> reuse

    int result = INT_MAX;

    for (int way : ways) {
        if (way <= target) {
            int sub = solve(target - way, ways);
            // only extend if sub-problem is reachable (avoid INT_MAX overflow)
            if (sub != INT_MAX)
                result = min(result, sub + 1);
        }
    }

    return memo[target] = result;
}

// ----------------------------------------------------------------------------
// 2. TABULATION (Bottom-Up 1D DP)
// ----------------------------------------------------------------------------
// Logic: Build dp[0..target] iteratively.
//   dp[0] = 0
//   dp[i] = 1 + min(dp[i-way]) for all way <= i, if dp[i-way] != INF
// We go small -> large so that when we compute dp[i], all dp[i-way] are
// already known. No recursion, no stack overflow.
// Time : O(target * K)
// Space: O(target) for dp array.
int tabulation(int target, vector<int>& ways) {
    const int INF = 1e9;
    vector<int> dp(target + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= target; ++i) {
        for (int way : ways) {
            if (way <= i && dp[i - way] != INF) {
                dp[i] = min(dp[i], dp[i - way] + 1);
            }
        }
    }

    return dp[target]; // caller should check INF -> impossible
}


// ============================================================================
// 3. SPACE OPTIMIZED CODE
// ============================================================================
// QUESTION: Can we do O(1) space like House Robber / Climbing Stairs?
//
// ANSWER: NOT in general for arbitrary `ways`.
//
// Reason:
//   dp[i] depends on dp[i-way] for EVERY way in `ways`.
//   The farthest lookback = max(ways) = say M.
//   So to compute dp[i] we must remember the last M answers:
//     dp[i-1], dp[i-2], ..., dp[i-M]
//   We CANNOT throw them away, otherwise dp[i] would be wrong.
//
//   Therefore:
//     - Tabulation needs O(target) space.
//     - Best possible general optimization = O(M) space where M = max(ways),
//       using a circular buffer / sliding window.
//     - O(1) space is possible ONLY in special cases:
//         Ex: ways = [1,2] -> M=2 -> we only need prev1, prev2 -> O(1).
//         ways = [1,2,3] -> need prev1, prev2, prev3 -> O(1) (constant 3).
//
// HOW THE WINDOW TRICK WORKS:
//   Instead of storing dp[0..target], store only last (M+1) values in a
//   circular array `window` of size M+1.
//   Real index i maps to window index = i % (M+1).
//   When we move i forward, old entries that are more than M steps behind
//   are safely overwritten because they will never be needed again
//   (since biggest jump is M).
//
//   Example: ways=[1,3,5], M=5, window size=6.
//     i=7 needs dp[6], dp[4], dp[2] -> all within last 5 values -> still
//     present in window. dp[0], dp[1] that got overwritten are not needed.
//
// Time : O(target * K)  (same, we still loop the same)
// Space: O(M) = O(max(ways)) instead of O(target). Huge win when target is
//        large (1e5) and M is small (like <= 10).
// ============================================================================
int spaceOptimized(int target, vector<int>& ways) {
    if (target == 0) return 0;
    if (ways.empty()) return -1;

    const int INF = 1e9;
    int maxWay = *max_element(ways.begin(), ways.end());

    // Circular buffer of size maxWay+1.
    // window[i % (maxWay+1)] always holds answer for sum i (if i already computed).
    vector<int> window(maxWay + 1, INF);
    window[0] = 0; // dp[0] = 0 stored at index 0 % (maxWay+1) = 0

    for (int i = 1; i <= target; ++i) {
        int curIdx = i % (maxWay + 1);
        window[curIdx] = INF; // reset before computing dp[i]

        for (int way : ways) {
            if (way <= i) {
                int prevIdx = (i - way) % (maxWay + 1);
                if (window[prevIdx] != INF) {
                    window[curIdx] = min(window[curIdx], window[prevIdx] + 1);
                }
            }
        }
    }

    int ans = window[target % (maxWay + 1)];
    return (ans >= INF ? -1 : ans); // -1 = impossible
}

// ----------------------------------------------------------------------------
// 3b. SPECIAL CASE O(1) SPACE: when ways = {1, 2} (classic min-jumps version)
// ----------------------------------------------------------------------------
// If jumps allowed are only 1 and 2:
//   dp[i] = 1 + min(dp[i-1], dp[i-2])
// We only ever need the last 2 values -> two variables are enough.
// This is shown here just to explain what "true O(1) space" looks like.
// Time: O(target), Space: O(1).
int spaceOptimized_1_2(int target) {
    // With jumps 1 and 2, every target is reachable, answer = ceil(target/2).
    // We still show DP form for learning.
    if (target == 0) return 0;
    if (target == 1) return 1;
    int prev2 = 0; // dp[0]
    int prev1 = 1; // dp[1]
    int curr = 0;
    for (int i = 2; i <= target; ++i) {
        curr = 1 + min(prev1, prev2); // dp[i] = 1 + min(dp[i-1], dp[i-2])
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

// Clean wrapper most interviews expect:
int minCostTargetReach(int target, vector<int>& ways) {
    return spaceOptimized(target, ways);
}

int main(){
    // Demo:
    // target=7, ways=[1,3,5] -> expected 3
    vector<int> ways = {1, 3, 5};
    int target = 7;

    // memo version needs memo sized target+1 filled with -1
    memo.assign(target + 1, -1);
    int ansMemo = solve(target, ways);

    int ansTab = tabulation(target, ways);
    int ansOpt = spaceOptimized(target, ways);

    cout << "Memo: " << ansMemo << "\n";
    cout << "Tabulation: " << (ansTab >= 1e9 ? -1 : ansTab) << "\n";
    cout << "SpaceOptimized: " << ansOpt << "\n";
    return 0;
}
