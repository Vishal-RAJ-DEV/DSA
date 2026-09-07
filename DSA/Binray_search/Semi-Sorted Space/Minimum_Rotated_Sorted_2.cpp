#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
  CODE 1 — Track Minimum in `ans` variable

  INTUITION:
  - In a rotated sorted array, at least one half is always sorted.
  - We exploit this by checking which half is sorted, recording its
    minimum, and then searching the OTHER half (where the true minimum
    may hide).
  - We use an `ans` variable to accumulate the minimum found so far.

  KEY OBSERVATIONS:
  1. If nums[low] < nums[high]: the entire current range is sorted,
     so nums[low] is the minimum → done.
  2. If nums[low] == nums[mid] == nums[high]: duplicates make it
     impossible to decide which half is sorted → safely shrink both
     ends (low++, high--) to skip one duplicate from each side.
  3. If nums[low] <= nums[mid]: left half [low..mid] is sorted.
     - Minimum of left half is nums[low], record it.
     - The pivot (and thus the true minimum) must be in the RIGHT half
       → search right: low = mid + 1.
  4. Else (nums[mid] > nums[low]): right half [mid..high] is sorted.
     - Minimum of right half is nums[mid], record it.
     - The pivot must be in the LEFT half
       → search left: high = mid - 1.

  FLOW:
  Each iteration eliminates one half of the search space OR shrinks
  the range by removing duplicates, guaranteeing convergence.
*/
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int low = 0;
        int high = n - 1;
        int ans = INT_MAX;

        while( low <= high){
            int mid = low + ( high - low) /2;

            // Case 1: Entire range [low..high] is sorted.
            // nums[low] is the smallest in this range → no need to search further.
            if(nums[low] < nums[high]){
                ans = min( ans , nums[low]);
                break;
            }

            // Case 2: All three pointers see the same value → ambiguous.
            // We can't tell which half is sorted, so remove one duplicate
            // from each end and try again.
            if(nums[low] == nums[mid] && nums[mid] == nums[high]){
                ans = min(ans , nums[low]);
                low++;
                high--;
                continue;
            }

            // Case 3: Left half [low..mid] is sorted (nums[low] <= nums[mid]).
            // The minimum of the left half is nums[low] — record it.
            // The pivot (true overall minimum) is in the right half → go right.
            if(nums[low] <= nums[mid]){
                ans = min(ans , nums[low]);
                low = mid + 1;
            }
            // Case 4: Right half [mid..high] is sorted.
            // The minimum of the right half is nums[mid] — record it.
            // The pivot is in the left half → go left.
            else{
                ans = min(ans , nums[mid]);
                high = mid - 1;
            }
        }

        return ans;
    }
};


/*
  CODE 2 — Converge low and high to the minimum directly (no `ans` var)

  INTUITION:
  - Same idea as Code 1 (at least one half is sorted), but instead of
    tracking the minimum in a separate variable, we SHRINK the search
    space [low..high] until low == high, at which point that single
    element IS the minimum.

  WHY low < high (not low <= high)?
  - We want low and high to CONVERGE to the same index.
  - If we used low <= high, low could overshoot high and we'd lose
    the answer. With low < high, the loop ends exactly when low == high.

  HOW `high = mid` WORKS (CRITICAL):
  - When nums[mid] < nums[high], the minimum is somewhere in [low..mid].
  - We set high = mid (NOT mid - 1) because mid itself could BE the
    minimum. This is safe because mid < high when nums[mid] < nums[high],
    so the range still shrinks by at least 1.
  - If we did mid - 1, we might skip the actual minimum.

  HOW `low = mid + 1` WORKS:
  - When nums[mid] > nums[high], the minimum is in [mid+1..high].
  - We know mid is NOT the minimum (it's greater than nums[high]),
    so we can safely exclude it: low = mid + 1.

  DUPLICATE HANDLING:
  - When nums[mid] == nums[high], we can't determine which half
    contains the minimum. We safely discard nums[high] (high--)
    because even if nums[high] was the minimum, there's another
    equal element at mid that we'll still consider.

  WHY return nums[low]:
  - When the loop ends, low == high. That index holds the minimum
    element of the entire array.
*/
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            // nums[mid] < nums[high]: right half is sorted.
            // The minimum must be in [low..mid] (mid could BE the min).
            // Set high = mid (not mid-1!) to keep mid as a candidate.
            if (nums[mid] < nums[high]) {
                high = mid;
            }
            // nums[mid] > nums[high]: left half is sorted but the pivot
            // is in the right half [mid+1..high].
            // mid is definitely not the min → skip it.
            else if (nums[mid] > nums[high]) {
                low = mid + 1;
            }
            // nums[mid] == nums[high]: ambiguous — can't decide which side.
            // Safely remove nums[high] (duplicate of nums[mid] is still
            // in the range, so we don't miss the minimum).
            else {
                high--;
            }
        }

        // low == high → both point to the minimum element.
        return nums[low];
    }
};

int main(){
    return 0;
}