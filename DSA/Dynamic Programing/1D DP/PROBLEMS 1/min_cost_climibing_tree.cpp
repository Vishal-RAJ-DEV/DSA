// ============================================================================
// QUESTION: Min Cost Climbing Stairs (LeetCode 746)
// ----------------------------------------------------------------------------
// You are given an integer array `cost` where cost[i] is the cost of the i-th
// step on a staircase. Once you pay the cost, you can either climb ONE or TWO
// steps.
//
// Rules:
//  1. You can start from step 0 OR step 1 (starting is free, you only pay
//     when you LAND on / LEAVE a step).
//  2. You need to reach the TOP, which is just BEYOND the last index
//     (i.e. position n, where n = cost.size()). Reaching top costs 0.
//  3. Goal: find the MINIMUM total cost to reach the top.
//
// Example 1:
//   cost = [10, 15, 20]
//   -> Start at index 1 (pay 15), jump 2 steps to top. Total = 15. Answer = 15.
//
// Example 2:
//   cost = [1,100,1,1,1,100,1,1,100,1]
//   -> Optimal path 0->2->4->5? Actually 0->2->4->6->7->9->top = 6. Answer = 6.
//
// Why DP?
//  At every step i, the cheapest way to stand on i is:
//     minCost(i) = cost[i] + min(minCost(i-1), minCost(i-2))
//  because you could only have come from i-1 (1-step) or i-2 (2-steps).
//  Final answer = min(minCost(n-1), minCost(n-2)) because top can be reached
//  from last OR second-last step with a 1 or 2 jump (no extra cost for top).
//
// This file shows 3 ways to solve the same recurrence:
//  1. Memoization (Top-Down Recursion + DP array)  -> O(n) time, O(n) space + stack
//  2. Tabulation (Bottom-Up Iterative DP)          -> O(n) time, O(n) space
//  3. Space Optimized (only 2 variables)           -> O(n) time, O(1) space
// ============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// APPROACH 1: MEMOIZATION (Top-Down DP)
// Idea: Start from the destination and recursively go backwards.
//   solve(i) = minimum cost to reach step i starting from 0/1.
// Recurrence: solve(i) = cost[i] + min(solve(i-1), solve(i-2))
// Base cases: i<0 -> 0 (went past ground, no cost), i==0/1 -> cost[i] (starting point)
// We store results in dp[] to avoid recomputing overlapping subproblems.
// ============================================================================
class Memoization  {
public:
    // Returns min cost to stand on step `i`.
    int solve( int i , vector<int>& cost , vector<int>&dp){
        if( i < 0 ) return 0;//at the top , cross the 0th index

        if( i==0 || i == 1 ) return cost[i];
        if( dp[i] != -1) return dp[i];

        return dp[i] = cost[i] + min(solve(i-1 , cost , dp) , solve( i -2 , cost,  dp));
    }
    // Wrapper: top (index n) can be jumped to from n-1 or n-2, so take min of both.
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n , -1);
        return  min(solve ( n - 1, cost , dp) , solve(n -2 ,cost , dp));
    }
};



// ============================================================================
// APPROACH 2: TABULATION (Bottom-Up DP)
// Idea: Build answer forward iteratively, no recursion.
//   dp[i] = min cost to reach step i (here dp is 1-indexed for convenience).
//   dp[0] = 0 (ground before stairs, free)
//   dp[1] = cost[0] (stand on step 0)
//   dp[2] = cost[1] (stand on step 1)
//   For i>=3: dp[i] = cost[i-1] + min(dp[i-1], dp[i-2])
//             (pay current step cost + cheaper of previous two ways)
// Final answer = min(dp[n], dp[n-1]) because top can come from last 2 steps.
// Time: O(n), Space: O(n)
// ============================================================================
class Tabulation {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int>dp(n + 1);
        dp[0] = 0;
        dp[1] = cost[0];
        dp[2] = cost[1];

        for( int i = 3 ; i < n + 1 ;  i++){

            int cost1 = cost[i-1];
            int cost2 = min( dp[i-1] , dp[i-2]);

            dp[i] = cost1 + cost2;
        }

        return min( dp[n] , dp[n-1]);
    }
};

// ============================================================================
// APPROACH 3: SPACE OPTIMIZED (Best for interviews)
// Observation: To compute cost for step i, we only need previous TWO values,
// not the whole dp[] array. So keep just `prev` and `sec`.
//   prev = min cost to reach i-2, sec = min cost to reach i-1
//   curr = cost[i] + min(prev, sec)  -> min cost to reach i
//   Then slide window: prev = sec, sec = curr
// Final answer = min(prev, sec) = min of last two steps (jump to top free).
// Time: O(n), Space: O(1)
// Edge case: if n<=2, just start at cheaper of step 0/1 and jump to top.
// Example trace for [10,15,20]:
//   prev=10, sec=15 -> i=2: curr=20+min(10,15)=30 -> prev=15, sec=30
//   answer = min(15,30)=15
// ============================================================================
class SpaceOptimized {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int prev = cost[0] ;
        int sec = cost[1];

        if( n <= 2) return min(prev , sec);
        for( int i = 2 ; i < n ;  i++){

            int curr = cost[i] + min( prev , sec);

            prev = sec;
            sec = curr;
        }

        return min( prev , sec);
    }
};

// Driver to test: cost = [10,15,20] -> expected output 15
// (start at 15 at index 1, then jump 2 steps to top, pay only 15)
int main(){
    SpaceOptimized obj;
     vector<int> cost{10, 15, 20};
        cout << obj.minCostClimbingStairs(cost) << endl;
        
    return 0;
}
