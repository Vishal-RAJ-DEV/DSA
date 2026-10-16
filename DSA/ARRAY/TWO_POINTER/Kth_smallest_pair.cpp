#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
 PROBLEM: Kth Smallest Pair Distance (LeetCode 719 style)
===============================================================================
 Given an integer array `nums` and an integer `k`, return the k-th SMALLEST
 absolute difference between any two DIFFERENT elements of the array.

 More precisely:
   - Consider every pair (nums[i], nums[j]) with 0 <= i < j < n.
   - For each pair, compute |nums[i] - nums[j]| (the absolute difference).
   - Collect all these differences, sort them in non-decreasing order.
   - Return the element at position (k-1) of that sorted list
     (i.e. k is 1-based: k=1 means the smallest difference).

 WHAT IS IT ASKING, EXACTLY?
   It is NOT asking for the actual pair. It only wants the VALUE of the
   k-th smallest distance. Equal distances each count separately
   (duplicates matter — two pairs with the same distance both occupy slots).

 EXAMPLE:
   nums = [1, 3, 1], k = 1
   All pairs (i<j):
     (0,1): |1-3| = 2
     (0,2): |1-1| = 0
     (1,2): |3-1| = 2
   Sorted differences: [0, 2, 2]
   k=1 -> answer = 0
   k=2 -> answer = 2
   k=3 -> answer = 2
===============================================================================
 APPROACH: COUNTING (FREQUENCY) ARRAY  — O(n^2 + D), D = max element
===============================================================================
 IDEA:
   The absolute difference of any pair cannot exceed the largest element
   in the array (assuming non-negative numbers), and it is always >= 0.
   So the "distance universe" is small: 0 .. maxElement.

   Step 1: Create a frequency array vec[] where vec[d] stores HOW MANY pairs
           have an absolute difference of exactly d.
   Step 2: Brute-force every pair (i<j), compute diff = |nums[i]-nums[j]|,
           and increment vec[diff].  This is O(n^2) time.
   Step 3: Walk through vec from distance = 0 upward, subtracting each
           bucket's count from k. As soon as k <= 0, the current distance
           is the k-th smallest.

 WHY THIS WORKS (intuition):
   Walking from d = 0 upward means we are visiting distances in sorted
   order (counting sort idea). Subtracting vec[d] from k is like skipping
   over that many already-counted smaller (or equal) distances.
   When k drops to 0 or below, we have "used up" all distances smaller than
   the current d, so d is the answer.

 SIMPLE WALKTHROUGH (nums = [1,3,1]):
   maxElement = 3  ->  vec has size 4 (indices 0..3)
   Pairs:
     |1-3| = 2  -> vec[2] = 1
     |1-1| = 0  -> vec[0] = 1
     |3-1| = 2  -> vec[2] = 2
   vec = [1, 0, 2, 0]

   k = 1:
     d=0: k -= vec[0]  =>  k = 1-1 = 0  -> k <= 0, return 0  ✓

   k = 2:
     d=0: k -= 1  => k = 1
     d=1: k -= 0  => k = 1
     d=2: k -= 2  => k = -1 -> return 2  ✓

 COMPLEXITY:
   Time  : O(n^2 + D)  where D = max(nums) — pair counting dominates
   Space : O(D)        for the frequency array
   NOTE  : This simple counting approach is fine when D is moderate.
           For huge value ranges, a binary-search + two-pointer solution
           is preferred (O(n log n + n log D)), but that is a different file.
===============================================================================
*/

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int n = nums.size();
        int maxele  = *max_element( nums.begin() , nums.end());
        // vec[d] stores how many pairs have absolute difference d.
        // This works because the distance range is small enough to count directly.
        vector<int>vec(maxele + 1 , 0);

        // Check every pair and count its distance.
        for( int i= 0 ; i < n ; i++){
            for( int j = i + 1 ; j < n ; j++){
                int diff = abs( nums[i] - nums[j]);
                vec[diff]++;
            }
        }

        // Walk through distances from smallest to largest.
        // Subtract each bucket size from k until k becomes <= 0.
        // The current distance is then the k-th smallest pair distance.
        for( int i = 0 ; i<= maxele ;i++){
            k -= vec[i];
            if( k <= 0){
                return i;
            }
        }

        return -1;
    }
};


/*
===============================================================================
 SECOND CODE: BINARY SEARCH ON THE ANSWER + TWO-POINTER COUNTING
 (the efficient version — same problem, O(n log n + n log D) time)
===============================================================================
 BIG IDEA:
   Instead of generating ALL pair distances and sorting them (O(n^2 log n)),
   we binary search on the ANSWER ITSELF — the distance value.

   The k-th smallest distance must lie in the range:
       low = 0                        (smallest possible difference)
       high = nums[n-1] - nums[0]     (largest possible difference, after sorting)

   For a candidate distance `mid`, we only need to know ONE thing:
       "How many pairs have distance <= mid?"
   Call this count(mid). It is monotonic:
       if mid grows, count(mid) can only grow or stay the same.

   Then:
     - If count(mid) >= k  -> the k-th smallest distance is <= mid,
                               so try smaller values: high = mid
     - If count(mid) <  k  -> even mid is too small, the answer is bigger,
                               so: low = mid + 1

   When low == high, we have pinned the exact k-th smallest distance.

---------------------------------------------------------------------------
 STEP 1: HOW count(mid) IS COMPUTED  (two pointers, O(n))
---------------------------------------------------------------------------
 After sorting the array, use a sliding window [left, right]:

   For each `right`, advance `left` while:
         nums[right] - nums[left] > mid

   When the while-loop stops, EVERY index i in [left, right-1] satisfies:
         nums[right] - nums[i] <= mid
   (sorted array => differences only shrink as i moves right).
   So `right - left` new valid pairs end at `right`.

   Sum this for all `right` => total pairs with distance <= mid.

 Example: nums = [1, 3, 6] sorted, mid = 3
   right=1 (val 3): 3-1 = 2 <= 3 -> count += 1-0 = 1   pair (1,3)
   right=2 (val 6): 6-1 = 5 > 3  -> left++ => left=1
                    6-3 = 3 <= 3 -> count += 2-1 = 1   pair (3,6)
   count(3) = 2  (pair (1,6) with distance 5 is correctly excluded)

---------------------------------------------------------------------------
 STEP 2: WHY THE BINARY SEARCH LOOP IS `while (low < high)` with `high = mid`
---------------------------------------------------------------------------
 This is the "narrow until one value remains" form:

   while (low < high):
     mid = low + (high - low) / 2      // rounds toward low
     if count(mid) >= k:  high = mid   // mid might BE the answer, keep it
     else:                low  = mid + 1

   - `high = mid` (NOT mid-1) because mid itself could already be the answer,
     so we must not throw it away.
   - The loop stops when low == high; that single remaining value is the
     smallest distance d with count(d) >= k — exactly the k-th smallest.
   - mid is floored, so when only 2 values remain (high = low+1),
     mid = low, avoiding an infinite loop.

---------------------------------------------------------------------------
 WALKTHROUGH: nums = [1, 3, 1], k = 1
---------------------------------------------------------------------------
   Sorted: [1, 1, 3]
   low = 0, high = 3 - 1 = 2

   Iteration 1: low=0, high=2, mid=1
     count(1): pairs with distance <= 1 -> only (1,1) diff 0 => count=1
     count >= k (1 >= 1) -> high = 1

   Iteration 2: low=0, high=1, mid=0
     count(0): pairs with distance <= 0 -> (1,1) diff 0 => count=1
     count >= k -> high = 0

   low == high == 0 -> return 0   (correct: distances are [0, 2, 2])

---------------------------------------------------------------------------
 COMPLEXITY vs. THE FIRST CODE ABOVE
---------------------------------------------------------------------------
   First code (counting array) : O(n^2 + D) time, O(D) space
   This code (binsearch+2ptr)  : O(n log n + n log D) time, O(1) extra space
   D = max(nums) - min(nums).
   This version scales far better when D is huge (e.g. values up to 1e6+).
===============================================================================
*/

class Solution {
public:
    // Binary search on the answer (the distance value).
    // Returns the smallest distance d such that at least k pairs have
    // distance <= d — that d is exactly the k-th smallest pair distance.
    int smallestDistancePair(vector<int>& nums, int k) {

        // Sorting is required so the two-pointer window below works:
        // after sorting, nums[right] - nums[left] grows as left moves right.
        sort(nums.begin(), nums.end());

        int n = nums.size();
        int low = 0;                        // smallest possible distance
        int high = nums[n - 1] - nums[0];   // largest possible distance

        // Narrow the search until low == high (the answer).
        while (low < high) {
            int mid = low + (high - low) / 2;   // candidate distance

            // ---- Count pairs with distance <= mid (two pointers) ----
            // Window invariant: [left, right-1] are exactly the indices i
            // with nums[right] - nums[i] <= mid.
            int count = 0;
            int left = 0;

            for (int right = 0; right < n; right++) {
                // Shrink window from left until diff fits within mid.
                while (nums[right] - nums[left] > mid) {
                    left++;
                }
                // Indices [left, right-1] all form valid pairs with right.
                count += right - left;
            }

            // ---- Decide which half to keep ----
            if (count >= k) {
                // At least k pairs fit under mid, so the k-th smallest
                // distance is mid or smaller. Keep mid (it may BE the answer).
                high = mid;
            } else {
                // Fewer than k pairs fit under mid — mid is too small.
                // The answer must be strictly larger.
                low = mid + 1;
            }
        }

        // low == high: the unique smallest distance with count >= k.
        return low;
    }
};



int main(){
    Solution sol;
    vector<int> nums = {1, 3, 1};
    int k = 1;
    int result = sol.smallestDistancePair(nums, k);
    cout << "The " << k << "-th smallest distance pair is: " << result << endl;
    
    return 0;
}
