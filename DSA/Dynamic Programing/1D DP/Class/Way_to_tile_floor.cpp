// ============================================================================
// QUESTION: Ways to Tile Floor (2 x n board with 2 x 1 dominoes)
// ----------------------------------------------------------------------------
// Given floor of size 2 x n, count ways to tile it with 2 x 1 tiles
// (tiles can be placed vertically OR horizontally, rotation allowed).
//
// Example:
//   n=1 -> 1 way:   [|]
//   n=2 -> 2 ways:  [||] , [=] (two horizontal stacked)
//   n=3 -> 3 ways
//   n=4 -> 5 ways  (it becomes Fibonacci!)
//
// Why recurrence f(n) = f(n-1) + f(n-2)?
//  Look at the RIGHTMOST column of the 2 x n board:
//  Case 1: place ONE vertical tile covering column n.
//           Remaining board = 2 x (n-1) -> f(n-1) ways.
//  Case 2: place TWO horizontal tiles stacked, covering columns n-1 and n.
//           (one horizontal alone is impossible, it leaves a hole, so they
//            must come in a pair). Remaining board = 2 x (n-2) -> f(n-2) ways.
//  These 2 cases are disjoint and cover all possibilities, so add them.
//
// Base cases:
//  n=0 -> 1 way (empty floor, do nothing - needed for recurrence)
//  n=1 -> 1 way (single vertical tile)
//  n<0 -> 0 ways (invalid, overshoot) - handled by n<=1 returning 1 here.
//
// This file shows 3 ways to compute the same recurrence:
//  1. Memoization (Top-Down Recursion + dp) -> O(n) time, O(n) space + stack
//  2. Tabulation (Bottom-Up Iterative)      -> O(n) time, O(n) space
//  3. Space Optimized (2 variables)        -> O(n) time, O(1) space
// NOTE: answer grows like Fibonacci, so for large n use long long / modulo
// (e.g. GFG asks mod 1e9+7). Here int is kept to match original code.
// ============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// APPROACH 1: MEMOIZATION (Top-Down) - the original code below
// ----------------------------------------------------------------------------
// Logic:
//  solve(n) = number of ways to tile 2 x n board.
//  If n<=1 return 1 (base: empty or single column).
//  Else solve(n) = solve(n-1)  // put vertical tile at end
//                + solve(n-2); // put pair of horizontal tiles at end
//  dp[n] caches result so each n computed once (else naive recursion is O(2^n)).
// Example trace n=4:
//  solve(4) = solve(3)+solve(2) = (solve(2)+solve(1)) + (solve(1)+solve(0))
//           = (2+1)+(1+1) = 5.
// ============================================================================
class Solution {
public:
    // Returns ways to tile 2 x n. dp[n] = -1 means not computed yet.
    int solve(vector<int>& dp, int n) {
        // Base: 0-length floor has 1 way (empty), 1-length has 1 way (one |).
        if (n <= 1)
            return 1;

        // Overlapping subproblem: reuse cached answer.
        if (dp[n] != -1)
            return dp[n];

        // Choice 1: vertical tile -> n-1 left. Choice 2: 2x horizontal -> n-2 left.
        return dp[n] = solve(dp, n - 1) + solve(dp, n - 2);
    }

    // Wrapper: creates dp[0..n] with -1 (unknown) and starts recursion.
    int numberOfWays(int n) {
        vector<int> dp(n + 1, -1);

        return solve(dp, n);  
    }
};



// ============================================================================
// APPROACH 2: TABULATION (Bottom-Up Iterative DP)
// ----------------------------------------------------------------------------
// Idea: solve smallest subproblems first, no recursion.
//  dp[0] = 1 (empty floor), dp[1] = 1 (one vertical tile).
//  For i = 2..n: dp[i] = dp[i-1] + dp[i-2]
//    (vertical at end + pair-horizontal at end, same logic as memoization).
// Answer = dp[n].
// Time: O(n), Space: O(n), no recursion stack.
// Example n=4: dp=[1,1,2,3,5] -> 5.
// ============================================================================
class Tabulation {
public:
    int numberOfWays(int n) {
        // Handle base directly (also avoids dp size issue when n=0).
        if (n <= 1) return 1;

        vector<int> dp(n + 1, 0);
        dp[0] = 1; // 1 way to tile 2x0 (do nothing)
        dp[1] = 1; // 1 way to tile 2x1 (single |)

        // Build up: to tile 2xi, either add | to 2x(i-1) or == to 2x(i-2).
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};

// ============================================================================
// APPROACH 3: SPACE OPTIMIZED (only 2 variables, Fibonacci style)
// ----------------------------------------------------------------------------
// Observation: dp[i] needs ONLY dp[i-1] and dp[i-2]. No need for full array.
//  Keep: prev2 = f(i-2), prev1 = f(i-1).
//  Then: curr = prev1 + prev2  (= f(i)), slide window forward.
//  Start: prev2 = f(0) = 1, prev1 = f(1) = 1.
//  Loop i=2..n, return prev1 after loop (= f(n)).
// Time: O(n), Space: O(1).
// Example n=4: (1,1) -> i=2 curr=2 -> (1,2) -> i=3 curr=3 -> (2,3)
//              -> i=4 curr=5 -> answer 5.
// ============================================================================
class SpaceOptimized {
public:
    int numberOfWays(int n) {
        if (n <= 1) return 1; // f(0)=1, f(1)=1

        int prev2 = 1; // f(0)
        int prev1 = 1; // f(1)

        // Each step: new ways = ways ending with | + ways ending with ==
        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2; // f(i) = f(i-1) + f(i-2)
            prev2 = prev1; // slide: old f(i-1) becomes f(i-2) for next i
            prev1 = curr;  // curr becomes f(i-1) for next i
        }

        return prev1; // = f(n)
    }
};


int main(){
    Solution memo;
    Tabulation tab;
    SpaceOptimized opt;

    // Expected Fibonacci-like: n=1->1, n=2->2, n=3->3, n=4->5, n=5->8
    for (int n = 1; n <= 5; n++) {
        cout << "n=" << n
             << " Memo=" << memo.numberOfWays(n)
             << " Tab=" << tab.numberOfWays(n)
             << " Opt=" << opt.numberOfWays(n) << endl;
    }
    return 0;
}