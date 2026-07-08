#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // count stores the total number of valid (beautiful) subsets found so far
    int count;

    /**
     * RECURSIVE FUNCTION (Backtracking):
     * - Explores all subsets of nums[] using pick/not-pick pattern at each index.
     * - Uses an unordered_map (mpp) to track which numbers are already chosen
     *   in the current subset being built.
     * 
     * BEAUTIFUL SUBSET DEFINITION:
     * A subset is "beautiful" if for every pair (a, b) in the subset,
     * |a - b| != k. Equivalently, NO two numbers differ by exactly k.
     * 
     * WHY map with (nums[idx] - k) and (nums[idx] + k) matters:
     * - If we want to pick nums[idx], we must ensure it doesn't create
     *   a pair with difference = k with any already-picked element.
     * - An already-picked element could be either:
     *     1) Smaller by k:  picked = nums[idx] - k   →  diff = nums[idx] - (nums[idx] - k) = k
     *     2) Larger by k:   picked = nums[idx] + k   →  diff = (nums[idx] + k) - nums[idx] = k
     * - So we check: if mpp[nums[idx] - k] > 0 OR mpp[nums[idx] + k] > 0,
     *   then picking nums[idx] would violate the condition → skip the pick branch.
     * 
     * HOW map stores elements:
     * - mpp[num] = frequency of num in the current subset being built.
     * - We increment BEFORE recursing (pick) and decrement AFTER (backtrack).
     * - This way, as we explore different branches, the map always reflects
     *   only the elements chosen in the CURRENT path of recursion.
     * 
     * HOW count increases:
     * - Every time we reach idx >= nums.size(), we have explored one complete
     *   subset (a leaf of the recursion tree). We increment count for each leaf.
     * - This counts EVERY possible subset (including the empty set).
     * - The final answer subtracts 1 to exclude the empty subset.
     * 
     * ============================================================
     *               DETAILED DRY RUN
     * ============================================================
     * Input: nums = {2, 4, 6},  k = 2
     * 
     * We start with: idx=0, mpp = {}, count=0
     * 
     * Call Tree (indented = deeper recursion):
     * 
     * solve(idx=0, mpp={})
     * ├── PICK 2? Check mpp[0] && mpp[4] → both 0 → YES
     * │   mpp = {2:1}
     * │   └── solve(idx=1, mpp={2:1})
     * │       ├── PICK 4? Check mpp[2] && mpp[6]
     * │       │   → mpp[2] = 1 (2-4 = -2? No! Wait: nums[1]=4, so check mpp[4-2]=mpp[2] AND mpp[4+2]=mpp[6])
     * │       │   → mpp[2] = 1  ← 2 is ALREADY picked! (4 - 2 = 2 = k) → BLOCKED!
     * │       │   → CANNOT PICK 4
     * │       │   (skip pick branch)
     * │       └── NOT PICK 4 (mpp stays {2:1})
     * │           └── solve(idx=2, mpp={2:1})
     * │               ├── PICK 6? Check mpp[4] && mpp[8]
     * │               │   → both 0 → YES (6-2=4≠k, 6-6=0≠k)
     * │               │   mpp = {2:1, 6:1}
     * │               │   └── solve(idx=3, mpp={2:1, 6:1})
     * │               │       └── BASE: idx>=3 → count++ (count=1) ✅ Subset = {2,6}
     * │               │   (backtrack) mpp = {2:1}
     * │               └── NOT PICK 6 (mpp = {2:1})
     * │                   └── solve(idx=3, mpp={2:1})
     * │                       └── BASE: idx>=3 → count++ (count=2) ✅ Subset = {2}
     * │   (backtrack from idx=0 pick) mpp = {}
     * │
     * └── NOT PICK 2 (mpp = {})
     *     └── solve(idx=1, mpp={})
     *         ├── PICK 4? Check mpp[2] && mpp[6] → both 0 → YES
     *         │   mpp = {4:1}
     *         │   └── solve(idx=2, mpp={4:1})
     *         │       ├── PICK 6? Check mpp[4] && mpp[8]
     *         │       │   → mpp[4] = 1  ← 4 is ALREADY picked! (6-4=2=k) → BLOCKED!
     *         │       │   (skip pick branch)
     *         │       └── NOT PICK 6 (mpp = {4:1})
     *         │           └── solve(idx=3, mpp={4:1})
     *         │               └── BASE: idx>=3 → count++ (count=3) ✅ Subset = {4}
     *         │   (backtrack) mpp = {}
     *         │
     *         └── NOT PICK 4 (mpp = {})
     *             └── solve(idx=2, mpp={})
     *                 ├── PICK 6? Check mpp[4] && mpp[8] → both 0 → YES
     *                 │   mpp = {6:1}
     *                 │   └── solve(idx=3, mpp={6:1})
     *                 │       └── BASE: idx>=3 → count++ (count=4) ✅ Subset = {6}
     *                 │   (backtrack) mpp = {}
     *                 └── NOT PICK 6 (mpp = {})
     *                     └── solve(idx=3, mpp={})
     *                         └── BASE: idx>=3 → count++ (count=5) ✅ Subset = {} (EMPTY)
     * 
     * Final count = 5. Return count - 1 = 5 - 1 = 4. ✅
     * The 4 beautiful subsets: {2}, {4}, {6}, {2,6}
     * (Empty set excluded by the -1)
     * ============================================================
     */
    void solve(int idx, unordered_map<int, int>& mpp, vector<int>& nums, int k) {

        // BASE CASE: processed all elements → one complete subset found
        if (idx >= nums.size()) {
            count++;        // increment count for this subset
            return;
        }

        // --- PICK branch (include nums[idx] in the subset) ---
        // Condition: NEITHER (nums[idx] - k) NOR (nums[idx] + k) already exists in map.
        // If either exists, picking nums[idx] would create a pair with diff = k → invalid.
        // !mpp[x] means mpp[x] is 0 → safe (that number is NOT already picked).
        if (!mpp[nums[idx] - k] && !mpp[nums[idx] + k]) {

            // Mark nums[idx] as picked (increase its frequency in the map)
            mpp[nums[idx]]++;

            // Recurse to the next index with the map updated
            solve(idx + 1, mpp, nums, k);

            // BACKTRACK: remove nums[idx] from map before exploring the "not-pick" branch
            // This ensures the map is clean for sibling branches.
            mpp[nums[idx]]--;
        }

        // --- NOT-PICK branch (exclude nums[idx]) ---
        // Always try the "not take" path regardless of whether we took or not.
        // Map is unchanged (no modification was made in this branch).
        solve(idx + 1, mpp, nums, k);
    }

    /**
     * beautifulSubsets:
     * - Initializes map and count.
     * - Calls solve() which explores all 2^n subsets via recursion + backtracking.
     * - Returns count - 1 because the empty subset (where no element is picked)
     *   is counted during recursion but should NOT be part of the answer.
     * 
     * TIME COMPLEXITY: O(2^n) in worst case (each element has pick/not-pick choice).
     * SPACE COMPLEXITY: O(n) for recursion stack + O(n) for map.
     */
    int beautifulSubsets(vector<int>& nums, int k) {
        unordered_map<int, int> mpp;  // map to track picked elements in current subset
        count = 0;
        solve(0, mpp, nums, k);
        return count - 1;  // exclude the empty subset
    }
};

int main(){
    Solution sol;

    // Example 1
    vector<int> nums1 = {2, 4, 6};
    int k1 = 2;
    cout << "nums = {2,4,6}, k = 2 → " << sol.beautifulSubsets(nums1, k1) << " (expected: 4)\n";
    // Explanation: beautiful subsets = {2}, {4}, {6}, {2,6}

    // Example 2
    vector<int> nums2 = {1};
    int k2 = 1;
    cout << "nums = {1}, k = 1 → " << sol.beautifulSubsets(nums2, k2) << " (expected: 1)\n";
    // Explanation: beautiful subsets = {1}

    // Example 3: all elements differ by k → each element can only be alone
    vector<int> nums3 = {1, 2, 3, 4};
    int k3 = 1;
    cout << "nums = {1,2,3,4}, k = 1 → " << sol.beautifulSubsets(nums3, k3) << "\n";

    return 0;
}

