// =============================================================================
// PROBLEM: Maximize The Cut Segments (GFG)
// -----------------------------------------------------------------------------
// Given a rod of length `n`, and three allowed cut lengths `x, y, z`.
// In one step you must cut off exactly x or y or z length.
// Goal: cut the rod into MAXIMUM number of pieces such that the pieces
// exactly sum to n (no leftover).
// If it is impossible to cut exactly, return 0.
//
// Examples:
//   n=4, x=2, y=1, z=1  -> 4 pieces (1+1+1+1). Answer = 4.
//   n=5, x=5, y=3, z=2  -> 2 pieces (3+2).     Answer = 2.
//   n=7, x=5, y=2, z=2  -> 2 pieces (5+2).     Answer = 2.
//   n=3, x=5, y=7, z=9  -> impossible.         Answer = 0.
//
// Core idea (all 3 methods below):
//   dp[i] = max pieces to get exact length i, or -1/IMPOSSIBLE if not possible.
//   Recurrence: to build length i, last cut was x or y or z, so:
//      dp[i] = 1 + max(dp[i-x], dp[i-y], dp[i-z])  (only valid predecessors)
//   Base: dp[0] = 0 (zero length needs zero pieces).
//
// THREE WAYS IN THIS FILE:
//   1. SolutionMemo      : top-down recursion + memo, O(n) space.
//   2. SolutionTabulation: bottom-up, O(n) space.
//   3. SolutionSpaceOpt  : bottom-up with circular buffer, O(max(x,y,z)) space.
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

// =============================================================================
// METHOD 1: TOP-DOWN MEMOIZATION (recursion + dp array)
// -----------------------------------------------------------------------------
// Logic: solve(n) = max pieces for length n.
//   - if n == 0: exact fit, 0 more pieces needed -> return 0.
//   - if n < 0 : overshot, this path is invalid -> return -INF (-1e9) so that
//                max() never picks it (even after +1 it stays very negative).
//   - if dp[n] != -1: already solved -> reuse (memo part).
//   - else try all 3 cuts: a = solve(n-x), b = solve(n-y), c = solve(n-z).
//     Answer = max(a,b,c) + 1  (+1 = the current cut we just made).
// How it works: recursion explores n -> n-x/y/z -> ... -> 0 or negative.
//   memo[] ensures each length n is computed only once.
// Example: n=5,x=5,y=3,z=2:
//   solve(5) = 1 + max(solve(0), solve(2), solve(3))
//   solve(0)=0 is valid, solve(2)->solve(0) via z=2, solve(3)->solve(0) via y=3.
//   Best = 1 + max(0, 1, 1) = 2 (3+2).
// At the end: max(0, ans) converts "impossible" (negative) to 0 as asked.
// Time: O(n), Space: O(n) memo + O(n) recursion stack.
// =============================================================================
class SolutionMemo {
public:
    int solve(int n, int x, int y, int z, vector<int>& dp) {
        // Base case 1: exact length achieved, no more pieces needed.
        if (n == 0)
            return 0;

        // Base case 2: overshot (negative length) -> invalid path.
        // Return -INF so max() ignores it.
        if (n < 0)
            return -1e9;

        // Memo check: if dp[n] already computed, return it directly.
        if (dp[n] != -1)
            return dp[n];

        // Try cutting x, y, z as the LAST cut and solve the remaining length.
        int a = solve(n - x, x, y, z, dp);
        int b = solve(n - y, x, y, z, dp);
        int c = solve(n - z, x, y, z, dp);

        // +1 counts the current cut; max picks the cut giving most pieces.
        // If all of a,b,c are -INF (impossible), dp[n] stays very negative.
        return dp[n] = max({a, b, c}) + 1;
    }

    int maximizeTheCuts(int n, int x, int y, int z) {
        // dp[i] = -1 means "not computed yet". NOTE: -1 doubles as
        // "impossible" later, but here dp[0] is never -1 after solve runs.
        vector<int> dp(n + 1, -1);

        int ans = solve(n, x, y, z, dp);

        // If ans < 0, exact cut was impossible -> return 0 per problem.
        return max(0, ans);
    }
};

// =============================================================================
// METHOD 2: BOTTOM-UP TABULATION (iterative, O(n) space)
// -----------------------------------------------------------------------------
// Logic: same recurrence, but fill dp[0..n] in increasing order.
//   dp[0] = 0 (0 length = 0 pieces).
//   dp[i] = -1 initially = "impossible".
//   For each length i = 1..n:
//     - if we can come from i-x (i>=x and dp[i-x] is possible),
//       candidate = dp[i-x] + 1 (one extra cut of length x).
//     - similarly for y and z. Take max of valid candidates.
// How it works: dp[i-x] < i, so already computed. We extend only from
//   reachable lengths (dp[...] != -1), which guarantees exact sum.
// Example: n=4,x=2,y=1,z=1:
//   dp[0]=0
//   dp[1]=dp[0]+1=1, dp[2]=max(dp[0]+1,dp[1]+1)=2, ... dp[4]=4.
// Time: O(n), Space: O(n).
// =============================================================================
class SolutionTabulation {
public:
    int maximizeTheCuts(int n, int x, int y, int z) {
        // dp[i] = max pieces for length i, -1 = impossible.
        vector<int> dp(n + 1, -1);

        // Base: length 0 needs 0 pieces.
        dp[0] = 0;

        // Build i = 1..n in order; all dependencies (i-x/y/z) are smaller.
        for (int i = 1; i <= n; i++) {

            // Last cut was x: need i>=x and prefix (i-x) must be reachable.
            if (i >= x && dp[i - x] != -1)
                dp[i] = max(dp[i], dp[i - x] + 1);

            // Last cut was y.
            if (i >= y && dp[i - y] != -1)
                dp[i] = max(dp[i], dp[i - y] + 1);

            // Last cut was z.
            if (i >= z && dp[i - z] != -1)
                dp[i] = max(dp[i], dp[i - z] + 1);
        }

        // dp[n] = -1 means impossible -> return 0.
        return max(0, dp[n]);
    }
};



// =============================================================================
// METHOD 3: SPACE-OPTIMIZED BOTTOM-UP (circular buffer, O(max) space)
// -----------------------------------------------------------------------------
// KEY OBSERVATION: dp[i] depends ONLY on dp[i-x], dp[i-y], dp[i-z].
//   So we only need to remember the last max(x,y,z) values, not all n.
// HOW (circular buffer):
//   size = max(x,y,z) + 1. Slot of length i is i % size.
//   dp_mod[(i-x) % size] holds answer for length (i-x) because (i-x) was
//   computed within the last max() steps, so its slot has NOT been
//   overwritten yet (distance x,y,z < size guarantees a different slot
//   from i % size).
// STEPS:
//   1. dp array of `size`, init -1 (impossible), dp[0] = 0.
//   2. For i = 1..n: compute ans = max of reachable predecessors + 1,
//      using modulo indices. Then STORE dp[i % size] = ans (overwrites the
//      value of i-size, which will never be needed again because future
//      queries only look back at most max(x,y,z) = size-1 steps).
//   3. Answer = dp[n % size].
// CAREFUL: must read predecessors BEFORE writing dp[i % size], and must
//   check i >= x/y/z (else i-x is negative, modulo would be wrong).
// Example: x=5,y=3,z=2 -> size=6. To compute dp[10] we need dp[5],dp[7],dp[8],
//   all within slots that still hold lengths 5..9. Slot of length 4
//   (10%6 == 4%6) gets safely overwritten.
// Time: O(n), Space: O(max(x,y,z)) instead of O(n).
// =============================================================================
class SolutionSpaceOpt {
public:
    int maximizeTheCuts(int n, int x, int y, int z) {

        // Buffer must hold max lookback + 1 slots so i and i-max don't collide.
        int size = max({x, y, z}) + 1;

        // dp[k] here means answer for the latest length i with i % size == k.
        vector<int> dp(size, -1);

        // Base: length 0 -> 0 pieces.
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {

            // ans for length i; stays -1 if no predecessor is reachable.
            int ans = -1;

            // Last cut x: predecessor length (i-x), read via modulo index.
            // Guard i>=x avoids negative index; !=-1 ensures prefix reachable.
            if (i >= x && dp[(i - x) % size] != -1)
                ans = max(ans, dp[(i - x) % size] + 1);

            // Last cut y.
            if (i >= y && dp[(i - y) % size] != -1)
                ans = max(ans, dp[(i - y) % size] + 1);

            // Last cut z.
            if (i >= z && dp[(i - z) % size] != -1)
                ans = max(ans, dp[(i - z) % size] + 1);

            // Store answer for i, overwriting length (i-size) which is now
            // too old to ever be needed (all lookbacks are < size).
            dp[i % size] = ans;
        }

        // Answer for n lives in slot n % size; -1 (impossible) -> 0.
        return max(0, dp[n % size]);
    }
};


int main(){
    return 0;
}