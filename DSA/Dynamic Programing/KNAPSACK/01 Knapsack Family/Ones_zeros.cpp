#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Ones and Zeroes (474)
    Given an array of binary strings strs and two integers m and n.
    Find the size of the largest subset of strs such that there are
    at most m 0's and n 1's in the subset.

    This is a 0/1 Knapsack problem with TWO constraints:
    - Constraint 1: Maximum m zeros allowed
    - Constraint 2: Maximum n ones allowed
    - Value: Each string has value 1 (we want to maximize count)

    For each string, we can either TAKE it or SKIP it (0/1 choice).
*/

// ==========================================
// Approach 1: Recursion (Brute Force)
// Time: O(2^n) - exponential
// Space: O(n) - recursion stack
// ==========================================
class Recursion {
public:
    int solve(vector<string>& strs, int idx, int m, int n) {

        // Base case: No strings left to consider
        if (idx == strs.size())
            return 0;

        // Count zeros and ones in current string
        int zeros = 0, ones = 0;
        for (char ch : strs[idx]) {
            if (ch == '0')
                zeros++;
            else
                ones++;
        }

        // Option 1: SKIP current string
        // Don't use any zeros/ones, move to next string
        int skip = solve(strs, idx + 1, m, n);

        // Option 2: TAKE current string (only if we have enough zeros and ones)
        // Use up zeros and ones from our budget, move to next string
        int take = 0;
        if (zeros <= m && ones <= n) {
            take = 1 + solve(strs, idx + 1, m - zeros, n - ones);
        }

        // Return the best of take vs skip
        return max(take, skip);
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        return solve(strs, 0, m, n);
    }
};

// ==========================================
// Approach 2: Memoization (Top-Down DP)
// Time: O(n * m * n * n) = O(n * m^2)
// Space: O(n * m * n) for dp array + recursion stack
// ==========================================
class Memoization {
public:
    int solve(vector<string>& strs,
              int idx,
              int m,
              int n,
              vector<vector<vector<int>>>& dp) {

        // Base case: No strings left
        if (idx == strs.size())
            return 0;

        // Return cached result if already computed
        if (dp[idx][m][n] != -1)
            return dp[idx][m][n];

        // Count zeros and ones in current string
        int zeros = 0;
        int ones = 0;
        for (char ch : strs[idx]) {
            if (ch == '0')
                zeros++;
            else
                ones++;
        }

        // Option 1: SKIP current string
        int skip = solve(strs, idx + 1, m, n, dp);

        // Option 2: TAKE current string (if enough resources)
        int take = 0;
        if (zeros <= m && ones <= n) {
            take = 1 + solve(strs, idx + 1, m - zeros, n - ones, dp);
        }

        // Cache and return the best result
        return dp[idx][m][n] = max(take, skip);
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        int sz = strs.size();

        // 3D DP: dp[idx][zeros_available][ones_available]
        vector<vector<vector<int>>> dp(
            sz,
            vector<vector<int>>(
                m + 1,
                vector<int>(n + 1, -1)
            )
        );

        return solve(strs, 0, m, n, dp);
    }
};

// ==========================================
// Approach 3: Tabulation (Bottom-Up 3D DP)
// Time: O(n * m * n)
// Space: O(n * m * n)
// ==========================================
class Tabulation3D {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int sz = strs.size();

        // 3D DP table
        // dp[i][z][o] = max strings using first i strings
        //               with z zeros and o ones available
        vector<vector<vector<int>>> dp(
            sz + 1,
            vector<vector<int>>(
                m + 1,
                vector<int>(n + 1, 0)
            )
        );

        // Build solution for each string
        for (int i = 1; i <= sz; i++) {

            // Count zeros and ones in current string
            int zeros = 0;
            int ones = 0;
            for (char ch : strs[i - 1]) {
                if (ch == '0')
                    zeros++;
                else
                    ones++;
            }

            // Try every possible (zeros, ones) combination
            for (int z = 0; z <= m; z++) {
                for (int o = 0; o <= n; o++) {

                    // Skip current string: same as previous row
                    dp[i][z][o] = dp[i - 1][z][o];

                    // Take current string (if we have enough resources)
                    if (zeros <= z && ones <= o) {
                        dp[i][z][o] = max(
                            dp[i][z][o],
                            1 + dp[i - 1][z - zeros][o - ones]
                        );
                    }
                }
            }
        }

        return dp[sz][m][n];
    }
};

// ==========================================
// Approach 4: Space Optimized Tabulation (2D DP with BACKWARD loop)
// Time: O(n * m * n)
// Space: O(m * n) - optimized from 3D to 2D
// ==========================================
class SpaceOptimized {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {

        // dp[z][o] = maximum number of strings possible
        //            with z zeros and o ones available
        // Initially 0 for all states
        vector<vector<int>> dp(
            m + 1,
            vector<int>(n + 1, 0)
        );

        // Process every string one by one
        for (string& s : strs) {

            // Count resources (zeros and ones) required by this string
            int zeros = 0;
            int ones = 0;
            for (char ch : s) {
                if (ch == '0')
                    zeros++;
                else
                    ones++;
            }

            /*
                ============================================================
                WHY BACKWARD LOOP? - CRITICAL CONCEPT
                ============================================================

                This is a 0/1 KNAPSACK problem:
                - Each string can be used AT MOST ONCE
                - We either TAKE it or SKIP it

                When we use 1D DP (space optimization from 3D to 2D),
                we must iterate BACKWARD to avoid using the same string
                MULTIPLE TIMES.

                ============================================================
                FORWARD vs BACKWARD LOOP - KEY DIFFERENCE
                ============================================================

                FORWARD LOOP (z = 0 to m, o = 0 to n):
                ---------------------------------------
                When we compute dp[z][o], the value dp[z-zeros][o-ones]
                might have ALREADY BEEN UPDATED in this same iteration
                (for the current string).

                This means: We could use the SAME string multiple times!
                This becomes UNBOUNDED KNAPSACK (unlimited copies).

                Example with forward loop:
                - String "01" needs (1 zero, 1 one)
                - dp[1][1] = max(dp[1][1], 1 + dp[0][0]) = 1
                - dp[2][2] = max(dp[2][2], 1 + dp[1][1]) = 2  <-- WRONG!
                - We used "01" TWICE! (dp[1][1] was already updated)

                BACKWARD LOOP (z = m to zeros, o = n to ones):
                ------------------------------------------------
                When we compute dp[z][o], the value dp[z-zeros][o-ones]
                is from the PREVIOUS iteration (previous string).

                This means: Each string is used AT MOST ONCE.
                This is correct 0/1 KNAPSACK behavior.

                Example with backward loop:
                - String "01" needs (1 zero, 1 one)
                - dp[2][2] = max(dp[2][2], 1 + dp[1][1])  <-- dp[1][1] is old value (0)
                - dp[1][1] = max(dp[1][1], 1 + dp[0][0])  <-- Now we update dp[1][1]
                - We used "01" only ONCE! (correct)

                ============================================================
                VISUAL EXAMPLE
                ============================================================

                strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3

                After processing "10" (needs 1 zero, 1 one):
                dp[1][1] = 1 (take "10")
                dp[2][2] = 1 (take "10")
                ... other states updated similarly

                After processing "0001" (needs 3 zeros, 1 one):
                - Backward: dp[4][2] = max(dp[4][2], 1 + dp[1][1])
                  Uses dp[1][1] from PREVIOUS string processing (value 1)
                  So dp[4][2] = 2 (take both "10" and "0001")
                - If forward: dp[4][2] might use dp[1][1] that was just
                  updated in THIS iteration, causing double counting

                ============================================================
            */

            // BACKWARD loop ensures each string is used at most once
            for (int z = m; z >= zeros; z--) {
                for (int o = n; o >= ones; o--) {

                    /*
                        At state dp[z][o], we have two choices:

                        1. DON'T take current string:
                           dp[z][o] remains unchanged (from previous strings)

                        2. TAKE current string:
                           - Use 'zeros' zeros and 'ones' ones from our budget
                           - Get 1 for this string
                           - Add best result with remaining capacity: dp[z-zeros][o-ones]

                        Since we iterate backward, dp[z-zeros][o-ones] contains
                        the result from PREVIOUS strings only (not current string).
                        This guarantees each string is counted at most once.
                    */
                    dp[z][o] = max(
                        dp[z][o],                          // Skip current string
                        1 + dp[z - zeros][o - ones]       // Take current string
                    );
                }
            }
        }

        // Answer: maximum strings with full capacity (m zeros, n ones)
        return dp[m][n];
    }
};

/*
    Summary:
    --------
    1. Recursion:        Try all 2^n subsets, very slow
    2. Memoization:      Cache 3D states, same as recursion but faster
    3. Tabulation 3D:    Bottom-up with 3D DP, no recursion overhead
    4. Space Optimized:  Bottom-up with 2D DP, BACKWARD loop for 0/1 knapsack

    Key Insight:
    - 0/1 Knapsack (each item once) -> BACKWARD loop
    - Unbounded Knapsack (unlimited copies) -> FORWARD loop
*/

int main(){
    return 0;
}
