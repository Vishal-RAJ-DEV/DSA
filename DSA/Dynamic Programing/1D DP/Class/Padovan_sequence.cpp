// ============================================================================
// QUESTION: Padovan Sequence (GFG)
// ----------------------------------------------------------------------------
// Padovan is like Fibonacci but with a different recurrence:
//   P(0) = 1, P(1) = 1, P(2) = 1
//   P(n) = P(n-2) + P(n-3)  for n >= 3
//
// Sequence: 1, 1, 1, 2, 2, 3, 4, 5, 7, 9, 12, 16, 21, ...
// Example: n=3 -> P(1)+P(0) = 1+1 = 2
//          n=4 -> P(2)+P(1) = 1+1 = 2
//          n=5 -> P(3)+P(2) = 2+1 = 3
//          n=6 -> P(4)+P(3) = 2+2 = 4
//
// Return P(n) % (1e9+7) because values grow fast.
// Constraints on GFG are large (n up to 1e6), so O(n) DP is needed;
// naive recursion without memo is exponential.
//
// This file shows 3 ways to compute the same recurrence:
//  1. Memoization (Top-Down Recursion + dp) -> O(n) time, O(n) space + stack
//  2. Tabulation (Bottom-Up Iterative)      -> O(n) time, O(n) space
//  3. Space Optimized (3 variables)        -> O(n) time, O(1) space
// ============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// APPROACH 1: MEMOIZATION (Top-Down) - the original code below
// ----------------------------------------------------------------------------
// Logic:
//  solve(n) = Padovan number P(n).
//  Base: n <= 2 -> 1 (P0=P1=P2=1 by definition).
//  Else: solve(n) = (solve(n-2) + solve(n-3)) % MOD.
//    NOTE it skips n-1 entirely - unlike Fibonacci which uses n-1 and n-2.
//    That is the whole character of Padovan.
//  dp[n] caches result (-1 = not computed) so each n is solved once.
//  Without dp, recursion branches into 2 calls per level -> O(2^n).
//  With dp, each n computed once -> O(n).
// Example trace n=5:
//  solve(5) = solve(3)+solve(2) = (solve(1)+solve(0)) + 1 = (1+1)+1 = 3.
// ============================================================================
class Solution {
  public:
  int const MOD = 1e9 + 7;
  // Returns P(n). dp[n] = -1 means not computed yet.
  int solve(int n , vector<int>&dp){
      // Base: first three Padovan numbers are all 1.
      if(n <= 2) return 1;
      
      // Overlapping subproblem: reuse cached answer.
      if( dp[n] != -1) return dp[n];
      
      // Recurrence: P(n) = P(n-2) + P(n-3). Mod to avoid overflow.
      return dp[n] = ( solve(n -2 , dp) + solve(n -3 , dp) ) % MOD ;
  }
    // Wrapper: creates dp[0..n] filled with -1, starts recursion.
    int padovanSequence(int n) {
        // code here
        vector<int>dp( n +1 , -1);
        return solve(n , dp) % MOD;
    }
};




// ============================================================================
// APPROACH 2: TABULATION (Bottom-Up Iterative DP)
// ----------------------------------------------------------------------------
// Idea: solve smallest n first, no recursion.
//  dp[0] = 1, dp[1] = 1, dp[2] = 1 (base).
//  For i = 3..n: dp[i] = (dp[i-2] + dp[i-3]) % MOD.
// Answer = dp[n].
// Time: O(n), Space: O(n), no recursion stack (safe for n = 1e6).
// Example n=6: dp = [1,1,1,2,2,3,4] -> 4.
// ============================================================================
class Tabulation {
  public:
  int const MOD = 1e9 + 7;
  int padovanSequence(int n) {
      // Base: first three values are fixed.
      if (n <= 2) return 1;

      vector<int> dp(n + 1, 0);
      dp[0] = 1; // P(0)
      dp[1] = 1; // P(1)
      dp[2] = 1; // P(2)

      // Build up: P(i) needs i-2 and i-3, both already computed since i grows.
      for (int i = 3; i <= n; i++) {
          dp[i] = (dp[i - 2] + dp[i - 3]) % MOD;
      }

      return dp[n];
  }
};

// ============================================================================
// APPROACH 3: SPACE OPTIMIZED (only 3 variables)
// ----------------------------------------------------------------------------
// Observation: dp[i] needs ONLY dp[i-2] and dp[i-3]. dp[i-1] is NOT used
// for the sum, but we must still carry it forward because it becomes
// dp[i-2] / dp[i-3] in later steps. So keep a sliding window of 3:
//  a = P(i-3), b = P(i-2), c = P(i-1) at start of iteration i.
//  Then: curr = P(i) = (a + b) % MOD   // = P(i-3)+P(i-2)
//  Slide: a = b, b = c, c = curr.
// Init for i=3: a=P(0)=1, b=P(1)=1, c=P(2)=1 -> curr = 1+1 = 2 = P(3).
// Time: O(n), Space: O(1) - best for large n (GFG n up to 1e6).
// Example n=6:
//  (1,1,1) i=3->2 => (1,1,2) i=4->2 => (1,2,2) i=5->3 => (2,2,3) i=6->4.
// ============================================================================
class SpaceOptimized {
  public:
  int const MOD = 1e9 + 7;
  int padovanSequence(int n) {
      if (n <= 2) return 1; // P(0)=P(1)=P(2)=1

      long long a = 1; // P(i-3), starts P(0)
      long long b = 1; // P(i-2), starts P(1)
      long long c = 1; // P(i-1), starts P(2)

      // Each step computes P(i) = P(i-3)+P(i-2) = a+b, then slides window.
      for (int i = 3; i <= n; i++) {
          long long curr = (a + b) % MOD; // P(i)
          a = b;    // old P(i-2) becomes P(i-3) for next i
          b = c;    // old P(i-1) becomes P(i-2) for next i
          c = curr; // curr becomes P(i-1) for next i
      }

      return (int)c; // after loop, c = P(n)
  }
};


int main(){
    Solution memo;
    Tabulation tab;
    SpaceOptimized opt;

    // Expected: 0->1, 1->1, 2->1, 3->2, 4->2, 5->3, 6->4, 7->5, 8->7, 9->9
    for (int n = 0; n <= 9; n++) {
        cout << "n=" << n
             << " Memo=" << memo.padovanSequence(n)
             << " Tab=" << tab.padovanSequence(n)
             << " Opt=" << opt.padovanSequence(n) << endl;
    }
    return 0;
}