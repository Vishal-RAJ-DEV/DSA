#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
PROBLEM: Friends Pairing Problem (Count Friends Pairings)
--------------------------------------------------------------------------------
Given n friends, each person can either:
  1. Stay single (alone), OR
  2. Pair up with exactly one other friend.

We have to count the total number of different ways n friends can stay
single or pair up. Order of pairs does not matter.
Example: n = 3 (A,B,C)
  1. {A},{B},{C} (all single)
  2. {A,B},{C}
  3. {A,C},{B}
  4. {B,C},{A}
Answer = 4.

Recurrence:
    f(n) = f(n-1) + (n-1) * f(n-2)
    Base: f(0) = 1 (one way to arrange 0 people: do nothing / empty set)
          f(1) = 1 (only one way: stay single)
================================================================================
*/

class Solution {
  public:
    // -------------------------------------------------------------------------
    // 1. RECURSION + MEMOIZATION (Top-Down) - Already written by you
    // TC: O(n), SC: O(n) dp + O(n) recursion stack
    // -------------------------------------------------------------------------
    int solve(int n, vector<int>&dp){
        if(n <= 1) return 1;

        if(dp[n] != -1) return dp[n];

        return dp[n] = solve(n-1, dp) + (n-1) * solve(n-2, dp);
    }
    int countFriendsPairings(int n) {
        // code here
        vector<int>dp(n + 1, -1);
        return solve(n, dp);
    }

    /*
    ================================================================================
    LOGIC EXPLAINED: Why do we multiply (n-1) with solve(n-2) ?
    --------------------------------------------------------------------------------
    Focus on the n-th person (call him person 'n'). He has exactly 2 exclusive
    choices. We count ways for each choice separately and ADD them
    (Addition Principle of Counting).

    CASE 1: Person 'n' stays SINGLE.
    --------------------------------
    If nth person stays alone, he contributes no pairing. The problem reduces to
    arranging the remaining (n-1) people.
        Ways(Case 1) = f(n-1) = solve(n-1)

    CASE 2: Person 'n' PAIRS UP with somebody.
    ------------------------------------------
    Person 'n' cannot stay unpaired here; he must pick exactly ONE partner
    from the remaining (n-1) people.

    Step 2a - Choose the partner:
        Number of choices = (n-1)C1 = (n-1).
        Example n=4 (A,B,C,D), fix D. D can pair with A or B or C => 3 choices.
        Each choice gives a DIFFERENT overall arrangement:
            {D,A}... vs {D,B}... vs {D,C}... are distinct.
        This is why we CANNOT just write + solve(n-2). That would count only
        pairing with one fixed partner and miss the other (n-2) possibilities.

    Step 2b - Arrange the rest:
        Once the pair (n, partner) is fixed, 2 people are consumed.
        Remaining people = n - 2.
        They can be single/paired among themselves in f(n-2) ways.

    Step 2c - Combine by Multiplication Principle:
        For EACH of the (n-1) partner choices, there are f(n-2) ways to
        arrange the rest.
            Ways(Case 2) = (n-1) * f(n-2) = (n-1) * solve(n-2)

    TOTAL:
        f(n) = Ways(Case 1) + Ways(Case 2)
             = f(n-1) + (n-1) * f(n-2)

    INTUITION CHECK with n = 3 (friends A,B,C, focus on C):
        Case 1: C single -> arrange A,B -> f(2) = 2 ways: {A},{B} and {A,B}
        Case 2: C pairs -> C has (3-1)=2 partner choices (A or B).
                If C-A paired, remaining = {B} -> f(1)=1 way.
                If C-B paired, remaining = {A} -> f(1)=1 way.
                Total = 2 * 1 = 2 ways.
        Grand total = 2 + 2 = 4. Correct.
    ================================================================================
    */

    // -------------------------------------------------------------------------
    // 2. TABULATION (Bottom-Up)
    // -------------------------------------------------------------------------
    // IDEA: We already know recurrence f(i) = f(i-1) + (i-1)*f(i-2).
    // Instead of recursion, build dp[] from small to large:
    //   dp[0] = 1, dp[1] = 1
    //   for i = 2..n: dp[i] = dp[i-1] + (i-1) * dp[i-2]
    // At the end dp[n] is the answer.
    // TC: O(n) time (single loop), SC: O(n) for dp array.
    // -------------------------------------------------------------------------
    int countFriendsPairingsTabulation(int n) {
        if (n <= 1) return 1;

        vector<long long> dp(n + 1, 0); // long long to delay overflow
        dp[0] = 1; // base: 0 people -> 1 way (empty arrangement)
        dp[1] = 1; // base: 1 person -> 1 way (stay single)

        for (int i = 2; i <= n; i++) {
            long long staySingle = dp[i - 1];                 // Case 1: ith person alone
            long long pairUp = (long long)(i - 1) * dp[i - 2]; // Case 2: pair with any of (i-1)
            dp[i] = staySingle + pairUp;
            // NOTE: On GFG this problem often asks answer % (1e9+7).
            // In that case write: dp[i] = (staySingle + pairUp) % 1000000007;
        }
        return (int)dp[n];
    }

    // -------------------------------------------------------------------------
    // 3. SPACE OPTIMIZATION
    // -------------------------------------------------------------------------
    // OBSERVATION: To compute dp[i] we need ONLY dp[i-1] and dp[i-2].
    // We do NOT need the whole dp[0..n] array. So keep just 2 variables:
    //   prev2 = f(i-2), prev1 = f(i-1)
    //   curr  = prev1 + (i-1) * prev2
    // Then slide forward: prev2 = prev1, prev1 = curr.
    // TC: O(n) time, SC: O(1) extra space.
    // -------------------------------------------------------------------------
    int countFriendsPairingsSpaceOpt(int n) {
        if (n <= 1) return 1;

        long long prev2 = 1; // f(0)
        long long prev1 = 1; // f(1)

        for (int i = 2; i <= n; i++) {
            long long curr = prev1 + (long long)(i - 1) * prev2;
            // With modulo (if required): curr = (prev1 + (i-1)*prev2) % MOD;

            // move window forward for next i+1
            prev2 = prev1;
            prev1 = curr;
        }
        return (int)prev1; // after loop, prev1 = f(n)
    }
};



int main(){
    Solution s;
    int n = 4;
    cout << "Memoization: " << s.countFriendsPairings(n) << endl;
    cout << "Tabulation: " << s.countFriendsPairingsTabulation(n) << endl;
    cout << "Space Opt: " << s.countFriendsPairingsSpaceOpt(n) << endl;
    // Expected: n=0->1, 1->1, 2->2, 3->4, 4->10
    return 0;
}
