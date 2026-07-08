#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
 * PROBLEM: LeetCode 1512 - Number of Good Pairs
 *
 * DEFINITION:
 * A good pair (i, j) satisfies:
 *   - i < j
 *   - nums[i] == nums[j]
 * 
 * Count ALL such pairs in the array.
 *
 * ============================================================
 *            WORKING EXPLANATION
 * ============================================================
 * 
 * APPROACH: Single-pass using frequency map
 * 
 * - We traverse the array left to right once.
 * - unordered_map<int, int> pairs keeps track of how many times
 *   each number has been SEEN SO FAR (before the current index).
 * 
 * KEY INSIGHT:
 *   When we encounter a number at index i, ALL previous occurrences
 *   of the same number form valid good pairs with this one.
 *   Because: previous index < current index, AND values are equal.
 * 
 * HOW THE MAP IS USED:
 * - pairs[num] = frequency of 'num' among elements already processed
 *   (i.e., elements at indices 0 to i-1).
 * - At each step:
 *     1) Check if nums[i] already exists in the map.
 *        - If YES → pairs[nums[i]] previous occurrences exist.
 *          Each forms a good pair with the current element.
 *          So add pairs[nums[i]] to count.
 *     2) Increment pairs[nums[i]] by 1 to include the current
 *        occurrence for future matches.
 * 
 * WHY THIS WORKS (Mathematical):
 *   For a number that appears 'freq' times total:
 *   Number of good pairs = sum_{occurrence=1}^{freq} (occurrence - 1)
 *                        = 0 + 1 + 2 + ... + (freq-1)
 *                        = freq * (freq - 1) / 2
 * 
 *   The loop computes this same sum incrementally:
 *   - 1st occurrence: count += 0  (no previous)  → after: freq = 1
 *   - 2nd occurrence: count += 1  → after: freq = 2
 *   - 3rd occurrence: count += 2  → after: freq = 3
 *   - 4th occurrence: count += 3  → after: freq = 4
 *   Total = 0 + 1 + 2 + 3 = 6 = 4*3/2 ✅
 * 
 * ============================================================
 *               DETAILED DRY RUN
 * ============================================================
 * Input: nums = {1, 2, 3, 1, 1, 3}
 * 
 * Initial: pairs = {}, count = 0
 * 
 * i=0, nums[0] = 1
 *   pairs.find(1) → NOT found (1 seen 0 times before)
 *   count += 0  → count = 0
 *   pairs[1] = 0 + 1 = 1   → pairs = {1:1}
 *   📝 No good pair formed (no previous 1)
 * 
 * i=1, nums[1] = 2
 *   pairs.find(2) → NOT found
 *   count += 0  → count = 0
 *   pairs[2] = 0 + 1 = 1   → pairs = {1:1, 2:1}
 * 
 * i=2, nums[2] = 3
 *   pairs.find(3) → NOT found
 *   count += 0  → count = 0
 *   pairs[3] = 0 + 1 = 1   → pairs = {1:1, 2:1, 3:1}
 * 
 * i=3, nums[3] = 1
 *   pairs.find(1) → FOUND! pairs[1] = 1 (1 seen once before at i=0)
 *   count += 1  → count = 1   ✅ Good pair: (0,3)
 *   pairs[1] = 1 + 1 = 2     → pairs = {1:2, 2:1, 3:1}
 * 
 * i=4, nums[4] = 1
 *   pairs.find(1) → FOUND! pairs[1] = 2 (1 seen twice before at i=0,3)
 *   count += 2  → count = 3   ✅ Good pairs: (0,4), (3,4)
 *   pairs[1] = 2 + 1 = 3     → pairs = {1:3, 2:1, 3:1}
 * 
 * i=5, nums[5] = 3
 *   pairs.find(3) → FOUND! pairs[3] = 1 (3 seen once before at i=2)
 *   count += 1  → count = 4   ✅ Good pair: (2,5)
 *   pairs[3] = 1 + 1 = 2     → pairs = {1:3, 2:1, 3:2}
 * 
 * Final count = 4 ✅
 * Good pairs: (0,3), (0,4), (3,4), (2,5)
 * All satisfy i < j and nums[i] == nums[j].
 * 
 * ============================================================
 * TIME COMPLEXITY:  O(n)  — single pass
 * SPACE COMPLEXITY: O(n)  — map stores up to n unique values
 * ============================================================
 */

class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        // pairs[num] = frequency of num seen so far (before current index)
        unordered_map<int, int> pairs;
        int count = 0;  // total good pair count

        for (int i = 0; i < nums.size(); i++) {

            // If nums[i] was seen before, each previous occurrence
            // forms a good pair with nums[i] at current index.
            if (pairs.find(nums[i]) != pairs.end()) {
                // Add the number of previous occurrences to count
                // because each pairs with current nums[i].
                count += pairs[nums[i]];
            }

            // Increment frequency for current element
            // (it becomes a "previous occurrence" for future indices)
            pairs[nums[i]] = pairs[nums[i]] + 1;
        }

        return count;
    }
};


int main(){
    Solution sol;
    vector<int> nums = {1, 2, 3, 1, 1, 3};
    int goodPairs = sol.numIdenticalPairs(nums);
    cout << "Number of good pairs: " << goodPairs << endl;  // Expected: 4

    // Additional test
    vector<int> nums2 = {1, 1, 1, 1};
    cout << "nums = {1,1,1,1} → " << sol.numIdenticalPairs(nums2) << " (expected: 6)\n";
    // 4*3/2 = 6 pairs: (0,1)(0,2)(0,3)(1,2)(1,3)(2,3)

    return 0;
}
