#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
                     PERMUTATION - RECURSION TREE & WORKING
================================================================================

Example: nums = {1, 2, 3}

RECURSION TREE (showing every call, swap, and backtrack):
---------------------------------------------------------

perms([1,2,3], idx=0)                          <-- STACK LEVEL 0
|  Loop j = 0 to 2 (3 iterations)
|
|-- j=0: swap(0,0) -> [1,2,3] (no change)
|   |
|   +-- perms([1,2,3], idx=1)                  <-- STACK LEVEL 1
|   |   |  Loop j = 1 to 2 (2 iterations)
|   |   |
|   |   |-- j=1: swap(1,1) -> [1,2,3] (no change)
|   |   |   |
|   |   |   +-- perms([1,2,3], idx=2)          <-- STACK LEVEL 2
|   |   |       |  Loop j = 2 to 2 (1 iteration)
|   |   |       |
|   |   |       |-- j=2: swap(2,2) -> [1,2,3] (no change)
|   |   |       |   |
|   |   |       |   +-- perms([1,2,3], idx=3)  <-- STACK LEVEL 3 (BASE CASE)
|   |   |       |       |  idx == nums.size() -> STORE [1,2,3], return
|   |   |       |       |
|   |   |       |   backtrack: swap(2,2) -> [1,2,3] (restored)
|   |   |       |
|   |   |       Loop ends. Return to caller.
|   |   |
|   |   |   backtrack: swap(1,1) -> [1,2,3] (restored)
|   |   |
|   |   |-- j=2: swap(1,2) -> [1,3,2]
|   |   |   |
|   |   |   +-- perms([1,3,2], idx=2)          <-- STACK LEVEL 2
|   |   |       |  Loop j = 2 to 2 (1 iteration)
|   |   |       |
|   |   |       |-- j=2: swap(2,2) -> [1,3,2] (no change)
|   |   |       |   |
|   |   |       |   +-- perms([1,3,2], idx=3)  <-- STACK LEVEL 3 (BASE CASE)
|   |   |       |       |  idx == nums.size() -> STORE [1,3,2], return
|   |   |       |       |
|   |   |       |   backtrack: swap(2,2) -> [1,3,2] (restored)
|   |   |       |
|   |   |       Loop ends. Return to caller.
|   |   |
|   |   |   backtrack: swap(1,2) -> [1,2,3] (restored)
|   |   |
|   |   Loop ends. Return to caller.
|
|   backtrack: swap(0,0) -> [1,2,3] (restored)
|
|-- j=1: swap(0,1) -> [2,1,3]
|   |
|   +-- perms([2,1,3], idx=1)                  <-- STACK LEVEL 1
|   |   |  Loop j = 1 to 2 (2 iterations)
|   |   |
|   |   |-- j=1: swap(1,1) -> [2,1,3] (no change)
|   |   |   |
|   |   |   +-- perms([2,1,3], idx=2)          <-- STACK LEVEL 2
|   |   |       |  Loop j = 2 to 2 (1 iteration)
|   |   |       |
|   |   |       |-- j=2: swap(2,2) -> [2,1,3] (no change)
|   |   |       |   |
|   |   |       |   +-- perms([2,1,3], idx=3)  <-- STACK LEVEL 3 (BASE CASE)
|   |   |       |       |  idx == nums.size() -> STORE [2,1,3], return
|   |   |       |       |
|   |   |       |   backtrack: swap(2,2) -> [2,1,3] (restored)
|   |   |       |
|   |   |       Loop ends. Return to caller.
|   |   |
|   |   |   backtrack: swap(1,1) -> [2,1,3] (restored)
|   |   |
|   |   |-- j=2: swap(1,2) -> [2,3,1]
|   |   |   |
|   |   |   +-- perms([2,3,1], idx=2)          <-- STACK LEVEL 2
|   |   |       |  Loop j = 2 to 2 (1 iteration)
|   |   |       |
|   |   |       |-- j=2: swap(2,2) -> [2,3,1] (no change)
|   |   |       |   |
|   |   |       |   +-- perms([2,3,1], idx=3)  <-- STACK LEVEL 3 (BASE CASE)
|   |   |       |       |  idx == nums.size() -> STORE [2,3,1], return
|   |   |       |       |
|   |   |       |   backtrack: swap(2,2) -> [2,3,1] (restored)
|   |   |       |
|   |   |       Loop ends. Return to caller.
|   |   |
|   |   |   backtrack: swap(1,2) -> [2,1,3] (restored)
|   |   |
|   |   Loop ends. Return to caller.
|
|   backtrack: swap(0,1) -> [1,2,3] (restored)
|
|-- j=2: swap(0,2) -> [3,2,1]
|   |
|   +-- perms([3,2,1], idx=1)                  <-- STACK LEVEL 1
|   |   |  Loop j = 1 to 2 (2 iterations)
|   |   |
|   |   |-- j=1: swap(1,1) -> [3,2,1] (no change)
|   |   |   |
|   |   |   +-- perms([3,2,1], idx=2)          <-- STACK LEVEL 2
|   |   |       |  Loop j = 2 to 2 (1 iteration)
|   |   |       |
|   |   |       |-- j=2: swap(2,2) -> [3,2,1] (no change)
|   |   |       |   |
|   |   |       |   +-- perms([3,2,1], idx=3)  <-- STACK LEVEL 3 (BASE CASE)
|   |   |       |       |  idx == nums.size() -> STORE [3,2,1], return
|   |   |       |       |
|   |   |       |   backtrack: swap(2,2) -> [3,2,1] (restored)
|   |   |       |
|   |   |       Loop ends. Return to caller.
|   |   |
|   |   |   backtrack: swap(1,1) -> [3,2,1] (restored)
|   |   |
|   |   |-- j=2: swap(1,2) -> [3,1,2]
|   |   |   |
|   |   |   +-- perms([3,1,2], idx=2)          <-- STACK LEVEL 2
|   |   |       |  Loop j = 2 to 2 (1 iteration)
|   |   |       |
|   |   |       |-- j=2: swap(2,2) -> [3,1,2] (no change)
|   |   |       |   |
|   |   |       |   +-- perms([3,1,2], idx=3)  <-- STACK LEVEL 3 (BASE CASE)
|   |   |       |       |  idx == nums.size() -> STORE [3,1,2], return
|   |   |       |       |
|   |   |       |   backtrack: swap(2,2) -> [3,1,2] (restored)
|   |   |       |
|   |   |       Loop ends. Return to caller.
|   |   |
|   |   |   backtrack: swap(1,2) -> [3,2,1] (restored)
|   |   |
|   |   Loop ends. Return to caller.
|
|   backtrack: swap(0,2) -> [1,2,3] (restored)
|
Loop ends. Done.

================================================================================
                         STACK SPACE ANALYSIS
================================================================================

Maximum stack depth = nums.size() + 1 = 4 (for n=3)

  STACK FRAME              LOCAL VARIABLES
  -----------------------  --------------------------------
  perms(nums, idx=0, res)  j iterates: 0, 1, 2
  |                        nums = [1,2,3] (root call)
  |
  +-- perms(nums, idx=1, res)   j iterates: 1, 2
  |   |                          nums = [1,2,3]
  |   |
  |   +-- perms(nums, idx=2, res)   j iterates: 2
  |   |   |                          nums = [1,2,3]
  |   |   |
  |   |   +-- perms(nums, idx=3, res)  <-- BASE CASE (popped immediately)
  |   |       STACK AT PEAK: 4 frames alive simultaneously
  |   |
  |   (after idx=2 returns, idx=1 continues its loop)
  |
  (after idx=1 returns, idx=0 continues its loop)

Space complexity: O(n) for recursion stack depth.
Each stack frame holds: nums reference, idx value, j loop variable.
Total permutations generated: n! = 3! = 6.

================================================================================
                    HOW THE LOOP WORKS AT EACH RECURSION CALL
================================================================================

KEY INSIGHT: At recursion level `idx`, the loop `for(j=idx; j<n; j++)`
tries placing each remaining element at position `idx`.

Level 0 (idx=0): j = 0, 1, 2  --> 3 choices for position 0
  - j=0: fix element at index 0 (itself), recurse for remaining
  - j=1: swap index 0 with index 1, recurse for remaining
  - j=2: swap index 0 with index 2, recurse for remaining

Level 1 (idx=1): j = 1, 2  --> 2 choices for position 1
  - j=1: fix element at index 1 (itself), recurse for remaining
  - j=2: swap index 1 with index 2, recurse for remaining

Level 2 (idx=2): j = 2  --> 1 choice for position 2
  - j=2: only element left, swap with itself, recurse

Level 3 (idx=3): BASE CASE  --> no loop, just store result

Pattern: At level idx, the loop runs (n - idx) times.
Total loop iterations across all calls = n! * (some factor) but
the key insight is that each path from root to leaf produces
exactly one permutation.

================================================================================
                    HOW BACKTRACKING WORKS
================================================================================

The swap-then-recurse-then-unswap pattern ensures:
1. BEFORE recursive call: we PLACE the chosen element at position idx
2. AFTER recursive call: we RESTORE the array to its original state

This means when we return from a recursive call, the array is exactly
the same as before we entered that call. This allows the loop to try
the next candidate with a CLEAN array state.

Without the backtrack swap, the array would be corrupted and subsequent
iterations of the loop would operate on wrong data.

Example trace for first few steps:
  Start: [1,2,3]
  j=0: swap(0,0)->[1,2,3], recurse, swap(0,0)->[1,2,3] (restored)
  j=1: swap(0,1)->[2,1,3], recurse, swap(0,1)->[1,2,3] (restored)
  j=2: swap(0,2)->[3,2,1], recurse, swap(0,2)->[1,2,3] (restored)

After all 3 iterations, nums is back to [1,2,3] -- original state!
================================================================================
*/

class Solution {
public:
    void perms( vector<int>&nums , int idx , vector<vector<int>>&res){
        // Base case: one full permutation is formed when idx reaches the end.
        // At this point, all n positions have been filled, so we store a copy.
        // Stack depth at this point = n+1 (idx=0,1,...,n are all on the stack).
        if(idx == nums.size()){
            res.push_back(nums);
            return;
        }

        // Loop: at recursion level idx, try placing each remaining element
        // at position idx. The loop runs (n - idx) times.
        //
        // WHY j starts at idx: elements before idx are already "fixed" in
        // their positions by previous recursion levels. We only swap among
        // the remaining unfixed positions [idx, idx+1, ..., n-1].
        //
        // Each iteration:
        //   1. SWAP  - place candidate nums[j] at position idx
        //   2. RECURSE - build permutations for positions [idx+1 .. n-1]
        //   3. UNSWAP - restore array so next iteration sees original state
        for( int j = idx; j < nums.size(); j++){
            // Choose: place nums[j] at the current position idx.
            // This "fixes" the element at idx and pushes it out of the
            // candidate pool for deeper recursion levels.
            swap(nums[idx] , nums[j]);

            // Explore: recurse to fill positions [idx+1 .. n-1].
            // The recursive call will have its own loop trying candidates
            // from the remaining unfixed positions.
            perms(nums , idx+1 , res);

            // Undo choice (backtrack): restore nums[idx] and nums[j] so
            // the array is in its pre-swap state. This is critical because
            // the next iteration of THIS loop needs the original array.
            swap(nums[idx] , nums[j]);
        } 
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>res;
        // Start generating permutations from index 0.
        // This is the root of the recursion tree.
        // Stack starts with 1 frame, grows to max depth of n+1.
        perms(nums , 0 , res);
        return res;
    }
};


int main(){
    int n;
    cin>>n;
    // Read input array.
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }

    // Generate all permutations.
    Solution s;
    vector<vector<int>> res = s.permute(nums);

    // Print each permutation in a separate line.
    for(auto &it : res){
        for(auto &el : it){
            cout<<el<<" ";
        }
        cout<<endl;
    }
    
    return 0;
}
