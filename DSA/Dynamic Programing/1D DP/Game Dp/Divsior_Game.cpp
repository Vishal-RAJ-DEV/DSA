#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// QUESTION: Divisor Game (LeetCode 1025)
// ----------------------------------------------------------------------------
// Alice and Bob take turns playing a game, with Alice playing FIRST.
//
// Initially there is a number N on the chalkboard.
// On each player's turn, that player makes a move consisting of:
//   - Choose any x with 0 < x < N  AND  N % x == 0  (x must be a divisor of N)
//   - Replace N with N - x.
//
// If a player cannot make a move (no valid divisor exists), they LOSE the turn
// (i.e., the OTHER player wins).
//
// Return true if Alice WINS the game, assuming both players play optimally.
//
// Example 1: N = 2
//   Alice picks x = 1 (divisor of 2), N becomes 2 - 1 = 1.
//   Bob's turn with N = 1: no x with 0 < x < 1 exists -> Bob cannot move -> Bob loses.
//   => Alice wins => return true.
//
// Example 2: N = 3
//   Alice can only pick x = 1, N becomes 3 - 1 = 2.
//   Bob's turn with N = 2: Bob picks x = 1, N becomes 1.
//   Alice's turn with N = 1: no move -> Alice loses => return false.
//
// WHAT IS ASKING HERE?
// -> This is a two-player ZERO-SUM GAME with optimal play.
// -> We must decide: does the FIRST player (Alice) have a winning strategy?
//
// GAME DP PATTERN (Minimax idea):
//   state n is WINNING  if there EXISTS one legal move x such that
//        the resulting state (n - x) is LOSING for the opponent.
//   state n is LOSING   if EVERY legal move leads to a WINNING state
//        for the opponent (no escaping move exists).
//
// Base case: N = 1 -> no divisor x with 0 < x < 1 -> current player LOSES.
//            dp[1] = false (false = losing position).
// ============================================================================



// ----------------------------------------------------------------------------
// Approach-1: MEMOIZATION (Top-Down DP / Recursion + caching)
// Time  : O(n * sqrt(n))  -> for each n we test divisors x < n (worst ~n, but
//         only divisors are tested; still simple bound O(n^2) if written plainly).
// Space : O(n) for dp array + O(n) recursion stack.
//
// Logic:
//   win(n) = true  if some divisor x of n makes win(n - x) == false
//   win(n) = false otherwise (all moves give opponent a win, or n == 1)
//
// Here dp[n] stores: -1 = not computed yet,
//                    0 = false (losing position)
//                    1 = true  (winning position)
// ----------------------------------------------------------------------------
class Solution_Memo {
public:
    bool solve(int n, vector<int>& dp) {
        // ---- Base case ----
        // N == 1: no valid divisor x (need 0 < x < 1), so current player LOSES.
        if (n == 1)
            return false;

        // ---- Memoization check ----
        // If dp[n] already computed (0 or 1), return the stored answer.
        if (dp[n] != -1)
            return dp[n];

        // ---- Try every possible move ----
        // x must be a proper divisor: 0 < x < n and n % x == 0.
        for (int x = 1; x < n; x++) {
            if (n % x == 0) {

                // Make the move: n -> n - x, then ask: is the OPPONENT losing?
                // If opponent LOSES from (n - x), then THIS move is winning for us.
                if (solve(n - x, dp) == false) {
                    // Found a winning move: store true and return immediately.
                    return dp[n] = true;
                }
                // Else: opponent wins from (n - x), so this move is bad.
                // Keep trying other divisors.
            }
        }

        // ---- No winning move found ----
        // Every legal move gives opponent a winning position -> we LOSE.
        return dp[n] = false;
    }

    bool divisorGame(int n) {
        // dp[i] = -1 means "not computed yet", for i = 0..n.
        vector<int> dp(n + 1, -1);

        // Ask: is state n a winning position for the player whose turn it is?
        // Alice moves first, so result for n == result for Alice.
        return solve(n, dp);
    }
};



// ----------------------------------------------------------------------------
// Approach-2: TABULATION (Bottom-Up DP - iterative)
// Time  : O(n * n) in worst case = O(n^2) (for each i, scan x from 1..i-1)
//         (can be optimized to O(n * sqrt(n)) by iterating only over divisors)
// Space : O(n) for dp array, no recursion stack.
//
// Logic:
//   Build answers for SMALL n first, then use them for BIGGER n.
//   dp[i] = true  if exists divisor x of i such that dp[i - x] == false
//   dp[i] = false otherwise
//   Loop runs i = 2..n; i = 1 already set as false (base case).
// ----------------------------------------------------------------------------
class Solution_Tabulation {
public:
    bool divisorGame(int n) {
        // dp[i] = can current player WIN when the chalkboard number is i?
        // Initialize all to false (assume losing until proven otherwise).
        vector<bool> dp(n + 1, false);

        // Base case: N = 1 -> player to move cannot move -> LOSES.
        dp[1] = false;

        // Fill dp for every value from 2 up to n (bottom-up order).
        for (int i = 2; i <= n; i++) {
            // Check every candidate move x (must be a divisor of i).
            for (int x = 1; x < i; x++) {

                // Legal move AND opponent LOSES from (i - x)?
                if (i % x == 0 && dp[i - x] == false) {
                    // One winning move is enough -> state i is WINNING.
                    dp[i] = true;
                    break;  // No need to check other divisors.
                }
            }
            // If loop ends without break: no winning move -> dp[i] stays false.
        }

        // Answer for original N. Alice starts, so if dp[n] true -> Alice wins.
        return dp[n];
    }
};



// ----------------------------------------------------------------------------
// Approach-3: MATH / PATTERN Observation - O(1) - BEST
// Time  : O(1)
// Space : O(1)
//
// Observation from small values (simulate by hand):
//   n = 1 -> false (L)
//   n = 2 -> true  (W)  only move: 2-1 = 1 (L for Bob)
//   n = 3 -> false (L)  only move: 3-1 = 2 (W for Bob)
//   n = 4 -> true  (W)  moves: 4-1=3(L for Bob) OR 4-2=2(W) -> choose 4-1
//   n = 5 -> false (L)  moves: 5-1=4(W for Bob) only proper divisor is 1
//   n = 6 -> true  (W)  moves: 6-1=5(L for Bob), 6-2=4, 6-3=3
//   n = 7 -> false (L)  only move 7-1=6 (W for Bob)
//
// Pattern: ALL EVEN n are WINNING, ALL ODD n are LOSING.
//
// Why? Because:
//   - If n is EVEN: x = 1 is a divisor -> n-1 becomes ODD. We hand an odd
//     number to opponent.
//   - If n is ODD: every divisor x of an odd n is ODD -> n - x becomes EVEN.
//     We are FORCED to hand an EVEN number to opponent.
//   - Base: n = 1 (odd) is losing. So all odd states lead to even states
//     which are opponent's winning zone...
//   - Also note: with x = 1 always available for even n, player keeps
//     forcing opponent onto odd numbers, and odd -> even always.
//     Eventually opponent reaches 1 (odd) and loses.
//
// So: Alice wins  <=>  n is EVEN  <=>  n % 2 == 0.
// ----------------------------------------------------------------------------
class Solution_Math {
public:
    bool divisorGame(int n) {
        // Even N -> Alice (first player) always wins with optimal play.
        // Odd  N -> Alice always loses.
        return n % 2 == 0;
    }
};



// NOTE: Original file had THREE classes all named `Solution`, which causes a
// "redefinition of class Solution" compilation error. Renamed above to:
//   Solution_Memo      -> memoization (top-down DP)
//   Solution_Tabulation -> tabulation (bottom-up DP)
//   Solution_Math      -> O(1) pattern/observation solution
// For LeetCode submission, rename any ONE of them back to `Solution`.
//
// COMPARISON SUMMARY:
//   Approach        | Time   | Space | Idea
//   ----------------|--------|-------|------------------------------
//   Memoization     | O(n^2) | O(n)  | Recursion + cache
//   Tabulation      | O(n^2) | O(n)  | Build small -> big
//   Math (pattern)  | O(1)   | O(1)  | Even wins / Odd loses
//
// Why "Game DP" folder?
//   This is the classic "win/lose position" DP:
//   a position is winning iff at least one move leads to a losing
//   position for the opponent; otherwise it is losing.
// ============================================================================

int main(){
    return 0;
}
