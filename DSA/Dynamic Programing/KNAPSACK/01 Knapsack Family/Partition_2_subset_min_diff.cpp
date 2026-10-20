#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
=============================================================================
 PARTITION INTO 2 SUBSETS WITH MINIMUM SUM DIFFERENCE
 Classic DP  ->  0/1 Knapsack  ->  Subset Sum variant
=============================================================================

 ----------------------------------------------------------------------------
 1. THE INTUITION / MATH
 ----------------------------------------------------------------------------
 Take:  arr = [1, 6, 11, 5]

 We must split the elements into two groups so that
 the absolute difference of their sums is minimum.

 Let:
     S  = sum of ALL array elements
     s1 = sum of subset 1
     s2 = sum of subset 2

 Every element goes to exactly one subset, so:
     s1 + s2 = S          ->   s2 = S - s1

 The difference we want to minimise:
     D = | s1 - s2 |
       = | s1 - (S - s1) |
       = | S - 2*s1 |                    <-- THE KEY FORMULA

 So we do NOT need to try every pair of subsets (that would be 2^n).
 We only need ONE subset whose sum s1 is as close as possible to S/2,
 because  |S - 2*s1|  is smallest when s1 is nearest to S/2.

 For our example:
     S = 1 + 6 + 11 + 5 = 23
     S / 2 = 11.5   ->   we look for the largest achievable sum <= 11

     Best subset:  {1, 5, 6}  sum = 12   ... but 12 > 11.5 is not allowed
                    (we only test sums <= floor(S/2) = 11)
     Achievable <= 11:  {11} = 11   and   {1,5,6}... = 12 (too big)
     Actually best s1 = 11  ->  s2 = 12
     D = |23 - 2*11| = |23 - 22| = 1        <-- answer = 1

     Subset 1 = {11}          sum = 11
     Subset 2 = {1, 6, 5}     sum = 12
     difference = 1  (minimum possible)

 IMPORTANT: testing only sums s <= floor(S/2) is enough, because any
 s > S/2 has a mirror image S - s < S/2 with the same |S - 2s| value.

 ----------------------------------------------------------------------------
 2. REDUCTION TO THE SUBSET-SUM PROBLEM
 ----------------------------------------------------------------------------
 "Is there a subset with sum exactly s?"  ->  that is the classic
 0/1 Knapsack / Subset Sum DP.

 Answer for every s in [0 .. S/2], then pick the LARGEST s that is
 achievable, and return  S - 2*s.

 Recurrence for "can we form sum s using arr[0..i] ?" :

     take    = (arr[i] <= s) && can(i-1, s - arr[i])   // include arr[i]
     notTake = can(i-1, s)                             // skip arr[i]

     dp[i][s] = take || notTake

 Base cases:
     dp[i][0]  = true   for all i   // sum 0 is made by taking NOTHING
     dp[0][x]  = (arr[0] == x)      // with only the first element

 ----------------------------------------------------------------------------
 3. SOLUTION A - MEMOIZATION (top-down recursion)
 ----------------------------------------------------------------------------
 solve(i, target) asks:
   "Using only arr[0..i], can I build exactly `target`?"

   * target == 0        -> yes, empty selection          (base case)
   * i == 0             -> only arr[0] is left, so it works only if arr[0]==target
   * dp[i][target]!=-1  -> already computed, return it (memo / overlap saving)
   * otherwise          -> try notTake, and take if arr[i] <= target,
                           store the OR result in dp[i][target]

 dp table size: n x (S/2 + 1), initialised with -1 (= not computed yet).

 Why does the loop run s from target DOWN TO 0?
     Because D = |S - 2*s| shrinks as s grows towards S/2. So the FIRST
     (i.e. largest) achievable s gives the minimum difference -> return
     sum - 2*s immediately.

     s = S/2  ->  difference = 0   (perfect partition)
     ... down to ...
     s = 0    ->  difference = S   (one subset empty, the fallback)

 DRY RUN of the recursion for arr = [1, 6, 11, 5], S = 23, target = 11:

     solve(3, 11)   // arr[3] = 5 <= 11, so both branches exist
       notTake = solve(2, 11)          // do not use 5
       take    = solve(2, 11 - 5) = solve(2, 6)   // use 5

       solve(2, 11)  // arr[2] = 11
         notTake = solve(1, 11)
         take    = solve(1, 11-11) = solve(1, 0)
                     -> target == 0  ->  TRUE
         => take = TRUE  =>  solve(2, 11) = TRUE   (dp[2][11] = 1)

       => take branch of solve(3,11) = TRUE  =>  solve(3, 11) = TRUE

     Back in minDifference: s = 11 is achievable on the very first try,
         return  sum - 2*s = 23 - 22 = 1.

 Complexity:  O(n * S)  time,  O(n * S)  space  (S = total sum, here S/2 states per row).

 ----------------------------------------------------------------------------
 4. SOLUTION B - TABULATION (bottom-up, same recurrence, no recursion)
 ----------------------------------------------------------------------------
 dp[i][s] = "can arr[0..i] produce sum s?"

 Fill order: row by row (i = 0 -> n-1), each row s = 0 -> target.
 Each cell only needs the previous row (i-1), so no recursion stack.

 Step 1:  dp[i][0] = true for every row          // sum 0 always possible
 Step 2:  dp[0][arr[0]] = true if arr[0] <= target
 Step 3:  dp[i][s] = dp[i-1][s]  ||  (arr[i] <= s ? dp[i-1][s-arr[0->i]] : false)
 Step 4:  scan s from target down to 0, first dp[n-1][s] == true wins.

 FULL DRY RUN:  arr = [1, 6, 11, 5],  sum = 23,  target = 11
 (T = true, F = false; row i uses only arr[0..i])

   s ->       0   1   2   3   4   5   6   7   8   9  10  11
   i=0 (1)    T   T   F   F   F   F   F   F   F   F   F   F
   i=1 (6)    T   T   F   F   F   F   T   T   F   F   F   F
   i=2 (11)   T   T   F   F   F   F   T   T   F   F   F   T
   i=3 (5)    T   T   F   F   F   T   T   T   F   F   F   T

   How row i=1 (arr[1] = 6) is computed, e.g.:
       s=6: notTake = dp[0][6] = F
            take    = dp[0][6-6] = dp[0][0] = T   ->  dp[1][6] = T
       s=7: notTake = dp[0][7] = F
            take    = dp[0][7-6] = dp[0][1] = T   ->  dp[1][7] = T
       s=8: notTake = F , take = dp[0][2] = F     ->  dp[1][8] = F

   How row i=3 (arr[3] = 5) is computed, e.g.:
       s=11: notTake = dp[2][11] = T             ->  dp[3][11] = T
       s=10: notTake = dp[2][10] = F
             take    = dp[2][10-5] = dp[2][5] = F ->  dp[3][10] = F
       s=5:  notTake = dp[2][5] = F
             take    = dp[2][0] = T               ->  dp[3][5] = T

   Final scan (s = 11 down to 0) on the last row:
       dp[3][11] = T  ->  return sum - 2*s = 23 - 22 = 1   <-- ANSWER

   (If no s in [0..target] were reachable -- impossible for s=0, which is
    always true -- we fall back to `return sum`, meaning one subset empty.)

 Complexity:  O(n * S)  time,  O(n * S)  space  (can be cut to O(S) with
             a single 1-D array processed right-to-left, exactly like the
             0/1 knapsack space optimisation).

 ----------------------------------------------------------------------------
 5. WHY THE ANSWER IS ALWAYS  sum - 2 * bestSum
 ----------------------------------------------------------------------------
     subset1 = bestSum = s
     subset2 = sum - s
     diff    = | (sum - s) - s | = | sum - 2*s |
     and since s <= sum/2,  sum - 2*s >= 0,  so abs() is not even needed.
=============================================================================
*/

class Solution {                      // ---------- MEMOIZATION (top-down) ----------
public:
    // "Can I build exactly `target` using only arr[0..i] ?"
    bool solve(int i, int target, vector<int>& arr, vector<vector<int>>& dp) {
        if (target == 0) return true;              // empty subset makes sum 0
        if (i == 0) return arr[0] == target;       // only arr[0] available

        if (dp[i][target] != -1) return dp[i][target];   // already solved -> reuse

        bool notTake = solve(i - 1, target, arr, dp);    // skip arr[i]

        bool take = false;
        if (arr[i] <= target) {                          // only if it can fit
            take = solve(i - 1, target - arr[i], arr, dp);   // include arr[i]
        }

        return dp[i][target] = (take || notTake);  // memoise: either way works
    }

    int minDifference(vector<int>& arr) {
        int n = arr.size();
        int sum = accumulate(arr.begin(), arr.end(), 0);
        int target = sum / 2;                       // we aim for the half-sum

        vector<vector<int>> dp(n, vector<int>(target + 1, -1));   // -1 = uncomputed

        // Largest achievable s <= sum/2 gives |sum - 2s| closest to 0
        for (int s = target; s >= 0; s--) {
            if (solve(n - 1, s, arr, dp)) {
                return sum - 2 * s;                 // = difference between the two subsets
            }
        }

        return sum;   // fallback: one subset empty, difference = whole sum
    }
};




class SolutionTabulation {           // ---------- TABULATION (bottom-up) ----------
public:
    int minDifference(vector<int>& arr) {
        int n = arr.size();
        int sum = accumulate(arr.begin(), arr.end(), 0);
        int target = sum / 2;                        // best subset sum <= S/2

        // dp[i][s] = can arr[0..i] produce exactly sum s ?
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

        // Sum 0 is possible by choosing no elements.
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }

        // Base case: using only the first element.
        if (arr[0] <= target) {
            dp[0][arr[0]] = true;
        }

        // Fill the DP table row by row (each row = one more element allowed).
        for (int i = 1; i < n; i++) {
            for (int s = 1; s <= target; s++) {
                bool notTake = dp[i - 1][s];            // skip arr[i]

                bool take = false;
                if (arr[i] <= s) {
                    take = dp[i - 1][s - arr[i]];       // include arr[i]
                }

                dp[i][s] = take || notTake;             // reachable either way
            }
        }

        // Find the largest achievable sum <= sum / 2.
        for (int s = target; s >= 0; s--) {
            if (dp[n - 1][s]) {
                return sum - 2 * s;                     // minimum difference
            }
        }

        return sum;   // fallback: one subset empty
    }
};




int main(){
    vector<int> arr = {1, 6, 11, 5};   // sum = 23, target = 11
    Solution memo;
    SolutionTabulation tab;
    cout << "Memoization  answer : " << memo.minDifference(arr) << endl;      // 1
    cout << "Tabulation   answer : " << tab.minDifference(arr)  << endl;      // 1
    return 0;
}
