/*
================================================================================
PROBLEM: Minimize Max Difference Between Pairs
================================================================================

Given an array `nums` and integer `p`, select exactly `p` pairs (each element
can be used in at most one pair). Among all chosen pairs, consider the
DIFFERENCE (absolute) of each pair. We want to MINIMIZE the MAXIMUM difference
among all p pairs. Return that minimized maximum difference.

Example: nums = [10, 1, 2, 7, 1, 3], p = 2
  Sorted: [1, 1, 2, 3, 7, 10]
  Best pairs: (1,1) diff=0, (2,3) diff=1 → max diff = 1
  Answer: 1

================================================================================
APPROACH: Binary Search on Answer + Greedy Validation
================================================================================

KEY INSIGHT:
  - The answer (minimized max difference) is some value between 0 and max-min.
  - For any candidate value 'd', we can CHECK: "Can we form p pairs where
    every pair has difference <= d?"
  - If yes → the answer is ≤ d (try smaller).
  - If no  → the answer is > d (try larger).
  - This is binary search on the answer.

WHY SORT FIRST?
  - After sorting, the optimal pairs are always ADJACENT elements.
  - Why? If you have sorted a ≤ b ≤ c, pairing (a,c) is always worse than
    either (a,b) or (b,c) because c-a ≥ b-a and c-a ≥ c-b.
  - So we only need to check adjacent pairs after sorting.

WHY GREEDY WORKS (canMake):
  - Scan left to right. If nums[i+1] - nums[i] <= maxDiff, pair them and
    skip both (i += 2). Otherwise move forward (i++).
  - Greedy is optimal because: pairing earlier (smaller indices) never hurts
    future pairs. By taking the first valid pair we find, we leave more room
    for later pairs. Any other pairing strategy cannot form MORE pairs.

TIME: O(n log n) for sort + O(n log n) for binary search × O(n) check = O(n log n + n log max)
================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    --------------------------------------------------------------------------------
    canMake(nums, p, maxDiff): Can we form p pairs with all diffs <= maxDiff?
    --------------------------------------------------------------------------------

    GREEDY STRATEGY:
      - Scan left to right through the sorted array.
      - If adjacent elements nums[i] and nums[i+1] differ by <= maxDiff,
        pair them up and skip both (i += 2).
      - Otherwise, this element can't pair well, move forward (i++).
      - Count pairs as we go. If we reach p pairs, return true.

    WHY i += 2 after pairing?
      - Each element can be used in at most ONE pair. Once paired, skip it.

    WHY this greedy is correct:
      - In a sorted array, if nums[i+1] - nums[i] <= maxDiff, pairing them
        is always safe. Not pairing them would mean trying to pair nums[i]
        with some nums[j] where j > i+1, which has a LARGER difference.
        So taking the earliest valid pair is always optimal.
    --------------------------------------------------------------------------------
    */
    bool canMake(vector<int>& nums, int p, int maxDiff) {
        int pairs = 0;

        for (int i = 0; i < nums.size() - 1; ) {
            // Check if current and next element can form a valid pair
            if (nums[i + 1] - nums[i] <= maxDiff) {
                pairs++;  // formed a valid pair
                i += 2;   // skip both elements (each used once)
            } else {
                i++;      // can't pair nums[i] with nums[i+1], try next
            }

            // Early exit: we have enough pairs
            if (pairs >= p)
                return true;
        }

        return false;  // couldn't form p pairs
    }

    /*
    --------------------------------------------------------------------------------
    minimizeMax(nums, p): Find the minimized maximum difference
    --------------------------------------------------------------------------------

    BINARY SEARCH ON ANSWER:
      - low  = 0 (best case: all pairs have diff 0).
      - high = max - min (worst case: only one possible pair spans full range).
      - For each mid, check if we can form p pairs with all diffs <= mid.
      - If yes → high = mid (answer is <= mid, try smaller).
      - If no  → low = mid + 1 (answer is > mid, need larger threshold).

    When low == high, that's the minimum possible max difference.
    --------------------------------------------------------------------------------
    */
    int minimizeMax(vector<int>& nums, int p) {
        // Sort so optimal pairs are always adjacent
        sort(nums.begin(), nums.end());

        int low = 0;
        int high = nums.back() - nums.front(); // max possible difference

        // Binary search on the answer
        while (low < high) {
            int mid = low + (high - low) / 2;

            if (canMake(nums, p, mid))
                high = mid;    // possible with maxDiff=mid, try smaller
            else
                low = mid + 1; // not possible, need larger threshold
        }

        return low; // minimum achievable max difference
    }
};



int main(){
    return 0;
}