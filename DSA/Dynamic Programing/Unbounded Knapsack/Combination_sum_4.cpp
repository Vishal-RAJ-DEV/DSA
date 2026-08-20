#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Combination Sum IV
    Given an array of distinct integers nums and a target integer target,
    return the number of combinations that add up to target.

    Why Order Matters:
    -----------------
    In this problem, (1,2) and (2,1) are considered DIFFERENT combinations.
    Example: nums = [1,2,3], target = 4
    Valid sequences: (1,1,1,1), (1,1,2), (1,2,1), (2,1,1), (2,2), (1,3), (3,1)
    Total = 7 combinations

    Since order matters, we are counting PERMUTATIONS, not just combinations.
    We try all possibilities at each step because any number can be placed
    at any position in the sequence.
*/

// ==========================================
// Approach 1: Pure Recursion (Brute Force)
// Time Complexity: O(n^target) - exponential
// Space Complexity: O(target) - recursion stack depth
// ==========================================
class Recursion {
public:
    int solve(int target, vector<int>& nums) {
        // Base case: target 0 means we found a valid combination
        if (target == 0)
            return 1;

        int ans = 0;

        // Try every number at current position (order matters)
        for (int num : nums) {
            if (num <= target) {
                // Recurse with reduced target
                // Each recursive call represents placing 'num' at current position
                ans += solve(target - num, nums);
            }
        }

        return ans;
    }

    int combinationSum4(vector<int>& nums, int target) {
        return solve(target, nums);
    }
};

// ==========================================
// Approach 2: Memoization (Top-Down DP)
// Time Complexity: O(target * n)
// Space Complexity: O(target) for dp array + O(target) for recursion stack
// ==========================================
class Memoization {
public:
    int solve(int target, vector<int>& nums, vector<int>& dp) {
        // Base case: target 0 means we found a valid combination
        if (target == 0)
            return 1;

        // If already computed, return cached result
        if (dp[target] != -1)
            return dp[target];

        int ans = 0;

        // Try every number at current position (order matters)
        for (int num : nums) {
            if (num <= target) {
                // Recurse with reduced target and memoize
                ans += solve(target - num, nums, dp);
            }
        }

        // Cache the result before returning
        return dp[target] = ans;
    }

    int combinationSum4(vector<int>& nums, int target) {
        // Initialize dp array with -1 (uncomputed state)
        vector<int> dp(target + 1, -1);
        return solve(target, nums, dp);
    }
};

// ==========================================
// Approach 3: Tabulation (Bottom-Up DP)
// Time Complexity: O(target * n)
// Space Complexity: O(target)
// ==========================================
class Tabulation {
public:
    int combinationSum4(vector<int>& nums, int target) {
        // dp[t] = number of combinations that sum to target t
        vector<int> dp(target + 1, 0);

        // Base case: 1 way to make sum 0 (use no elements)
        dp[0] = 1;

        // Build solution for each target from 1 to target
        for (int t = 1; t <= target; t++) {
            // Try every number as the last element in the combination
            for (int num : nums) {
                if (num <= t) {
                    // If we place 'num' at the end, add ways to make (t - num)
                    dp[t] += dp[t - num];
                }
            }
        }

        return dp[target];
    }
};

/*
    Summary of Approaches:
    ----------------------
    1. Recursion:     Try all possibilities, but redundant calculations make it slow.
    2. Memoization:   Cache results to avoid recomputation, same logic as recursion.
    3. Tabulation:    Build solution iteratively from smaller subproblems.

    Key Insight:
    - Since order matters, we iterate target as outer loop and nums as inner loop.
    - This ensures all permutations are counted (e.g., [1,2] and [2,1] both counted).
    - If order didn't matter, we would swap the loops (nums as outer, target as inner).
*/

int main(){
    return 0;
}
