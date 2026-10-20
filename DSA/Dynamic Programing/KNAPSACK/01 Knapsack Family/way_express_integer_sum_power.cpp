#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM: LeetCode 2787 - Ways to Express an Integer as Sum of Powers

------------------------------------------------------------
1. APPROACH: BOTTOM-UP DYNAMIC PROGRAMMING (TABULATION)
------------------------------------------------------------

We need to find the number of ways to express n as the sum
of distinct positive integers raised to power x.

For example:
n = 10, x = 2

10 = 1^2 + 3^2
   = 1 + 9

Therefore, one valid combination is {1, 3}.

We use bottom-up DP with a 1D array to count the combinations.

This problem is a variation of the 0/1 Knapsack problem because
each number raised to power x can be selected at most once.


------------------------------------------------------------
2. INTUITION AND LOGIC
------------------------------------------------------------

Consider every number num and calculate:

power = num^x

For each power, we have two choices:

CHOICE 1: SKIP
Do not use the current power.
The existing number of ways remains unchanged.

CHOICE 2: TAKE
Use the current power.
If we want to form sum s, we must previously have formed:

s - power

Therefore, the number of new ways contributed by taking
the current power is dp[s - power].

We add the two choices together.

IMPORTANT:
We count combinations, not different orders of the same
combination. For example, {1, 3} and {3, 1} are the same way.


------------------------------------------------------------
3. DP STATE
------------------------------------------------------------

dp[s] = number of ways to form sum s using the powers
        processed so far.

For example:
dp[5] = number of ways to form sum 5 using the powers
        we have considered so far.

Initially, we have not processed any powers.

dp[0] = 1
There is exactly one way to form sum 0: choose nothing.

dp[1], dp[2], ..., dp[n] = 0
Initially, no positive sum can be formed.


------------------------------------------------------------
4. BASE CASE
------------------------------------------------------------

dp[0] = 1

WHY?

Suppose the current power is 4 and we want to form sum 4.

We use the transition:

dp[4] += dp[4 - 4]
dp[4] += dp[0]

Since dp[0] = 1, we discover one way to form sum 4:
select the power 4 itself.

If dp[0] were 0, we would never be able to count a combination
that consists of just one selected power.


------------------------------------------------------------
5. DP TRANSITION
------------------------------------------------------------

For each power = num^x:

dp[s] = dp[s] + dp[s - power]

This update is performed only when s >= power.

Here:
- dp[s] represents the ways that already existed (SKIP).
- dp[s - power] represents the additional ways obtained by
  selecting the current power (TAKE).

We take the result modulo 10^9 + 7 to avoid excessively
large answers.


------------------------------------------------------------
6. WHY DO WE ITERATE BACKWARD?
------------------------------------------------------------

We iterate:

for (int s = n; s >= power; s--)

This is the most important part of the solution.

We must use each power at most once.

By iterating backward, dp[s - power] still represents
combinations formed before processing the current power.

If we iterated forward, dp[s - power] might already contain
the current power, allowing it to be selected repeatedly.

Backward iteration ensures that every power is used at most
once, which makes this a 0/1 Knapsack solution.


------------------------------------------------------------
7. HOW THE CODE WORKS
------------------------------------------------------------

STEP 1:
Create a DP array of size n + 1 and initialize every value
to zero.

STEP 2:
Set dp[0] = 1 because there is one way to form sum zero.

STEP 3:
Start from num = 1 and calculate num^x.

STEP 4:
If num^x > n, stop. This power and all larger powers
cannot be part of a valid combination.

STEP 5:
For the current power, iterate s from n down to power.

Update:
dp[s] = (dp[s] + dp[s - power]) % MOD

STEP 6:
Repeat for every valid power.

STEP 7:
Return dp[n], which contains the number of ways to form n.


------------------------------------------------------------
8. COMPLEXITY
------------------------------------------------------------

Let k = floor(n^(1/x)), the largest integer whose x-th
power does not exceed n.

Time Complexity: O(n * k)
We process k valid powers, updating at most n sums per power.

Space Complexity: O(n)
We use a single DP array of size n + 1.
*/

class Solution {
public:
    const int MOD = 1e9 + 7;
    vector<vector<int>> dp;

    // INTUITION:
    // We need to express n as the sum of distinct numbers raised to power x.
    // For example, if n = 10 and x = 2:
    // 10 = 1^2 + 3^2
    //
    // Each number can be selected at most once.
    // Therefore, this is a 0/1 Knapsack counting problem.
    // For every number, we have two choices: TAKE it or SKIP it.
    
    // Calculates num^exp, but stops early if the result exceeds limit.
    // This avoids unnecessary multiplication and prevents large overflow.
    int power_int(int num, int exp, int limit) {
        long long ans = 1;

        for (int i = 0; i < exp; i++) {
            ans *= num;

            // We only care whether the power is <= limit.
            // If it exceeds limit, it cannot be selected.
            if (ans > limit) return limit + 1;
        }

        return (int)ans;
    }

    // STATE:
    // solve(num, n, x) represents the number of ways to form
    // the remaining sum n using distinct numbers from 1 to num,
    // where every selected number is raised to power x.

    int solve(int num, int n, int x) {

        // BASE CASE 1:
        // If the remaining sum becomes 0, we have successfully
        // formed the required sum.
        // Return 1 because we found one valid combination.
        if (n == 0) return 1;

        // BASE CASE 2:
        // If no numbers are left but n is still positive,
        // we cannot form the remaining sum.
        // Therefore, there are 0 valid ways.
        if (num == 0) return 0;

        // MEMOIZATION:
        // If we have already calculated this state,
        // return the stored answer instead of recalculating it.
        if (dp[num][n] != -1) return dp[num][n];
        
        // Calculate the current number raised to power x.
        // Example: num = 3, x = 2 -> power = 9.
        int power = power_int(num, x, n);
        
        // CHOICE 1: SKIP the current number.
        // We do not use num^x, so the remaining sum stays n.
        // We can only consider numbers from 1 to num-1.
        int skip = solve(num - 1, n, x);

        // CHOICE 2: TAKE the current number.
        // We use num^x, so subtract it from the remaining sum.
        // We move to num-1 to ensure the same number cannot be
        // selected again.
        int take = 0;

        // We can take the current number only if its power
        // does not exceed the remaining sum.
        if (power <= n) {
            take = solve(num - 1, n - power, x);
        }

        // TRANSITION:
        // Total valid ways = ways that skip + ways that take.
        //
        // dp[num][n] = solve(num-1, n, x)
        //            + solve(num-1, n-num^x, x)
        //
        // The second term is included only when num^x <= n.
        // Apply modulo to keep the result within the required range.
        return dp[num][n] = (take + skip) % MOD;
    }

    int numberOfWays(int n, int x) {
        
        // Initially, all states are -1, meaning "not calculated".
        // dp[num][sum] stores the answer for solve(num, sum, x).
        dp.assign(n + 1, vector<int>(n + 1, -1));

        // Initially, the target remaining sum is n.
        // We allow numbers from 1 through n.
        return solve(n, n, x);
    }
};


class Solution {
public:
    const int MOD = 1e9 + 7;

    int numberOfWays(int n, int x) {
        // dp[s] = number of ways to form sum s using powers processed so far.
        vector<int> dp(n + 1, 0);

        // Base case: there is one way to form sum 0 — choose nothing.
        dp[0] = 1;

        // Process each number and calculate num^x.
        for (int num = 1; ; num++) {
            long long power = 1;

            for (int i = 0; i < x; i++) {
                power *= num;

                // Stop calculating if the power exceeds the target.
                if (power > n) break;
            }

            // Larger numbers will also have powers greater than n.
            if (power > n) break;

            // Transition: ways to skip + ways to take the current power.
            // Iterate backward so each power is used at most once.
            for (int s = n; s >= power; s--) {
                dp[s] = (dp[s] + dp[s - power]) % MOD;
            }
        }

        // Number of ways to form the target sum n.
        return dp[n];
    }
};


int main(){
    Solution sol;
    cout << sol.numberOfWays(10, 2) << endl;    
    return 0;
}