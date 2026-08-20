#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: K Inverse Pairs Array (629)
    Given two integers n and k, find how many different arrays
    consist of numbers from 1 to n such that there are exactly
    k inverse pairs.

    ================================================================
    WHAT IS AN INVERSE PAIR?
    ================================================================
    In a permutation of [1, 2, ..., n], an inverse pair is a pair
    (i, j) where i < j BUT nums[i] > nums[j].

    The order is "inverted" - larger number appears before smaller.

    Examples:
    [1, 2, 3] → 0 inverse pairs (sorted, no inversions)
    [1, 3, 2] → 1 inverse pair: (3, 2)
    [2, 1, 3] → 1 inverse pair: (2, 1)
    [2, 3, 1] → 2 inverse pairs: (2, 1), (3, 1)
    [3, 1, 2] → 2 inverse pairs: (3, 1), (3, 2)
    [3, 2, 1] → 3 inverse pairs: (3, 2), (3, 1), (2, 1)

    ================================================================
    INTUITION: BUILDING PERMUTATIONS BY INSERTING NUMBERS
    ================================================================

    Key Insight: Build permutation of [1, 2, ..., n] by inserting
    number n into a permutation of [1, 2, ..., n-1].

    When we insert number n at different positions, it creates
    DIFFERENT numbers of new inverse pairs:

    Permutation of [1, 2, ..., n-1] has n positions to insert n:

    Position:   [ _  1  _  2  _  3  _ ... _  n-1  _ ]
                  ↑                                   ↑
                START                               END

    If we insert n at:
    - END (after all elements):     0 new inverse pairs
    - Before last element:          1 new inverse pair
    - Before second-to-last:        2 new inverse pairs
    - ...
    - Before first element (START): n-1 new inverse pairs

    Example: n = 4, inserting 4 into [1, 2, 3]

    [1, 2, 3, 4] → 4 at END → 0 new inversions with existing
    [1, 2, 4, 3] → 4 before 3 → 1 new inversion: (4, 3)
    [1, 4, 2, 3] → 4 before 2,3 → 2 new inversions: (4, 2), (4, 3)
    [4, 1, 2, 3] → 4 at START → 3 new inversions: (4, 1), (4, 2), (4, 3)

    ================================================================
    RECURRENCE RELATION
    ================================================================

    If we want k inverse pairs total, and we insert n at a position
    that creates i new inverse pairs, then we need (k - i) inverse
    pairs from the permutation of [1, 2, ..., n-1].

    dp[n][k] = Sum of dp[n-1][k-i] for i = 0 to min(k, n-1)

    Why min(k, n-1)?
    - Maximum new inversions by inserting n = n-1 (at the start)
    - We can't create more new inversions than k (we need exactly k total)

    ================================================================
    VISUAL EXAMPLE: n = 3, k = 1
    ================================================================

    dp[0][0] = 1 (empty array, 0 inversions: base case)
    dp[1][0] = 1 → [1]
    dp[2][0] = 1 → [1, 2]
    dp[2][1] = 1 → [2, 1]

    dp[3][0] = dp[2][0] = 1 → [1, 2, 3]
    dp[3][1] = dp[2][1] + dp[2][0] = 1 + 1 = 2
              → [1, 3, 2] (from dp[2][1], add 3 at end)
              → [2, 1, 3] (from dp[2][0], add 3 at end)

    Answer: dp[3][1] = 2
*/

// ==========================================
// Approach 1: Memoization (Top-Down DP)
// Time: O(n * k * min(k, n-1))
// Space: O(n * k)
// ==========================================
class Memoization
{
public:
    static const int MOD = 1e9 + 7;

    int solve(int n, int k, vector<vector<int>> &dp)
    {
        // Base case: 0 inversions means sorted array, exactly 1 way
        if (k == 0)
            return 1;

        // Base case: No numbers left but still need inversions, impossible
        if (n == 0)
            return 0;

        // Return cached result if already computed
        if (dp[n][k] != -1)
            return dp[n][k];

        long long ans = 0;

        /*
            Insert number n into permutation of [1, 2, ..., n-1]
            i = number of NEW inverse pairs created by inserting n

            If we insert n at position (n-1-i) from the end:
            - i elements come after n → i new inversions (n > those elements)
            - We need (k - i) inversions from remaining [1..n-1]

            i ranges from 0 to min(k, n-1):
            - i = 0: insert at end (0 new inversions)
            - i = n-1: insert at start (n-1 new inversions)
            - i can't exceed k (we only need k total)
        */
        for (int i = 0; i <= min(k, n - 1); i++)
        {
            ans = (ans + solve(n - 1, k - i, dp)) % MOD;
        }

        return dp[n][k] = ans;
    }

    int kInversePairs(int n, int k)
    {
        vector<vector<int>> dp(n + 1,
                               vector<int>(k + 1, -1));
        return solve(n, k, dp);
    }
};

// ==========================================
// Approach 2: Tabulation with Inner Loop
// Time: O(n * k * min(k, n-1))
// Space: O(n * k)
// ==========================================
class Tabulation
{
public:
    int kInversePairs(int n, int k)
    {
        const int MOD = 1e9 + 7;

        /*
            dp[i][j] = number of permutations of [1, 2, ..., i]
                       having exactly j inverse pairs

            Base case: dp[i][0] = 1 for all i
            (Exactly one way to have 0 inversions: sorted array)
        */
        vector<vector<int>> dp(
            n + 1,
            vector<int>(k + 1, 0));

        // Base case: 0 inversions → sorted array → 1 way
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 1;
        }

        // Build the table for i = 1 to n, j = 1 to k
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                long long ans = 0;

                /*
                    Insert number i into permutation of [1..i-1]
                    x = new inverse pairs created by inserting i

                    Sum dp[i-1][j-x] for x = 0 to min(j, i-1)
                */
                for (int x = 0;
                     x <= min(j, i - 1);
                     x++)
                {
                    ans += dp[i - 1][j - x];
                    ans %= MOD;
                }

                dp[i][j] = ans;
            }
        }

        return dp[n][k];
    }
};

// ==========================================
// Approach 3: Optimized Tabulation (Sliding Window)
// Time: O(n * k)  ← OPTIMIZED!
// Space: O(n * k)
// ==========================================
/*
    ================================================================
    HOW IS THE OPTIMIZATION DONE? (VERY IMPORTANT)
    ================================================================

    The inner loop in Approach 2 computes:
        dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + ... + dp[i-1][j-(i-1)]

    This is a SUM of i consecutive elements from the previous row.

    OPTIMIZATION TRICK: Sliding Window / Prefix Sum

    Instead of re-computing the sum each time, we can observe:

    dp[i][j]   = dp[i-1][j]   + dp[i-1][j-1] + ... + dp[i-1][j-(i-1)]
    dp[i][j-1] = dp[i-1][j-1] + dp[i-1][j-2] + ... + dp[i-1][j-i]

    Notice: dp[i][j] and dp[i-1][j-1] are almost the same sum!
    dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-i]
              ───────────   ──────────   ─────────────
              previous sum  + new element - element leaving window

    This is the SLIDING WINDOW technique!

    ================================================================
    STEP-BY-STEP LOGIC OF OPTIMIZATION
    ================================================================

    dp[i][j] = dp[i-1][j] + dp[i][j-1]

    Wait, let me explain more carefully:

    Original recurrence:
        dp[i][j] = sum(dp[i-1][j-x] for x = 0 to min(j, i-1))

    Let's expand:
        dp[i][j]   = dp[i-1][j]   + dp[i-1][j-1] + ... + dp[i-1][j-i+1]
        dp[i][j-1] = dp[i-1][j-1] + dp[i-1][j-2] + ... + dp[i-1][j-i]

    So:
        dp[i][j] = dp[i][j-1] + dp[i-1][j] - (dp[i-1][j-i] if j >= i else 0)

    Why subtract dp[i-1][j-i]?
    - When we shift window from j-1 to j, we ADD dp[i-1][j] at the front
    - We REMOVE dp[i-1][j-i] from the back (element that falls outside window)
    - Window size is always i (from 0 to i-1)

    ================================================================
    VISUAL EXAMPLE
    ================================================================

    For i = 3, computing dp[3][5]:
    dp[3][5] = dp[2][5] + dp[2][4] + dp[2][3]  (3 elements, window size = i = 3)

    For i = 3, computing dp[3][4]:
    dp[3][4] = dp[2][4] + dp[2][3] + dp[2][2]

    dp[3][5] = dp[3][4] + dp[2][5] - dp[2][2]
              ────────   ────────   ────────
              previous   + add new  - remove old

    ================================================================
*/
class OptimizedTabulation
{
public:
    static const int MOD = 1e9 + 7;

    int kInversePairs(int n, int k)
    {
        vector<vector<int>> dp(
            n + 1,
            vector<int>(k + 1, 0));

        // Base case: 0 inversions → sorted array → 1 way
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                /*
                    Sliding Window Optimization:
                    dp[i][j] = dp[i][j-1] + dp[i-1][j]

                    This adds the new element dp[i-1][j] to the window.
                    But we also need to subtract the element that falls
                    outside the window of size i.

                    If j >= i, subtract dp[i-1][j-i]
                    (this element is no longer in the valid range)
                */
                long long ans = dp[i - 1][j];      // Add new element
                ans += dp[i][j - 1];                // Previous window sum

                // Remove element that falls outside the window
                if (j >= i)
                {
                    ans -= dp[i - 1][j - i];
                }

                // Handle negative modulo (due to subtraction)
                ans = (ans + MOD) % MOD;

                dp[i][j] = ans;
            }
        }

        return dp[n][k];
    }
};

/*
    SUMMARY:
    ========

    Approach 1: Memoization - O(n*k*min(k,n)) time, O(n*k) space
    Approach 2: Tabulation with loop - O(n*k*min(k,n)) time, O(n*k) space
    Approach 3: Optimized with sliding window - O(n*k) time, O(n*k) space

    Key Optimization:
    - Original inner loop: Sum of i elements → O(i) per state
    - With sliding window: Use previous sum + add - remove → O(1) per state

    The trick is recognizing that consecutive sums share most elements,
    so we can maintain a running sum instead of re-computing from scratch.
*/

int main()
{
    return 0;
}
