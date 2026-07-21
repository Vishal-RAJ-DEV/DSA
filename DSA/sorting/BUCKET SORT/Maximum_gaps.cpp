#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  PROBLEM: Maximum Gap (LeetCode 164)
 * ================================================================
 *  Given an unsorted array, find the maximum difference between
 *  successive elements in its SORTED form.
 *
 *  Example:
 *    Input:  [3, 6, 9, 1]
 *    Sorted: [1, 3, 6, 9]
 *    Gaps:    2  3  3
 *    Max gap = 3
 *
 *  Constraint: Must be O(n) time and space.
 * ================================================================
 */

// ================================================================
// APPROACH 1: SORTING (O(n log n))
// ================================================================
// Intuition: After sorting the array, the maximum gap is simply
// the maximum difference between adjacent elements.
//
// Algorithm:
//   1. Sort the array.
//   2. Iterate i from 0 to n-2, computing nums[i+1] - nums[i].
//   3. Track and return the maximum difference.
//
// Time:  O(n log n)  — dominated by sorting
// Space: O(1)        — sorting may take O(n) extra space depending on impl
//
// Note: This does NOT meet the O(n) constraint, but is the simplest
//       baseline solution.
// ================================================================

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.size() < 2)
            return 0;

        int maxGap = 0;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 1; i++) {
            int newDiff = nums[i + 1] - nums[i];
            if (newDiff > maxGap)
                maxGap = newDiff;
        }

        return maxGap;
    }
};

/*
 * ================================================================
 *  DRY RUN — Sorting Approach
 * ================================================================
 *  nums = [3, 6, 9, 1]
 *
 *  After sort: [1, 3, 6, 9]
 *
 *  i=0:  3-1 = 2   maxGap = 2
 *  i=1:  6-3 = 3   maxGap = 3
 *  i=2:  9-6 = 3   maxGap = 3
 *
 *  Result: 3
 * ================================================================
 */

// ================================================================
// APPROACH 2: BUCKET SORT / PIGEONHOLE PRINCIPLE (O(n))
// ================================================================
// KEY INSIGHT (Pigeonhole Principle):
//   If we have n numbers in range [mn, mx], there are n-1 gaps.
//   The average gap = (mx - mn) / (n - 1).
//
//   The MAXIMUM gap can NEVER be smaller than this average.
//   So the max gap ≥ ceil((mx - mn) / (n - 1)).
//
//   We set bucketSize = ceil((mx - mn) / (n - 1)).
//   Then any two numbers that fall in the SAME bucket differ by
//   LESS than bucketSize → they can NEVER be the maximum gap.
//
//   Therefore, the maximum gap can ONLY occur between the max of
//   one bucket and the min of the NEXT non-empty bucket.
//
// ALGORITHM:
//   1. Find min (mn) and max (mx) of the array.
//   2. If mn == mx → all equal → gap = 0.
//   3. bucketSize = max(1, (mx - mn) / (n - 1))
//      (max with 1 to avoid division by zero when all elements identical)
//   4. numBuckets = (mx - mn) / bucketSize + 1
//   5. Create bucketMin[], bucketMax[], used[] for each bucket.
//   6. For each element, place it into bucket: idx = (x - mn) / bucketSize
//      Update bucketMin[idx], bucketMax[idx], used[idx].
//   7. Iterate buckets left to right:
//      - Skip empty buckets.
//      - ans = max(ans, bucketMin[current] - prev)
//      - prev = bucketMax[current]
//      (prev starts as mn — the last "max" before the first bucket)
//   8. Return ans.
//
// PROOF OF CORRECTNESS:
//   Since max gap ≥ average gap = bucketSize, and within-bucket
//   differences are < bucketSize, the max gap MUST cross buckets.
//   Comparing bucketMin[i] - bucketMax[prev_nonempty] suffices.
//
// TIME:  O(n)  — single pass to place + single pass to scan buckets
// SPACE: O(n)  — bucket arrays of size ~n
// ================================================================

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();

        if (n < 2)
            return 0;

        // --- Step 1: Find range ---
        int mn = *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());

        if (mn == mx)
            return 0;  // all elements equal

        // --- Step 2: Determine bucket size and count ---
        /*
         * Average gap = (mx - mn) / (n - 1)
         * This is the theoretical minimum possible max gap.
         * We use this as the bucket size so that two elements in
         * the same bucket can NEVER produce the maximum gap.
         *
         * Example: nums = [1, 3, 6, 9], n=4
         *   avg gap = (9-1)/3 = 8/3 ≈ 2.67
         *   bucketSize = ceil(8/3) = 3
         *
         *   Buckets: [1, 3) [3, 6) [6, 9) [9, 12)
         *   (each of size 3)
         */

        int bucketSize = max(1, (mx - mn) / (n - 1));
        int bucketCount = (mx - mn) / bucketSize + 1;

        // --- Step 3: Initialize buckets ---
        vector<int> bucketMin(bucketCount, INT_MAX);
        vector<int> bucketMax(bucketCount, INT_MIN);
        vector<bool> used(bucketCount, false);

        // --- Step 4: Place each number into its bucket ---
        for (int x : nums) {
            int idx = (x - mn) / bucketSize;

            bucketMin[idx] = min(bucketMin[idx], x);
            bucketMax[idx] = max(bucketMax[idx], x);
            used[idx] = true;
        }

        // --- Step 5: Scan buckets to find max gap ---
        /*
         * For each non-empty bucket:
         *   ans = max(ans, bucketMin[i] - prevMax)
         *   prevMax = bucketMax[i]
         *
         * prev starts as mn (the minimum element).
         * mn is conceptually the "max" of the imaginary bucket before
         * the first real bucket.
         */

        int ans = 0;
        int prev = mn;  // last seen maximum value

        for (int i = 0; i < bucketCount; i++) {
            if (!used[i])
                continue;

            ans = max(ans, bucketMin[i] - prev);
            prev = bucketMax[i];
        }

        return ans;
    }
};

/*
 * ================================================================
 *  DRY RUN — Bucket Approach
 * ================================================================
 *  nums = [3, 6, 9, 1],  n = 4
 *
 *  mn = 1, mx = 9
 *
 *  bucketSize = max(1, (9-1)/(4-1)) = max(1, 8/3) = max(1, 2) = 2
 *  bucketCount = (9-1)/2 + 1 = 4 + 1 = 5
 *
 *  Buckets (size 2 each):
 *    idx 0: [1, 3)
 *    idx 1: [3, 5)
 *    idx 2: [5, 7)
 *    idx 3: [7, 9)
 *    idx 4: [9, 11)
 *
 *  Placing elements:
 *    3: idx = (3-1)/2 = 1  → bucketMin[1]=3, bucketMax[1]=3
 *    6: idx = (6-1)/2 = 2  → bucketMin[2]=6, bucketMax[2]=6
 *    9: idx = (9-1)/2 = 4  → bucketMin[4]=9, bucketMax[4]=9
 *    1: idx = (1-1)/2 = 0  → bucketMin[0]=1, bucketMax[0]=1
 *
 *  Buckets:
 *    idx | used | min  | max
 *    -----+------+------+-----
 *    0   |  ✓   |  1   |  1
 *    1   |  ✓   |  3   |  3
 *    2   |  ✓   |  6   |  6
 *    3   |  ✗   |  —   |  —
 *    4   |  ✓   |  9   |  9
 *
 *  Scanning (prev starts at mn = 1):
 *    i=0 (used): ans = max(0, 1-1) = 0,  prev = 1
 *    i=1 (used): ans = max(0, 3-1) = 2,  prev = 3
 *    i=2 (used): ans = max(2, 6-3) = 3,  prev = 6
 *    i=3 (empty): skip
 *    i=4 (used): ans = max(3, 9-6) = 3,  prev = 9
 *
 *  Result: 3  ✓
 *
 *  Notice: bucket 3 was empty! The gap 9-6=3 crosses from bucket 2
 *  to bucket 4, skipping the empty bucket 3. This is exactly why
 *  the max gap is always between buckets, not within them.
 * ================================================================
 */

int main() {
    return 0;
}
