#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ============================================================
   PROBLEM : SEARCH INSERT POSITION (LeetCode 35)
   Given a SORTED ascending array and a target, return the index
   where target IS (if present) or the index where it WOULD BE
   inserted to keep the array sorted. This is exactly the
   LOWER_BOUND of target: the first index i with nums[i] >= target.

   ============================================================
   MONOTONIC PROPERTY (the heart of this binary search)
   ============================================================
   Define a predicate P(i) = (nums[i] >= target) over the indices.

   For a sorted array:
       P(i) = false, false, ..., false, true, true, ..., true
                       (first "true" is the answer)

   P is MONOTONIC: once it becomes true at some index, it stays
   true for every larger index (all later elements are bigger).
   This "false...true" boundary is what binary search locates.

   The code searches for the FIRST index where P(i) is true:
     - If P(mid) is true  -> mid is a candidate, but the first
       true may be even earlier -> search LEFT (high = mid - 1).
     - If P(mid) is false -> everything before mid is also false,
       so the boundary lies to the RIGHT -> search RIGHT
       (low = mid + 1).

   When the loop ends, low has crossed high and points exactly at
   the first true index -> the insert position.

   ============================================================
   ALGORITHM (Lower-Bound Binary Search)
   ============================================================
   1. low = 0, high = n-1.
   2. While low <= high:
        mid = low + (high - low) / 2   [safe overflow-free midpoint]
        if nums[mid] >= target : high = mid - 1  (true -> go left)
        else                   : low  = mid + 1  (false -> go right)
   3. Return low  (= first index with nums[mid] >= target).

   ============================================================
   TRACE DIAGRAM : nums = [1, 3, 5, 6], target = 5
   ============================================================
     idx:  0  1  2  3
     val: [1][3][5][6]
     P  :  F  F  T  T        (first true at index 2)

     low=0 high=3 -> mid=1 ; nums[1]=3 >= 5 ? NO  -> low=2
     low=2 high=3 -> mid=2 ; nums[2]=5 >= 5 ? YES -> high=1
     loop ends (low=2 > high=1) -> return 2   CORRECT.

   ============================================================
   WHY THIS WORKS FOR EVERY CASE
   ============================================================
   - target present : returns its index (first true).
   - target absent, fits inside range : returns the position where
     it would slide in, keeping order.
   - target smaller than all : all P false -> low stays 0.
   - target bigger than all  : all P true  -> low ends at n
     (one past the last index) = correct insert position at the end.

   COMPLEXITY : Time O(log n), Space O(1).
   ============================================================ */

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();

        int low = 0;
        int high = n -1;

        while( low <= high){
            int mid = low + (high - low) / 2;

            if( nums[mid] >= target) {
                high = mid - 1;
            }else{
                low = mid + 1;
            }
        }

        return low;
    }
};





int main(){
    return 0;
}