#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
  MOUNTAIN ARRAY — LeetCode 1095

  A mountain array is defined as:
    - arr[0] < arr[1] < ... < arr[peak] (strictly increasing)
    - arr[peak] > arr[peak+1] > ... > arr[n-1] (strictly decreasing)
    - The peak element is the maximum element in the array.

  The MountainArray interface provides:
    - get(index)   → returns the element at the given index
    - length()     → returns the length of the array
  We are NOT given the actual array — we can only query via get().
  This means we CANNOT access arr[i] directly; every access costs a call.

  PROBLEM:
  Find the index of `target` in the mountain array. If not found, return -1.
  If the target appears twice, return the smaller index.

  APPROACH — 3-step Binary Search:
  1. FIND THE PEAK: The array goes up then down. The peak is where the
     direction changes. We binary search for it.
  2. SEARCH LEFT HALF (increasing part): The left half [0..peak] is
     sorted in ascending order → standard binary search.
  3. SEARCH RIGHT HALF (decreasing part): The right half [peak+1..n-1]
     is sorted in descending order → binary search with flipped logic.

  WHY 3 STEPS?
  - A normal binary search only works on monotonic arrays.
  - By splitting at the peak, we get two monotonic halves, each
    searchable with standard binary search.
  - We search the left half FIRST to return the smallest index
    if the target exists in both halves (problem requirement).
*/

// --------------------------------------------------
// MountainArray class — wrapper around a vector.
// In the actual LeetCode problem, this is provided
// by the judge. We define it here for local testing.
// --------------------------------------------------
class MountainArray {
private:
    vector<int> arr;
public:
    MountainArray(vector<int> a) : arr(a) {}

    // Return the element at the given index.
    int get(int index) {
        return arr[index];
    }

    // Return the length of the mountain array.
    int length() {
        return arr.size();
    }
};


class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {

        int n = mountainArr.length();

        // ==================================================
        // STEP 1: Find the peak index of the mountain array.
        //
        // The array increases up to the peak, then decreases.
        // We compare mid with mid+1:
        //   - If arr[mid] < arr[mid+1]: we're on the ascending
        //     slope, so the peak is to the RIGHT of mid.
        //   - Otherwise: we're on or past the peak, so the peak
        //     is at mid or to its LEFT.
        //
        // We use `low < high` (not <=) so low and high converge
        // to exactly the peak index.
        // ==================================================
        int low = 0;
        int high = n - 1;

        while (low < high) {

            int mid = low + (high - low) / 2;

            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                // Ascending slope → peak is to the right
                low = mid + 1;
            }
            else {
                // Descending slope or at peak → peak is at mid or left
                high = mid;
            }
        }

        // low == high == peak index
        int peak = low;


        // ==================================================
        // STEP 2: Binary search in the LEFT (increasing) half.
        //
        // Range: [0 .. peak] — strictly increasing.
        // This is a standard ascending binary search:
        //   - If mid value == target → found, return index.
        //   - If mid value <  target → target is to the right.
        //   - If mid value >  target → target is to the left.
        //
        // We search the left half FIRST because if the target
        // appears in both halves, we need the smaller index.
        // ==================================================
        low = 0;
        high = peak;

        while (low <= high) {

            int mid = low + (high - low) / 2;
            int value = mountainArr.get(mid);

            if (value == target) {
                return mid;
            }
            else if (value < target) {
                // Target is larger → search right
                low = mid + 1;
            }
            else {
                // Target is smaller → search left
                high = mid - 1;
            }
        }


        // ==================================================
        // STEP 3: Binary search in the RIGHT (decreasing) half.
        //
        // Range: [peak+1 .. n-1] — strictly decreasing.
        // The binary search logic is FLIPPED:
        //   - If mid value == target → found, return index.
        //   - If mid value <  target → target must be to the LEFT
        //     (because values decrease to the right, so smaller
        //     values are farther right — target can't be there).
        //   - If mid value >  target → target must be to the RIGHT
        //     (larger values are to the left, smaller to the right,
        //     so target is somewhere in between).
        // ==================================================
        low = peak + 1;
        high = n - 1;

        while (low <= high) {

            int mid = low + (high - low) / 2;
            int value = mountainArr.get(mid);

            if (value == target) {
                return mid;
            }
            else if (value < target) {
                // In a decreasing array, values to the right are even smaller
                // → target must be to the left
                high = mid - 1;
            }
            else {
                // value > target → in a decreasing array, values to the left
                // are larger, values to the right are smaller
                // → target is somewhere to the right
                low = mid + 1;
            }
        }

        // Target not found in either half.
        return -1;
    }
};


int main(){
    // Local testing example:
    // Mountain array: [1, 2, 3, 4, 5, 3, 1]
    // Peak = 4 (index 4, value 5)
    // Searching for target = 3 → should return index 2 (first occurrence)
    MountainArray ma({1, 2, 3, 4, 5, 3, 1});
    Solution sol;
    cout << "Index of 3: " << sol.findInMountainArray(3, ma) << endl;  // Output: 2

    cout << "Index of 5: " << sol.findInMountainArray(5, ma) << endl;  // Output: 4
    cout << "Index of 0: " << sol.findInMountainArray(0, ma) << endl;  // Output: -1

    return 0;
}