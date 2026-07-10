#include <bits/stdc++.h>
using namespace std;

/*
Problem: Best Time to Buy and Sell Stock II
You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).
You must sell the stock before you buy again.

State Representation:
- buy = 0: We can BUY the stock (we are not holding any stock currently)
- buy = 1: We can SELL the stock (we are holding one stock currently)

At each index, we have two choices:
1. TAKE (execute the transaction): buy (pay -Arr[ind]) or sell (gain +Arr[ind])
2. NOT TAKE (skip): move to next index with same buy state

Base case:
- ind == n (no days left): profit = 0, regardless of whether we hold stock or not
*/

// ============================================================
// Approach 1: Recursion + Memoization (Top-Down)
// ============================================================
class Memoization {
    /*
    Recursion breakdown:
    f(ind, buy):
        if ind == n -> return 0

        if buy == 0 (can buy):
            TAKE    = -Arr[ind] + f(ind+1, 1)   // buy the stock
            NOT TAKE =  0        + f(ind+1, 0)  // skip buying
            ans = max(TAKE, NOT TAKE)

        if buy == 1 (can sell):
            TAKE    =  Arr[ind] + f(ind+1, 0)   // sell the stock
            NOT TAKE =  0        + f(ind+1, 1)  // skip selling
            ans = max(TAKE, NOT TAKE)

        return ans
    */
    long solve(long *Arr, int ind, int buy, int n, vector<vector<long>> &dp) {
        // Base case: No days left, no profit can be made
        if (ind == n) {
            return 0;
        }

        // Return already computed result for this state (ind, buy)
        if (dp[ind][buy] != -1) {
            return dp[ind][buy];
        }

        long profit = 0;

        if (buy == 0) {
            // We can BUY: max(skip, buy)
            profit = max(
                0 + solve(Arr, ind + 1, 0, n, dp),          // NOT TAKE: skip, stay in buy state
                -Arr[ind] + solve(Arr, ind + 1, 1, n, dp)   // TAKE: buy, move to sell state
            );
        }

        if (buy == 1) {
            // We can SELL: max(skip, sell)
            profit = max(
                0 + solve(Arr, ind + 1, 1, n, dp),          // NOT TAKE: skip, stay in sell state
                Arr[ind] + solve(Arr, ind + 1, 0, n, dp)      // TAKE: sell, move to buy state
            );
        }

        return dp[ind][buy] = profit;
    }

public:
    long getMaximumProfit(long *Arr, int n) {
        if (n == 0) return 0;
        vector<vector<long>> dp(n, vector<long>(2, -1));
        return solve(Arr, 0, 0, n, dp);
    }
};

// ============================================================
// Approach 2: Tabulation (Bottom-Up)
// ============================================================
class Tabulation {
    /*
    * Transition: dp[ind][buy] = max profit from index ind to n-1,
    *             given the current buy/sell state.
    * Base case: dp[n][0] = dp[n][1] = 0 (no days left)
    * Fill order: ind from n-1 to 0, buy from 0 to 1
    */
public:
    long getMaximumProfit(long *Arr, int n) {
        vector<vector<long>> dp(n + 1, vector<long>(2, 0));
        // dp[n][0] = dp[n][1] = 0 already set by initialization

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                if (buy == 0) {
                    // Can buy -> max(skip, take)
                    dp[ind][buy] = max(
                        dp[ind + 1][0],             // NOT TAKE
                        -Arr[ind] + dp[ind + 1][1]  // TAKE (buy)
                    );
                } else {
                    // Can sell -> max(skip, take)
                    dp[ind][buy] = max(
                        dp[ind + 1][1],             // NOT TAKE
                        Arr[ind] + dp[ind + 1][0]   // TAKE (sell)
                    );
                }
            }
        }

        // Start at day 0 in buy state (can buy)
        return dp[0][0];
    }
};

// ============================================================
// Approach 3: Space Optimized Tabulation (2 arrays)
// ============================================================
class TabulationSpaceOptimized {
    /*
    * Observation: dp[ind] only depends on dp[ind+1], so we only need
    * two arrays: current and ahead.
    */
public:
    long getMaximumProfit(long *Arr, int n) {
        vector<long> ahead(2, 0);  // dp[ind+1]
        vector<long> cur(2, 0);    // dp[ind]

        for (int ind = n - 1; ind >= 0; ind--) {
            // buy == 0
            cur[0] = max(ahead[0], -Arr[ind] + ahead[1]);
            // buy == 1
            cur[1] = max(ahead[1], Arr[ind] + ahead[0]);

            ahead = cur; // shift forward
        }

        return ahead[0];
    }
};

// ============================================================
// Approach 4: Space Optimized with 4 variables
// ============================================================
class TabulationFourVariables {
public:
    long getProfit(long *Arr, int n) {
        /*
        * aheadBuy = profit from day+1 in buy state (can buy)
        * aheadNotBuy = profit from day+1 in sell state (can sell)
        *
        * Recurrence:
        * curBuy    = max(aheadBuy,      -Arr[ind] + aheadNotBuy)
        * curNotBuy = max(aheadNotBuy,    Arr[ind] + aheadBuy)
        */
        long aheadBuy = 0;
        long aheadNotBuy = 0;

        for (int ind = n - 1; ind >= 0; ind--) {
            long curBuy = max(aheadBuy, -Arr[ind] + aheadNotBuy);
            long curNotBuy = max(aheadNotBuy, Arr[ind] + aheadBuy);

            aheadBuy = curBuy;
            aheadNotBuy = curNotBuy;
        }

        return aheadBuy;
    }
};

int main() {
    int n = 6;
    long Arr[n] = {7, 1, 5, 3, 6, 4};

    Memoization sol1;
    cout << "Memoization: " << sol1.getMaximumProfit(Arr, n) << endl;

    Tabulation sol2;
    cout << "Tabulation: " << sol2.getMaximumProfit(Arr, n) << endl;

    TabulationSpaceOptimized sol3;
    cout << "Space Opt (2 arrays): " << sol3.getMaximumProfit(Arr, n) << endl;

    TabulationFourVariables sol4;
    cout << "Space Opt (4 vars): " << sol4.getProfit(Arr, n) << endl;

    return 0;
}