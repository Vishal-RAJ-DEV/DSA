#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// PROBLEM: LeetCode 2366 — Minimum Replacements to Sort the Array
//
// What the problem asks:
//   You are given a 0-indexed integer array nums. In one operation,
//   you can replace any element nums[i] with two positive integers
//   x and y such that nums[i] = x + y. This counts as ONE operation.
//   You can repeat this on any resulting numbers.
//
//   Goal: Make the array non-decreasing (sorted in ascending order)
//         using the MINIMUM number of replacement operations.
//
// Example:
//   nums = [16, 5]
//   Output: 3
//   Explanation:
//     16 → 8+8   (op 1)
//     8  → 4+4   (op 2)
//     8  → 4+4   (op 3)
//     Result: [4,4,4,4,5] (non-decreasing)
//
// Key Insight:
//   Most people try left-to-right — that fails because future splits
//   depend on past decisions. Instead, process RIGHT-TO-LEFT so we
//   always know the maximum allowed value for the current element.
// ============================================================

class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {

        long long ans = 0;                    // Total operations counter

        int limit = nums.back();              // Last element is fixed (nothing after it to compare)
                                              // 'limit' = the maximum value the current element can
                                              //           have after splitting, to keep the array sorted

        // Process from SECOND-LAST element to the FIRST (right to left)
        for(int i = nums.size()-2; i>=0; i--) {

            // CASE 1: Current element is already ≤ limit
            //         → No splitting needed, just update limit to current value
            if(nums[i] <= limit) {
                limit = nums[i];              // New limit = current value (smaller = more restrictive)
            }

            // CASE 2: Current element is too large (> limit)
            //         → Must split it so that every piece ≤ limit
            else {

                // ──── How many pieces do we need? ────
                // We need each piece ≤ limit, so:
                //   pieces = ceil(nums[i] / limit)
                //
                // Example: nums[i]=17, limit=5
                //   17/5 = 3.4 → need 4 pieces (5+5+5+2)
                //
                // Integer ceiling formula:
                //   ceil(a/b) = (a + b - 1) / b
                int pieces = (nums[i] + limit - 1) / limit;

                // ──── How many operations? ────
                // Splitting into 'pieces' from 1 number needs (pieces-1) operations:
                //   Example: 16 → 4 pieces needs 3 splits
                //     split 1: 16 → 8+8
                //     split 2: 8  → 4+4
                //     split 3: 8  → 4+4
                ans += pieces - 1;

                // ──── What should the new limit be? ────
                // After splitting, the leftmost piece determines the new limit
                // for the element to our left. We want the LARGEST possible
                // limit (least restrictive) while keeping the split valid.
                //
                // If we split unevenly (e.g. 17 → 5+5+5+2), the smallest piece
                // is 2, which makes the limit very tight for the next element.
                //
                // To keep the limit as LARGE as possible, we split as evenly
                // as we can: each piece = nums[i] / pieces (floor)
                //
                // Example: nums[i]=17, pieces=4
                //   17/4 = 4  →  split: 4+4+4+5
                //   smallest piece = 4
                //   So limit = 4 (not 2 from the uneven split)
                //
                // Why does this work? The smallest piece after an even split
                // is floor(nums[i]/pieces), so any element to the left just
                // needs to be ≤ that value.
                limit = nums[i] / pieces;     // Largest possible limit for the next left element
            }
        }

        return ans;                           // Total replacement operations
    }
};


int main(){
    return 0;
}
