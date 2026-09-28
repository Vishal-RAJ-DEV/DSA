#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    dp[n] = number of ways to make sum n.

    Last number can be:

        1 -> dp[n-1]
        3 -> dp[n-3]
        4 -> dp[n-4]

    Therefore:

        dp[n] = dp[n-1] + dp[n-3] + dp[n-4]

    Base case:

        dp[0] = 1

    Why dp[0] = 1?

    There is exactly one way to make sum 0:
    choose nothing.

    This allows the recurrence to work naturally.

    Example for n = 4:

        dp[4] = dp[3] + dp[1] + dp[0]
              = 2 + 1 + 1
              = 4
*/


// =========================================================
// 1. MEMOIZATION / TOP-DOWN
// =========================================================

class SolutionMemoization {
public:

    int solve(int n, vector<int>& dp) {

        // Sum 0 has one way: choose nothing
        if (n == 0)
            return 1;

        // Negative sum is impossible
        if (n < 0)
            return 0;

        // Already calculated
        if (dp[n] != -1)
            return dp[n];

        /*
            Choose the last number:

            Last = 1 -> solve(n-1)
            Last = 3 -> solve(n-3)
            Last = 4 -> solve(n-4)
        */
        return dp[n] = solve(n - 1, dp)
                     + solve(n - 3, dp)
                     + solve(n - 4, dp);
    }

    int countWays(int n) {

        vector<int> dp(n + 1, -1);

        return solve(n, dp);
    }
};


// =========================================================
// 2. TABULATION / BOTTOM-UP
// =========================================================

class SolutionTabulation {
public:

    int countWays(int n) {

        /*
            dp[i] = number of ways to make sum i.
        */
        vector<int> dp(n + 1, 0);

        // One way to make sum 0
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {

            // Add 1 to the current sum
            dp[i] += dp[i - 1];

            // Add 3 to the current sum
            if (i >= 3)
                dp[i] += dp[i - 3];

            // Add 4 to the current sum
            if (i >= 4)
                dp[i] += dp[i - 4];
        }

        return dp[n];
    }
};


// =========================================================
// 3. SPACE OPTIMIZATION
// =========================================================

class Solution {
public:

    int countWays(int n) {

        /*
            Recurrence:

                dp[i] = dp[i-1] + dp[i-3] + dp[i-4]

            We need values from 4 positions back,
            so we can keep only the last 4 values.
        */

        if (n == 0)
            return 1;

        if (n == 1)
            return 1;

        if (n == 2)
            return 1;

        if (n == 3)
            return 2;

        int a = 1; // dp[0]
        int b = 1; // dp[1]
        int c = 1; // dp[2]
        int d = 2; // dp[3]

        for (int i = 4; i <= n; i++) {

            // dp[i] = dp[i-1] + dp[i-3] + dp[i-4]
            int curr = d + b + a;

            // Move the window forward
            a = b;
            b = c;
            c = d;
            d = curr;
        }

        return d;
    }
};


int main() {
    return 0;
}