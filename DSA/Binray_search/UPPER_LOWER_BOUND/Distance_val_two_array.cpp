/*
QUESTION (LeetCode 1385 — Find the Distance Value Between Two Arrays):
Given two arrays arr1, arr2 and an integer d, return the distance value.

The distance value is:
  Number of elements arr1[i] such that there is NO element arr2[j]
  with |arr1[i] - arr2[j]| ≤ d.

In other words:
  For each arr1[i], check if ANY arr2[j] is "too close" (within d).
  If none is too close → count that arr1[i].

Example:
  arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
  arr1[0]=4:   |4-10|=6, |4-9|=5, |4-1|=3, |4-8|=4   → all > 2 → ✓ count
  arr1[1]=5:   |5-10|=5, |5-9|=4, |5-1|=4, |5-8|=3   → all > 2 → ✓ count
  arr1[2]=8:   |8-10|=2 ≤ 2 ✗ → NOT counted
  Output: 2

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:

        // ────────────────────────────────────────────────────────────
    // noCloseElement(arr2, start_range, end_range):
    //
    //   Returns true if NO element in arr2 lies within
    //   [start_range, end_range]. Otherwise returns false.
    //
    //   This is the core check: is arr1[i] "far enough" from
    //   every element in arr2?
    //
    // WHY BINARY SEARCH:
    //   arr2 is sorted, so we can check if ANY element falls in
    //   the interval [start, end] in O(log |arr2|) instead of O(|arr2|).
    //
    //   Binary search narrows down to find if the interval overlaps
    //   with any arr2 element.
    //
    // LOGIC:
    //   1. low=0, high=arr2.size()-1
    //   2. While low ≤ high:
    //        mid = low + (high - low) / 2
    //
    //        If arr2[mid] ∈ [start, end] → found a "too close" element
    //          → return false (this arr1[i] is INVALID / NOT counted)
    //
    //        Else if arr2[mid] < start → mid is too small, search right
    //          → low = mid + 1
    //
    //        Else (arr2[mid] > end) → mid is too large, search left
    //          → high = mid - 1
    //
    //   3. If loop ends, no element in arr2 is in [start, end]
    //      → return true (arr1[i] is VALID / counted)
    //
    // DRY RUN:
    //   arr2 = [1,8,9,10] (sorted), d = 2
    //
    //   arr1[0] = 4 → range [2, 6]
    //     mid=1: arr2[1]=8 > 6 → high=0
    //     mid=0: arr2[0]=1 < 2 → low=1
    //     low=1 > high=0 → exit → no element in [2,6] → return true ✓
    //
    //   arr1[1] = 5 → range [3, 7]
    //     mid=1: arr2[1]=8 > 7 → high=0
    //     mid=0: arr2[0]=1 < 3 → low=1
    //     low=1 > high=0 → exit → no element in [3,7] → return true ✓
    //
    //   arr1[2] = 8 → range [6, 10]
    //     mid=1: arr2[1]=8 ∈ [6,10] → return false ✗
    //
    // TIME  : O(log |arr2|) per call
    // SPACE : O(1)
    // ────────────────────────────────────────────────────────────

    bool noCloseElement(vector<int>& arr, int start, int end) {
        int low  = 0;
        int high = (int)arr.size() - 1;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            if (start <= arr[mid] && arr[mid] <= end) {
                // Found arr2[j] that satisfies |arr1[i] - arr2[j]| ≤ d
                return false;          // arr1[i] is INVALID (has a close neighbor)
            }
            else if (arr[mid] < start) {
                low = mid + 1;         // too small → search on the right
            }
            else {                     // arr[mid] > end
                high = mid - 1;        // too large → search on the left
            }
        }

        // No element in arr2 lies in [start, end]
        return true;                   // arr1[i] is VALID (far from all arr2)
    }

public:

    // ────────────────────────────────────────────────────────────
    // findTheDistanceValue
    //
    // INTUITION — HOW THE "FORBIDDEN RANGE" IS DERIVED:
    //
    //   The condition that disqualifies arr1[i] is:
    //
    //          |arr1[i] - arr2[j]| ≤ d
    //
    //   Using the absolute value property:   |x| ≤ d  ⟺  -d ≤ x ≤ d
    //
    //   Let x = arr1[i] - arr2[j]. Then:
    //
    //          -d ≤ arr1[i] - arr2[j] ≤ d
    //
    //   Solve for arr2[j]:
    //
    //     Left side:   -d ≤ arr1[i] - arr2[j]
    //                  -d - arr1[i] ≤ -arr2[j]
    //                  arr1[i] + d ≥ arr2[j]           (multiply by -1, flip inequality)
    //                  arr2[j] ≤ arr1[i] + d           ← upper bound
    //
    //     Right side:  arr1[i] - arr2[j] ≤ d
    //                  -arr2[j] ≤ d - arr1[i]
    //                  arr2[j] ≥ arr1[i] - d           (multiply by -1, flip inequality)
    //                                                     ← lower bound
    //
    //   Combining both:
    //
    //         arr1[i] - d  ≤  arr2[j]  ≤  arr1[i] + d
    //
    //   This is the "forbidden range"  [arr1[i] - d, arr1[i] + d].
    //
    //   If ANY arr2[j] falls inside this interval, arr1[i] is too close
    //   to some element in arr2 and is NOT counted.
    //
    //   Example:
    //     arr1[i] = 8, d = 2
    //     8 - 2 ≤ arr2[j] ≤ 8 + 2   →   [6, 10]
    //     If arr2 has any element ∈ [6, 10] → arr1[i]=8 is disqualified ✓
    //
    //   Since we check this for every arr1[i], we sort arr2 once and
    //   binary search each time — much faster than O(n₁ × n₂).
    //
    // ALGORITHM:
    //   1. Sort arr2 (for binary search).
    //   2. For each num in arr1:
    //        start = num - d
    //        end   = num + d
    //        if noCloseElement(arr2, start, end) == true → count++
    //   3. Return count.
    //
    // DRY RUN:
    //   arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
    //
    //   Sort arr2 → [1,8,9,10]
    //
    //   num=4: range [4-2, 4+2] = [2,6]  → no element in [2,6] → count=1
    //   num=5: range [5-2, 5+2] = [3,7]  → no element in [3,7] → count=2
    //   num=8: range [8-2, 8+2] = [6,10] → arr2[1]=8 is in [6,10] → NOT counted
    //
    //   Return 2 ✓
    //
    // TIME  : O(n₂ log n₂ + n₁ log n₂)
    //          = sort(arr2)     + binary search for each arr1[i]
    // SPACE : O(log n₂) (sorting stack) / O(1) otherwise
    // ────────────────────────────────────────────────────────────

    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {

        sort(arr2.begin(), arr2.end());          // needed for binary search

        int count = 0;

        for (int num : arr1) {
            // Forbidden range: any arr2[j] in [num-d, num+d] disqualifies num
            if (noCloseElement(arr2, num - d, num + d)) {
                count++;
            }
        }

        return count;
    }
};


int main() {
    Solution sol;

    vector<tuple<vector<int>, vector<int>, int>> tests = {
        {{4,5,8}, {10,9,1,8}, 2},           // expected 2
        {{1,4,2,3}, {-4,-3,6,10,20,30}, 3}, // expected 2
        {{2,1,100,3}, {-5,-2,10,-3,7}, 6},  // expected 1
    };

    for (auto &it: tests) {
        auto &a1 = get<0>(it);
        auto &a2 = get<1>(it);
        int d = get<2>(it);
        cout << sol.findTheDistanceValue(a1, a2, d) << "\n";
    }

    return 0;
}
