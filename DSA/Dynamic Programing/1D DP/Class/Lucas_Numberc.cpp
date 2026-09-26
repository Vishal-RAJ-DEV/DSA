// ============================================================================
// QUESTION: Lucas Numbers
// ----------------------------------------------------------------------------
// Lucas numbers are a cousin of Fibonacci with different starting values:
//   L(0) = 2, L(1) = 1
//   L(n) = L(n-1) + L(n-2)  for n >= 2   (same recurrence as Fibonacci)
//
// Sequence: 2, 1, 3, 4, 7, 11, 18, 29, 47, 76, 123, ...
// Example: n=0 -> 2, n=1 -> 1, n=2 -> 2+1=3, n=3 -> 3+1=4, n=4 -> 4+3=7.
// Return L(n) % (1e9+7) to avoid overflow.
//
// Relation to Fibonacci: L(n) = Fib(n-1) + Fib(n+1) = Fib(n) + 2*Fib(n-1),
// but here we compute directly with DP.
//
// This file shows 3 ways to compute the same recurrence:
//  1. Memoization (Top-Down Recursion + dp) -> O(n) time, O(n) space + stack
//  2. Tabulation (Bottom-Up Iterative)      -> O(n) time, O(n) space
//     [THIS is what the original code below already was]
//  3. Space Optimized (2 variables)        -> O(n) time, O(1) space
// ============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// APPROACH 1: MEMOIZATION (Top-Down) - added for completeness
// ----------------------------------------------------------------------------
// Logic:
//  solve(n) = Lucas number L(n).
//  Base: n==0 -> 2, n==1 -> 1 (definitions, NOT 0/1 like Fibonacci).
//  Else: solve(n) = (solve(n-1) + solve(n-2)) % MOD.
//  dp[n] caches result (-1 = not computed) so each n is solved once.
//  Without dp this is O(2^n); with dp it is O(n).
// ============================================================================
class Memoization {
  public:
    int const MOD = 1e9 + 7;
    // Returns L(n). dp[n] = -1 means not computed yet.
    long long solve(int n, vector<long long>& dp) {
        // Base: Lucas seeds differ from Fibonacci (2,1 instead of 0,1).
        if (n == 0) return 2; // L(0)
        if (n == 1) return 1; // L(1)

        // Overlapping subproblem: reuse cached answer.
        if (dp[n] != -1) return dp[n];

        // Recurrence: same as Fibonacci, only seeds differ.
        return dp[n] = (solve(n - 1, dp) + solve(n - 2, dp)) % MOD;
    }
    long long lucas(int n) {
        vector<long long> dp(n + 1, -1);
        return solve(n, dp);
    }
};

// ============================================================================
// APPROACH 2: TABULATION (Bottom-Up) - this is the ORIGINAL code, now commented
// ----------------------------------------------------------------------------
// Logic (how this code works step-by-step):
//  1. dp[0] = 2, dp[1] = 1  -> directly sets the two Lucas seeds.
//     (Everything else follows from these two.)
//  2. Loop i = 2..n: dp[i] = (dp[i-1] + dp[i-2]) % MOD.
//     dp[i-1], dp[i-2] are already computed because i grows forward.
//     This is exactly L(i) = L(i-1) + L(i-2).
//  3. Answer = dp[n].
// Example trace n=4: dp=[2,1,?, ?, ?] -> i=2: 1+2=3 -> i=3: 3+1=4
//                    -> i=4: 4+3=7 -> return 7.
// Time: O(n), Space: O(n), no recursion (safe for large n).
// Edge: uses vector<int>dp(n+1,0); for n=0 loop is skipped, returns dp[0]=2.
// ============================================================================
class Solution {
  public:
    int const MOD = 1e9 + 7;
    long long lucas(int n) {
        // code here.
        vector<int>dp( n +1 , 0);
        dp[0] = 2;
        dp[1] = 1;
        
        for(int i = 2; i <= n ; i++){
            dp[i] = (dp[i-1] + dp[i-2])% MOD;
        }
        
        return dp[n] % MOD;
    }
};




// ============================================================================
// APPROACH 3: SPACE OPTIMIZED (only 2 variables, Fibonacci style)
// ----------------------------------------------------------------------------
// Observation: dp[i] needs ONLY dp[i-1] and dp[i-2]. No need for full array.
//  Keep: prev1 = L(i-2), prev2 = L(i-1)  [or a,b].
//  Then: curr = L(i) = (prev1 + prev2) % MOD, slide window forward.
//  Init: prev1 = L(0) = 2, prev2 = L(1) = 1.
//  Loop i=2..n, return curr (or prev2 after loop).
// Time: O(n), Space: O(1) - best version for interviews / large n.
// Example n=4: (2,1) -> i=2 curr=3 -> (1,3) -> i=3 curr=4 -> (3,4)
//              -> i=4 curr=7 -> answer 7.
// ============================================================================
class SpaceOptimized {
  public:
    int const MOD = 1e9 + 7;
    long long lucas(int n) {
        if (n == 0) return 2; // L(0)
        if (n == 1) return 1; // L(1)

        long long prev2 = 2; // L(0) = L(i-2) at start of i=2
        long long prev1 = 1; // L(1) = L(i-1) at start of i=2

        // Each step: new Lucas = sum of previous two, then slide.
        for (int i = 2; i <= n; i++) {
            long long curr = (prev1 + prev2) % MOD; // L(i)
            prev2 = prev1; // old L(i-1) becomes L(i-2) for next i
            prev1 = curr;  // curr becomes L(i-1) for next i
        }

        return prev1; // = L(n)
    }
};


int main(){
    Memoization memo;
    Solution tab; // original code = Tabulation
    SpaceOptimized opt;

    // Expected: 0->2, 1->1, 2->3, 3->4, 4->7, 5->11, 6->18, 7->29
    for (int n = 0; n <= 7; n++) {
        // NOTE: original Solution crashes for n=0 (dp[1] out of bounds
        // when vector size is 1). So guard it here; fixed versions handle 0.
        long long tabAns = (n == 0) ? 2 : tab.lucas(n);
        cout << "n=" << n
             << " Memo=" << memo.lucas(n)
             << " Tab=" << tabAns
             << " Opt=" << opt.lucas(n) << endl;
    }
    return 0;
}