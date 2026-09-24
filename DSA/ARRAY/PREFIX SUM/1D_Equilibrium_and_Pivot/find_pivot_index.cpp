/*
================================================================================
                          FIND PIVOT INDEX (EQUILIBRIUM INDEX)
================================================================================

PROBLEM STATEMENT:
------------------
Given an array of integers nums, find the LEFTMOST index i such that:
    sum of all elements to the LEFT of i  ==  sum of all elements to the RIGHT of i

The pivot index is the index where the left sum equals the right sum.
If no such index exists, return -1.

IMPORTANT: The element at the pivot index itself is NOT included in either sum.

Example:
    nums = [1, 7, 3, 6, 5, 6]
    
    Index 0: Left = []        , Right = [7,3,6,5,6] = 27  --> 0 != 27
    Index 1: Left = [1]       , Right = [3,6,5,6]   = 20  --> 1 != 20
    Index 2: Left = [1,7]     , Right = [6,5,6]     = 17  --> 8 != 17
    Index 3: Left = [1,7,3]   , Right = [5,6]       = 11  --> 11 == 11 ✓
    
    Answer: 3 (pivot index)

================================================================================
                            UNDERSTANDING THE APPROACH
================================================================================

NAIVE APPROACH (Two separate loops per index):
-----------------------------------------------
For each index i, calculate left sum and right sum separately.
    Time: O(n^2) - too slow

BETTER APPROACH (Prefix Sum array):
------------------------------------
1. Build a prefix sum array where prefix[i] = sum of nums[0..i]
2. For each index, left sum = prefix[i-1], right sum = prefix[n-1] - prefix[i]
    Time: O(n), Space: O(n)

BEST APPROACH (Single pass with running sums) -- THIS CODE:
------------------------------------------------------------
1. First, compute totalSum = sum of all elements
2. Maintain a running leftSum as we iterate
3. At each index i:
   - rightSum = totalSum - leftSum - nums[i]
   - If leftSum == rightSum, return i
   - Add nums[i] to leftSum
    Time: O(n), Space: O(1) -- OPTIMAL

================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
        FUNCTION: pivotIndex
        --------------------
        Finds the leftmost index where left sum equals right sum.

        LOGIC:
        ------
        1. Initialize rightSum = total sum of all elements
        2. Iterate through each index:
           a. Subtract current element from rightSum (now rightSum = sum of elements to the RIGHT)
           b. Check if leftSum == rightSum
           c. If yes, we found the pivot index
           d. Otherwise, add current element to leftSum (for next iteration)
        3. If no pivot found, return -1

        WHY THIS WORKS:
        ---------------
        - Before the loop: rightSum = totalSum (includes ALL elements)
        - At index i, BEFORE processing nums[i]:
            rightSum = nums[i] + nums[i+1] + ... + nums[n-1]  (right portion + current)
        - After rightSum -= nums[i]:
            rightSum = nums[i+1] + ... + nums[n-1]  (strictly RIGHT of i)
        - leftSum = nums[0] + ... + nums[i-1]  (strictly LEFT of i)
        - So we check: leftSum == rightSum ?
    */
    int pivotIndex(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Calculate total sum of all elements
        // This will be used to compute right sum efficiently
        int rightSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            rightSum += nums[i];
        }

        // Step 2: Iterate and check each index for pivot condition
        int leftSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            
            // Remove current element from rightSum
            // Now rightSum = sum of elements strictly to the RIGHT of index i
            rightSum -= nums[i];

            // Check if left sum equals right sum
            // If yes, index i is the pivot index
            if (rightSum == leftSum) return i;

            // Add current element to leftSum for next iteration
            // For next index (i+1), leftSum will include nums[i]
            leftSum += nums[i];
        }

        // No pivot index found
        return -1;
    }
};

/*
================================================================================
                        DRY RUN / TRACE TABLE
================================================================================

nums = [1, 7, 3, 6, 5, 6], n = 6

Initial: rightSum = 1+7+3+6+5+6 = 28, leftSum = 0

Index 0 (nums[0] = 1):
    rightSum = 28 - 1 = 27    (sum of elements right of index 0)
    Check: leftSum(0) == rightSum(27)? NO
    leftSum = 0 + 1 = 1

Index 1 (nums[1] = 7):
    rightSum = 27 - 7 = 20    (sum of elements right of index 1)
    Check: leftSum(1) == rightSum(20)? NO
    leftSum = 1 + 7 = 8

Index 2 (nums[2] = 3):
    rightSum = 20 - 3 = 17    (sum of elements right of index 2)
    Check: leftSum(8) == rightSum(17)? NO
    leftSum = 8 + 3 = 11

Index 3 (nums[3] = 6):
    rightSum = 17 - 6 = 11    (sum of elements right of index 3)
    Check: leftSum(11) == rightSum(11)? YES ✓
    Return 3

ANSWER: pivot index = 3

================================================================================
                        COMPLEXITY ANALYSIS
================================================================================

TIME COMPLEXITY:  O(n)
    - Single pass to calculate total sum: O(n)
    - Single pass to find pivot: O(n)
    - Total: O(n) + O(n) = O(n)

SPACE COMPLEXITY: O(1)
    - Only two extra variables: leftSum, rightSum
    - No extra data structures used

================================================================================
*/

int main(){
    Solution sol;
    vector<int> nums = {1, 7, 3, 6, 5, 6}; 
    int pivot = sol.pivotIndex(nums);
    if(pivot != -1) {
        cout << "Pivot index: " << pivot << endl;
    } else {
        cout << "No pivot index found." << endl;
    }
    return 0;
}