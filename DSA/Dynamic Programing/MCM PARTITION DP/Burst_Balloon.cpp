#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ============================================================================
   PROBLEM : Burst Balloons (LeetCode 312)

   You are given n balloons, indexed from 0 to n-1. Each balloon has a number.
   If you burst balloon i, you get nums[left] * nums[i] * nums[right] coins,
   where left/right are the nearest NOT-YET-BURST balloons on each side.
   Find the maximum coins you can collect by bursting all balloons.

   KEY INSIGHT (Interval DP / MCM pattern):
   Instead of thinking "which balloon to burst FIRST",
   think "which balloon is burst LAST in the current interval [i..j]".

   Why LAST?
   - When we decide that balloon k is the last to burst in [i..j],
     the balloons i-1 and j+1 are still alive at that moment.
     So bursting k gives exactly  nums[i-1] * nums[k] * nums[j+1]  coins.
   - The left interval [i..k-1] and right interval [k+1..j] are then
     independent subproblems, because k acts as a boundary between them.

   Recurrence:
     dp[i][j] = max over k in [i..j] of
                ( nums[i-1] * nums[k] * nums[j+1]  +  dp[i][k-1]  +  dp[k+1][j] )

   To avoid handling boundary conditions, we pad the array with two virtual
   balloons of value 1 at both ends (nums[0] = 1, nums[n+1] = 1).
   Original balloons now occupy indices 1..n. The answer is dp[1][n].

   Complexity:
     States          : O(n^2)
     Transitions     : O(n) per state  =>  Total O(n^3)
     Space           : O(n^2)
   ============================================================================ */


/* ============================================================================
   APPROACH 1 : RECURSION + MEMOIZATION (TOP-DOWN)

   solve(i, j) returns the max coins obtainable by bursting all balloons in the
   interval [i..j]. The overlapping subproblem structure is handled by dp[i][j].
   ============================================================================ */
class Solution {
public:

    // Returns max coins for interval [i..j] (inclusive)
    int solve(int i, int j, vector<int>& nums, vector<vector<int>>& dp)
    {
        // BASE CASE: empty interval -> no balloons left, no coins
        if(i > j)
            return 0;

        // MEMOIZATION: return the pre-computed answer if it already exists
        if(dp[i][j] != -1)
            return dp[i][j];

        int maxi = 0;

        // Try every balloon k as the LAST balloon to burst in [i..j]
        for(int k = i; k <= j; k++)
        {
            // k is burst last, so neighbours i-1 and j+1 are still alive
            int currentCoins = nums[i-1] * nums[k] * nums[j+1];

            // Solve left interval [i..k-1] independently
            int left = solve(i, k-1, nums, dp);

            // Solve right interval [k+1..j] independently
            int right = solve(k+1, j, nums, dp);

            // Take the best possible k
            maxi = max(maxi, currentCoins + left + right);
        }

        // Store and return the result for interval [i..j]
        return dp[i][j] = maxi;
    }

    int maxCoins(vector<int>& balloons)
    {
        int n = balloons.size();

        // Pad array with virtual balloons of value 1 on both sides
        vector<int> nums = balloons;    // copy the real balloons (indices 1..n)
        nums.insert(nums.begin(), 1);   // virtual balloon at index 0
        nums.push_back(1);              // virtual balloon at index n+1

        // dp[i][j] = -1 means interval [i..j] is not yet computed
        vector<vector<int>> dp(n+2, vector<int>(n+2, -1));

        // Answer for the full interval of real balloons [1..n]
        return solve(1, n, nums, dp);
    }
};


/* ============================================================================
   APPROACH 2 : TABULATION (BOTTOM-UP) - REVERSE-i TRAVERSAL

   The ONLY rule tabulation must obey:
   every sub-interval must be fully computed BEFORE the interval that uses it.

   Dependencies of dp[i][j] and where they live in the table:

     - dp[i][k-1] : same row i, column k-1 (left of j).
                    Ready if columns are filled left -> right.
     - dp[k+1][j] : row k+1 (BELOW i), same column j.
                    Ready only if ALL lower rows are filled first.

   So the two fill rules are:

     1. i from n DOWN to 1 (bottom -> top):
        Lower rows (larger i) are filled before higher rows.
        This guarantees dp[k+1][j] is always available.

     2. j from i UP to n (left -> right):
        In the current row, smaller j values are filled first.
        This guarantees dp[i][k-1] is always available.

   Why does j start at i?
     - dp[i][i-1] is an EMPTY interval -> value 0 by initialisation.
     - We only need the upper triangle (j >= i).

   FILL TRACE for n = 4 (rows filled in this order):
     i = 4 : (4,4)
     i = 3 : (3,3) (3,4)
     i = 2 : (2,2) (2,3) (2,4)
     i = 1 : (1,1) (1,2) (1,3) (1,4)

   Verify dp[2][4]: it needs
     - dp[2][k-1] -> same row 2, already filled (j grew left -> right)
     - dp[k+1][4] for k = 2,3,4 -> rows 3 and 4, already filled (i moved down->up)
   Every dependency is available before it is needed.
   ============================================================================ */
class Solution {
public:

    int maxCoins(vector<int>& balloons)
    {
        int n = balloons.size();

        // Pad array with virtual balloons of value 1 on both sides
        vector<int> nums = balloons;    // copy the real balloons (indices 1..n)
        nums.insert(nums.begin(), 1);   // virtual balloon at index 0
        nums.push_back(1);              // virtual balloon at index n+1

        // dp table initialised to 0 (empty intervals already give 0)
        vector<vector<int>> dp(n+2, vector<int>(n+2, 0));

        // i goes from bottom-right of the table towards top-left
        for(int i = n; i >= 1; i--)
        {
            // j always starts at i so we only fill the upper triangle
            for(int j = i; j <= n; j++)
            {
                int maxi = 0;

                // Try every balloon k as the LAST balloon in [i..j]
                for(int k = i; k <= j; k++)
                {
                    // k is burst last, neighbours i-1 and j+1 are alive
                    int currentCoins =
                        nums[i-1] * nums[k] * nums[j+1];

                    // Left interval is already computed (same row, smaller j)
                    int left = dp[i][k-1];

                    // Right interval is already computed (larger i row)
                    int right = dp[k+1][j];

                    // Take the best k
                    maxi = max(maxi,
                               currentCoins + left + right);
                }

                dp[i][j] = maxi;
            }
        }

        // Answer for the full interval of real balloons [1..n]
        return dp[1][n];
    }
};


/* ============================================================================
   APPROACH 3 : TABULATION (BOTTOM-UP) - BY INTERVAL LENGTH

   This is the canonical MCM / matrix-chain-order fill pattern.
   The recurrence is IDENTICAL to Approach 2; only the fill ORDER changes.

   Both dependencies of dp[i][j] are on intervals STRICTLY smaller than [i..j]:

     - dp[i][k-1] has length  (k-1) - i + 1  =  k - i  <  len
     - dp[k+1][j] has length  j - (k+1) + 1  =  j - k   <  len

   So if we process intervals in increasing order of LENGTH,
   every smaller interval is guaranteed to be filled before we need it.

   WHAT EACH LOOP DOES:
     - outer len  : the SIZE of the interval we are solving right now (1..n).
     - inner i    : sliding START position; window stays inside [1..n].
     - j = i + len - 1 : the matching END position.
       Together (i, j) visits every interval of exactly that length.

   FILL TRACE for n = 4:
     len = 1 : (1,1) (2,2) (3,3) (4,4)          <- diagonal
     len = 2 : (1,2) (2,3) (3,4)                <- stripe above diagonal
     len = 3 : (1,3) (2,4)
     len = 4 : (1,4)                            <- the full answer

   In other words: fill the diagonal, then the stripe above it, then the one
   above that, ... until (1,n) is reached.

   COMPARISON WITH APPROACH 2:
     - Approach 2 relies on the geometric fact
       "dependencies are left/below -> fill rows bottom-up".
     - Approach 3 relies on the logical fact
       "dependencies are smaller intervals -> fill by increasing size".
     - Both run in O(n^3) time, O(n^2) space, and both return dp[1][n].
   ============================================================================ */
class Solution {
public:

    int maxCoins(vector<int>& balloons)
    {
        int n = balloons.size();

        // Pad array with virtual balloons of value 1 on both sides
        vector<int> nums = balloons;    // copy the real balloons (indices 1..n)
        nums.insert(nums.begin(), 1);   // virtual balloon at index 0
        nums.push_back(1);              // virtual balloon at index n+1

        // dp table initialised to 0 (empty intervals already give 0)
        vector<vector<int>> dp(n+2, vector<int>(n+2, 0));

        // len = size of the current interval; we solve SMALL intervals first
        for(int len = 1; len <= n; len++)
        {
            // i = starting index; condition keeps j = i + len - 1 inside [1..n]
            for(int i = 1; i + len - 1 <= n; i++)
            {
                // End index of the interval starting at i with this length
                int j = i + len - 1;

                int maxi = 0;

                // Try every balloon k as the LAST balloon in [i..j]
                for(int k = i; k <= j; k++)
                {
                    // k is burst last, neighbours i-1 and j+1 are alive
                    int currentCoins =
                        nums[i-1] * nums[k] * nums[j+1];

                    // Both sub-intervals have length < len -> already filled
                    int left = dp[i][k-1];
                    int right = dp[k+1][j];

                    // Take the best k
                    maxi = max(maxi,
                               currentCoins + left + right);
                }

                dp[i][j] = maxi;
            }
        }

        // Answer for the full interval of real balloons [1..n]
        return dp[1][n];
    }
};


int main(){
    return 0;
}
