// ============================================================================
// QUESTION: Integer Break (LeetCode 343)
// ----------------------------------------------------------------------------
// Given an integer n, break it into the SUM of k (k >= 2) positive integers
// such that their PRODUCT is maximized. Return that maximum product.
//
// Examples:
//   n = 2  -> 1 + 1                 product = 1
//   n = 3  -> 1 + 2                 product = 2
//   n = 4  -> 2 + 2                 product = 4   (NOT 1+3 = 3)
//   n = 5  -> 2 + 3                 product = 6
//   n = 10 -> 3 + 3 + 4 (=3+3+2+2)  product = 36
//
// Why DP?
//  Look at the FIRST cut of i: cut off a piece of size j (1 <= j < i).
//  The remaining part (i - j) has two options:
//    1) keep it whole          -> product = j * (i - j)
//    2) break it further       -> product = j * dp[i - j]
//  We try every j, take the max. Subproblems overlap (dp[i - j] is reused
//  for many i) and the optimal split contains optimal smaller splits
//  (optimal substructure) -> plain 1D DP works.
//
// NOTE: could not read DOC/Explain Integer Break Logic.pdf in this session,
// so the explanations below are written from the standard problem logic.
// ============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// APPROACH 1: MEMOIZATION (Top-Down Recursion + DP)
// ----------------------------------------------------------------------------
// Logic:
//  solve(n) = maximum product when n is broken into >= 2 parts.
//  Base: solve(1) = 1 (nothing to break; acts as identity in products).
//  For every cut j = 1 .. n-1:
//    break_n     = j * solve(n - j)   // remainder is broken further
//    not_break_n = j * (n - j)        // remainder kept as one piece
//    maxprod = max of all those candidates
//  Memoize solve(n) in dp[n] so each value is computed only once.
//
// Example trace n = 4:
//   j=1: break = 1*solve(3)=1*2=2 , notBreak = 1*3=3 -> 3
//   j=2: break = 2*solve(2)=2*1=2 , notBreak = 2*2=4 -> 4
//   j=3: break = 3*solve(1)=3*1=3 , notBreak = 3*1=3 -> 3
//   answer = 4 (2 * 2).
//
// Time : O(n^2)  (n states, each scans up to n cuts)
// Space: O(n) dp array + O(n) recursion stack worst case.
// ============================================================================
class Solution {
public:
    int solve(int n, vector<int>& dp) {
        if (n == 1) return 1;            // base: nothing left to break
        if (dp[n] != -1) return dp[n];   // already solved -> reuse

        int maxprod = 0;

        for (int i = 1; i < n; i++) {
            int break_n = i * solve(n - i, dp); // cut i, break the rest
            int not_break_n = i * (n - i);      // cut i, keep the rest whole

            maxprod = max(maxprod, max(break_n, not_break_n));
        }

        return dp[n] = maxprod;
    }

    int integerBreak(int n) {
        vector<int> dp(n + 1, -1);
        return solve(n, dp);
    }
};



// ============================================================================
// APPROACH 2: TABULATION (Bottom-Up, iterative 1D DP)
// ----------------------------------------------------------------------------
// Same recurrence as memoization, but NO recursion - we fill the table from
// small values to big values:
//
//  dp[i] = maximum product when i is broken into >= 2 parts.
//  Base : dp[1] = 1
//  Fill : for i = 2 .. n
//           for cut j = 1 .. i-1
//             dp[i] = max( dp[i],
//                           j * (i - j),   // rest kept whole
//                           j * dp[i - j] ) // rest broken further
//  Answer = dp[n].
//
// Why does the order work? When computing dp[i], every dp[i - j] (i-j < i)
// was already computed in an earlier iteration -> no recursion needed.
//
// (Note: looping j to i-1 is required, not just i/2, because the two sides
//  are NOT symmetric once dp is involved: j*dp[i-j] and (i-j)*dp[j] differ.)
//
// Example trace filling:
//   dp[1] = 1
//   dp[2]: j=1 -> max(1*1, 1*dp[1]) = 1
//   dp[3]: j=1 -> max(1*2, 1*dp[2])=2 ; j=2 -> max(2*1, 2*dp[1])=2 -> 2
//   dp[4]: j=1 -> 3 ; j=2 -> max(4, 2*dp[1]=2)=4 ; j=3 -> 3   -> 4
//   dp[5]: j=2 -> 6 (2*dp[3]=2*2... best is 2*3 notBreak/j=3: 3*2) -> 6
//   dp[10] = 36
//
// Time : O(n^2)  (nested loops)
// Space: O(n) for dp only, O(1) extra (no recursion stack).
// ============================================================================
class Tabulation {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[1] = 1; // base case

        for (int i = 2; i <= n; i++) {
            // try every first cut j of i
            for (int j = 1; j < i; j++) {
                int not_break = j * (i - j);   // keep the (i-j) piece whole
                int break_rest = j * dp[i - j]; // break the (i-j) piece further

                // keep the best product seen so far for i
                dp[i] = max(dp[i], max(not_break, break_rest));
            }
        }

        return dp[n];
    }
};



// ============================================================================
// APPROACH 3: SPACE OPTIMIZATION (O(n) time, O(1) space - rolling variables)
// ----------------------------------------------------------------------------
// KEY OBSERVATION (why we can drop the whole dp[] array):
//
//  Claim: an optimal break never needs a piece >= 5 or a piece == 1
//  (for n >= 4). Proof sketch:
//    * piece x >= 5 -> split as 2 + (x-2):  2(x-2) = 2x - 4 > x  since x > 4.
//      So big pieces are always worth splitting.
//    * piece 4 -> same product as 2 + 2 (4 = 4), so treat it as two 2s.
//    * piece 1 -> merging 1 into any neighbour x gives (x+1) > 1*x.
//      (Only n = 2, 3 FORCE a 1: answers 1+1 and 1+2 - handled as bases.)
//  => every optimal piece is a 2 or a 3.
//
//  Therefore, for i >= 3, the LAST piece of the optimal break of i is
//  either 2 or 3:
//      dp[i] = max( best[i-2] * 2 ,   // last piece 2, rest = best split of i-2
//                   best[i-3] * 3 )   // last piece 3, rest = best split of i-3
//
//  where best[k] = best product of parts summing to k with >= 1 part
//                = max(k, dp[k])      (either keep k whole, or break it)
//
//  dp[i] now only needs best[i-2] and best[i-3] -> keep only the LAST 3
//  best values in a size-3 circular buffer: best[i % 3].
//  Read happens before write at index (i-3)%3 == i%3, so no data is lost.
//
//  This DP is identical to the famous "greedy with 3s" math solution:
//  fill with as many 3s as possible (a 4 beats 3+1), i.e.
//      n%3==0 -> 3^(n/3),  n%3==1 -> 4*3^((n-4)/3),  n%3==2 -> 2*3^((n-2)/3)
//
// Example trace (best[] inited = {0, 1, 2} for indices {0, 1, 2}):
//   i=3: 2*best[1]=2*1=2 , 3*best[0]=0     -> dp=2  ; best[0]=max(3,2)=3
//   i=4: 2*best[2]=4     , 3*best[1]=3     -> dp=4  ; best[1]=4
//   i=5: 2*best[0]=6     , 3*best[2]=6     -> dp=6  ; best[2]=6
//   i=6: 2*best[1]=8     , 3*best[0]=9     -> dp=9  ; best[0]=9
//   ... i=10 -> 36.
//
// Time : O(n)  (single pass)
// Space: O(1)  (3 slots + a couple of variables, no dp array, no recursion)
// ============================================================================
class SpaceOptimized {
public:
    int integerBreak(int n) {
        // bases where a piece of 1 is forced (theorem above assumes n >= 4)
        if (n == 2) return 1; // 1 + 1
        if (n == 3) return 2; // 1 + 2

        // best[k % 3] = best[k] = max(k, dp[k]) = best product summing to k
        int best[3] = {0, 1, 2}; // best[0]=0 (unused sentinel), best[1]=1, best[2]=2
        int dp_i = 0;            // dp[i] of the current iteration

        for (int i = 3; i <= n; i++) {
            // last piece is 2 -> rest must sum to i-2
            int use2 = best[(i - 2) % 3] * 2;
            // last piece is 3 -> rest must sum to i-3 (index 0 gives 0 at i=3)
            int use3 = best[(i - 3) % 3] * 3;

            dp_i = max(use2, use3);   // dp[i]
            best[i % 3] = max(i, dp_i); // best[i]: keep i whole vs break it
        }

        return dp_i; // dp[n]
    }
};



int main(){
    int n = 10;

    Solution memo;
    Tabulation tab;
    SpaceOptimized opt;

    // Expected for n = 10: 36 (3 + 3 + 2 + 2) from all three approaches
    cout << "Memoization  : " << memo.integerBreak(n) << endl;
    cout << "Tabulation   : " << tab.integerBreak(n) << endl;
    cout << "SpaceOptimized: " << opt.integerBreak(n) << endl;

    // small sanity checks
    for (int i = 2; i <= 50; i++) {
        int a = memo.integerBreak(i);
        int b = tab.integerBreak(i);
        int c = opt.integerBreak(i);
        if (a != b || b != c) {
            cout << "MISMATCH at n=" << i << ": " << a << " " << b << " " << c << endl;
            return 1;
        }
    }
    cout << "All approaches match for n = 2..50" << endl;
    return 0;
}
