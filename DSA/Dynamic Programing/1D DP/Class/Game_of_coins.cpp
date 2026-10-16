#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// =============================================================================
// PROBLEM: Game of Coins / Coin Game Winner (GFG)
// -----------------------------------------------------------------------------
// There are `n` coins. Two players A (first) and B (second) alternate.
// In one move a player MUST take exactly 1 or x or y coins (if enough coins
// are left). The player who takes the LAST coin wins (normal play).
// Return 1 if first player (A) wins with optimal play, else 0.
//
// Examples (x=3, y=4):
//   n=0 -> 0 (no move, first loses)
//   n=1 -> 1 (take 1 and win)
//   n=2 -> 0 (only take-1 possible -> leaves 1, opponent wins)
//   n=5 -> 1 (take 3, leave 2 which is losing for opponent)
// =============================================================================
// REAL LOGIC / INTUITION: "Leave a LOSING position for the opponent"
// -----------------------------------------------------------------------------
// Define for every pile size i, from the point of view of "player to move":
//   dp[i] = 1 (WIN)  : current player can force a win from i coins.
//   dp[i] = 0 (LOSE) : current player loses from i coins if opponent is optimal.
//
// Two rules (whole game theory here):
//   (1) i is WIN  if THERE EXISTS a move to a LOSE position.
//         -> you choose that move, opponent gets a losing pile.
//   (2) i is LOSE if EVERY legal move goes to a WIN position.
//         -> whatever you do, opponent still wins.
//
// Base: dp[0] = LOSE (no coins -> you cannot move -> you already lost,
//   previous player took last coin and won).
//
// Recurrence:
//   dp[i] = 1 if (dp[i-1]==0) OR (i>=x && dp[i-x]==0) OR (i>=y && dp[i-y]==0)
//   dp[i] = 0 otherwise.
// That is exactly what both codes below check.
// =============================================================================
// TREE DIAGRAM: how coins actually change (example n=5, x=3, y=4)
// -----------------------------------------------------------------------------
// Each node = coins left + whose turn. Edge = "take k". Leaf 0 = player to
// move has no move -> LOSES, so its parent (who moved to 0) WINS.
//
//                               5(A)
//                  take1 /    take3 |    \ take4
//                       /        |          \
//                   4(B)        2(B)        1(B)
//                /  |  \          |             |
//         take1/ take3| \take4 take1|         take1|
//             /     |   \   \     |               |
//          3(A)   1(A) 0(A) 1(A)  [1(A)]         0(A)
//           |      |    LOSE  |    (=WIN node)   LOSE
//           .      .     ^    .      ^             ^
//           .      .     |    .      |             |
//  Expand 3(A): 3->2,0,- : 3 takes 1 to 2(B), takes 3 to 0(B).
//  Since 0(B)=LOSE, 3(A)=WIN. Similarly 1(A)=WIN (takes to 0).
//
// Bottom-up labels (W=1 win for player to move, L=0 lose):
//   dp[0]=L (base)
//   dp[1]=W (1->0(L), exists L)
//   dp[2]=L (2->1(W) only; 3,4 not allowed; all W => L)
//   dp[3]=W (3->2(L) via take1, also 3->0(L) via take3; exists L)
//   dp[4]=W (4->3(W), 4->1(W), 4->0(L); exists L via take4)
//   dp[5]=W (5->4(W), 5->2(L) via take3, 5->1(W); exists L via take3)
//
// Winning path for A: 5(A) --take3--> 2(B) --take1--> 1(A) --take1--> 0(B)
//   A leaves 2 (a LOSE pile) to B. Whatever B does (only take1 to 1),
//   A takes last coin. If A had wrongly taken 1 first (5->4), B would take
//   4 (4->0) and win immediately. So optimal choice matters, DP finds it.
//
// Table for this example:
//   i:        0 1 2 3 4 5
//   dp[i]:    0 1 0 1 1 1   (1 = current player wins)
// =============================================================================

// =============================================================================
// METHOD 1: TOP-DOWN MEMOIZATION (recursion + memo)
// -----------------------------------------------------------------------------
// solve(n): returns 1 if player to move with n coins wins, else 0.
//   - if n==0 return 0 (LOSE, no move).
//   - if dp[n]!=-1 return cached value (memo; -1 = uncomputed).
//   - else: if ANY legal move leads to 0 (opponent loses), return/store 1.
//     Order tried: take 1, take x, take y. First LOSE-child found -> WIN.
//   - if all moves lead to 1 (opponent wins), return/store 0.
// Time: O(n), Space: O(n) memo + O(n) recursion stack.
// =============================================================================
class SolutionMemo {
public:
    int solve(int n, int x, int y, vector<int>& dp) {

        // No coins → current player cannot move → loses.
        if (n == 0)
            return 0;

        // Already solved this pile size → reuse (memoization).
        if (dp[n] != -1)
            return dp[n];

        // Move 1: take 1 coin, opponent faces (n-1).
        // If opponent loses from there (==0), we win → store 1.
        if (n >= 1 && solve(n - 1, x, y, dp) == 0)
            return dp[n] = 1;

        // Move 2: take x coins, opponent faces (n-x).
        if (n >= x && solve(n - x, x, y, dp) == 0)
            return dp[n] = 1;

        // Move 3: take y coins, opponent faces (n-y).
        if (n >= y && solve(n - y, x, y, dp) == 0)
            return dp[n] = 1;

        // No move leaves opponent in LOSE → every move gives opponent WIN.
        // So current pile is LOSE.
        return dp[n] = 0;
    }

    int findWinner(int n, int x, int y) {
        vector<int> dp(n + 1, -1);

        return solve(n, x, y, dp);
    }
};

// =============================================================================
// METHOD 2: BOTTOM-UP TABULATION (iterative)
// -----------------------------------------------------------------------------
// Same WIN/LOSE logic, but fill dp[0..n] in increasing order.
// dp[i-1], dp[i-x], dp[i-y] are all < i, so already known when computing i.
//   dp[0]=0 (LOSE), dp[1]=1 (WIN: take 1 to 0).
//   for i=2..n:
//     dp[i]=1 if any reachable predecessor is 0, else 0.
// Note: the if/else-if chain is just an OR of the three conditions —
//   dp[i-1]==0 OR (i>=x && dp[i-x]==0) OR (i>=y && dp[i-y]==0).
// Time: O(n), Space: O(n).
// =============================================================================
class SolutionTabulation {
public:
    int findWinner(int n, int x, int y) {
        vector<int> dp(n + 1, -1);

        // dp[i] = 1 → player to move with i coins wins.
        // dp[i] = 0 → player to move with i coins loses.

        dp[0] = 0;  // No coins left → current player cannot make a move → loses.
        if (n >= 1)
            dp[1] = 1;  // One coin → take it, opponent gets 0 (LOSE) → win.

        for (int i = 2; i <= n; i++) {

            // Take 1 coin → opponent gets i-1 coins.
            // If that is LOSE (0), current i is WIN (1).
            if (dp[i - 1] == 0) {
                dp[i] = 1;

            // Take x coins → opponent gets i-x coins.
            } else if (i >= x && dp[i - x] == 0) {
                dp[i] = 1;

            // Take y coins → opponent gets i-y coins.
            } else if (i >= y && dp[i - y] == 0) {
                dp[i] = 1;

            } else {
                // Every legal move hands opponent a WIN pile → i is LOSE.
                dp[i] = 0;
            }
        }

        return dp[n];
    }
};




int main(){
    return 0;
}