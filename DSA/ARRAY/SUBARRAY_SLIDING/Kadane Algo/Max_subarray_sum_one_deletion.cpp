// =============================================================================
// MAXIMUM SUBARRAY SUM WITH ONE DELETION
// =============================================================================
// Problem: Find the maximum sum of a non-empty subarray where you can
//          delete AT MOST one element from the subarray.
//
// KEY DIFFERENCE FROM KADANE'S:
//   - Kadane's: Find max subarray sum (no deletion allowed)
//   - This: Find max subarray sum with at most one deletion
//
// INTUITION:
//   We need to track TWO states at each position:
//   1. Best sum with NO deletion so far
//   2. Best sum with EXACTLY ONE deletion so far
//
// WHY TWO STATES?
//   - A deletion can "save" us from a negative element
//   - But we can only use this trick ONCE
//   - So we must track whether we've used our deletion or not
//
// EXAMPLE:
//   arr = [1, -2, 0, 3]
//   Without deletion: max sum = 3 (subarray [3])
//   With one deletion: max sum = 4 (delete -2 from [1,-2,0,3] → [1,0,3])
//
// TIME: O(n)  |  SPACE: O(1)
// =============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSum(vector<int>& arr) {

        // =========================================================================
        // STATE VARIABLES
        // =========================================================================
        
        // totalsum = max subarray sum ending at current position with NO deletion
        // This is exactly Kadane's algorithm state
        int totalsum = arr[0];

        // delete_sum = max subarray sum ending at current position with EXACTLY ONE deletion
        // INT_MIN means we haven't encountered a deletable element yet
        int delete_sum = INT_MIN;

        int n = arr.size();

        // Answer can be negative (if all elements are negative)
        int ans = arr[0];

        // =========================================================================
        // MAIN LOOP - Process each element from index 1 to n-1
        // =========================================================================
        for (int i = 1; i < n; i++) {

            int x = arr[i];  // Current element

            // =====================================================================
            // POSSIBILITY 1: NO DELETION (Standard Kadane's)
            // =====================================================================
            // We have two choices:
            //   a) Start a new subarray from x: x
            //   b) Extend previous subarray: totalsum + x
            //
            // Visual:
            //   Previous: [ ... ]  →  totalsum
            //   Option a: [x]            →  x
            //   Option b: [ ... x]       →  totalsum + x
            // =====================================================================
            int curr_totalsum = max(x, totalsum + x);


            // =====================================================================
            // POSSIBILITY 2: EXACTLY ONE DELETION
            // =====================================================================
            // We have two choices:
            //   a) Delete current element x: use totalsum (no deletion before)
            //   b) Already deleted before, extend: delete_sum + x
            //
            // Visual:
            //   Option a: [ ... ] DELETE x  →  totalsum
            //             (deletion used now)
            //
            //   Option b: [ ... DEL ... ] x  →  delete_sum + x
            //             (deletion used earlier)
            // =====================================================================
            int curr_delete_sum = totalsum;  // Option a: delete current x

            if (delete_sum != INT_MIN) {
                // Option b: extend previous one-deletion sum
                curr_delete_sum = max(curr_delete_sum, delete_sum + x);
            }


            // =====================================================================
            // UPDATE STATES FOR NEXT ITERATION
            // =====================================================================
            totalsum = curr_totalsum;
            delete_sum = curr_delete_sum;


            // =====================================================================
            // UPDATE ANSWER
            // =====================================================================
            // Answer is max of: previous answer, no-deletion sum, one-deletion sum
            ans = max(ans, max(totalsum, delete_sum));
        }

        return ans;
    }
};

// =============================================================================
// MAIN - Test with detailed trace
// =============================================================================
int main(){
    vector<int> arr = {1, -2, 0, 3};

    /*
    DETAILED TRACE: arr = [1, -2, 0, 3]
    
    Initial State:
    totalsum = 1 (max subarray ending at index 0, no deletion)
    delete_sum = INT_MIN (no deletion used yet)
    ans = 1
    
    ============================================================================
    ITERATION i=1, x = arr[1] = -2
    ============================================================================
    
    POSSIBILITY 1: No Deletion
    ┌─────────────────────────────────────────────────────┐
    │  Option a: Start new from -2    → -2               │
    │  Option b: Extend 1 + (-2)      → -1               │
    │  curr_totalsum = max(-2, -1) = -1                  │
    └─────────────────────────────────────────────────────┘
    
    POSSIBILITY 2: One Deletion
    ┌─────────────────────────────────────────────────────┐
    │  Option a: Delete -2, use totalsum → 1             │
    │  Option b: No previous delete_sum (INT_MIN)        │
    │  curr_delete_sum = 1                               │
    └─────────────────────────────────────────────────────┘
    
    After i=1:
    ┌─────────────────┬─────────────────┬─────────────────┐
    │     State       │    Value        │    Meaning      │
    ├─────────────────┼─────────────────┼─────────────────┤
    │  totalsum       │      -1         │  Best ending at │
    │                 │                 │  index 1, no    │
    │                 │                 │  deletion       │
    ├─────────────────┼─────────────────┼─────────────────┤
    │  delete_sum     │       1         │  Best ending at │
    │                 │                 │  index 1, with  │
    │                 │                 │  one deletion   │
    └─────────────────┴─────────────────┴─────────────────┘
    
    ans = max(1, max(-1, 1)) = 1
    
    ============================================================================
    ITERATION i=2, x = arr[2] = 0
    ============================================================================
    
    POSSIBILITY 1: No Deletion
    ┌─────────────────────────────────────────────────────┐
    │  Option a: Start new from 0     → 0                │
    │  Option b: Extend -1 + 0        → -1               │
    │  curr_totalsum = max(0, -1) = 0                    │
    └─────────────────────────────────────────────────────┘
    
    POSSIBILITY 2: One Deletion
    ┌─────────────────────────────────────────────────────┐
    │  Option a: Delete 0, use totalsum → -1             │
    │  Option b: Extend delete_sum + 0 → 1 + 0 = 1      │
    │  curr_delete_sum = max(-1, 1) = 1                  │
    └─────────────────────────────────────────────────────┘
    
    After i=2:
    totalsum = 0, delete_sum = 1
    
    ans = max(1, max(0, 1)) = 1
    
    ============================================================================
    ITERATION i=3, x = arr[3] = 3
    ============================================================================
    
    POSSIBILITY 1: No Deletion
    ┌─────────────────────────────────────────────────────┐
    │  Option a: Start new from 3     → 3                │
    │  Option b: Extend 0 + 3         → 3                │
    │  curr_totalsum = max(3, 3) = 3                     │
    └─────────────────────────────────────────────────────┘
    
    POSSIBILITY 2: One Deletion
    ┌─────────────────────────────────────────────────────┐
    │  Option a: Delete 3, use totalsum → 0              │
    │  Option b: Extend delete_sum + 3 → 1 + 3 = 4      │
    │  curr_delete_sum = max(0, 4) = 4  ← BEST!         │
    └─────────────────────────────────────────────────────┘
    
    After i=3:
    totalsum = 3, delete_sum = 4
    
    ans = max(1, max(3, 4)) = 4
    
    ============================================================================
    FINAL ANSWER: 4
    ============================================================================
    
    How did we get 4?
    
    delete_sum = 4 at index 3 means:
    - We used our one deletion
    - Best subarray ending at index 3 with one deletion
    
    The subarray is [1, -2, 0, 3]
    We delete -2 → [1, 0, 3]
    Sum = 1 + 0 + 3 = 4 ✓
    
    Visual:
    Index:    0     1     2     3
    Value:   [1]  [-2]   [0]   [3]
              ↓     ↓     ↓     ↓
            keep  DELETE  keep  keep
              ↓           ↓     ↓
            [1]          [0]   [3]
    
    Sum = 1 + 0 + 3 = 4
    */

    Solution sol;
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    cout << "Maximum sum with at most one deletion: " << sol.maximumSum(arr) << endl;

    return 0;
}