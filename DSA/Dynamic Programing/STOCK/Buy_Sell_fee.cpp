#include <bits/stdc++.h>
using namespace std;

/*
============================================================
  PROBLEM: Best Time to Buy and Sell Stock with Transaction Fee
  - You are given an array 'prices' where prices[i] is the
    stock price on day i.
  - You may complete as many transactions as you like (no
    limit on k), but each transaction (buy + sell) incurs a
    fixed transaction fee.
  - You must sell before buying again.
  - Goal: Maximize profit after subtracting all transaction fees.

============================================================
  WHY IS THE FEE SUBTRACTED AT THE TIME OF SELLING?
============================================================
  A transaction consists of: BUY (pay price) + SELL (receive price).
  The broker charges the fee once per completed transaction.

  Two conventions are equivalent:

    1) Subtract fee on SELL (used here):
         profit = (sellingPrice) - fee - (buyingPrice)
                = sellingPrice - fee  +  (-buyingPrice)
         Recurrence:
           On buy:  -Arr[ind] + dp[ind+1][1]
           On sell:  Arr[ind] - fee + dp[ind+1][0]

    2) Subtract fee on BUY:
         profit = sellingPrice - (buyingPrice + fee)
         Recurrence:
           On buy:  -(Arr[ind] + fee) + dp[ind+1][1]
           On sell:  Arr[ind] + dp[ind+1][0]

  Both give the same final profit. We subtract on sell because
  it feels more natural: "when I sell, I pay the fee out of my
  proceeds." The state machine stays the same; only the cost
  placement changes.

============================================================
  STATE DEFINITION
============================================================
  - dp[ind][buy] → max profit from day 'ind' onward with
    given buy-state (0 = can buy, 1 = can sell / holding).
  - No 'cap' dimension because transactions are unlimited;
    the only cost is the per-transaction fee.

============================================================
  APPROACH 1: Recursion + Memoization (Top-Down)
============================================================
  - At each state (ind, buy):
      buy == 0 (not holding):
        - Skip: move to ind+1, stay in buy=0.
        - Buy: pay -Arr[ind], move to ind+1, buy=1.
               (no fee charged on buy)
      buy == 1 (holding):
        - Skip: move to ind+1, stay in buy=1.
        - Sell: gain +Arr[ind], pay -fee, move to ind+1,
                buy=0.
  - Base case: ind == n → 0 profit.
  - Memoize in dp[ind][buy] (size n × 2).
*/

class StockWithFeeRec {
    int getAns(vector<int>& Arr, int ind, int buy, int n, int fee,
               vector<vector<int>>& dp) {
        if (ind == n) return 0;

        if (dp[ind][buy] != -1) return dp[ind][buy];

        int profit = 0;

        if (buy == 0) { // Can buy
            profit = max(
                0 + getAns(Arr, ind + 1, 0, n, fee, dp),
                -Arr[ind] + getAns(Arr, ind + 1, 1, n, fee, dp)
            );
        }

        if (buy == 1) { // Can sell — pay fee here
            profit = max(
                0 + getAns(Arr, ind + 1, 1, n, fee, dp),
                Arr[ind] - fee + getAns(Arr, ind + 1, 0, n, fee, dp)
            );
        }

        return dp[ind][buy] = profit;
    }

public:
    int maxProfit(int n, int fee, vector<int>& Arr) {
        if (n == 0) return 0;
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return getAns(Arr, 0, 0, n, fee, dp);
    }
};

/*
============================================================
  APPROACH 2: Tabulation (Bottom-Up)
============================================================
  - Fill dp from ind = n-1 down to 0.
  - dp[ind][*] depends only on dp[ind+1][*] → size n+1 suffices.
  - dp[n][0] = dp[n][1] = 0 (past the last day, no profit).
  - Answer = dp[0][0].
*/

class StockWithFeeTab {
public:
    int maxProfit(int n, int fee, vector<int>& Arr) {
        if (n == 0) return 0;

        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for (int ind = n - 1; ind >= 0; ind--) {
            // Can buy
            dp[ind][0] = max(
                0 + dp[ind + 1][0],
                -Arr[ind] + dp[ind + 1][1]
            );

            // Can sell — subtract fee from selling price
            dp[ind][1] = max(
                0 + dp[ind + 1][1],
                Arr[ind] - fee + dp[ind + 1][0]
            );
        }

        return dp[0][0];
    }
};

/*
============================================================
  APPROACH 3: Space-Optimized Tabulation
============================================================
  - dp[ind][*] only depends on dp[ind+1][*].
  - We keep two 1D arrays (each of size 2):
      ahead → dp[ind+1][0], dp[ind+1][1]
      cur   → dp[ind][0],   dp[ind][1]
  - Initially ahead = {0, 0} (dp[n]).
  - After each iteration, ahead = cur.
  - Space: O(1).
*/

class StockWithFeeOpt {
public:
    int maxProfit(int n, int fee, vector<int>& Arr) {
        if (n == 0) return 0;

        // ahead[0] = dp[ind+1][0],  ahead[1] = dp[ind+1][1]
        vector<int> ahead(2, 0);
        vector<int> cur(2, 0);

        for (int ind = n - 1; ind >= 0; ind--) {
            cur[0] = max(0 + ahead[0], -Arr[ind] + ahead[1]);

            cur[1] = max(0 + ahead[1], Arr[ind] - fee + ahead[0]);

            ahead = cur;
        }

        return ahead[0];
    }
};

/*
============================================================
  MAIN
============================================================
  Input:  prices = {1, 3, 2, 8, 4, 9},  fee = 2
  Optimal:
    - Buy at 1, sell at 8 → profit 7 - 2(fee) = 5
    - Buy at 4, sell at 9 → profit 5 - 2(fee) = 3
    - Total = 8
*/

int main() {
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    int n = prices.size();
    int fee = 2;

    StockWithFeeRec sol1;
    StockWithFeeTab sol2;
    StockWithFeeOpt sol3;

    cout << "Recursion + Memoization : " << sol1.maxProfit(n, fee, prices) << endl;
    cout << "Tabulation              : " << sol2.maxProfit(n, fee, prices) << endl;
    cout << "Space Optimized          : " << sol3.maxProfit(n, fee, prices) << endl;

    return 0;
}
