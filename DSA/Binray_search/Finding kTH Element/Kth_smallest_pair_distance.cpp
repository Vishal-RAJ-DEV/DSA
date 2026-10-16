/*
===============================================================================
 PROBLEM: Kth Smallest Pair Distance (LeetCode 719 style)
===============================================================================
 Given an integer array `nums` and an integer `k`, return the k-th SMALLEST
 absolute difference between any two different elements of the array.

 Example: nums = [1, 3, 6], k = 2
   Sorted: [1, 3, 6]
   Pair distances: |1-3|=2, |1-6|=5, |3-6|=3
   Sorted distances: [2, 3, 5]
   k=2 -> answer = 3

===============================================================================
 KEY IDEA: BINARY SEARCH ON THE ANSWER (not on the index)
===============================================================================
 Generating all n*(n-1)/2 distances and sorting them is O(n^2 log n) and
 needs O(n^2) memory. Too slow for large n.

 Instead we ask a DIFFERENT question:
   "How many pairs have a distance <= X?"
 If we can answer that FAST, we can binary-search on X itself:

   - The answer always lies in [0, max(nums) - min(nums)].
   - Define feasible(X) = (number of pairs with distance <= X) >= k.
     feasible(X) is monotonic: if it's true for X, it's true for every
     larger X too (a bigger threshold can only include MORE pairs).
   - Binary search finds the SMALLEST X where feasible(X) is true.
     That X is exactly the k-th smallest distance.

 WHY?
   Sort the distances: d1 <= d2 <= ... <= dN. The k-th smallest is dk.
   Count(X) = #{pairs : distance <= X}.
   - If X < dk, then Count(X) < k   (fewer than k distances fit under X).
   - If X >= dk, then Count(X) >= k (at least the first k distances fit).
   So the smallest X with Count(X) >= k is exactly dk.

===============================================================================
 STEP 1: COUNT PAIRS WITH DISTANCE <= mid   — TWO POINTERS, O(n)
===============================================================================
 First SORT the array. Then use a sliding window [left, right]:

   For each right endpoint, advance left while:
        nums[right] - nums[left] > mid
   Once the while-loop stops, EVERY element in [left, right-1] satisfies
   nums[right] - nums[i] <= mid  (array is sorted, so differences only
   shrink as we move left -> right). That gives (right - left) valid pairs
   ending at `right`. Sum this over all right.

 Example, nums = [1, 3, 6], mid = 3:
   right=1 (val 3): left stays 0, |3-1|=2 <= 3  -> count += 1-0 = 1  pair (1,3)
   right=2 (val 6): |6-1|=5 > 3 so left++ -> left=1; |6-3|=3 <= 3
                     -> count += 2-1 = 1  pair (3,6)
   Total Count(3) = 2 pairs. Correct (the pair (1,6) with distance 5 is excluded).

 Complexity of one count call: O(n) time, O(1) extra space.

===============================================================================
 STEP 2: BINARY SEARCH TO NARROW THE ANSWER
===============================================================================
   low  = 0                      (smallest possible distance)
   high = max(nums) - min(nums)  (largest possible distance)

   while (low <= high):
     mid = low + (high - low) / 2          (avoids overflow)

     if Count(mid) >= k:                    // mid could be the answer
         // But a SMALLER distance might also satisfy >= k, so try lower.
         high = mid - 1
     else:                                  // mid is too small
         // The k-th distance must be bigger than mid.
         low = mid + 1

   When the loop ends, low = high + 1, and `low` is the smallest distance
   for which Count(low) >= k -> that is the k-th smallest distance.

===============================================================================
 COMPLEXITY
===============================================================================
   Time  : O(n log n + n log D)
           - O(n log n) to sort
           - O(log D) binary search steps, each calling countPairs in O(n)
           where D = max(nums) - min(nums)
   Space : O(1) extra (sorting may use O(log n) internally)

 Compare with the counting-array approach in
 DSA\\ARRAY\\TWO_POINTER\\Kth_smallest_pair.cpp:
   that one is O(n^2 + D) — simple, but fails when D (value range) is huge.
   This binary-search approach works even for very large values.
===============================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Count how many pairs have distance <= mid.
    // REQUIRES nums to be SORTED. Uses two pointers (sliding window).
    //
    // Invariant for a fixed right: [left, right-1] are exactly the indices
    // i such that nums[right] - nums[i] <= mid. Because the array is sorted,
    // if nums[right]-nums[left] > mid we just move left forward — no need
    // to ever move left backward, so the whole scan is O(n).
    int countPairs(vector<int>& nums, int mid) {
        int count = 0;
        int left = 0;

        for (int right = 0; right < nums.size(); right++) {

            // Shrink the window from the left until the difference
            // nums[right] - nums[left] is within the allowed limit.
            while (nums[right] - nums[left] > mid) {
                left++;
            }

            // Every index i in [left, right-1] forms a valid pair (i, right)
            // because nums[right] - nums[i] <= mid.
            // Number of such indices = right - left.
            count += right - left;
        }

        return count;
    }

    int smallestDistancePair(vector<int>& nums, int k) {

        // Sorting enables the two-pointer counting trick.
        sort(nums.begin(), nums.end());

        // The k-th smallest distance must lie in this range.
        int low = 0;
        int high = nums.back() - nums.front();

        // Binary search on the ANSWER VALUE (the distance itself).
        // We are looking for the smallest distance d such that
        // at least k pairs have distance <= d.
        while (low <= high) {

            int mid = low + (high - low) / 2;

            // If at least k pairs have distance <= mid,
            // mid (or something smaller) can still be the answer,
            // so search the left half.
            if (countPairs(nums, mid) >= k) {
                high = mid - 1;
            }

            // Fewer than k pairs fit under mid, so the true k-th
            // smallest distance must be larger than mid.
            else {
                low = mid + 1;
            }
        }

        // Loop ends when low == high + 1.
        // `low` is the smallest distance with Count(low) >= k,
        // i.e. exactly the k-th smallest pair distance.
        return low;
    }
};



int main(){
    Solution sol;
    vector<int> nums = {1, 3, 6};
    int k = 2;
    int result = sol.smallestDistancePair(nums, k);
    cout << "The " << k << "-th smallest distance pair is: " << result << endl;
    // Expected: distances are [2, 3, 5] -> 2nd smallest = 3
    return 0;
}