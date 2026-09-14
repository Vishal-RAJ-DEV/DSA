/*
================================================================================
PROBLEM: Median of Uniqueness Array
================================================================================

Given an array `nums`, consider ALL possible subarrays. For each subarray,
count the number of DISTINCT (unique) elements in it. This gives us an array
of distinct-counts called the "uniqueness array". Return the MEDIAN of this
uniqueness array.

Example: nums = [1, 2, 3]
  Subarrays and their distinct counts:
    [1] -> 1, [2] -> 1, [3] -> 1
    [1,2] -> 2, [2,3] -> 2
    [1,2,3] -> 3
  Uniqueness array = [1, 1, 1, 2, 2, 3]
  Median (middle element) = 2

================================================================================
APPROACH: Binary Search on Answer + Sliding Window
================================================================================

KEY INSIGHT:
  - There are n*(n+1)/2 total subarrays, so the uniqueness array has that many
    elements.
  - The median is the element at position ceil(total/2) when sorted.
  - Instead of building the entire uniqueness array (too expensive), we ask:
    "How many subarrays have AT MOST k distinct elements?"
  - If we know this count for any k, we can binary search for the smallest k
    where the count >= target (the median position). That k IS the median.

WHY THIS WORKS:
  - Let f(k) = number of subarrays with at most k distinct elements.
  - f(k) is non-decreasing: more k means more subarrays qualify.
  - We want the smallest k such that f(k) >= target.
  - This is a classic "binary search on answer" pattern.

================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    --------------------------------------------------------------------------------
    countAtMost(nums, k): Count subarrays with at most k distinct elements
    --------------------------------------------------------------------------------

    SLIDING WINDOW TECHNIQUE:
      - Maintain a window [left, right] that always has <= k distinct elements.
      - Expand right, track distinct count using frequency array.
      - When distinct > k, shrink from left until valid again.
      - For each valid right, all subarrays ending at right starting from
        left to right are valid. That's (right - left + 1) subarrays.

    WHY (right - left + 1)?
      - If window [left, right] is valid (<= k distinct), then every subarray
        ending at right: [left..right], [left+1..right], ..., [right..right]
        is also valid (they are subsets, so distinct count only decreases).
      - There are exactly (right - left + 1) such subarrays.

    TIME: O(n) - each element is added and removed at most once.
    --------------------------------------------------------------------------------
    */
    long long countAtMost(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> freq(100001, 0);  // frequency of each value (values <= 100000)

        int left = 0;       // left boundary of sliding window
        int distinct = 0;   // current number of distinct elements in window
        long long count = 0; // total count of valid subarrays found

        for (int right = 0; right < n; right++) {
            // Expand window: add nums[right]
            if (freq[nums[right]] == 0)
                distinct++;  // new distinct element encountered
            freq[nums[right]]++;

            // Shrink window from left until distinct <= k
            while (distinct > k) {
                freq[nums[left]]--;
                if (freq[nums[left]] == 0)
                    distinct--;  // element fully removed, distinct drops
                left++;
            }

            // All subarrays ending at 'right' starting from 'left' to 'right'
            // have at most k distinct elements. Count them.
            count += right - left + 1;
        }

        return count;
    }

    /*
    --------------------------------------------------------------------------------
    medianOfUniquenessArray(nums): Find the median of the uniqueness array
    --------------------------------------------------------------------------------

    BINARY SEARCH ON ANSWER:
      - The median value can range from 1 (minimum distinct count possible)
        to n (maximum, all elements distinct).
      - We binary search on this value.
      - For each candidate 'mid', check if countAtMost(nums, mid) >= target.
      - If yes, the median is <= mid, so search lower (high = mid).
      - If no, the median is > mid, so search higher (low = mid + 1).

    TARGET CALCULATION:
      - total = n*(n+1)/2 = number of subarrays = size of uniqueness array.
      - target = (total + 1) / 2 = position of median (1-indexed, upper middle).
      - We need the smallest k where at least 'target' subarrays have <= k distinct.

    INVARIANT:
      - When low == high, that value is the answer because:
        - countAtMost(low) >= target (so median <= low)
        - countAtMost(low-1) < target (so median > low-1)
        - Therefore median == low.

    TIME: O(n * log n) - binary search does O(log n) iterations, each calling
          countAtMost which is O(n).
    --------------------------------------------------------------------------------
    */
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();

        // Total number of subarrays (size of uniqueness array)
        long long total = 1LL * n * (n + 1) / 2;

        // Median position (1-indexed, upper middle for even-length arrays)
        long long target = (total + 1) / 2;

        // Binary search on the answer: distinct count from 1 to n
        int low = 1;
        int high = n;

        while (low < high) {
            int mid = low + (high - low) / 2;

            // How many subarrays have at most 'mid' distinct elements?
            if (countAtMost(nums, mid) >= target)
                // Enough subarrays have <= mid distinct, so median <= mid
                high = mid;
            else
                // Not enough, median must be larger
                low = mid + 1;
        }

        // low == high == median of uniqueness array
        return low;
    }
};


int main(){
    return 0;
}