#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  PROBLEM: Replace Elements in an Array (LeetCode 2295)
 * ================================================================
 *  You are given an array nums and a list of operations.
 *  Each operation [oldVal, newVal] means:
 *    "Replace ALL occurrences of oldVal in nums with newVal."
 *
 *  Operations are applied SEQUENTIALLY.
 *  After all operations, return the modified array.
 *
 *  Example:
 *    nums = [1, 2, 4, 6]
 *    operations = [[1, 3], [4, 3], [6, 1]]
 *
 *    Step 1: [1,2,4,6] → replace 1→3 → [3,2,4,6]
 *    Step 2: [3,2,4,6] → replace 4→3 → [3,2,3,6]
 *    Step 3: [3,2,3,6] → replace 6→1 → [3,2,3,1]
 *    Result: [3, 2, 3, 1]
 *
 *  Note: The same value can be replaced multiple times across
 *  different operations (e.g., 4→3 in step 2, 6→1 in step 3).
 *  Also, new values themselves may later be replaced.
 *
 *  TWO APPROACHES:
 *    1. Forward Simulation (index tracking)  — O(n + m)
 *    2. Reverse Mapping (chain resolution)   — O(n + m)
 * ================================================================
 */

// ================================================================
// APPROACH 1: Forward Simulation (index tracking)
// ================================================================
// ALGORITHM:
//   1. Build a hashmap: value → its index in nums
//      (assumes all values are unique — which is guaranteed)
//   2. For each operation [oldVal, newVal]:
//      a. Look up the index of oldVal from the map
//      b. Replace nums[idx] = newVal
//      c. Remove oldVal from map, insert newVal → idx
//   3. Return nums
//
// INTUITION:
//   Since each element's value changes, we need to quickly find
//   WHERE the old value currently is to replace it. A hashmap
//   from value→index gives O(1) lookup.
//
//   After replacement, the old key is stale (value no longer in
//   array), and the new value is now at that index, so we update
//   the map accordingly.
//
// TIME:  O(n + m)  — n to build map, m operations each O(1)
// SPACE: O(n)      — hashmap of n entries
// ================================================================

class Solution_Forward {
public:
    vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations) {

        // Map each VALUE to its INDEX in nums
        // (The problem guarantees all nums values are unique)
        unordered_map<int, int> mp;  // value → index

        for (int i = 0; i < nums.size(); i++)
            mp[nums[i]] = i;

        // Process each operation sequentially
        for (auto& op : operations) {

            int oldValue = op[0];   // value to be replaced
            int newValue = op[1];   // replacement value

            // Find where oldValue currently sits in the array
            int idx = mp[oldValue];

            // Replace it in the array
            nums[idx] = newValue;

            // Update the hashmap:
            //   oldValue no longer exists in the array → erase
            //   newValue now lives at this index → insert
            mp.erase(oldValue);
            mp[newValue] = idx;
        }

        return nums;
    }
};

// ================================================================
// APPROACH 2: Reverse Mapping (chain resolution)
// ================================================================
// ALGORITHM:
//   1. Process operations from RIGHT to LEFT (reverse order).
//   2. Build a map: oldValue → finalValueAfterAllOperations.
//   3. In one final pass, replace each num using this map.
//
// INTUITION:
//   When we process operations in REVERSE, we always know the
//   FINAL value that any value will eventually become.
//
//   Consider operations: [[1,3], [4,3], [6,1]]
//   Processing reverse:
//
//     i=2: op=[6,1]
//       newVal=1 is NOT in map → mp[6] = 1
//       (6 is replaced by 1, and 1 stays as is)
//
//     i=1: op=[4,3]
//       newVal=3 is NOT in map → mp[4] = 3
//       (4 is replaced by 3, and 3 stays as is)
//
//     i=0: op=[1,3]
//       newVal=3 IS in map (mp[3] doesn't exist, but wait...
//       Actually mp[3] is not set, so mp[1] = 3)
//
//   But what about CHAINING? Consider ops: [[1,2], [2,3]]
//     Processing reverse:
//       i=1: op=[2,3] → mp[2] = 3   (2→3)
//       i=0: op=[1,2] → newVal=2 IS in map!
//                        So mp[1] = mp[2] = 3
//                        (1→2→3, so 1 finally becomes 3)
//
//   This CHAINING is the key: if the newValue itself will later
//   be replaced, we follow the chain to get the FINAL value.
//
// WHY REVERSE WORKS:
//   Processing backwards means we already know the eventual fate
//   of every value. When we encounter an operation [old→new],
//   if new is in the map, it means new will itself be replaced
//   later (which is earlier in reverse = later in forward time).
//   So old should map to wherever new eventually ends up.
//
// TIME:  O(n + m)  — single reverse pass + single final pass
// SPACE: O(m)      — at most one mapping per operation
// ================================================================

class Solution_Reverse {
public:
    vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations) {

        // mp[oldValue] = final value after all future operations
        unordered_map<int, int> mp;

        // Process operations in REVERSE order
        for (int i = operations.size() - 1; i >= 0; i--) {

            int oldValue = operations[i][0];  // value to replace
            int newValue = operations[i][1];  // replacement

            /*
             * If newValue itself will be replaced later (i.e., it
             * is already in the map from a previous reverse step),
             * then oldValue should directly point to THAT final value.
             *
             * Example:
             *   ops = [[1,2], [2,3]]
             *   reverse: i=1 → mp[2] = 3
             *            i=0 → newVal=2 IS in mp, so mp[1] = mp[2] = 3
             *   So 1 → 2 → 3 resolves directly to 1 → 3
             */
            if (mp.count(newValue))
                mp[oldValue] = mp[newValue];
            else
                mp[oldValue] = newValue;
        }

        // Apply all mappings in a single pass over nums
        for (int& x : nums) {
            if (mp.count(x))
                x = mp[x];
        }

        return nums;
    }
};

/*
 * ================================================================
 *  DRY RUN
 * ================================================================
 *  nums = [1, 2, 4, 6]
 *  operations = [[1, 3], [4, 3], [6, 1]]
 *
 *  --------------------------------------------------------------
 *  APPROACH 1 (Forward):
 *  --------------------------------------------------------------
 *  Initial map: {1:0, 2:1, 4:2, 6:3}
 *
 *  op [1,3]: idx=mp[1]=0 → nums[0]=3 → mp={2:1, 4:2, 6:3, 3:0}
 *  op [4,3]: idx=mp[4]=2 → nums[2]=3 → mp={2:1, 6:3, 3:2}  (4 erased, 3→2 updated)
 *  op [6,1]: idx=mp[6]=3 → nums[3]=1 → mp={2:1, 3:2, 1:3}
 *
 *  Final nums: [3, 2, 3, 1]
 *
 *  --------------------------------------------------------------
 *  APPROACH 2 (Reverse):
 *  --------------------------------------------------------------
 *  i=2: op=[6,1] → mp doesn't have 1 → mp[6] = 1
 *  i=1: op=[4,3] → mp doesn't have 3 → mp[4] = 3
 *  i=0: op=[1,3] → mp doesn't have 3 → mp[1] = 3
 *
 *  Map: {6:1, 4:3, 1:3}
 *
 *  Apply: nums[0]=1 → 3, nums[1]=2 (not in map), nums[2]=4 → 3, nums[3]=6 → 1
 *  Final nums: [3, 2, 3, 1]
 *
 *  --------------------------------------------------------------
 *  CHAINING EXAMPLE:
 *  --------------------------------------------------------------
 *  nums = [1, 2]
 *  operations = [[1, 2], [2, 3]]
 *
 *  Reverse:
 *    i=1: op=[2,3] → mp doesn't have 3 → mp[2] = 3
 *    i=0: op=[1,2] → mp HAS 2! → mp[1] = mp[2] = 3  (chain: 1→2→3)
 *
 *  Map: {2:3, 1:3}
 *  Apply: nums[0]=1 → 3, nums[1]=2 → 3
 *  Final: [3, 3]
 *
 *  Forward verification:
 *    Step 1: [1,2] → [2,2]  (1→2)
 *    Step 2: [2,2] → [3,3]  (2→3)
 *  ✓ Correct
 * ================================================================
 */

int main() {
    return 0;
}
