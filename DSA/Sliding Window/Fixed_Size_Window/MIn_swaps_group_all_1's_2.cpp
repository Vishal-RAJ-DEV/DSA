/*
================================================================================
              MINIMUM SWAPS TO GROUP ALL 1'S TOGETHER - EXPLANATION
================================================================================

PROBLEM:
--------
Given a binary array (only 0s and 1s).
Find minimum swaps to group ALL 1s together.

A swap = exchange positions of any two elements.

EXAMPLE:
--------
  Input:  [1, 0, 1, 0, 1]
  
  Total 1s = 3
  We want all 3 ones to be together: [1, 1, 1, 0, 0] or [0, 1, 1, 1, 0] etc.
  
  One possible solution:
    Swap nums[1] and nums[2]: [1, 1, 0, 0, 1]  (not grouped yet)
    Swap nums[2] and nums[4]: [1, 1, 1, 0, 0]  (grouped!)
  
  But minimum swaps = 1 (we'll see why below)


================================================================================
                    INTUITION / KEY INSIGHT
================================================================================

THINKING PROCESS:
-----------------
1. We need ALL 1s to be in a CONTIGUOUS block
2. The size of this block must be exactly `totalOnes`
   (because we're grouping ALL 1s together)
3. So we need to find a window of size `totalOnes` that has
   MAXIMUM number of 1s already

WHY THIS WORKS:
---------------
  If we have a window of size `totalOnes` with `maxOnes` ones:
  
  Window:  [1, 0, 1, 0, 1]  (size = 3, ones = 3)
           Window has 3 ones already!
           Zeros in window = 3 - 3 = 0
           Swaps needed = 0
  
  Window:  [0, 1, 0, 1, 1]  (size = 3, ones = 2)
           Window has 2 ones
           Zeros in window = 3 - 2 = 1
           Swaps needed = 1
           (One swap brings a 1 from outside into the window)

FORMULA:
--------
  Minimum Swaps = totalOnes - maxOnes
  
  Where:
    totalOnes = total number of 1s in array
    maxOnes   = maximum 1s found in any window of size totalOnes


================================================================================
                    WHY WINDOW SIZE = totalOnes?
================================================================================

  We're grouping ALL 1s together.
  
  If total 1s = 3, we need a contiguous block of size 3 containing all 1s.
  
  Example:
    Array: [1, 0, 1, 0, 1]
    Total 1s = 3
    
    We look for a window of size 3 with most 1s:
    
    Window [0..2]: [1, 0, 1] -> 2 ones
    Window [1..3]: [0, 1, 0] -> 1 one
    Window [2..4]: [1, 0, 1] -> 2 ones
    
    Max ones in any window = 2
    Swaps = 3 - 2 = 1


================================================================================
                    SLIDING WINDOW MECHANISM
================================================================================

  Algorithm:
  ----------
  1. Count total 1s (let's call it `k`)
  2. Use sliding window of size `k`
  3. Find window with MAXIMUM 1s
  4. Answer = k - maxOnes

  Visual:
  -------
  Array: [1, 0, 1, 0, 1, 0, 1]
  Total 1s = 4 (k = 4)
  
  Window size = 4
  
  Step 1: Window at [0..3]
          [1, 0, 1, 0] -> 2 ones
          
  Step 2: Window at [1..4]
          [0, 1, 0, 1] -> 2 ones
          
  Step 3: Window at [2..5]
          [1, 0, 1, 0] -> 2 ones
          
  Step 4: Window at [3..6]
          [0, 1, 0, 1] -> 2 ones
  
  Max ones = 2
  Swaps = 4 - 2 = 2


================================================================================
                    CIRCULAR ARRAY HANDLING
================================================================================

  WHY CIRCULAR?
  --------------
  The array is treated as CIRCULAR (wraps around).
  
  Example:
    Array: [1, 0, 0, 1, 0, 0, 1, 0]
    Total 1s = 3
    
    If array is circular, we can also consider:
      Window wrapping from end to beginning
      [1, 0] + [1, 0, 0, 1, 0, 0] (conceptually)
    
    So window at end can "see" elements at beginning.

  HOW TO HANDLE CIRCULAR?
  ------------------------
  We iterate up to `n + k - 1` (not just `n`)
  Use modulo `i % n` to wrap around
  
  Example:
    n = 8, k = 3
    Iterate i from 0 to 10 (n + k - 1 = 10)
    
    i=0: nums[0%8] = nums[0]
    i=1: nums[1%8] = nums[1]
    ...
    i=7: nums[7%8] = nums[7]
    i=8: nums[8%8] = nums[0]  (wraps to beginning!)
    i=9: nums[9%8] = nums[1]
    i=10: nums[10%8] = nums[2]

  WINDOW SLIDING WITH MODULO:
  ---------------------------
  Add element:    nums[i % n]
  Remove element: nums[(i - k) % n]
  
  This creates a "virtual" circular window.


================================================================================
                    STEP-BY-STEP CODE WORKING
================================================================================

  Let's trace through: nums = [1, 0, 1, 0, 1]
  
  Step 1: Count total 1s
          totalOnes = 3
  
  Step 2: Edge case check
          totalOnes <= 1? No, continue
  
  Step 3: Initialize sliding window
          onesInWindow = 0
          maxOnes = 0
  
  Step 4: Sliding window loop (i = 0 to n + totalOnes - 2 = 6)
          
          i=0: nums[0%5] = 1 -> onesInWindow = 1
               i < totalOnes-1 (2)? Yes, don't remove yet
               i >= totalOnes-1 (2)? No, don't update max
          
          i=1: nums[1%5] = 0 -> onesInWindow = 1
               i < totalOnes-1 (2)? Yes, don't remove yet
               i >= totalOnes-1 (2)? No, don't update max
          
          i=2: nums[2%5] = 1 -> onesInWindow = 2
               i < totalOnes-1 (2)? No, need to remove
               i >= totalOnes (3)? No, don't remove yet
               i >= totalOnes-1 (2)? Yes! maxOnes = max(0, 2) = 2
          
          i=3: nums[3%5] = 0 -> onesInWindow = 2
               i >= totalOnes (3)? Yes, remove nums[(3-3)%5] = nums[0] = 1
               onesInWindow = 1
               maxOnes = max(2, 1) = 2
          
          i=4: nums[4%5] = 1 -> onesInWindow = 2
               i >= totalOnes (3)? Yes, remove nums[(4-3)%5] = nums[1] = 0
               onesInWindow = 2
               maxOnes = max(2, 2) = 2
          
          i=5: nums[5%5] = 1 -> onesInWindow = 3
               i >= totalOnes (3)? Yes, remove nums[(5-3)%5] = nums[2] = 1
               onesInWindow = 2
               maxOnes = max(2, 2) = 2
          
          i=6: nums[6%5] = 0 -> onesInWindow = 2
               i >= totalOnes (3)? Yes, remove nums[(6-3)%5] = nums[3] = 0
               onesInWindow = 2
               maxOnes = max(2, 2) = 2
  
  Step 5: Calculate answer
          swaps = totalOnes - maxOnes = 3 - 2 = 1


================================================================================
                    WHY ANSWER = totalOnes - maxOnes?
================================================================================

  Logic:
  ------
  - We have `totalOnes` ones in the array
  - We found a window of size `totalOnes` with `maxOnes` ones
  - The window has `totalOnes - maxOnes` zeros
  - Each swap can replace one zero with one one from outside
  
  Visual:
  --------
  Array: [1, 0, 1, 0, 1]
  Best window: [1, 0, 1] (indices 0-2)
  
  Window has: 2 ones, 1 zero
  Zeros in window = 3 - 2 = 1
  
  We need 1 swap to replace that zero with the 1 from index 4
  
  After swap: [1, 1, 1, 0, 0] -> All 1s grouped!


================================================================================
                    COMPLETE VISUALIZATION
================================================================================

  nums = [1, 0, 1, 0, 1, 0, 1]
  n = 7, totalOnes = 4
  
  Array Visualization:
    Index:  0  1  2  3  4  5  6
    Value:  1  0  1  0  1  0  1
    
    [1] [0] [1] [0] [1] [0] [1]
    
  Sliding Window (size = 4):
  
    Window 1: [1, 0, 1, 0] (indices 0-3) -> 2 ones
    Window 2: [0, 1, 0, 1] (indices 1-4) -> 2 ones
    Window 3: [1, 0, 1, 0] (indices 2-5) -> 2 ones
    Window 4: [0, 1, 0, 1] (indices 3-6) -> 2 ones
    Window 5: [1, 0, 1, 1] (indices 4-6,0) -> 3 ones (circular!)
    Window 6: [0, 1, 1, 1] (indices 5-6,0-1) -> 3 ones (circular!)
  
    Wait, let me recalculate:
    Window 5: indices 4,5,6,0 -> [1, 0, 1, 1] = 3 ones
    Window 6: indices 5,6,0,1 -> [0, 1, 1, 0] = 2 ones
  
    Actually maxOnes = 3
    
  Answer: totalOnes - maxOnes = 4 - 3 = 1


================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        // ================================================================
        // STEP 1: Count total number of 1s
        // ================================================================
        // We need to know how many 1s exist to determine:
        //   1. Window size (must be = totalOnes)
        //   2. How many swaps might be needed
        //
        int totalOnes = 0;

        for (int num : nums) {
            totalOnes += num;  // Add 1 if num is 1, add 0 if num is 0
        }

        // ================================================================
        // STEP 2: Handle edge cases
        // ================================================================
        // If 0 or 1 ones, they're already grouped (no swaps needed)
        //
        if (totalOnes <= 1) {
            return 0;
        }

        // ================================================================
        // STEP 3: Initialize sliding window variables
        // ================================================================
        // onesInWindow = count of 1s in current window
        // maxOnes = maximum 1s found in any valid window
        //
        int onesInWindow = 0;
        int maxOnes = 0;

        // ================================================================
        // STEP 4: Sliding window of size = totalOnes
        // ================================================================
        // We iterate up to n + totalOnes - 1 to handle circular array
        //
        // Why n + totalOnes - 1?
        //   - We need to consider windows that wrap around the end
        //   - The last window starts at index n-1 and wraps to index 0
        //   - This requires iterating totalOnes extra positions
        //
        for (int i = 0; i < n + totalOnes - 1; i++) {

            // ============================================================
            // ADD CURRENT ELEMENT TO WINDOW
            // ============================================================
            // Use i % n to handle circular behavior (wrap around)
            // If nums[i % n] == 1, increment onesInWindow
            //
            if (nums[i % n] == 1) {
                onesInWindow++;
            }

            // ============================================================
            // REMOVE ELEMENT THAT GOES OUTSIDE WINDOW
            // ============================================================
            // When window size exceeds totalOnes, remove leftmost element
            // Leftmost element index = i - totalOnes
            // Use modulo for circular behavior
            //
            if (i >= totalOnes) {
                if (nums[(i - totalOnes) % n] == 1) {
                    onesInWindow--;
                }
            }

            // ============================================================
            // UPDATE MAX ONES (when window is valid)
            // ============================================================
            // Window becomes valid when its size = totalOnes
            // This happens when i >= totalOnes - 1
            //
            if (i >= totalOnes - 1) {
                maxOnes = max(maxOnes, onesInWindow);
            }
        }

        // ================================================================
        // STEP 5: Calculate minimum swaps
        // ================================================================
        // Zeros inside the best window = swaps required
        //
        // Why?
        //   - Best window has maxOnes ones
        //   - Window size = totalOnes
        //   - Zeros in window = totalOnes - maxOnes
        //   - Each swap replaces one zero with one one from outside
        //   - So we need (totalOnes - maxOnes) swaps
        //
        return totalOnes - maxOnes;
    }
};


// ============================================================================
//                           MAIN FUNCTION
// ============================================================================
//
// TEST CASES:
// -----------
// 1. nums = [1, 0, 1, 0, 1]
//    totalOnes = 3
//    maxOnes in window of size 3 = 2
//    Answer = 3 - 2 = 1
//
// 2. nums = [0, 0, 0, 1, 0]
//    totalOnes = 1
//    Answer = 0 (already grouped)
//
// 3. nums = [1, 1, 0, 0, 1]
//    totalOnes = 3
//    maxOnes in window of size 3 = 3 (indices 0-2)
//    Answer = 3 - 3 = 0
//
// ============================================================================
int main(){
    return 0;
}
