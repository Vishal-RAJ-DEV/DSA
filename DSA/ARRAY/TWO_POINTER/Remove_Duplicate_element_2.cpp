/*
===============================================================================
 PROBLEM: Remove Duplicates from Sorted Array II  (LeetCode - 80)
===============================================================================

 PROBLEM STATEMENT:
 ------------------
 Given an integer array 'nums' sorted in non-decreasing order, remove the
 duplicates IN-PLACE such that each unique element appears AT MOST TWICE.
 The relative order of the elements must be kept the same.

 Return the number of valid elements after removal (i.e., the new logical
 length of the array). The judge then checks the first 'k' elements of
 'nums' against the expected answer.

 The function signature must stay:
     int removeDuplicates(vector<int>& nums);

 IMPORTANT CONSTRAINTS / RULES:
   1. The operation must be done IN-PLACE (no extra array allowed).
   2. We may use O(1) extra memory only.
   3. The input array IS already sorted - this is the key property we exploit.
   4. Each value may appear 0, 1, or 2 times in the final array.

 EXAMPLES:
 ---------
 Example 1:
   Input : nums = [1,1,1,2,2,3]
   Output: 5
   Result: [1,1,2,2,3,_]      (the '_' is garbage/ignored value)

 Example 2:
   Input : nums = [0,0,1,1,1,1,2,3,3]
   Output: 7
   Result: [0,0,1,1,2,3,3,_]

 Example 3:
   Input : nums = [1,1,1,1,1]
   Output: 2
   Result: [1,1,_,_,_]

-------------------------------------------------------------------------------
 DIFFERENCE FROM "REMOVE DUPLICATES I" (LeetCode - 26):
 ----------------------------------------------
 In problem 26 every element may appear only ONCE.
 In problem 80 every element may appear at most TWICE.
 So the acceptance test changes from comparing with nums[k-1]
 to comparing with nums[k-2].
===============================================================================
*/


/*
===============================================================================
 APPROACH: TWO POINTER TECHNIQUE (Slow / Fast Pointers)
===============================================================================

 We use two pointers that both move FORWARD through the array:

   i  ->  "fast" / read pointer : scans every element of the input array.
                                 It always moves one step at a time (i++).
   k  ->  "slow" / write pointer: marks the length of the valid region
                                 [0 .. k-1] that we have built so far.
                                 It only moves forward when we accept an
                                 element (k++).

 Both pointers only move to the right -> each element is looked at a
 constant number of times -> TIME COMPLEXITY = O(n), SPACE = O(1).

 WHY TWO POINTERS WORK HERE:
 ---------------------------
 Because the array is sorted, all equal values sit together in one block.
 So while reading with 'i', the already-accepted region behind 'k' always
 holds the "final answer so far", and we only need to ask:

     "Will allowing nums[i] into the answer break the 'at most twice' rule?"

===============================================================================
 INTUITION / CORE IDEA OF THE CONDITION
===============================================================================

 The tricky part is deciding: SHOULD we copy nums[i] into position k?

 Key observation:
   When we are about to write at index k, the valid part of the array is
   nums[0 .. k-1].

   If we append nums[i] at position k, then in the final array the element
   nums[i] would occupy index k, and its last two occurrences would be at
   indices (k) and (k-1) and (k-2) ... 

   More simply: after appending, the last TWO accepted values are
   nums[k-2] and nums[k-1] (if they exist).

   The count of how many times nums[i] would already appear in the answer
   if nums[k-2] == nums[i] is 2 (because the array is sorted, so equal
   values are contiguous - if the value at k-2 equals nums[i], then k-1
   also equals nums[i]).

   Therefore we ACCEPT nums[i] if and only if:

        k < 2                     -> less than 2 elements accepted so far,
                                      so we can never exceed the limit,
                                      OR
        nums[i] != nums[k - 2]    -> the value two positions behind in the
                                      answer is different, so nums[i] is a
                                      NEW value (or a 1st/2nd occurrence of
                                      a value we still have room for).

   Otherwise (k >= 2 AND nums[i] == nums[k-2]) we SKIP / reject nums[i],
   because that would make a value appear a 3rd time.

 WHY COMPARE WITH nums[k-2] AND NOT nums[k-1]?
 ---------------------------------------------
   nums[k-1] only tells us "is this a duplicate of the previous one" - that
   is enough for problem 26 (limit = 1).
   For limit = 2 we must look TWO steps back:
       - If nums[k-2] is a different value -> nums[i] is safe to add.
       - If nums[k-2] is the same value     -> we already have 2 copies,
                                               reject nums[i].
===============================================================================
*/


#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     FUNCTION: removeDuplicates
     PARAMS  : nums -> sorted vector, modified IN-PLACE
     RETURNS : k    -> new logical length (number of kept elements)
     TIME    : O(n)  - single pass, each element visited once
     SPACE   : O(1)  - only two integer variables used
    */
    int removeDuplicates(vector<int>& nums) {
        int k = 0;   // slow pointer / write index.
                     // Also represents "how many valid elements we have
                     // kept so far". The valid region is nums[0..k-1].

        // fast pointer / read index -> scans the whole input array
        for (int i = 0; i < nums.size(); i++) {

            // DECISION RULE:
            //   k < 2               -> we still have free slots
            //                          (0 or 1 element accepted yet),
            //                          so accepting anything is legal.
            //
            //   nums[i] != nums[k-2] -> the element two places before in
            //                          the answer differs from nums[i],
            //                          so nums[i] is not already present
            //                          twice -> safe to accept.
            //
            // If BOTH parts are false (k >= 2 && nums[i] == nums[k-2]),
            // nums[i] would be the 3rd copy of that value -> skip it.
            if (k < 2 || nums[i] != nums[k - 2]) {

                nums[k] = nums[i];  // copy the accepted element to the
                                    // "answer" region (in-place overwrite)
                k++;                // grow the answer by one
            }
            // else: do nothing -> the element is effectively deleted
            //       because later elements will overwrite position k.
        }

        return k;   // new length; caller only inspects nums[0..k-1]
    }
};


/*
===============================================================================
 DRY RUN / WALKTHROUGH
-------------------------------------------------------------------------------
Case: nums = [1,1,1,2,2,3]

 step | i | nums[i] | k | k<2 | nums[k-2] | condition | action   | nums (after)      | k
 ------|---|---------|---|-----|-----------|-----------|----------|-------------------|---
  1    | 0 |   1     | 0 | yes |   -       | true      | copy     | [1,1,1,2,2,3]     | 1
  2    | 1 |   1     | 1 | yes |   -       | true      | copy     | [1,1,1,2,2,3]     | 2
  3    | 2 |   1     | 2 | no  | nums[0]=1 | equal->NO | skip     | [1,1,1,2,2,3]     | 2
  4    | 3 |   2     | 2 | no  | nums[0]=1 | diff ->YES| copy     | [1,1,2,2,2,3]     | 3
  5    | 4 |   2     | 3 | no  | nums[1]=1 | diff ->YES| copy     | [1,1,2,2,2,3]     | 4
  6    | 5 |   3     | 4 | no  | nums[2]=2 | diff ->YES| copy     | [1,1,2,2,3,3]     | 5

 Final k = 5  -> answer region = [1,1,2,2,3]   (correct)
===============================================================================


===============================================================================
 EDGE CASES:
 -----------
 1) Empty array        -> loop never runs, returns 0.
 2) All elements same  -> only first two are kept, returns 2.
 3) No duplicates      -> k < 2 OR always different -> everything kept.
 4) Single element     -> k<2 is true for the first element, returns 1.

===============================================================================
 COMPARISON WITH APPROACHES:
 ---------------------------
 * Brute force: use a map to count frequencies, then rebuild array.
   -> Needs O(n) extra space, violates the O(1) constraint.
 * Two pointers (used here): exploits the sorted order, in-place, O(1).
   -> This is the optimal solution.
===============================================================================
*/




int main(){
    return 0;
}