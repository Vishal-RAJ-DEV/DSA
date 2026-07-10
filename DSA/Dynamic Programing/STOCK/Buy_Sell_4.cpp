#include <bits/stdc++.h>
using namespace std;

/*
============================================================
  PROBLEM: Best Time to Buy and Sell Stock IV
  - You are given an array 'prices' where prices[i] is the
    stock price on day i.
  - You may complete at most 'k' transactions.
  - A transaction = Buy + Sell (1 buy + 1 sell).
  - You must sell before buying again.
  - Goal: Maximize profit.

============================================================
  WHAT IS 'cap' (CAPACITY) AND HOW DOES K WORK?
============================================================
  - 'cap' = remaining number of transactions we are allowed
    to complete.
  - Initially, cap = k (the user-given limit).
  - Every time we SELL a stock, we consume one transaction,
    so cap decreases by 1.
  - Buying does NOT consume a transaction — only selling does
    (since buy-sell pair = 1 transaction).
  - Base case: when ind == n (no more days) OR cap == 0
    (no transactions left), profit = 0.
  - The 3D DP states are: dp[day][buyState][remainingCaps]
    where:
      day  → index in prices (0..n-1)
      buy  → 0 = can buy, 1 = can sell (i.e., holding stock)
      cap  → remaining transactions left

============================================================
  APPROACH 1: Recursion + Memoization (Top-Down)
============================================================
  - We recursively explore all possibilities from day 0.
  - At each state (ind, buy, cap):
      if buy == 0 (not holding):
        - Skip: stay in buy state, move to next day.
        - Buy: pay -Arr[ind], move to sell state (buy=1),
               cap unchanged (buy doesn't consume a transaction).
      if buy == 1 (holding):
        - Skip: stay in sell state, move to next day.
        - Sell: gain +Arr[ind], move to buy state (buy=0),
                cap-1 (selling completes a transaction).
  - We memoize results in dp[ind][buy][cap] to avoid
    recomputation.
  - Answer = dp[0][0][k] (start at day 0, can buy, k transactions).
*/

class StockBuySell {
    // -------------------------------------------------------
    // Recursive helper with memoization
    // -------------------------------------------------------
    int getAns(vector<int>& Arr, int n, int ind, int buy, int cap,
               vector<vector<vector<int>>>& dp) {
        // Base case: no days left OR no transactions left
        if (ind == n || cap == 0) return 0;

        if (dp[ind][buy][cap] != -1) return dp[ind][buy][cap];

        int profit = 0;

        if (buy == 0) { // Not holding → can buy
            profit = max(
                0 + getAns(Arr, n, ind + 1, 0, cap, dp),      // Skip
                -Arr[ind] + getAns(Arr, n, ind + 1, 1, cap, dp) // Buy
            );
        }

        if (buy == 1) { // Holding → can sell
            profit = max(
                0 + getAns(Arr, n, ind + 1, 1, cap, dp),          // Skip
                Arr[ind] + getAns(Arr, n, ind + 1, 0, cap - 1, dp) // Sell
            );
            // NOTE: cap-1 only on sell — buying does NOT consume a transaction
        }

        return dp[ind][buy][cap] = profit;
    }

public:
    int maximumProfit(vector<int>& prices, int n, int k) {
        // dp[days][2][k+1] → -1 means uncomputed
        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return getAns(prices, n, 0, 0, k, dp);
    }
};

/*
============================================================
  APPROACH 2: Tabulation (Bottom-Up)
============================================================
  - We fill dp table from last day to first day.
  - dp[ind][buy][cap] = max profit from day 'ind' onward
    with given buy-state and remaining capacity.
  - Since we iterate ind from n-1 down to 0, we always
    have dp[ind+1][...][...] already computed.
  - Recurrence is the same as above, just iterative.
  - Base cases are implicitly 0 (dp[n][*][*] = 0,
    dp[*][*][0] = 0) because the table is zero-initialized.
*/

class StockBuySellTab {
public:
    int maximumProfit(vector<int>& Arr, int n, int k) {
        // dp[n+1][2][k+1] all zeros
        // We add +1 for n to avoid index-out-of-bounds for ind+1
        vector<vector<vector<int>>> dp(
            n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
                    if (buy == 0) { // Can buy
                        dp[ind][buy][cap] = max(
                            0 + dp[ind + 1][0][cap],
                            -Arr[ind] + dp[ind + 1][1][cap]);
                    }
                    if (buy == 1) { // Can sell
                        dp[ind][buy][cap] = max(
                            0 + dp[ind + 1][1][cap],
                            Arr[ind] + dp[ind + 1][0][cap - 1]);
                    }
                }
            }
        }
        return dp[0][0][k];
    }
};

/*
============================================================
  APPROACH 3: Space-Optimized Tabulation
============================================================
  - Notice that dp[ind][*][*] only depends on dp[ind+1][*][*].
  - So we only need two 2D layers (current & ahead), each of
    size [2][k+1].
  - ahead[b][c] corresponds to dp[ind+1][b][c]
  - cur[b][c]   corresponds to dp[ind][b][c]
  - After each iteration, we swap them.
  - This reduces space from O(n*2*k) to O(2*k) = O(k).
*/

class StockBuySellOpt {
public:
    int maximumProfit(vector<int>& Arr, int n, int k) {
        // ahead = dp[ind+1][2][k+1], cur = dp[ind][2][k+1]
        vector<vector<int>> ahead(2, vector<int>(k + 1, 0));
        vector<vector<int>> cur(2, vector<int>(k + 1, 0));

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
                    if (buy == 0) {
                        cur[buy][cap] = max(
                            0 + ahead[0][cap],
                            -Arr[ind] + ahead[1][cap]);
                    }
                    if (buy == 1) {
                        cur[buy][cap] = max(
                            0 + ahead[1][cap],
                            Arr[ind] + ahead[0][cap - 1]);
                    }
                }
            }
            // Move current → ahead for next iteration
            ahead = cur;
        }
        return ahead[0][k];
    }
};

/*
============================================================
  MAIN
============================================================
  - Demonstrates all three approaches on the same input.
  - Expected output: 6
    (Buy on day 3 at 0, sell on day 5 at 3 → profit 3;
     buy on day 6 at 1, sell on day 7 at 4 → profit 3;
     total = 6)
*/

int main() {
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
    int n = prices.size();
    int k = 2;

    StockBuySell s1;
    StockBuySellTab s2;
    StockBuySellOpt s3;

    int ans1 = s1.maximumProfit(prices, n, k);
    int ans2 = s2.maximumProfit(prices, n, k);
    int ans3 = s3.maximumProfit(prices, n, k);

    cout << "Recursion + Memoization : " << ans1 << endl;
    cout << "Tabulation              : " << ans2 << endl;
    cout << "Space Optimized          : " << ans3 << endl;

    return 0;
}
