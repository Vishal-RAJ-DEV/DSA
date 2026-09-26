/*
================================================================================
PROBLEM: Perfect Square
================================================================================

Given an integer n, return the LEAST number of perfect square numbers
that sum to n.

Perfect squares: 1, 4, 9, 16, 25, 36, ... (i*i for i = 1, 2, 3, ...)

Example: n = 12
  12 = 4 + 4 + 4 = 3 squares  (best)
  12 = 9 + 1 + 1 + 1 = 4 squares
  12 = 1+1+1+1+1+1+1+1+1+1+1+1 = 12 squares
  Answer: 3

Example: n = 13
  13 = 4 + 9 = 2 squares  (best)
  Answer: 2

================================================================================
DP FORMULA
================================================================================

dp[i] = minimum number of perfect squares that sum to i

For each i, try ALL perfect squares j*j <= i:
  If we USE j*j, then we need 1 (for j*j) + dp[i - j*j] (for the rest)

  dp[i] = min over all j where j*j <= i of (1 + dp[i - j*j])

Base case: dp[0] = 0 (zero needs zero squares)

Example trace for n = 12:

  dp[0] = 0

  dp[1]: try 1*1=1 -> 1 + dp[0] = 1        => dp[1] = 1

  dp[2]: try 1*1=1 -> 1 + dp[1] = 2        => dp[2] = 2

  dp[3]: try 1*1=1 -> 1 + dp[2] = 3        => dp[3] = 3

  dp[4]: try 1*1=1 -> 1 + dp[3] = 4
          try 2*2=4 -> 1 + dp[0] = 1        => dp[4] = 1  (4 = 2*2)

  dp[5]: try 1*1=1 -> 1 + dp[4] = 2
          try 2*2=4 -> 1 + dp[1] = 2        => dp[5] = 2  (5 = 4+1)

  dp[6]: try 1*1=1 -> 1 + dp[5] = 3
          try 2*2=4 -> 1 + dp[2] = 3        => dp[6] = 3  (6 = 4+1+1)

  dp[7]: try 1*1=1 -> 1 + dp[6] = 4
          try 2*2=4 -> 1 + dp[3] = 4        => dp[7] = 4  (7 = 4+1+1+1)

  dp[8]: try 1*1=1 -> 1 + dp[7] = 5
          try 2*2=4 -> 1 + dp[4] = 2        => dp[8] = 2  (8 = 4+4)

  dp[9]: try 1*1=1 -> 1 + dp[8] = 3
          try 2*2=4 -> 1 + dp[5] = 3
          try 3*3=9 -> 1 + dp[0] = 1        => dp[9] = 1  (9 = 3*3)

  dp[10]: try 1*1=1 -> 1 + dp[9] = 2
           try 2*2=4 -> 1 + dp[6] = 4
           try 3*3=9 -> 1 + dp[1] = 2       => dp[10] = 2 (10 = 9+1)

  dp[11]: try 1*1=1 -> 1 + dp[10] = 3
           try 2*2=4 -> 1 + dp[7] = 5
           try 3*3=9 -> 1 + dp[2] = 3       => dp[11] = 3 (11 = 9+1+1)

  dp[12]: try 1*1=1 -> 1 + dp[11] = 4
           try 2*2=4 -> 1 + dp[8] = 3
           try 3*3=9 -> 1 + dp[3] = 4       => dp[12] = 3 (12 = 4+4+4)

  ANSWER: dp[12] = 3

VISUAL: How dp[12] is computed
  ┌────────────────────────────────────────────────────────────┐
  │  dp[12] = min of:                                         │
  │                                                            │
  │    1 + dp[12 - 1]  = 1 + dp[11] = 1 + 3 = 4              │
  │    1 + dp[12 - 4]  = 1 + dp[8]  = 1 + 2 = 3  <-- BEST    │
  │    1 + dp[12 - 9]  = 1 + dp[3]  = 1 + 3 = 4              │
  │                                                            │
  │  dp[12] = 3                                               │
  └────────────────────────────────────────────────────────────┘

TIME COMPLEXITY:  O(n * sqrt(n))
  - Outer loop: i from 1 to n (n iterations)
  - Inner loop: j from 1 to sqrt(i) (sqrt(n) iterations on average)

SPACE COMPLEXITY: O(n) for the dp array
================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// MEMOIZATION (TOP-DOWN DP)
// ============================================================================
//
// IDEA:
//   Start from n, recursively try every perfect square j*j <= n.
//   For each choice, recursively solve for the remaining value (n - j*j).
//   Take the minimum across all choices.
//
//   dp[n] = min(1 + dp[n - j*j])  for all j where j*j <= n
//
// WHY TOP-DOWN?
//   - We start from the GOAL (n) and work DOWN to base case (0)
//   - Use recursion + memoization to avoid recomputing subproblems
//   - Natural to write: "to solve n, try all squares and pick best"
//
// RECURSION TREE for n=5:
//
//                     solve(5)
//                    /    |    \
//                 1+     1+     (3*3>5, stop)
//               solve(4) solve(1)
//              /   \        |
//           1+    1+      1+
//         solve(3) solve(0) solve(0)
//         /   \
//       1+    1+
//     solve(2) solve(-1) -- invalid, skip
//      /
//    1+
//  solve(1)
//    |
//  1+solve(0)
//
// Without memoization, this would be exponential.
// With memoization, each subproblem solved ONCE -> O(n * sqrt(n))
//
// ============================================================================

class Memoization {
public:

    int solve(int n, vector<int>& dp) {

        // Base case: 0 needs 0 perfect squares
        if (n == 0) return 0;

        // If already computed, return cached answer
        if (dp[n] != -1) {
            return dp[n];
        }

        int mincnt = INT_MAX;

        // Try every perfect square j*j that is <= n
        // j=1: try using 1 (1*1)
        // j=2: try using 4 (2*2)
        // j=3: try using 9 (3*3)
        // ...and so on until j*j > n
        for (int i = 1; i * i <= n; i++) {

            // 1 = we use the square i*i
            // solve(n - i*i) = best answer for what's left
            int cnt = 1 + solve(n - i * i, dp);

            mincnt = min(mincnt, cnt);
        }

        // Cache and return the best answer for n
        return dp[n] = mincnt;
    }

    int numSquares(int n) {

        // dp[i] = -1 means "not computed yet"
        // dp[i] = k means "minimum squares to make i is k"
        vector<int> dp(n + 1, -1);

        return solve(n, dp);
    }
};

// ============================================================================
// TABULATION (BOTTOM-UP DP)
// ============================================================================
//
// IDEA:
//   Build the answer FROM THE BOTTOM: start from dp[0] = 0,
//   then compute dp[1], dp[2], ..., dp[n] in order.
//
//   For each i, try all perfect squares j*j <= i:
//     dp[i] = min(dp[i], 1 + dp[i - j*j])
//
// WHY BOTTOM-UP?
//   - No recursion (no stack overflow risk)
//   - dp[i - j*j] is ALWAYS computed before dp[i] (since i-j*j < i)
//   - Slightly faster in practice (no function call overhead)
//
// DP TABLE FILL for n=12:
//
//   i=0:  dp[0] = 0                          (base case)
//
//   i=1:  try j=1: dp[1] = min(INF, 1+dp[0]) = 1
//
//   i=2:  try j=1: dp[2] = min(INF, 1+dp[1]) = 2
//
//   i=3:  try j=1: dp[3] = min(INF, 1+dp[2]) = 3
//
//   i=4:  try j=1: dp[4] = min(INF, 1+dp[3]) = 4
//          try j=2: dp[4] = min(4,   1+dp[0]) = 1   <-- 4 is 2*2
//
//   i=5:  try j=1: dp[5] = min(INF, 1+dp[4]) = 2
//          try j=2: dp[5] = min(2,   1+dp[1]) = 2   (tie: 4+1 or 1+4)
//
//   i=6:  try j=1: dp[6] = min(INF, 1+dp[5]) = 3
//          try j=2: dp[6] = min(3,   1+dp[2]) = 3
//
//   i=7:  try j=1: dp[7] = min(INF, 1+dp[6]) = 4
//          try j=2: dp[7] = min(4,   1+dp[3]) = 4
//
//   i=8:  try j=1: dp[8] = min(INF, 1+dp[7]) = 5
//          try j=2: dp[8] = min(5,   1+dp[4]) = 2   <-- 8 = 4+4
//
//   i=9:  try j=1: dp[9] = min(INF, 1+dp[8]) = 3
//          try j=2: dp[9] = min(3,   1+dp[5]) = 3
//          try j=3: dp[9] = min(3,   1+dp[0]) = 1   <-- 9 = 3*3
//
//   i=10: try j=1: dp[10] = min(INF, 1+dp[9])  = 2
//          try j=2: dp[10] = min(2,   1+dp[6])  = 2
//          try j=3: dp[10] = min(2,   1+dp[1])  = 2  (9+1)
//
//   i=11: try j=1: dp[11] = min(INF, 1+dp[10]) = 3
//          try j=2: dp[11] = min(3,   1+dp[7])  = 3
//          try j=3: dp[11] = min(3,   1+dp[2])  = 3  (9+1+1)
//
//   i=12: try j=1: dp[12] = min(INF, 1+dp[11]) = 4
//          try j=2: dp[12] = min(4,   1+dp[8])  = 3  <-- 12 = 4+4+4
//          try j=3: dp[12] = min(3,   1+dp[3])  = 3
//
//   FINAL TABLE:
//   Index:  0  1  2  3  4  5  6  7  8  9  10  11  12
//   dp:    [0][1][2][3][1][2][3][4][2][1][ 2][ 3][ 3]
// ============================================================================

class Tabulation {
public:

    int numSquares(int n) {

        // dp[i] = minimum perfect squares to sum to i
        // Initialize with INT_MAX (unreachable)
        vector<int> dp(n + 1, INT_MAX);

        // Base case: 0 needs 0 squares
        dp[0] = 0;

        // Fill dp table from 1 to n
        for (int i = 1; i <= n; i++) {

            // Try every perfect square j*j that is <= i
            // j=1 -> square=1, j=2 -> square=4, j=3 -> square=9, ...
            for (int j = 1; j * j <= i; j++) {

                int square = j * j;

                // If we USE square j*j:
                //   1 (for j*j itself) + dp[i - square] (for the rest)
                // Take minimum across all choices
                dp[i] = min(
                    dp[i],
                    1 + dp[i - square]
                );
            }
        }

        // dp[n] = answer for n
        return dp[n];
    }
};

// ============================================================================
// DRIVER CODE
// ============================================================================
// Uncomment the approach you want to test:
// ============================================================================

int main(){
    // Memoization m;
    // cout << m.numSquares(12) << endl;  // Output: 3

    // Tabulation t;
    // cout << t.numSquares(12) << endl;  // Output: 3

    return 0;
}