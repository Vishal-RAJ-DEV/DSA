#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * Solution 1: Tracking minimum value (Alternative approach)
 * This approach tracks the minimum value found so far during binary search.
 * It's less elegant but works. See Solution 2 for the optimal approach.
 */
class Solution1 {
  public:
    int findKRotation(vector<int> &arr) {
        int n = arr.size();
        int low = 0;
        int high = n - 1;

        // Edge case: if array is already sorted (not rotated), return 0
        if (arr[0] < arr[n - 1]) {
            return 0;
        }

        int ans = 0; // Stores index of minimum element found so far

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // If left half is sorted
            if (arr[low] <= arr[mid]) {
                // Update answer if current left is smaller than recorded minimum
                if (ans < arr[low]) {
                    ans = low;
                }
                low = mid + 1; // Search right half
            }
            else {
                // Right half has the break point
                if (ans < arr[mid]) {
                    ans = mid;
                }
                high = mid - 1; // Search left half
            }
        }

        return ans;
    }
};

/*
 * Solution 2: Optimal Binary Search (Clean & Efficient)
 * ================================================
 *
 * Problem: Find the number of times a sorted array has been rotated.
 * This is equivalent to finding the INDEX of the minimum element.
 *
 * Example: [4, 5, 6, 1, 2, 3]
 *           Original sorted: [1, 2, 3, 4, 5, 6]
 *           Rotated 3 times → minimum element 1 is at index 3
 *           Answer = 3
 *
 * ================================================
 * WHY COMPARE arr[mid] WITH arr[high]?
 * ================================================
 *
 * Key Insight: In a rotated sorted array, comparing mid with high
 * tells us which side contains the minimum (rotation point).
 *
 * We compare with high (not low) because:
 *   - arr[low] could be in the rotated portion → unreliable
 *   - arr[high] is always in a predictable position relative to mid
 *
 * ================================================
 * TWO CASES:
 * ================================================
 *
 * CASE 1: arr[mid] > arr[high]
 * ----------------------------
 * The minimum MUST be to the RIGHT of mid.
 *
 * Why? Because if the array were sorted from mid to high,
 * we'd expect arr[mid] < arr[high].
 * But since arr[mid] > arr[high], the "drop" (rotation point)
 * occurs somewhere after mid.
 *
 * Visual:
 *   [  sorted  | broken ]
 *              ↑
 *             mid
 *   arr[mid] > arr[high] → minimum is to the right
 *
 * Action: low = mid + 1
 *   (We discard mid and everything to its left)
 *
 * CASE 2: arr[mid] <= arr[high]
 * -----------------------------
 * The minimum is at mid OR somewhere to the LEFT.
 *
 * Why? Because arr[mid] <= arr[high] means the right half
 * is properly sorted (no rotation point there).
 * So the rotation point must be at mid or in the left half.
 *
 * Visual:
 *   [ broken |  sorted  ]
 *            ↑
 *           mid
 *   arr[mid] <= arr[high] → minimum is at mid or left
 *
 * Action: high = mid
 *   (We keep mid because it COULD be the minimum)
 *   NOTE: We do NOT do high = mid - 1
 *         because mid itself might be the minimum!
 *
 * ================================================
 * WHY while (low < high) instead of low <= high?
 * ================================================
 *
 * We're not searching for a value and checking every position.
 * We're NARROWING DOWN to one position — the minimum.
 *
 * Eventually low == high, and that position IS the minimum.
 * So we stop when low == high and return low.
 *
 * If we used low <= high, we might overshoot and miss the minimum.
 *
 * ================================================
 * WHY return low GIVES THE ANSWER
 * ================================================
 *
 * When the loop ends (low == high), both pointers converge
 * to the INDEX of the minimum element.
 *
 * The index of the minimum element = number of rotations.
 *
 * Example: [4, 5, 6, 1, 2, 3]
 *           Minimum element 1 is at index 3
 *           → Array was rotated 3 times
 *           → return low = 3 ✓
 *
 * ================================================
 * DRY RUN: arr = [4, 5, 6, 1, 2, 3]
 * ================================================
 *
 * Index:    0   1   2   3   4   5
 * Value:    4   5   6   1   2   3
 *
 * Initial: low = 0, high = 5
 *
 * --- Iteration 1 ---
 *   mid = 0 + (5-0)/2 = 2
 *   arr[mid] = arr[2] = 6
 *   arr[high] = arr[5] = 3
 *
 *   Check: 6 > 3?  → YES (Case 1)
 *   Minimum is to the RIGHT of mid
 *   → low = mid + 1 = 3
 *
 *   Search space: [1, 2, 3]  (indices 3 to 5)
 *                  ↑     ↑
 *                 low  high
 *   We discarded [4, 5, 6] — minimum cannot be there
 *
 * --- Iteration 2 ---
 *   mid = 3 + (5-3)/2 = 4
 *   arr[mid] = arr[4] = 2
 *   arr[high] = arr[5] = 3
 *
 *   Check: 2 > 3?  → NO (Case 2)
 *   Minimum is at mid OR to the LEFT
 *   → high = mid = 4
 *
 *   Search space: [1, 2]  (indices 3 to 4)
 *                  ↑  ↑
 *                 low high
 *
 * --- Iteration 3 ---
 *   mid = 3 + (4-3)/2 = 3
 *   arr[mid] = arr[3] = 1
 *   arr[high] = arr[4] = 2
 *
 *   Check: 1 > 2?  → NO (Case 2)
 *   Minimum is at mid OR to the LEFT
 *   → high = mid = 3
 *
 *   Search space: [1]  (index 3 only)
 *                  ↑
 *               low=high
 *
 * --- Loop Check ---
 *   low = 3, high = 3
 *   while (low < high) → 3 < 3 → FALSE → Loop ends
 *
 * --- Return ---
 *   return low = 3
 *
 *   [4, 5, 6, 1, 2, 3]
 *             ↑
 *           index 3 ← minimum element 1
 *   Array was rotated 3 times ✓
 *
 * ================================================
 * ONE-LINE MENTAL MODEL 🧠
 * ================================================
 *
 * "Is mid bigger than the rightmost element?
 *  If YES  → minimum is after mid    → low = mid + 1
 *  If NO   → minimum is at mid/left  → high = mid"
 *
 * That's the entire trick!
 */
class Solution {
public:
    int findKRotation(vector<int> &arr) {
        int low = 0;
        int high = arr.size() - 1;

        // Binary search: narrow down until low == high
        // At that point, low (== high) is the index of the minimum element
        while (low < high) {
            int mid = low + (high - low) / 2;

            // CASE 1: arr[mid] > arr[high]
            // The minimum element MUST be to the RIGHT of mid.
            // Because if mid-to-high were sorted, arr[mid] would be < arr[high].
            // The "drop" (rotation point) happens after mid.
            // Discard mid and everything to its left.
            if (arr[mid] > arr[high]) {
                low = mid + 1;
            }
            // CASE 2: arr[mid] <= arr[high]
            // The right half [mid..high] is sorted.
            // So the rotation point is at mid or in the left half.
            // We keep mid because it COULD be the minimum.
            // NOTE: We do NOT do high = mid - 1, because mid might be the answer.
            else {
                high = mid;
            }
        }

        // When loop ends, low == high == index of minimum element
        // The index of minimum = number of rotations
        return low;
    }
};



int main(){
    return 0;
}