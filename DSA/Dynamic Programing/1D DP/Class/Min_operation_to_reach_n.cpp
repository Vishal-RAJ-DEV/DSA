#include <bits/stdc++.h>
using namespace std;


// ============================================================
// 1. MEMOIZATION / TOP-DOWN
// ============================================================

class SolutionMemoization {
public:

    /*
        solve(n) = minimum operations needed
                   to reach 0 starting from n.

        We work BACKWARDS.

        Original operations:

            x -> x + 1
            x -> x * 2

        Reverse:

            x -> x - 1
            x -> x / 2
    */
    int solve(int n, vector<int>& dp) {

        // Already at 0
        if (n == 0)
            return 0;

        // Already calculated
        if (dp[n] != -1)
            return dp[n];

        /*
            Even number:

                It could have been produced by doubling.

                Example:
                    8 -> 4
                    6 -> 3
                    4 -> 2

                So reverse *2 using /2.
        */
        if (n % 2 == 0) {
            return dp[n] = 1 + solve(n / 2, dp);
        }

        /*
            Odd number:

                Doubling always produces an even number.

                Therefore an odd number must have been
                produced using +1.

                Reverse +1 using -1.
        */
        return dp[n] = 1 + solve(n - 1, dp);
    }


    int minOperation(int n) {

        // dp[i] = minimum operations from i to 0
        vector<int> dp(n + 1, -1);

        return solve(n, dp);
    }
};


// ============================================================
// 2. TABULATION / BOTTOM-UP
// ============================================================

class SolutionTabulation {
public:

    int minOperation(int n) {

        /*
            dp[i] = minimum operations required
                    to reach i starting from 0.

            We start with:

                dp[0] = 0
        */
        vector<int> dp(n + 1, INT_MAX);

        dp[0] = 0;

        /*
            From every number i, we have two choices:

                1. i -> i + 1
                2. i -> i * 2

            Take the minimum number of operations.
        */
        for (int i = 0; i < n; i++) {

            // Operation: +1
            dp[i + 1] = min(dp[i + 1], dp[i] + 1);

            // Operation: *2
            if (2 * i <= n) {
                dp[2 * i] = min(dp[2 * i], dp[i] + 1);
            }
        }

        return dp[n];
    }
};


// ============================================================
// 3. SPACE OPTIMIZATION / GREEDY
// ============================================================

class Solution {
public:

    int minOperation(int n) {

        /*
            Work backwards from n to 0.

            Reverse operations:

                +1 -> -1
                *2 -> /2

            If n is EVEN:

                The previous operation can be *2,
                so divide by 2.

            If n is ODD:

                Doubling can never create an odd number,
                so the previous operation MUST be +1.

                Therefore subtract 1.
        */

        int ans = 0;

        while (n > 0) {

            if (n % 2 == 0) {

                // Reverse the doubling operation
                n /= 2;

            } else {

                // Reverse the +1 operation
                n--;
            }

            ans++;
        }

        return ans;
    }
};


int main() {

    int n;
    cin >> n;

    // Using space-optimized solution
    Solution obj;

    cout << obj.minOperation(n) << endl;

    return 0;
}