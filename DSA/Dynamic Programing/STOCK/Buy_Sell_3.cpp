#include <bits/stdc++.h>
using namespace std;

/*
Problem: Best Time to Buy and Sell Stock III
You may complete AT MOST 2 transactions.

KEY DIFFERENCE from Stock II (unlimited transactions):
  - Stock II: No cap parameter, can buy/sell any number of times.
    The TAKE/NOT TAKE logic only tracks buy (0/1) state.
  - Stock III: Adds cap parameter (max 2 transactions).
    After selling twice, cap becomes 0 and all trading stops.

HOW cap LIMITS TRANSACTIONS:
  - cap = number of transactions REMAINING (starts at 2).
  - A "transaction" = one complete buy + sell cycle.
  - BUY: cap stays UNCHANGED (buying alone isn't a full transaction).
  - SELL: cap DECREMENTS by 1 (completes the buy+sell cycle).
  - When cap == 0: no more buying or selling allowed (base case returns 0).

  Example flow for Stock III (cap=2):
    cap=2 → BUY(x)  → cap=2 → SELL(x) → cap=1 (1 transaction done)
    cap=1 → BUY(x)  → cap=1 → SELL(x) → cap=0 (2 transactions done)
    cap=0 → STOP (no more trades)

  This contrasts with Stock I (cap=1) where only 1 transaction is possible.
  Stock III extends the same cap logic but with cap=2 instead of cap=1.

STATE REPRESENTATION:
  - ind: current day index
  - buy: 0 = can buy (not holding), 1 = can sell (holding a stock)
  - cap: remaining transaction count (0, 1, or 2)

TAKE / NOT TAKE STRUCTURE:
  For state (ind, buy, cap):
    if buy == 0 (can buy):
      NOT TAKE:  skip → 0 + f(ind+1, 0, cap)     // don't buy, stay in buy state
      TAKE:      buy  → -Arr[ind] + f(ind+1, 1, cap)  // buy, move to sell state
      ans = max(TAKE, NOT TAKE)

    if buy == 1 (can sell):
      NOT TAKE:  skip      → 0 + f(ind+1, 1, cap)        // don't sell, stay in sell state
      TAKE:      sell      → Arr[ind] + f(ind+1, 0, cap-1)  // sell, cap reduces
      ans = max(TAKE, NOT TAKE)

BASE CASES:
  - ind == n (no days left) → return 0
  - cap == 0 (no transactions left) → return 0
*/

// ============================================================
// Approach 1: Recursion + Memoization (Top-Down DP)
// ============================================================
class Memoization {
    /*
    3D DP state: dp[ind][buy][cap]
    Dimensions: [n][2][3]
       - n days
       - 2 states (buy=0 or buy=1)
       - 3 cap values (0, 1, 2) — cap=0 is always 0 (base case)

    The recursion explores all possibilities. Memoization avoids
    recomputation of repeated states (ind, buy, cap).
    */
    int solve(vector<int>& Arr, int n, int ind, int buy, int cap,
              vector<vector<vector<int>>>& dp) {
        // Base case: exhausted days OR no transactions left
        if (ind == n || cap == 0)
            return 0;

        if (dp[ind][buy][cap] != -1)
            return dp[ind][buy][cap];

        int profit = 0;

        if (buy == 0) {
            // Can BUY: max(skip buying, buy stock)
            int notTake = 0 + solve(Arr, n, ind + 1, 0, cap, dp);
            int take    = -Arr[ind] + solve(Arr, n, ind + 1, 1, cap, dp);
            profit = max(notTake, take);
        } else {
            // Can SELL: max(skip selling, sell stock)
            int notTake = 0 + solve(Arr, n, ind + 1, 1, cap, dp);
            int take    = Arr[ind] + solve(Arr, n, ind + 1, 0, cap - 1, dp);
            profit = max(notTake, take);
        }

        return dp[ind][buy][cap] = profit;
    }

public:
    int maxProfit(vector<int>& prices, int n) {
        // dp[ind][buy][cap] — cap dimension size 3 (0, 1, 2)
        vector<vector<vector<int>>> dp(
            n,
            vector<vector<int>>(2, vector<int>(3, -1))
        );
        // Start: day 0, buy=0 (can buy), cap=2 (2 transactions max)
        return solve(prices, n, 0, 0, 2, dp);
    }
};

// ============================================================
// Approach 2: Tabulation (Bottom-Up DP)
// ============================================================
class Tabulation {
    /*
    Instead of recursion, fill the 3D DP table iteratively.
    Base cases are already 0 via initialization (dp[n][*][*] = 0, dp[*][*][0] = 0).

    Fill order:
      ind: n-1 → 0 (bottom-up, since dp[ind] depends on dp[ind+1])
      buy: 0 → 1
      cap: 1 → 2 (cap=0 is always 0, no need to process)

    Transition (same as recursion but reversed direction):
      dp[ind][0][cap] = max(dp[ind+1][0][cap],              // skip buy
                            -Arr[ind] + dp[ind+1][1][cap])    // take buy

      dp[ind][1][cap] = max(dp[ind+1][1][cap],              // skip sell
                            Arr[ind] + dp[ind+1][0][cap-1])  // take sell
    */
public:
    int maxProfit(vector<int>& Arr, int n) {
        vector<vector<vector<int>>> dp(
            n + 1,
            vector<vector<int>>(2, vector<int>(3, 0))
        );

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= 2; cap++) {
                    if (buy == 0) {
                        dp[ind][0][cap] = max(
                            dp[ind + 1][0][cap],            // NOT TAKE: skip buying
                            -Arr[ind] + dp[ind + 1][1][cap] // TAKE: buy stock
                        );
                    } else {
                        dp[ind][1][cap] = max(
                            dp[ind + 1][1][cap],              // NOT TAKE: skip selling
                            Arr[ind] + dp[ind + 1][0][cap - 1] // TAKE: sell (cap-1)
                        );
                    }
                }
            }
        }

        // Result: day 0, buy state, 2 transactions remaining
        return dp[0][0][2];
    }
};

// ============================================================
// Approach 3: Space Optimized Tabulation (2D arrays)
// ============================================================
class TabulationSpaceOptimized {
    /*
    Observation: dp[ind] depends only on dp[ind+1] (next day).
    So we can replace the 3D table [n+1][2][3] with two 2D layers:
      - ahead[2][3]: represents dp[ind+1][buy][cap]
      - cur[2][3]:   represents dp[ind][buy][cap]

    After processing each day, shift: ahead = cur.
    This reduces space from O(n*2*3) to O(2*3) = O(1).

    cap logic is identical: selling accesses ahead[0][cap-1] which
    enforces the transaction limit.
    */
public:
    int maxProfit(vector<int>& Arr, int n) {
        // ahead[ind+1] layer: 2 buy states × 3 cap values
        vector<vector<int>> ahead(2, vector<int>(3, 0));
        // cur[ind] layer
        vector<vector<int>> cur(2, vector<int>(3, 0));

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= 2; cap++) {
                    if (buy == 0) {
                        cur[0][cap] = max(
                            ahead[0][cap],
                            -Arr[ind] + ahead[1][cap]
                        );
                    } else {
                        cur[1][cap] = max(
                            ahead[1][cap],
                            Arr[ind] + ahead[0][cap - 1]
                        );
                    }
                }
            }
            ahead = cur;
        }

        return ahead[0][2];
    }
};

// ============================================================
// Approach 4: Space Optimized with 4 variables (Transaction approach)
// ============================================================
class FourVariables {
    /*
    For Stock III (max 2 transactions), we can think of tracking
    four states directly, representing 2 buy and 2 sell opportunities:

      firstBuy   = min price seen so far (for 1st buy)
      firstSell  = max profit after 1st sell
      secondBuy  = effective cost for 2nd buy (price - profit from 1st sell)
      secondSell = max profit after 2nd sell

    This avoids the general DP table entirely and gives O(1) space.

    HOW cap is implicitly enforced:
      - We only track 2 buy and 2 sell states.
      - There's no way to do a 3rd transaction because there are
        no thirdBuy / thirdSell variables.
      - Each sell updates firstSell or secondSell, consuming one
        transaction slot.

    This approach is Stock III specific and doesn't generalize
    to Stock IV (k transactions) without a loop.
    */
public:
    int maxProfit(vector<int>& prices, int n) {
        int firstBuy   = INT_MAX;
        int firstSell  = 0;
        int secondBuy  = INT_MAX;
        int secondSell = 0;

        for (int i = 0; i < n; i++) {
            // First transaction: buy at lowest price so far
            firstBuy  = min(firstBuy, prices[i]);
            // First transaction: sell at max profit so far
            firstSell = max(firstSell, prices[i] - firstBuy);

            // Second transaction: effective buy = price - profit from first sell
            // This means we treat our total money as (profit from 1st) - price for 2nd buy
            secondBuy  = min(secondBuy, prices[i] - firstSell);
            // Second transaction: sell the second stock
            secondSell = max(secondSell, prices[i] - secondBuy);
        }

        return secondSell;
    }
};

int main() {
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
    int n = prices.size();

    Memoization sol1;
    cout << "1. Memoization:  " << sol1.maxProfit(prices, n) << endl;

    Tabulation sol2;
    cout << "2. Tabulation:   " << sol2.maxProfit(prices, n) << endl;

    TabulationSpaceOptimized sol3;
    cout << "3. Space Opt:     " << sol3.maxProfit(prices, n) << endl;

    FourVariables sol4;
    cout << "4. Four Vars:     " << sol4.maxProfit(prices, n) << endl;

    return 0;
}