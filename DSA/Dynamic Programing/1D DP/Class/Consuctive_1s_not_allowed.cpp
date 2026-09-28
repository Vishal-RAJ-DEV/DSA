#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    MAIN LOGIC:

    We need binary strings of length n with no "11".

    Consider the last digit:

    1. Last digit = 0
       The first n-1 positions can be any valid string.

       => dp[n-1]

    2. Last digit = 1
       Previous digit must be 0.

       So the string ends with "01".
       The first n-2 positions can be any valid string.

       => dp[n-2]

    Therefore:

        dp[n] = dp[n-1] + dp[n-2]

    Base cases:

        dp[1] = 2  -> "0", "1"
        dp[2] = 3  -> "00", "01", "10"
*/


// =========================================================
// 1. MEMOIZATION / TOP-DOWN
// =========================================================

class SolutionMemoization {
public:

    // solve(n) = number of valid binary strings of length n
    int solve(int n, vector<int>& dp) {

        // Base cases
        if (n == 1) return 2;
        if (n == 2) return 3;

        // Already calculated
        if (dp[n] != -1)
            return dp[n];

        /*
            Last digit = 0:
                solve(n-1)

            Last two digits = 01:
                solve(n-2)

            Therefore:
                dp[n] = dp[n-1] + dp[n-2]
        */
        return dp[n] = solve(n - 1, dp) + solve(n - 2, dp);
    }

    int countStrings(int n) {

        // dp[i] = valid strings of length i
        vector<int> dp(n + 1, -1);

        return solve(n, dp);
    }
};


// =========================================================
// 2. TABULATION / BOTTOM-UP
// =========================================================

class SolutionTabulation {
public:

    int countStrings(int n) {

        if (n == 1) return 2;

        /*
            dp[i] = number of valid binary strings
                    of length i
        */
        vector<int> dp(n + 1, 0);

        // Base cases
        dp[1] = 2;
        dp[2] = 3;

        /*
            Build the answer from smaller lengths.

            dp[i] = dp[i-1] + dp[i-2]
        */
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};


// =========================================================
// 3. SPACE OPTIMIZATION
// =========================================================

class Solution {
public:

    int countStrings(int n) {

        if (n == 1) return 2;

        /*
            We only need the previous two values:

                dp[i-2] -> prev2
                dp[i-1] -> prev1

            No need for the complete dp array.
        */
        int prev2 = 2; // dp[1]
        int prev1 = 3; // dp[2]

        for (int i = 3; i <= n; i++) {

            // dp[i] = dp[i-1] + dp[i-2]
            int curr = prev1 + prev2;

            // Move the window forward
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};


int main() {
    return 0;
}