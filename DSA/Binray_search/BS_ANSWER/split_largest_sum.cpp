#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
PROBLEM: Split Array Largest Sum (LeetCode 410)
================================================================================

Given an array nums and integer k, split nums into k contiguous subarrays.
Minimize the largest sum among these subarrays.

================================================================================
INTUITION & MONOTONIC PROPERTY EXPLANATION
================================================================================

We binary search on the answer X = "allowed maximum subarray sum".

KEY INSIGHT: Monotonic Property in the Range
--------------------------------------------
For any value X, we ask: "Can we split array into <= k subarrays
where each subarray sum is <= X?"

Let's see how this property behaves across the range of possible X values:

    Range: [low ... mid ... high]
            |         |
            v         v
          minSum    maxSum

For the example: nums = [7, 2, 5, 10, 8], k = 2

    Possible X values: [10, 11, 12, ..., 32]
    (minSum=10 is max element, maxSum=32 is total sum)

Now mark each value as TRUE (feasible) or FALSE (not feasible):

    X = 10: Need 4 subarrays [7], [2,5], [10], [8] -> FALSE (4 > 2)
    X = 11: Need 4 subarrays -> FALSE
    X = 12: Need 3 subarrays [7,2], [5], [10], [8] -> FALSE (4 > 2)
    X = 13: Need 3 subarrays -> FALSE
    X = 14: Need 2 subarrays [7,2,5], [10,8] -> TRUE (2 <= 2) ***
    X = 15: Need 2 subarrays -> TRUE
    ...
    X = 32: Need 1 subarray [7,2,5,10,8] -> TRUE

    VISUAL REPRESENTATION OF THE RANGE:
    ---------------------------------------------------------------
    Index:   10  11  12  13  14  15  16  17  ...  32
    Value:   F   F   F   F   T   T   T   T   ...   T
                      |               |
                      |               |
                  FALSE region    TRUE region
                  (left side)    (right side)
    ---------------------------------------------------------------

PATTERN: FALSE -> TRUE (monotonic)
----------------------------------
- As X increases, it becomes EASIER to fit subarrays within limit
- Small X: hard to split -> FALSE
- Large X: easy to split -> TRUE
- Once TRUE, all larger values are also TRUE (monotonic!)

THIS IS THE MONOTONIC PROPERTY!
- LEFT side of range: all FALSE (X too small, can't split)
- RIGHT side of range: all TRUE (X large enough, can split)
- We need to find the TRANSITION POINT: first TRUE (boundary)

================================================================================
BINARY SEARCH TEMPLATE: FIND FIRST TRUE FROM RIGHT SIDE
================================================================================

When TRUE is on the RIGHT side and we want the FIRST TRUE:

    while (low <= high) {
        mid = low + (high - low) / 2;

        if (isFeasible(mid)) {
            // mid is TRUE, but there might be a smaller TRUE on the left
            // So save this and search LEFT for first TRUE
            ans = mid;
            high = mid - 1;   // Go LEFT to find first TRUE
        } else {
            // mid is FALSE, first TRUE must be on the RIGHT
            low = mid + 1;    // Go RIGHT to find first TRUE
        }
    }

HOW LOW POINTS TO THE FIRST TRUE:
----------------------------------
Let's trace through our example:

    Initial: low = 10, high = 32

    Iteration 1: mid = 21
        isFeasible(21) = TRUE -> save ans=21, high = 20
        Range now: [10 ... 20]

    Iteration 2: mid = 15
        isFeasible(15) = TRUE -> save ans=15, high = 14
        Range now: [10 ... 14]

    Iteration 3: mid = 12
        isFeasible(12) = FALSE -> low = 13
        Range now: [13 ... 14]

    Iteration 4: mid = 13
        isFeasible(13) = FALSE -> low = 14
        Range now: [14 ... 14]

    Iteration 5: mid = 14
        isFeasible(14) = TRUE -> save ans=14, high = 13
        Range now: [14 ... 13] -> low > high, STOP!

    Final: low = 14, ans = 14

    WHY LOW = 14 (THE FIRST TRUE)?
    --------------------------------
    When loop ends: low = high + 1
    - low points to the SMALLEST value that wasn't checked as FALSE
    - All values < low were checked and found FALSE
    - low itself is the FIRST TRUE (transition point)

    At the end:
    - high = 13 (last FALSE value)
    - low = 14 (first TRUE value)
    - ans = 14 (saved when we found TRUE)

    CONCLUSION: low == ans == 14 (first TRUE = minimum largest sum)

================================================================================
*/

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int low = 0, high = 0;
        for (int num : nums) {
            low = max(low, num);    // Minimum possible: largest single element
            high += num;            // Maximum possible: entire array in one subarray
        }

        // Binary search for FIRST TRUE (minimum feasible largest sum)
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isFeasible(nums, mid, k)) {
                // mid is TRUE (feasible), but we want FIRST TRUE
                // Search LEFT half for a smaller TRUE
                high = mid - 1;
            } else {
                // mid is FALSE (not feasible), first TRUE is on RIGHT
                // Search RIGHT half
                low = mid + 1;
            }
        }

        // When loop ends:
        // - low = first TRUE (minimum feasible largest sum)
        // - high = last FALSE (one less than answer)
        // Both low and ans point to the same value: the answer!
        return low;
    }
    
    bool isFeasible(vector<int>& nums, int maxSum, int k) {
        // Greedily count how many subarrays needed if each sum <= maxSum
        int count = 1;
        int currentSum = 0;
        for (int num : nums) {
            currentSum += num;
            if (currentSum > maxSum) {
                count++;
                currentSum = num;
                if (count > k) return false;  // Need more than k subarrays -> not feasible
            }
        }
        return count <= k;  // Feasible if we can do it in k or fewer subarrays
    }
};

int main(){
    vector<int> nums = {7, 2, 5, 10, 8};
    int k = 2;
    Solution obj;

    /*
    EXAMPLE TRACE:
    =============
    nums = [7, 2, 5, 10, 8], k = 2
    low = 10 (max element), high = 32 (total sum)

    FEASIBILITY CHECK for different maxSum values:
    -----------------------------------------------
    maxSum=14: [7,2,5]=14, [10]=10, [8]=8 -> 3 subarrays -> FALSE (3 > 2)
    maxSum=15: [7,2,5]=14, [10]=10, [8]=8 -> 3 subarrays -> FALSE (3 > 2)
    maxSum=16: [7,2,5]=14, [10]=10, [8]=8 -> 3 subarrays -> FALSE (3 > 2)
    maxSum=17: [7,2,5]=14, [10]=10, [8]=8 -> 3 subarrays -> FALSE (3 > 2)
    maxSum=18: [7,2,5]=14, [10,8]=18    -> 2 subarrays -> TRUE  (2 <= 2) <-- FIRST TRUE!
    maxSum=19: [7,2,5]=14, [10,8]=18    -> 2 subarrays -> TRUE
    ...
    maxSum=32: [7,2,5,10,8]=32          -> 1 subarray  -> TRUE

    RANGE PATTERN (F=FALSE, T=TRUE):
    10  11  12  13  14  15  16  17  18  19  20 ... 32
    F   F   F   F   F   F   F   F   T   T   T  ...  T
                            |               |
                         LAST FALSE     FIRST TRUE
                            |               |
                          high=17         low=18

    Binary Search Steps:
    --------------------
    Step 1: low=10, high=32, mid=21
            isFeasible(21)? -> [7,2,5]=14, [10,8]=18 -> 2 subarrays -> TRUE
            high = 20

    Step 2: low=10, high=20, mid=15
            isFeasible(15)? -> [7,2,5]=14, [10]=10, [8]=8 -> 3 subarrays -> FALSE
            low = 16

    Step 3: low=16, high=20, mid=18
            isFeasible(18)? -> [7,2,5]=14, [10,8]=18 -> 2 subarrays -> TRUE
            high = 17

    Step 4: low=16, high=17, mid=16
            isFeasible(16)? -> [7,2,5]=14, [10]=10, [8]=8 -> 3 subarrays -> FALSE
            low = 17

    Step 5: low=17, high=17, mid=17
            isFeasible(17)? -> [7,2,5]=14, [10]=10, [8]=8 -> 3 subarrays -> FALSE
            low = 18

    Step 6: low=18, high=17 -> STOP (low > high)

    Final: low = 18 (first TRUE = answer)

    VERIFY:
    -------
    All splits and their largest sums:
    [7] [2,5,10,8]      -> max(7, 25)  = 25
    [7,2] [5,10,8]      -> max(9, 23)  = 23
    [7,2,5] [10,8]      -> max(14, 18) = 18  <-- MINIMUM = ANSWER
    [7,2,5,10] [8]      -> max(24, 8)  = 24

    Answer = 18 (confirmed!)
    */

    int result = obj.splitArray(nums, k);
    cout << "Minimum largest sum after splitting into " << k << " subarrays: " << result << endl;
    // Output should be 18
    
    return 0;
}
