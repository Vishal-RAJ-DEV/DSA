// =============================================================================
// PROBLEM: CSES 1637 - Removing Digits
// -----------------------------------------------------------------------------
// Given an integer n (1 <= n <= 1e6).
// In one step, you may subtract one of the NON-ZERO digits of the number.
// Example: 27 -> 20 (subtract 7) -> 18 (subtract 2) -> 10 (subtract 8)
//          -> 9 (subtract 1) -> 0 (subtract 9). Total = 5 steps.
// Goal: minimum number of steps to make n equal to 0.
// =============================================================================
//
// LOGIC: 1D Dynamic Programming (bottom-up)
// -----------------------------------------------------------------------------
// 1. Subproblem: dp[x] = min steps to reduce x to 0.
// 2. Base case: dp[0] = 0 (already zero, 0 steps).
// 3. Transition: from x, we can go to x - d for every digit d in x (d != 0).
//    So to reach x, last step must have come from x - d:
//        dp[x] = min(dp[x - d] + 1) over all non-zero digits d of x
// 4. Order: solve smaller numbers first (0,1,2,...,n) because x-d < x,
//    so dp[x-d] is already computed when we compute dp[x].
// 5. Answer: dp[n].
//
// Example dry run for n = 27:
//   dp[20] is known, dp[27] = min(dp[27-2]+1, dp[27-7]+1)
//            = min(dp[25]+1, dp[20]+1). We try all digits.
// Complexity: O(n * number_of_digits) ~ O(n log n), n = 1e6 is fine.
//
// THREE WAYS COVERED IN THIS FILE:
//   1. Bottom-Up Tabulation (O(n) space) -> solveBottomUp()
//   2. Top-Down Memoization (recursion + memo, O(n) space + recursion stack)
//      -> solveMemo() + helper dfs()
//   3. Space-Optimized Bottom-Up (O(1) space, only last 10 values)
//      -> solveSpaceOpt()
// =============================================================================

#include <bits/stdc++.h>
using namespace std;

// =============================================================================
// METHOD 1: BOTTOM-UP TABULATION (classic, best for n = 1e6)
// -----------------------------------------------------------------------------
// Logic: dp[i] = min steps i -> 0.
//   dp[0] = 0
//   dp[i] = min(dp[i - d] + 1) for each non-zero digit d of i.
// Why it works: to compute dp[i], we only need dp[<i] which is already filled
// because we go i = 1..n in increasing order.
// Time: O(n * digits), Space: O(n).
// =============================================================================
int solveBottomUp(int n) {
    // dp[i] = min steps to convert i to 0. Init with INF (1e9 = unreachable).
    vector<int> dp(n + 1, 1e9);
    dp[0] = 0; // Base case: 0 needs 0 steps.

    // Build answers bottom-up: dp[1]...dp[n].
    // dp[i - d] is always smaller than i, so already solved.
    for (int i = 1; i <= n; i++) {
        // Extract each decimal digit of i one by one.
        int tmp = i;
        while (tmp > 0) {
            int d = tmp % 10; // current last digit
            tmp /= 10;        // drop last digit

            // We can only subtract non-zero digits.
            if (d != 0) {
                // If we subtract d from i, previous number was (i - d).
                // One more step than the best way to reach (i - d).
                // Take minimum over all choices of d.
                dp[i] = min(dp[i], dp[i - d] + 1);
            }
        }
    }
    return dp[n];
}

// =============================================================================
// METHOD 2: TOP-DOWN MEMOIZATION (recursion + memo)
// -----------------------------------------------------------------------------
// Logic: same recurrence, but computed lazily via recursion:
//   f(0) = 0
//   f(x) = 1 + min(f(x - d)) for each non-zero digit d of x.
// How it works:
//   - dfs(x) asks: "what is answer for x?"
//   - It tries every digit d of x, recursively solves (x - d),
//     adds 1 for current step, takes minimum.
//   - memo[x] stores result so each x is solved only once.
//   - -1 means "not computed yet".
// Example: f(27) = 1 + min(f(25), f(20)). Recursion goes down to f(0).
// Time: O(n * digits), Space: O(n) memo + O(answer) recursion stack.
// NOTE: For n = 1e6 recursion depth can be ~1e5 steps -> may stack-overflow
// in C++. This version is for understanding; Method 1 is safer for max n.
// =============================================================================
int dfs(int x, vector<int> &memo) {
    // Base case: 0 needs 0 steps.
    if (x == 0) return 0;
    // If already solved, reuse it (this is the "memo" part).
    if (memo[x] != -1) return memo[x];

    int best = INT_MAX;
    int tmp = x;
    // Try every non-zero digit d of x as the subtracted digit.
    while (tmp > 0) {
        int d = tmp % 10; // last digit
        tmp /= 10;
        if (d != 0) {
            // 1 step (x -> x-d) + best answer from (x-d) to 0.
            best = min(best, dfs(x - d, memo) + 1);
        }
    }
    // Store and return.
    return memo[x] = best;
}

int solveMemo(int n) {
    // memo[i] = -1 means f(i) not computed yet.
    vector<int> memo(n + 1, -1);
    return dfs(n, memo);
}

// =============================================================================
// METHOD 3: SPACE-OPTIMIZED BOTTOM-UP (O(1) space)
// -----------------------------------------------------------------------------
// Key observation: max digit is 9, so:
//   dp[i] depends ONLY on dp[i-1] ... dp[i-9].
// We never need the whole dp[0..n] array, only the last 10 values!
// How: use circular buffer of size 10, index = i % 10.
//   dp_mod[i % 10] stores answer for i.
//   When computing i, dp_mod[(i-d) % 10] still holds answer for (i-d)
//   because d (1..9) != 0 mod 10, so it is a different slot that we
//   have not overwritten in this iteration.
// Steps:
//   1. dp_mod[0] = 0.
//   2. For i = 1..n: reset dp_mod[i%10] = INF, then
//      dp_mod[i%10] = min(dp_mod[(i-d)%10] + 1) over digits d.
//   3. Answer = dp_mod[n % 10].
// Time: O(n * digits), Space: O(10) = O(1).
// =============================================================================
int solveSpaceOpt(int n) {
    const int INF = 1e9;
    // Only 10 slots: slot k holds dp value for the latest number i with i%10==k.
    vector<int> dp(10, INF);
    dp[0] = 0; // dp[0] = 0.

    for (int i = 1; i <= n; i++) {
        // Reset current slot before taking min (it holds stale value of i-10).
        dp[i % 10] = INF;

        int tmp = i;
        while (tmp > 0) {
            int d = tmp % 10;
            tmp /= 10;
            if (d != 0) {
                // (i - d) was computed within last 9 steps, so its slot
                // dp[(i-d)%10] is still valid (not yet overwritten).
                dp[i % 10] = min(dp[i % 10], dp[(i - d) % 10] + 1);
            }
        }
    }
    return dp[n % 10];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    // Default: bottom-up is safest for n up to 1e6.
    cout << solveBottomUp(n) << "\n";

    // To test other versions, use:
    // cout << solveMemo(n) << "\n";     // top-down (may overflow stack for 1e6)
    // cout << solveSpaceOpt(n) << "\n"; // O(1) space version
    return 0;
}