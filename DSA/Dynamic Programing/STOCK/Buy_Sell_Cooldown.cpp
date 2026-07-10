#include <bits/stdc++.h>
using namespace std;

/*
============================================================
  PROBLEM: Best Time to Buy and Sell Stock with Cooldown
  - You are given an array 'prices' where prices[i] is the
    stock price on day i.
  - You may complete as many transactions as you like (no
    limit on k), BUT after you SELL a stock, you MUST wait
    one day before buying again (cooldown).
  - You must sell before buying again.
  - Goal: Maximize profit.

============================================================
  STATE DEFINITION
============================================================
  - dp[ind][buy] → max profit from day 'ind' onward with
    given buy-state (0 = can buy, 1 = can sell / holding).
  - No 'cap' dimension here because there's no transaction
    limit. The only restriction is the cooldown after a sell.

============================================================
  WHY TABULATION USES SIZE (n + 2)  — DETAILED EXPLANATION
============================================================
  In the tabulation approach, we iterate ind from n-1 down
  to 0. The recurrence when selling is:

      sell = Arr[ind] + dp[ind + 2][0]

  Why dp[ind + 2]? Because after selling on day 'ind', the
  cooldown forces us to skip day 'ind + 1' entirely. So the
  earliest we can buy again is day 'ind + 2'.

  Now, consider what happens at the last few indices:
    - When ind = n - 1 (last day):  ind + 2 = n + 1
    - When ind = n - 2 (2nd last):  ind + 2 = n
    - When ind = n - 3 (3rd last):  ind + 2 = n - 1  (fine)

  So during tabulation we need valid entries for:
      dp[n][*], dp[n+1][*]   (as base cases with 0 profit)

  If we allocated size (n + 1), then:
      dp[n + 1][*]  ← out-of-bounds access → crash/UB

  Therefore we allocate size (n + 2) so that both
      dp[n][*]  and  dp[n+1][*]
  are valid (both are zero-initialised as "beyond the array").

  Pictorially (n = 5, indices 0..4):
    Allocated:  dp[0]  dp[1]  dp[2]  dp[3]  dp[4]  dp[5]  dp[6]
                                                     ↑      ↑
                                                   n=5    n+1=6
    ind=4 → needs dp[6][0]  ← safe with n+2
    ind=3 → needs dp[5][0]  ← safe with n+2

  In general:
      dp[0..n-1]  = real days
      dp[n]       = "after day n-1" (no days left)
      dp[n+1]     = "one day beyond" (still no days left,
                     but needed because ind+2 can reach here)

============================================================
  APPROACH 1: Recursion + Memoization (Top-Down)
============================================================
  - At each state (ind, buy):
      buy == 0 (not holding):
        - Skip: move to ind+1, stay in buy=0.
        - Buy: pay -Arr[ind], move to ind+1, buy=1.
      buy == 1 (holding):
        - Skip: move to ind+1, stay in buy=1.
        - Sell: gain +Arr[ind], move to ind+2 (cooldown!),
                buy=0.
  - Base case: if ind >= n → 0 profit.
  - Memoize in dp[ind][buy] (size n × 2).
  - Note: ind can reach n (skip from last day), but NOT n+1
    in this recursion because we only ever do ind+2 when
    ind ≤ n-2, which gives at most n. So size n is safe for
    the memo table (we catch ind >= n at the base case).
*/

class StockCooldownRec {
    int getAns(vector<int>& Arr, int ind, int buy, int n,
               vector<vector<int>>& dp) {
        // Base case: no days left
        if (ind >= n) return 0;

        if (dp[ind][buy] != -1) return dp[ind][buy];

        int profit = 0;

        if (buy == 0) { // Can buy
            profit = max(
                0 + getAns(Arr, ind + 1, 0, n, dp),
                -Arr[ind] + getAns(Arr, ind + 1, 1, n, dp)
            );
        }

        if (buy == 1) { // Can sell
            profit = max(
                0 + getAns(Arr, ind + 1, 1, n, dp),
                Arr[ind] + getAns(Arr, ind + 2, 0, n, dp)
            );
            // ind + 2 because of 1-day cooldown after selling
        }

        return dp[ind][buy] = profit;
    }

public:
    int maxProfit(vector<int>& Arr) {
        int n = Arr.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return getAns(Arr, 0, 0, n, dp);
    }
};

/*
============================================================
  APPROACH 2: Tabulation (Bottom-Up)
============================================================
  - We fill dp from ind = n-1 down to 0.
  - dp[ind][buy] depends on dp[ind+1] and dp[ind+2].
  - Since we go backwards, those are already computed.
  - SIZE = n + 2:
      dp[0..n-1] → real days
      dp[n]      → ind = n   (beyond last day, profit = 0)
      dp[n+1]    → ind = n+1 (beyond last day, profit = 0)
    This guarantees safe access for dp[ind+2] when ind = n-1.
  - Answer = dp[0][0].
*/

class StockCooldownTab {
public:
    int maxProfit(vector<int>& Arr) {
        int n = Arr.size();
        // dp[ind][buy] for ind = 0..n+1 → total (n+2) rows
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));

        for (int ind = n - 1; ind >= 0; ind--) {
            // Can buy
            dp[ind][0] = max(
                0 + dp[ind + 1][0],
                -Arr[ind] + dp[ind + 1][1]
            );

            // Can sell — uses dp[ind+2] because of cooldown
            dp[ind][1] = max(
                0 + dp[ind + 1][1],
                Arr[ind] + dp[ind + 2][0]
            );
        }

        return dp[0][0];
    }
};

/*
============================================================
  APPROACH 3: Space-Optimized Tabulation
============================================================
  - dp[ind][*] only depends on dp[ind+1][*] and dp[ind+2][*].
  - We keep three 1D arrays (each of size 2):
      cur    → dp[ind][*]
      front1 → dp[ind+1][*]
      front2 → dp[ind+2][*]
  - Initially front1 = dp[n][*] = 0, front2 = dp[n+1][*] = 0.
  - After computing cur, we shift:
      front2 = front1
      front1 = cur
  - Space: O(1) (just 3 × 2 = 6 integers).
*/

class StockCooldownOpt {
public:
    int maxProfit(vector<int>& Arr) {
        int n = Arr.size();

        vector<int> cur(2, 0);    // dp[ind][0], dp[ind][1]
        vector<int> front1(2, 0); // dp[ind+1][0], dp[ind+1][1]
        vector<int> front2(2, 0); // dp[ind+2][0], dp[ind+2][1]

        for (int ind = n - 1; ind >= 0; ind--) {
            // Can buy
            cur[0] = max(0 + front1[0], -Arr[ind] + front1[1]);

            // Can sell — uses front2 (ind+2) because of cooldown
            cur[1] = max(0 + front1[1], Arr[ind] + front2[0]);

            // Shift for next iteration
            front2 = front1;
            front1 = cur;
        }

        return cur[0];
    }
};

/*
============================================================
  MAIN
============================================================
  Input:  prices = {4, 9, 0, 4, 10}
  Transactions:
    - Buy at 4, sell at 9  → profit 5
    - Cooldown (skip 0)
    - Buy at 4, sell at 10 → profit 6
    - Total = 11
*/

int main() {
    vector<int> prices = {4, 9, 0, 4, 10};

    StockCooldownRec sol1;
    StockCooldownTab sol2;
    StockCooldownOpt sol3;

    cout << "Recursion + Memoization : " << sol1.maxProfit(prices) << endl;
    cout << "Tabulation              : " << sol2.maxProfit(prices) << endl;
    cout << "Space Optimized          : " << sol3.maxProfit(prices) << endl;

    return 0;
}
