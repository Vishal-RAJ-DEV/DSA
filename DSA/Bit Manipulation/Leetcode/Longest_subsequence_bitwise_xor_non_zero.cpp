// =============================================================================
// LONGEST SUBSEQUENCE WITH BITWISE XOR NON-ZERO
// =============================================================================
// Problem: Find the longest subsequence where XOR of all elements ≠ 0.
//
// KEY PROPERTIES OF XOR:
//   - A ^ A = 0  (same elements cancel out)
//   - A ^ 0 = A  (XOR with zero doesn't change)
//   - XOR is commutative and associative
//
// INTUITION:
//   The answer depends on just TWO things:
//   1. XOR of ALL elements in the array
//   2. Whether there exists at least one non-zero element
//
// WHY?
//   - If totalXor ≠ 0: Take entire array (XOR is already non-zero)
//   - If totalXor = 0: Need to remove one element to make XOR non-zero
//     - If any element ≠ 0: Removing it breaks the "cancellation" → XOR becomes non-zero
//     - If all elements = 0: XOR will always be 0 → answer is 0
//
// TIME: O(n)  |  SPACE: O(1)
// =============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        
        // =====================================================================
        // STEP 1: Compute XOR of all elements
        // =====================================================================
        int totalXor = 0;
        bool hasNonZero = false;

        for (int x : nums) {
            totalXor ^= x;          // Accumulate XOR of all elements

            if (x != 0) {
                hasNonZero = true;  // Track if any non-zero exists
            }
        }

        // =====================================================================
        // STEP 2: Apply the three cases
        // =====================================================================
        
        // CASE 1: Total XOR is non-zero
        // → We can take the ENTIRE array
        // → Answer = n
        //
        // Example: [1, 2, 3]
        //   totalXor = 1 ^ 2 ^ 3 = 0 (not this case)
        //
        // Example: [1, 2, 4]
        //   totalXor = 1 ^ 2 ^ 4 = 7 ≠ 0
        //   Answer = 3 (take all)
        if (totalXor != 0) {
            return n;
        }

        // CASE 2: Total XOR is zero, but there's a non-zero element
        // → Remove ONE non-zero element to break the cancellation
        // → Answer = n - 1
        //
        // Why does this work?
        //   If totalXor = 0, then some elements "cancel" each other
        //   Removing a non-zero element breaks this cancellation
        //   The remaining XOR becomes non-zero
        //
        // Example: [1, 2, 3]
        //   totalXor = 1 ^ 2 ^ 3 = 0
        //   Remove 1: [2, 3] → 2 ^ 3 = 1 ≠ 0 ✓
        //   Remove 2: [1, 3] → 1 ^ 3 = 2 ≠ 0 ✓
        //   Remove 3: [1, 2] → 1 ^ 2 = 3 ≠ 0 ✓
        //   Answer = 2
        if (hasNonZero) {
            return n - 1;
        }

        // CASE 3: All elements are zero
        // → XOR will always be 0, no matter what subsequence we pick
        // → Answer = 0 (no valid subsequence)
        //
        // Example: [0, 0, 0]
        //   Any subsequence: 0 ^ 0 = 0
        //   Answer = 0
        return 0;
    }
};

// =============================================================================
// MAIN - Test with examples
// =============================================================================
int main(){
    /*
    EXAMPLES:
    
    Example 1: [1, 2, 4]
    ┌─────────────────────────────────────────────┐
    │  totalXor = 1 ^ 2 ^ 4 = 7 ≠ 0             │
    │  Answer = 3 (take entire array)             │
    │                                             │
    │  Verification: 1 ^ 2 ^ 4 = 7 ≠ 0 ✓        │
    └─────────────────────────────────────────────┘
    
    Example 2: [1, 2, 3]
    ┌─────────────────────────────────────────────┐
    │  totalXor = 1 ^ 2 ^ 3 = 0                  │
    │  hasNonZero = true                          │
    │  Answer = 2 (remove one element)            │
    │                                             │
    │  Remove 1: [2, 3] → 2 ^ 3 = 1 ≠ 0 ✓      │
    └─────────────────────────────────────────────┘
    
    Example 3: [0, 0, 0]
    ┌─────────────────────────────────────────────┐
    │  totalXor = 0 ^ 0 ^ 0 = 0                  │
    │  hasNonZero = false                         │
    │  Answer = 0 (impossible to get non-zero)    │
    └─────────────────────────────────────────────┘
    
    Example 4: [1, 1, 2, 3, 3]
    ┌─────────────────────────────────────────────┐
    │  totalXor = 1^1^2^3^3 = 2 ≠ 0             │
    │  Answer = 5 (take entire array)             │
    │                                             │
    │  Note: 1^1 = 0, 3^3 = 0, so 0^2 = 2       │
    └─────────────────────────────────────────────┘
    */

    Solution sol;

    vector<int> test1 = {1, 2, 4};
    vector<int> test2 = {1, 2, 3};
    vector<int> test3 = {0, 0, 0};
    vector<int> test4 = {1, 1, 2, 3, 3};

    cout << "[1, 2, 4] → " << sol.longestSubsequence(test1) << endl;
    cout << "[1, 2, 3] → " << sol.longestSubsequence(test2) << endl;
    cout << "[0, 0, 0] → " << sol.longestSubsequence(test3) << endl;
    cout << "[1, 1, 2, 3, 3] → " << sol.longestSubsequence(test4) << endl;

    return 0;
}