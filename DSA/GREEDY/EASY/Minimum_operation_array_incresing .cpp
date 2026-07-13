#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// PROBLEM (LeetCode 1827 - Minimum Operations to Make Array Increasing):
// Given an array of integers, in one operation you can increment any element by 1.
// Find the minimum number of operations to make the array strictly increasing
// (i.e. nums[i] < nums[i+1] for every i).

// WHY GREEDY WORKS:
// To make the array strictly increasing with minimum operations, we process left to right.
// At each step i, we only care about nums[i-1] and nums[i]. If nums[i-1] >= nums[i],
// we MUST increase nums[i] to nums[i-1] + 1 (the smallest valid value). Making it any
// larger would waste operations, and making it smaller would still violate the condition.
// This locally optimal choice (minimal increment at each step) leads to the globally
// optimal result because future elements only depend on the current value of nums[i].

// ============================================================
// APPROACH 1 (CURRENT) - Greedy In-Place Modification
// Time  : O(n)
// Space : O(1)
// Modifies the original array.
// ============================================================
//   int minOperations(vector<int>& nums) {
//       int n = nums.size();
//       if (n <= 1) return 0;
//       int ans = 0;
//       for (int i = 1; i < n; i++) {
//           if (nums[i-1] >= nums[i]) {
//               int needed = nums[i-1] - nums[i] + 1;
//               nums[i] += needed;
//               ans += needed;
//           }
//       }
//       return ans;
//   }

// ============================================================
// APPROACH 2 - Greedy Without Modifying Original (Using prev tracker)
// Time  : O(n)
// Space : O(1)
// Does NOT modify the original array. Tracks the "previous expected value".
// ============================================================
//   int minOperations(vector<int>& nums) {
//       int ans = 0;
//       int prev = nums[0];
//       for (int i = 1; i < nums.size(); i++) {
//           if (prev >= nums[i]) {
//               int needed = prev - nums[i] + 1;
//               ans += needed;
//               prev = nums[i] + needed;  // = prev + 1
//           } else {
//               prev = nums[i];
//           }
//       }
//       return ans;
//   }

// ============================================================
// APPROACH 3 - Using max() / Mathematical Formula
// Time  : O(n)
// Space : O(1)
// Directly computes the target value for each position using max().
// The minimum valid value at index i is max(nums[i], prev_target + 1).
// ============================================================
//   int minOperations(vector<int>& nums) {
//       int ans = 0;
//       int prev_target = nums[0];
//       for (int i = 1; i < nums.size(); i++) {
//           int target = max(nums[i], prev_target + 1);
//           ans += target - nums[i];
//           prev_target = target;
//       }
//       return ans;
//   }

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        int ans = 0;

        for (int i = 1; i < n; i++) {
            if (nums[i-1] >= nums[i]) {
                int oper = nums[i-1] - nums[i] + 1;
                nums[i] += oper;
                ans += oper;
            }
        }
        return ans;
    }
};



int main() {
    Solution sol;
    
    // Test 1: [1,1,1] -> [1,2,3] needs 1+2 = 3 ops
    vector<int> nums1 = {1, 1, 1};
    cout << sol.minOperations(nums1) << endl; // 3

    // Test 2: [1,5,2,4,1] -> needs 14 ops
    vector<int> nums2 = {1, 5, 2, 4, 1};
    cout << sol.minOperations(nums2) << endl; // 14

    // Test 3: [8] -> already increasing (single element)
    vector<int> nums3 = {8};
    cout << sol.minOperations(nums3) << endl; // 0

    return 0;
}
