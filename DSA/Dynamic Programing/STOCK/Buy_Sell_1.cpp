#include <bits/stdc++.h>
using namespace std;

/*
Problem: Best Time to Buy and Sell Stock I
You may complete AT MOST 1 transaction (buy once, sell once).
Goal: Maximize profit.

--------------------------------------------------------------
PART 1: NORMAL/TRADITIONAL APPROACHES (3 approaches)
These approaches exploit the "at most 1 transaction" constraint
directly — track min price so far and max profit.
--------------------------------------------------------------
*/

// ============================================================
// Approach 1: DP Array (O(n) space)
// ============================================================
class DpWithArray {
    /*
    dp[i] = maximum profit achievable up to day i.
    Transition: dp[i] = max(dp[i-1], prices[i] - minPriceSoFar)
    */
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        vector<int> dp(n, 0);
        int minPrice = prices[0];

        for (int i = 1; i < n; i++) {
            minPrice = min(minPrice, prices[i]);
            dp[i] = max(dp[i - 1], prices[i] - minPrice);
        }

        return dp[n - 1];
    }
};

// ============================================================
// Approach 2: Space Optimized (O(1) space)
// ============================================================
class DpSpaceOptimized {
    // Instead of a dp array, keep a single variable for dp[i-1].
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        int minPrice = prices[0];
        int maxProfit = 0;      // acts as dp[i-1]

        for (int i = 1; i < n; i++) {
            minPrice = min(minPrice, prices[i]);
            maxProfit = max(maxProfit, prices[i] - minPrice);
        }

        return maxProfit;
    }
};

// ============================================================
// Approach 3: Recursion (Brute Force, exponential)
// ============================================================
class RecursionBruteForce {
    /*
    HOW cap LIMITS TRANSACTIONS:
    ----------------------------------------
    cap = number of transactions REMAINING (initially 1 for Stock I).

    A "transaction" = one complete buy + sell pair.
    cap is decremented ONLY when we SELL (i.e., complete a cycle).

    Flow:
        cap = 1 (initial)
            |
        BUY stock  →  cap stays 1 (buying doesn't consume a transaction)
            |
        SELL stock →  cap becomes 0 (one full transaction done)
            |
        cap = 0 → BASE CASE: no more buys allowed, return 0

    Key rule: When cap = 0, we return 0 immediately.
    This means the recursion path is killed — no further buy or sell
    can happen. This effectively enforces "at most 1 transaction".

    buy = 1 → can BUY (or skip buying)
    buy = 0 → can SELL (or skip selling)

    Base cases:
    - i == n (no days left) → return 0
    - cap == 0 (no transactions left) → return 0

    Difference from Stock II (unlimited transactions):
    - Stock II: no cap parameter, can buy/sell infinitely many times
    - Stock I: cap starts at 1, decrements to 0 on first sell, then stops
    */
    int solve(int i, int buy, int cap, vector<int>& prices) {
        // Base case 1: No days left → no profit
        if (i == (int)prices.size()) return 0;

        // Base case 2: No transactions remaining → cannot buy or sell
        // This is the KEY guard that prevents a second transaction.
        // Once cap=0, all recursive paths return 0, so no further action is taken.
        if (cap == 0) return 0;

        if (buy) {
            // STATE: can BUY (not holding any stock)

            // TAKE (buy): pay prices[i], move to sell state (buy=0), cap UNCHANGED
            // cap doesn't decrease here because buying alone is NOT a full transaction
            int take = -prices[i] + solve(i + 1, 0, cap, prices);

            // NOT TAKE (skip): stay in buy state, cap unchanged
            int skip = solve(i + 1, 1, cap, prices);

            return max(take, skip);
        } else {
            // STATE: can SELL (holding a stock)

            // TAKE (sell): gain prices[i], move back to buy state (buy=1),
            // cap DECREMENTS by 1 because sell completes one full transaction
            // (buy + sell = 1 transaction). After this, cap=0, so no more buying.
            int take = prices[i] + solve(i + 1, 1, cap - 1, prices);

            // NOT TAKE (skip): stay in sell state, cap unchanged
            int skip = solve(i + 1, 0, cap, prices);

            return max(take, skip);
        }
    }

public:
    int maxProfit(vector<int>& prices) {
        // start at day 0, in buy state, with 1 transaction remaining
        return solve(0, 1, 1, prices);
    }
};


/*
--------------------------------------------------------------
PART 2: DYNAMIC PROGRAMMING APPROACHES (3 approaches)
These use the generic DP framework with states (i, buy, cap)
where cap = 1 (at most 1 transaction).
--------------------------------------------------------------
*/

// ============================================================
// Approach 4: Recursion + Memoization (Top-Down DP)
// ============================================================
class Memoization {
    /*
    DP state: dp[i][buy][cap] = max profit from day i onwards,
              given current buy/sell state and remaining transactions.

    HOW cap LIMITS TRANSACTIONS (same logic as recursion):
    --------------------------------------------------------
    - cap starts at 1 (at most 1 transaction allowed for Stock I)
    - cap is decremented ONLY when we SELL (completing a buy+sell cycle)
    - When cap = 0, we return 0 immediately → no more transactions possible
    - Buying does NOT change cap (buying alone isn't a complete transaction)

    Without cap, the recursion would allow unlimited buy-sell cycles.
    cap acts as a "remaining transaction budget" — once spent, trading stops.
    */
    int solve(int i, int buy, int cap,
              vector<int>& prices,
              vector<vector<vector<int>>>& dp) {

        // Base case 1: No days left → 0 profit
        if (i == (int)prices.size()) return 0;

        // Base case 2: No transactions left → cannot trade further
        // This prevents any further buy or sell from happening.
        if (cap == 0) return 0;

        if (dp[i][buy][cap] != -1)
            return dp[i][buy][cap];

        if (buy) {
            // TAKE (buy): pay prices[i], move to sell state, cap SAME
            int take = -prices[i] + solve(i + 1, 0, cap, prices, dp);
            // NOT TAKE: stay in buy state, cap SAME
            int skip = solve(i + 1, 1, cap, prices, dp);
            return dp[i][buy][cap] = max(take, skip);
        } else {
            // TAKE (sell): gain prices[i], move to buy state, cap DECREMENTS
            // cap-1 here ensures we've used up one transaction slot
            int take = prices[i] + solve(i + 1, 1, cap - 1, prices, dp);
            // NOT TAKE: stay in sell state, cap SAME
            int skip = solve(i + 1, 0, cap, prices, dp);
            return dp[i][buy][cap] = max(take, skip);
        }
    }

public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // dp[n][2][2]: last dim = cap (0 or 1). cap=0 is always 0 (base case)
        vector<vector<vector<int>>> dp(
            n,
            vector<vector<int>>(2, vector<int>(2, -1))
        );
        // start: day 0, buy=1 (can buy), cap=1 (1 transaction remaining)
        return solve(0, 1, 1, prices, dp);
    }
};

// ============================================================
// Approach 5: Tabulation (Bottom-Up DP)
// ============================================================
class Tabulation {
    /*
    HOW cap LIMITS TRANSACTIONS in Tabulation:
    ------------------------------------------
    - dp[i][buy][cap] is the 3D table
    - cap dimension has size 2: index 0 = 0 transactions left, index 1 = 1 transaction left
    - dp[i][buy][0] = 0 for all i, buy (no transactions left → no profit possible)
    - When selling: we use dp[i+1][1][cap-1], which accesses cap=0 slot (0 profit),
      thereby preventing any further transactions after that sell.

    Example for Stock I (cap=1):
        dp[i][1][1] = max(-prices[i] + dp[i+1][0][1],    // buy, go to sell state with cap=1
                           dp[i+1][1][1])                  // skip, stay in buy state

        dp[i][0][1] = max(prices[i] + dp[i+1][1][0],      // sell, cap becomes 0
                           dp[i+1][0][1])                  // skip, stay in sell state

    Notice: when selling, we index into dp[i+1][1][0] which is ALWAYS 0.
    This guarantees that after one sell, no more transactions happen.
    */
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        // dp[i][buy][cap], initialized to 0 (handles base cases)
        vector<vector<vector<int>>> dp(
            n + 1,
            vector<vector<int>>(2, vector<int>(2, 0))
        );

        for (int i = n - 1; i >= 0; i--) {
            for (int cap = 1; cap <= 1; cap++) {
                // buy = 1 (can buy)
                dp[i][1][cap] = max(
                    -prices[i] + dp[i + 1][0][cap],   // TAKE: buy
                    dp[i + 1][1][cap]                  // NOT TAKE: skip
                );

                // buy = 0 (can sell)
                dp[i][0][cap] = max(
                    prices[i] + dp[i + 1][1][cap - 1],  // TAKE: sell
                    dp[i + 1][0][cap]                  // NOT TAKE: skip
                );
            }
        }

        return dp[0][1][1];
    }
};

// ============================================================
// Approach 6: Space Optimized Tabulation (O(1) space)
// ============================================================
class TabulationSpaceOptimized {
    /*
    HOW cap LIMITS in space-optimized version:
    -----------------------------------------
    Same logic, just 2D arrays [2][2] where first dim = buy, second dim = cap.
    ahead[1][0] and ahead[0][0] are always 0 (cap=0 → no transactions left).
    When selling: ahead[1][cap-1] = ahead[1][0] = 0 → guarantees 1 transaction max.
    */
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        vector<vector<int>> ahead(2, vector<int>(2, 0));
        vector<vector<int>> curr(2, vector<int>(2, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int cap = 1; cap <= 1; cap++) {
                // buy = 1
                curr[1][cap] = max(
                    -prices[i] + ahead[0][cap],
                    ahead[1][cap]
                );

                // buy = 0
                curr[0][cap] = max(
                    prices[i] + ahead[1][cap - 1],
                    ahead[0][cap]
                );
            }
            ahead = curr;
        }

        return ahead[1][1];
    }
};

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    cout << "--- PART 1: Normal Approaches ---" << endl;
    DpWithArray d1;
    cout << "1. DP with array:  " << d1.maxProfit(prices) << endl;

    DpSpaceOptimized d2;
    cout << "2. DP space opt:   " << d2.maxProfit(prices) << endl;

    RecursionBruteForce d3;
    cout << "3. Recursion brute:" << d3.maxProfit(prices) << endl;

    cout << "\n--- PART 2: DP Approaches ---" << endl;
    Memoization d4;
    cout << "4. Memoization:    " << d4.maxProfit(prices) << endl;

    Tabulation d5;
    cout << "5. Tabulation:     " << d5.maxProfit(prices) << endl;

    TabulationSpaceOptimized d6;
    cout << "6. Tabulation opt:  " << d6.maxProfit(prices) << endl;

    return 0;
}