#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * ============================================================================
 * KNIGHT DIALER PROBLEM (LeetCode 935)
 * ============================================================================
 * Count distinct phone numbers of length 'n' dialed by a Knight on keypad:
 *
 *      1  2  3
 *      4  5  6
 *      7  8  9
 *         0
 *
 * Knight moves in L-shape. Precomputed valid jumps:
 *   0 -> 4, 6        1 -> 6, 8        2 -> 7, 9        3 -> 4, 8
 *   4 -> 0, 3, 9     5 -> (none)      6 -> 0, 1, 7     7 -> 2, 6
 *   8 -> 1, 3        9 -> 2, 4
 *
 * Answer = sum over all starting digits 0-9 of count(sequences of len n).
 * Return answer % (1e9 + 7).
 *
 * This file contains 4 approaches for the SAME problem, from brute force
 * to optimal. Class names are renamed as per the technique used:
 *   1. RecursiveSolution       -> Pure Recursion (Brute Force / Backtracking)
 *   2. MemoizationSolution     -> Top-Down DP (Recursion + Memoization)
 *   3. TabulationSolution      -> Bottom-Up DP (Iterative 2D table)
 *   4. SpaceOptimizedSolution  -> Bottom-Up DP with O(1) extra space
 * ============================================================================
 */


// ============================================================================
// APPROACH 1: PURE RECURSION (Brute Force / Backtracking)
// Class: RecursiveSolution
// ----------------------------------------------------------------------------
// IDEA:
//   solve(digit, remaining) = number of ways to complete the number if we
//   are currently AT 'digit' and 'remaining' more hops are still to be made.
//   From 'digit', try every valid knight jump and recurse.
//
// RECURRENCE:
//   solve(digit, 0) = 1            // no hops left -> 1 complete sequence
//   solve(digit, r) = sum over next in moves[digit] of solve(next, r-1)
//
// FINAL ANSWER:
//   knightDialer(n) = sum over digit 0..9 of solve(digit, n-1)
//
// TIME  : O( branching ^ n ) ~ exponential. Same (digit, remaining) state
//         is recomputed thousands of times. TLE for large n.
// SPACE : O(n) recursion stack depth.
//
// WHEN TO USE: Only to understand the recurrence. Base for next approaches.
// ============================================================================
class RecursiveSolution {
public:
    const int MOD = 1e9 + 7;

    // moves[d] = all digits reachable by one knight jump from digit d.
    vector<vector<int>> moves = {
        {4, 6},       // 0
        {6, 8},       // 1
        {7, 9},       // 2
        {4, 8},       // 3
        {0, 3, 9},    // 4
        {},           // 5 (isolated, knight can never land on / leave 5)
        {0, 1, 7},    // 6
        {2, 6},       // 7
        {1, 3},       // 8
        {2, 4}        // 9
    };

    // Count sequences starting FROM 'digit' with 'remaining' jumps still left.
    long long solve(int digit, int remaining) {
        // Base case: no jumps left -> current path forms 1 valid number.
        if (remaining == 0) {
            return 1;
        }

        long long ans = 0;
        // Explore every knight move (backtracking step).
        for (int nextDigit : moves[digit]) {
            ans = (ans + solve(nextDigit, remaining - 1)) % MOD;
        }
        return ans;
    }

    int knightDialer(int n) {
        long long ans = 0;
        // A number of length n can START from any digit 0..9.
        for (int digit = 0; digit <= 9; digit++) {
            ans = (ans + solve(digit, n - 1)) % MOD; // n-1 jumps to make
        }
        return ans;
    }
};


// ============================================================================
// APPROACH 2: TOP-DOWN DP (Recursion + MEMOIZATION)
// Class: MemoizationSolution
// ----------------------------------------------------------------------------
// IDEA:
//   Same recurrence as Approach 1, but CACHE the result of each state
//   (digit, remaining) in a table dp[digit][remaining] so it is computed
//   only ONCE. This converts exponential recursion into polynomial DP.
//
// STATE:
//   dp[digit][remaining] = solve(digit, remaining), -1 means "not computed".
//
// TRANSITION: identical to recursion:
//   dp[d][r] = sum over next in moves[d] of solve(next, r-1)
//
// TIME  : O(10 * n * avg_moves) = O(n). Only 10*n distinct states.
// SPACE : O(10 * n) for dp table + O(n) recursion stack.
//
// WHEN TO USE: Easiest optimization; good when you already have recursion.
// ============================================================================
class MemoizationSolution {
public:
    const int MOD = 1e9 + 7;

    vector<vector<int>> moves = {
        {4, 6},
        {6, 8},
        {7, 9},
        {4, 8},
        {0, 3, 9},
        {},
        {0, 1, 7},
        {2, 6},
        {1, 3},
        {2, 4}
    };

    // dp[digit][remaining] caches answer for that state. -1 = uncomputed.
    vector<vector<long long>> dp;

    long long solve(int digit, int remaining) {
        // Base case: sequence complete.
        if (remaining == 0) {
            return 1;
        }

        // MEMOIZATION CHECK: return already-computed state in O(1).
        if (dp[digit][remaining] != -1) {
            return dp[digit][remaining];
        }

        long long ans = 0;
        for (int nextDigit : moves[digit]) {
            ans = (ans + solve(nextDigit, remaining - 1)) % MOD;
        }

        // MEMOIZATION STORE: save before returning.
        return dp[digit][remaining] = ans;
    }

    int knightDialer(int n) {
        // 10 digits, 'remaining' ranges 0..n-1, so size n is enough.
        dp.assign(10, vector<long long>(n, -1));

        long long ans = 0;
        for (int digit = 0; digit <= 9; digit++) {
            ans = (ans + solve(digit, n - 1)) % MOD;
        }
        return ans;
    }
};


// ============================================================================
// APPROACH 3: BOTTOM-UP DP (TABULATION - Iterative 2D table)
// Class: TabulationSolution
// ----------------------------------------------------------------------------
// IDEA:
//   Flip memoization upside-down: solve smallest subproblems FIRST
//   (length = 1) and iteratively build up to length = n. No recursion.
//
// STATE:
//   dp[len][digit] = number of sequences of length 'len' ENDING at 'digit'.
//   (Note: direction flipped vs top-down which counted sequences STARTING
//    from digit; both give same total after summing over all digits.)
//
// BASE CASE:
//   dp[1][digit] = 1 for all digits (single-digit number).
//
// TRANSITION (for len = 2..n):
//   A sequence of length 'len' ending at 'nextDigit' comes from a sequence
//   of length 'len-1' ending at 'digit', where nextDigit is in moves[digit].
//   So: dp[len][nextDigit] += dp[len-1][digit]
//
// FINAL ANSWER:
//   sum over digit 0..9 of dp[n][digit]
//
// TIME  : O(n * 10 * avg_moves) = O(n)
// SPACE : O(n * 10) = O(n) for the full table. No recursion stack.
//
// WHEN TO USE: Preferred in interviews; avoids recursion overhead / limits.
// ============================================================================
class TabulationSolution {
public:
    int knightDialer(int n) {
        const int MOD = 1e9 + 7;

        vector<vector<int>> moves = {
            {4, 6},
            {6, 8},
            {7, 9},
            {4, 8},
            {0, 3, 9},
            {},
            {0, 1, 7},
            {2, 6},
            {1, 3},
            {2, 4}
        };

        // dp[len][digit]: count of length-'len' numbers ending at 'digit'.
        vector<vector<long long>> dp(n + 1, vector<long long>(10, 0));

        // Base case: length-1 number -> exactly 1 way to end at each digit.
        for (int digit = 0; digit <= 9; digit++) {
            dp[1][digit] = 1;
        }

        // Fill table bottom-up: len = 2 to n.
        for (int len = 2; len <= n; len++) {
            for (int digit = 0; digit <= 9; digit++) {
                // Propagate count from 'digit' (len-1) to each reachable next.
                for (int nextDigit : moves[digit]) {
                    dp[len][nextDigit] =
                        (dp[len][nextDigit] + dp[len - 1][digit]) % MOD;
                }
            }
        }

        // Sum over all ending digits for length n.
        long long ans = 0;
        for (int digit = 0; digit <= 9; digit++) {
            ans = (ans + dp[n][digit]) % MOD;
        }
        return ans;
    }
};


// ============================================================================
// APPROACH 4: SPACE-OPTIMIZED BOTTOM-UP DP (Rolling Array, BEST)
// Class: SpaceOptimizedSolution
// ----------------------------------------------------------------------------
// IDEA:
//   Key observation on Approach 3: dp[len] depends ONLY on dp[len-1].
//   So instead of storing all n rows, keep just TWO 1D arrays:
//   'dp'   = counts for previous length (len-1)
//   'next' = counts being built for current length (len)
//
// ALGORITHM:
//   1. dp[d] = 1 for all d            (length = 1 base case)
//   2. For len = 2..n:
//        next = [0]*10
//        for each digit d: for each nxt in moves[d]:
//            next[nxt] = (next[nxt] + dp[d]) % MOD
//        dp = next                      (roll forward)
//   3. Answer = sum(dp)
//
// TIME  : O(n * 10 * avg_moves) = O(n) - same as tabulation.
// SPACE : O(10) = O(1) - only two arrays of size 10. OPTIMAL.
//
// WHEN TO USE: Always for final submission - fastest + least memory.
// NOTE: Digit 5 naturally stays 0 for len >= 2 since nothing moves to it
//       (moves lists never contain 5), which the code handles automatically.
// ============================================================================
class SpaceOptimizedSolution {
public:
    int knightDialer(int n) {
        const int MOD = 1e9 + 7;

        vector<vector<int>> moves = {
            {4, 6},
            {6, 8},
            {7, 9},
            {4, 8},
            {0, 3, 9},
            {},
            {0, 1, 7},
            {2, 6},
            {1, 3},
            {2, 4}
        };

        // dp[digit] = count of numbers of CURRENT length ending at 'digit'.
        // Start with length = 1 base case.
        vector<long long> dp(10, 1);

        // Roll from length 2 up to n.
        for (int len = 2; len <= n; len++) {
            vector<long long> next(10, 0); // counts for current 'len'

            for (int digit = 0; digit <= 9; digit++) {
                for (int nextDigit : moves[digit]) {
                    next[nextDigit] =
                        (next[nextDigit] + dp[digit]) % MOD;
                }
            }

            dp = next; // discard older lengths, keep only latest
        }

        long long ans = 0;
        for (int digit = 0; digit <= 9; digit++) {
            ans = (ans + dp[digit]) % MOD;
        }
        return ans;
    }
};




int main(){
    return 0;
}
