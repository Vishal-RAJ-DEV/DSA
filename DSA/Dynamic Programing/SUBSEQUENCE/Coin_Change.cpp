#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    Given coins[] and amount, find the minimum number of coins needed to
    make exactly "amount".

    Example:
    coins = {1, 2, 5}, amount = 11

    Possible answer:
    5 + 5 + 1 = 11, so minimum coins = 3.

    Important:
    We can use the same coin unlimited times.
*/

// ================= MEMOIZATION / RECURSION =================
class Memoization {
public:
    int coinChange(vector<int>& coins, int amount) {
        /*
            dp[rem] stores the answer for remaining amount "rem".

            dp[rem] = -2 means:
            this state has not been calculated yet.

            dp[rem] = -1 means:
            it is impossible to make this remaining amount.

            dp[rem] >= 0 means:
            minimum coins needed to make this remaining amount.
        */
        vector<int> dp(amount + 1, -2);

        return helper(coins, amount, dp);
    }

private:
    int helper(vector<int>& coins, int rem, vector<int>& dp) {
        /*
            What does this function mean?

            helper(rem) returns:
            minimum number of coins needed to make amount "rem".

            Recursion idea:
            For the current remaining amount, try taking every coin once.

            If we take coin = 2, then the remaining problem becomes:
            helper(rem - 2)

            So:
            answer for rem = 1 + answer for rem - coin

            We take the minimum among all valid coin choices.
        */

        // Base case 1:
        // If remaining amount becomes 0, no more coins are needed.
        if (rem == 0) return 0;

        // Base case 2:
        // If remaining amount becomes negative, this path is invalid.
        if (rem < 0) return -1;

        // If this remaining amount was already solved, reuse the answer.
        if (dp[rem] != -2) return dp[rem];

        /*
            mini stores the best/minimum answer for current rem.

            At first, mini = INT_MAX means:
            "I have not found any valid way yet."

            For every coin:
            - solve the smaller problem helper(rem - coin)
            - if that smaller problem is possible, add 1 for the coin
              we used right now
            - keep the minimum answer in mini

            Example:
            coins = {1, 2, 5}, rem = 11

            Try coin 1:
            result = helper(10)
            possible answer = 1 + helper(10)

            Try coin 2:
            result = helper(9)
            possible answer = 1 + helper(9)

            Try coin 5:
            result = helper(6)
            possible answer = 1 + helper(6)

            mini will keep the smallest valid value among these.
        */
        int mini = INT_MAX;

        for (int coin : coins) {
            int res = helper(coins, rem - coin, dp);

            /*
                res >= 0 means rem - coin can be formed.

                If res = 2, then current answer using this coin is:
                1 + 2 = 3 coins.

                We compare it with mini and keep the smaller value.
            */
            if (res >= 0) {
                mini = min(mini, 1 + res);
            }
        }

        /*
            If mini is still INT_MAX, no coin choice worked.
            So answer for this rem is -1.

            Otherwise mini is the minimum number of coins needed.
        */
        dp[rem] = (mini == INT_MAX) ? -1 : mini;

        return dp[rem];
    }
};

// ================= TABULATION =================
class Tabulation {
public:
    int coinChange(vector<int>& coins, int amount) {
        /*
            dp[i] means:
            minimum number of coins needed to make amount i.

            dp[0] = 0 because amount 0 needs 0 coins.

            For every amount i:
            try every coin.

            If coin can be used, then:
            dp[i] = min(dp[i], 1 + dp[i - coin])

            Why?
            If we use this coin now, then we still need to make
            amount i - coin.
        */
        vector<int> dp(amount + 1, INT_MAX);

        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0 && dp[i - coin] != INT_MAX) {
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }

        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};

// ================= SPACE OPTIMIZED TABULATION =================
class SpaceOptimized {
public:
    int coinChange(vector<int>& coins, int amount) {
        /*
            For this coin change problem, the normal tabulation code is
            already space optimized.

            Why?
            The recurrence is:
            dp[i] = min(dp[i], 1 + dp[i - coin])

            To calculate dp[i], we only need answers for smaller amounts:
            dp[i - coin]

            So a 1D array is enough.

            There is no need for a 2D dp[index][amount] table here because
            coins can be used unlimited times and the state only depends on
            the remaining/current amount.

            Space Complexity:
            O(amount)

            Time Complexity:
            O(amount * number of coins)
        */
        vector<int> prev(amount + 1, INT_MAX);

        // Base case: amount 0 needs 0 coins.
        prev[0] = 0;

        /*
            prev[i] means:
            minimum coins needed to make amount i using all available coins.

            We move from smaller amount to larger amount so that when we are
            calculating prev[i], the answer prev[i - coin] is already known.
        */
        for (int i = 1; i <= amount; i++) {
            int mini = INT_MAX;

            for (int coin : coins) {
                if (i - coin >= 0 && prev[i - coin] != INT_MAX) {
                    mini = min(mini, 1 + prev[i - coin]);
                }
            }

            prev[i] = mini;
        }

        return prev[amount] == INT_MAX ? -1 : prev[amount];
    }
};

// Driver function
int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    SpaceOptimized obj;
    cout << obj.coinChange(coins, amount) << endl;

    return 0;
}
