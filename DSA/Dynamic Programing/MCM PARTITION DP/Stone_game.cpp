/*
================================================================================================
                         STONE GAME - FULL EXPLANATION
================================================================================================

QUESTION:
---------
Alex and Lee play a game with piles of stones. There are an EVEN number of piles.
Each pile has a positive integer number of stones.

The game proceeds as follows:
  1. Alex and Lee take turns, Alex goes first
  2. On each turn, a player picks EITHER the FIRST or LAST pile from the row
  3. The player takes all the stones from that pile
  4. The game ends when all piles are taken
  5. The player with MORE stones wins

Given an array piles (even length), return TRUE if Alex wins.

NOTE: Both players play OPTIMALLY (best possible moves).

KEY INSIGHT:
  This is a MINIMAX game problem. At each turn:
  - The current player wants to MAXIMIZE their score difference
  - The opponent wants to MINIMIZE it (or maximize THEIR difference)

  We track the SCORE DIFFERENCE (current player's score - opponent's score):
  - If difference > 0 -> current player is winning
  - If difference < 0 -> current player is losing

  When a player picks pile[i], the score change is:
    piles[i] - (best difference opponent can get from remaining piles)

  The minus sign is crucial: it means "I gain piles[i], but then I become
  the opponent and the other player gets the best they can from what's left"

------------------------------------------------------------------------------------------------

APPROACH 1: MEMOIZATION (Top-Down DP)
--------------------------------------
  - Start from the full range [0, n-1]
  - Recursively try picking left or right
  - Cache results in dp[l][r]
  - Time: O(n^2), Space: O(n^2)

APPROACH 2: TABULATION (Bottom-Up DP)
--------------------------------------
  - Start from base case (single piles)
  - Build up for longer intervals
  - Inner loop iterates l from left to right
  - Time: O(n^2), Space: O(n^2)

------------------------------------------------------------------------------------------------

WALKTHROUGH - Example: piles = [5, 3, 1, 4]
=============================================

  n = 4 (even number of piles)

  STATE: dp[l][r] = best score difference the current player can achieve
                     from piles[l..r]

  Base cases (single pile):
  ┌────────────────────────────────────────────────────┐
  │  dp[0][0] = 5  (only pile 0, take it -> diff = 5) │
  │  dp[1][1] = 3  (only pile 1, take it -> diff = 3) │
  │  dp[2][2] = 1  (only pile 2, take it -> diff = 1) │
  │  dp[3][3] = 4  (only pile 3, take it -> diff = 4) │
  └────────────────────────────────────────────────────┘

  Interval length = 2:
  ┌────────────────────────────────────────────────────────────────┐
  │  dp[0][1]: piles[0..1] = [5, 3]                               │
  │    takeLeft  = 5 - dp[1][1] = 5 - 3 = 2                      │
  │    takeRight = 3 - dp[0][1] ... wait, need dp[0][0]           │
  │    Actually: takeRight = piles[1] - dp[0][0] = 3 - 5 = -2    │
  │    dp[0][1] = max(2, -2) = 2                                  │
  │                                                                │
  │  dp[1][2]: piles[1..2] = [3, 1]                               │
  │    takeLeft  = 3 - dp[2][2] = 3 - 1 = 2                      │
  │    takeRight = 1 - dp[1][1] = 1 - 3 = -2                     │
  │    dp[1][2] = max(2, -2) = 2                                  │
  │                                                                │
  │  dp[2][3]: piles[2..3] = [1, 4]                               │
  │    takeLeft  = 1 - dp[3][3] = 1 - 4 = -3                     │
  │    takeRight = 4 - dp[2][2] = 4 - 1 = 3                      │
  │    dp[2][3] = max(-3, 3) = 3                                  │
  └────────────────────────────────────────────────────────────────┘

  Interval length = 3:
  ┌────────────────────────────────────────────────────────────────┐
  │  dp[0][2]: piles[0..2] = [5, 3, 1]                           │
  │    takeLeft  = 5 - dp[1][2] = 5 - 2 = 3                     │
  │    takeRight = 1 - dp[0][1] = 1 - 2 = -1                    │
  │    dp[0][2] = max(3, -1) = 3                                 │
  │                                                               │
  │  dp[1][3]: piles[1..3] = [3, 1, 4]                           │
  │    takeLeft  = 3 - dp[2][3] = 3 - 3 = 0                     │
  │    takeRight = 4 - dp[1][2] = 4 - 2 = 2                     │
  │    dp[1][3] = max(0, 2) = 2                                 │
  └────────────────────────────────────────────────────────────────┘

  Interval length = 4 (FULL RANGE):
  ┌────────────────────────────────────────────────────────────────┐
  │  dp[0][3]: piles[0..3] = [5, 3, 1, 4]                        │
  │    takeLeft  = 5 - dp[1][3] = 5 - 2 = 3                     │
  │    takeRight = 4 - dp[0][2] = 4 - 3 = 1                     │
  │    dp[0][3] = max(3, 1) = 3                                  │
  └────────────────────────────────────────────────────────────────┘

  RESULT: dp[0][3] = 3 > 0 -> Alex wins! TRUE

  DP TABLE (final):
  ┌──────────────────────────────────┐
  │      0    1    2    3            │
  │  0 [ 5    2    3    3 ]          │
  │  1 [ 0    3    2    2 ]          │
  │  2 [ 0    0    1    3 ]          │
  │  3 [ 0    0    0    4 ]          │
  └──────────────────────────────────┘

------------------------------------------------------------------------------------------------

WHY pickLeft = piles[l] - solve(l+1, r)?
------------------------------------------
  When I pick the left pile:
  - I gain piles[l] stones
  - But now it's the OPPONENT's turn on piles[l+1..r]
  - The opponent will play optimally, getting solve(l+1, r)
  - My NET difference = what I took - what opponent gets
  - So: pickLeft = piles[l] - solve(l+1, r)

  The MINUS is because the opponent's gain is my loss in the difference.

  Think of it as:
  ┌──────────────────────────────────────────────────────┐
  │  My turn: pick piles[l]                              │
  │  Score so far: +piles[l]                             │
  │                                                      │
  │  Opponent's turn on [l+1..r]:                        │
  │  They get best possible difference from their view   │
  │  From MY perspective, their gain = my loss           │
  │  My net = piles[l] - opponent's_best_difference     │
  └──────────────────────────────────────────────────────┘

================================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


/*
================================================================================================
APPROACH 1: MEMOIZATION (Top-Down DP)
================================================================================================

HOW IT WORKS:
  - We use recursion to explore all possible game states
  - State: (l, r) = we're considering piles from index l to r
  - dp[l][r] = best score difference current player can achieve from piles[l..r]
  - We MEMOIZE (cache) results to avoid recomputation

RECURSION TREE (for piles = [5,3,1,4]):
  ┌──────────────────────────────────────────────────────────────────────┐
  │  solve(0,3)                                                         │
  │  ├── pick left (5): 5 - solve(1,3)                                 │
  │  │   ├── pick left (3): 3 - solve(2,3)                             │
  │  │   │   ├── pick left (1): 1 - solve(3,3) = 1-4 = -3             │
  │  │   │   └── pick right (4): 4 - solve(2,2) = 4-1 = 3             │
  │  │   │   solve(2,3) = max(-3, 3) = 3                               │
  │  │   └── pick right (4): 4 - solve(1,2)                            │
  │  │       ├── pick left (3): 3 - solve(2,2) = 3-1 = 2              │
  │  │       └── pick right (1): 1 - solve(1,1) = 1-3 = -2            │
  │  │       solve(1,2) = max(2, -2) = 2                               │
  │  │   solve(1,3) = max(3-3, 4-2) = max(0, 2) = 2                   │
  │  │                                                                 │
  │  └── pick right (4): 4 - solve(0,2)                                │
  │      ├── pick left (5): 5 - solve(1,2) = 5-2 = 3                  │
  │      └── pick right (1): 1 - solve(0,1) = 1-2 = -1                │
  │      solve(0,2) = max(3, -1) = 3                                   │
  │                                                                    │
  │  solve(0,3) = max(5-2, 4-3) = max(3, 1) = 3 > 0 -> Alex wins     │
  └──────────────────────────────────────────────────────────────────────┘
*/
class StoneGameMemoization {
public:

    int solve(vector<int>& piles, int l, int r, vector<vector<int>>& dp) {

        // Base case: only one pile left
        // The current player MUST take it, so the difference = that pile's value
        if (l == r) {
            return piles[l];
        }

        // If already computed, return cached result
        if (dp[l][r] != -1) {
            return dp[l][r];
        }

        // Option 1: Take the LEFT pile
        // I gain piles[l], then opponent plays optimally on [l+1..r]
        // My net difference = piles[l] - opponent's best difference
        int takeLeft = piles[l] - solve(piles, l + 1, r, dp);

        // Option 2: Take the RIGHT pile
        // I gain piles[r], then opponent plays optimally on [l..r-1]
        // My net difference = piles[r] - opponent's best difference
        int takeRight = piles[r] - solve(piles, l, r - 1, dp);

        // I choose whichever gives me the BEST difference
        // Store and return the result
        return dp[l][r] = max(takeLeft, takeRight);
    }

    bool stoneGame(vector<int>& piles) {

        int n = piles.size();

        // Initialize dp table with -1 (uncomputed)
        // dp[l][r] stores the best score difference from piles[l..r]
        vector<vector<int>> dp(n, vector<int>(n, -1));

        // Start with the FULL range [0, n-1]
        int difference = solve(piles, 0, n - 1, dp);

        // If difference > 0, Alex (the current player at [0,n-1]) wins
        return difference > 0;
    }
};


/*
================================================================================================
APPROACH 2: TABULATION (Bottom-Up DP) - Version 1
================================================================================================

HOW IT WORKS:
  - Instead of recursion, we build the DP table ITERATIVELY
  - Start from base cases (single piles) and build up to larger intervals
  - Fill the table for interval length = 2, 3, 4, ..., n

  INNER LOOP ITERATES l FROM LEFT TO RIGHT:
    for (int l = 0; l + len - 1 < n; l++)
      r = l + len - 1
      ... compute dp[l][r]

  This works because when computing dp[l][r], we need:
    - dp[l+1][r] (interval starting one position to the right)
    - dp[l][r-1] (interval ending one position to the left)
  Both of these are SMALLER intervals, already computed in previous iterations.

VISUAL - How the table is filled (left to right per row):
┌────────────────────────────────────────────────────────┐
│  len=1: dp[0][0] dp[1][1] dp[2][2] dp[3][3]          │
│  len=2: dp[0][1] dp[1][2] dp[2][3]                    │
│  len=3: dp[0][2] dp[1][3]                              │
│  len=4: dp[0][3]                                       │
│                                                        │
│  Arrows show dependencies:                             │
│  dp[0][1] needs dp[1][1] (below) and dp[0][0] (left)  │
│  dp[0][3] needs dp[1][3] (below) and dp[0][2] (left)  │
└────────────────────────────────────────────────────────┘
*/
class StoneGameTabulation {
public:
    bool stoneGame(vector<int>& piles) {

        int n = piles.size();

        // dp[l][r] = best score difference from piles[l..r]
        vector<vector<int>> dp(n, vector<int>(n));

        // Base case: intervals of length 1
        // If only one pile, the current player takes it -> diff = piles[i]
        for (int i = 0; i < n; i++) {
            dp[i][i] = piles[i];
        }

        // Build intervals of increasing length: 2, 3, 4, ..., n
        for (int len = 2; len <= n; len++) {

            // l = left index, r = right index
            // l goes from 0 up to n-len
            for (int l = 0; l + len - 1 < n; l++) {

                // Calculate right index from left index and length
                int r = l + len - 1;

                // Option 1: Take left pile
                // I gain piles[l], opponent gets dp[l+1][r]
                int takeLeft = piles[l] - dp[l + 1][r];

                // Option 2: Take right pile
                // I gain piles[r], opponent gets dp[l][r-1]
                int takeRight = piles[r] - dp[l][r - 1];

                // Choose the better option
                dp[l][r] = max(takeLeft, takeRight);
            }
        }

        // dp[0][n-1] = best difference for the full range
        // Positive difference means Alex wins
        return dp[0][n - 1] > 0;
    }
};


int main(){
    StoneGameMemoization sol1;
    StoneGameTabulation sol2;

    vector<int> piles = {5, 3, 1, 4};

    cout << "Memoization:   " << (sol1.stoneGame(piles) ? "Alex wins" : "Lee wins") << endl;
    cout << "Tabulation:    " << (sol2.stoneGame(piles) ? "Alex wins" : "Lee wins") << endl;

    // Another example
    vector<int> piles2 = {3, 7, 2, 3};
    cout << "\nMemoization:   " << (sol1.stoneGame(piles2) ? "Alex wins" : "Lee wins") << endl;
    cout << "Tabulation:    " << (sol2.stoneGame(piles2) ? "Alex wins" : "Lee wins") << endl;

    return 0;
}