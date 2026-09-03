/*
 * Problem: Search in Rotated Sorted Array II (with Duplicates)
 *
 * Given an integer array sorted in ascending order (may contain duplicates)
 * that is rotated at an unknown pivot, search for target value k.
 * Return true if k is present, false otherwise.
 *
 * Original sorted:  [1, 2, 3, 3, 3, 4, 5, 6, 7, 8]
 * After rotation:   [7, 8, 1, 2, 3, 3, 3, 4, 5, 6]
 *                    pivot^
 *
 * Example 1: arr = [7, 8, 1, 2, 3, 3, 3, 4, 5, 6], k = 3  -> True
 * Example 2: arr = [7, 8, 1, 2, 3, 3, 3, 4, 5, 6], k = 10 -> False
 *
 * Approach: Modified Binary Search
 * --------------------------------
 * Key Insight: At any mid point, at least ONE half of the array is always sorted.
 *   - If arr[low] <= arr[mid]: LEFT half [low..mid] is sorted
 *   - Else: RIGHT half [mid..high] is sorted
 *
 * Why? Because rotation only creates ONE "break" in the sorted order.
 * So between low and mid, or mid and high, at most one break exists.
 *
 * Algorithm:
 *   1. Standard binary search with low and high pointers.
 *   2. If arr[mid] == k: found it, return true.
 *   3. DUPLICATE EDGE CASE: If arr[low] == arr[mid] == arr[high]:
 *      - We CANNOT determine which half is sorted (all three are same).
 *      - Solution: Shrink search space from both ends by 1.
 *      - This is safe because we already checked arr[mid] != k.
 *   4. If LEFT half is sorted (arr[low] <= arr[mid]):
 *      - Check if k lies in range [arr[low], arr[mid]]
 *      - If yes: search left (high = mid - 1)
 *      - If no:  search right (low = mid + 1)
 *   5. If RIGHT half is sorted:
 *      - Check if k lies in range [arr[mid], arr[high]]
 *      - If yes: search right (low = mid + 1)
 *      - If no:  search left (high = mid - 1)
 *
 * Time Complexity:
 *   - Best/Average: O(log n)
 *   - Worst (all duplicates): O(n) — when we keep shrinking by 1
 * Space Complexity: O(1)
 *
 * ============================================
 * DRY RUN 1: arr = [7, 8, 1, 2, 3, 3, 3, 4, 5, 6], k = 3
 * ============================================
 *
 * Initial: low=0, high=9
 *
 * Iteration 1:
 *   mid = (0+9)/2 = 4
 *   arr[4] = 3 == k → return TRUE
 *
 * Result: FOUND (in 1 step)
 *
 * ============================================
 * DRY RUN 2: arr = [7, 8, 1, 2, 3, 3, 3, 4, 5, 6], k = 10
 * ============================================
 *
 * Initial: low=0, high=9
 *
 * Iteration 1:
 *   mid = 4, arr[4] = 3 ≠ 10
 *   arr[low]=7, arr[mid]=3 → 7 <= 3 is FALSE → RIGHT half is sorted
 *   k=10 in [arr[mid]=3, arr[high]=6]? 10 in [3,6]? NO
 *   → search LEFT: high = mid - 1 = 3
 *
 * Iteration 2:
 *   low=0, high=3, mid=1, arr[1] = 8 ≠ 10
 *   arr[low]=7, arr[mid]=8 → 7 <= 8 is TRUE → LEFT half is sorted
 *   k=10 in [arr[low]=7, arr[mid]=8]? 10 in [7,8]? NO
 *   → search RIGHT: low = mid + 1 = 2
 *
 * Iteration 3:
 *   low=2, high=3, mid=2, arr[2] = 1 ≠ 10
 *   arr[low]=1, arr[mid]=1 → 1 <= 1 is TRUE → LEFT half is sorted
 *   k=10 in [arr[low]=1, arr[mid]=1]? 10 in [1,1]? NO
 *   → search RIGHT: low = mid + 1 = 3
 *
 * Iteration 4:
 *   low=3, high=3, mid=3, arr[3] = 2 ≠ 10
 *   arr[low]=2, arr[mid]=2 → 2 <= 2 is TRUE → LEFT half is sorted
 *   k=10 in [arr[low]=2, arr[mid]=2]? 10 in [2,2]? NO
 *   → search RIGHT: low = mid + 1 = 4
 *
 * low=4 > high=3 → loop ends → return FALSE
 *
 * Result: NOT FOUND
 *
 * ============================================
 * DRY RUN 3 (Duplicate Edge Case):
 * arr = [3, 1, 2, 3, 3, 3], k = 1
 * ============================================
 *
 * Initial: low=0, high=5
 *
 * Iteration 1:
 *   mid = 2, arr[2] = 2 ≠ 1
 *   arr[low]=3, arr[mid]=2 → 3 <= 2 is FALSE → RIGHT half is sorted
 *   k=1 in [arr[mid]=2, arr[high]=3]? 1 in [2,3]? NO
 *   → search LEFT: high = mid - 1 = 1
 *
 * Iteration 2:
 *   low=0, high=1, mid=0, arr[0] = 3 ≠ 1
 *   arr[low]=3, arr[mid]=3 → 3 <= 3 is TRUE → LEFT half is sorted
 *   k=1 in [arr[low]=3, arr[mid]=3]? 1 in [3,3]? NO
 *   → search RIGHT: low = mid + 1 = 1
 *
 * Iteration 3:
 *   low=1, high=1, mid=1, arr[1] = 1 == k → return TRUE
 *
 * Result: FOUND
 */

#include <bits/stdc++.h>
using namespace std;

bool searchInARotatedSortedArrayII(vector<int>&arr, int k) {
    int n = arr.size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        // Case 1: Target found at mid
        if (arr[mid] == k) return true;

        // Case 2: DUPLICATE EDGE CASE
        // When arr[low] == arr[mid] == arr[high], we cannot determine
        // which half is sorted. All three pointers have same value.
        // Solution: shrink the search space from both ends by 1.
        // This is safe because we already checked arr[mid] != k above.
        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low = low + 1;
            high = high - 1;
            continue; // Skip to next iteration, skip the rest of the logic
        }

        // Case 3: LEFT half [low..mid] is sorted
        // This is true when arr[low] <= arr[mid]
        // (no rotation point in the left half)
        if (arr[low] <= arr[mid]) {
            // Check if target lies within the sorted left half
            if (arr[low] <= k && k <= arr[mid]) {
                // Target is in left half → narrow search to left
                high = mid - 1;
            }
            else {
                // Target is NOT in left half → search right half
                low = mid + 1;
            }
        }
        // Case 4: RIGHT half [mid..high] is sorted
        // This means rotation point is in the left half
        else {
            // Check if target lies within the sorted right half
            if (arr[mid] <= k && k <= arr[high]) {
                // Target is in right half → narrow search to right
                low = mid + 1;
            }
            else {
                // Target is NOT in right half → search left half
                high = mid - 1;
            }
        }
    }

    // Target not found after exhaustive search
    return false;
}

int main()
{
    vector<int> arr = {7, 8, 1, 2, 3, 3, 3, 4, 5, 6};
    int k = 3;
    bool ans = searchInARotatedSortedArrayII(arr, k);
    if (!ans)
        cout << "Target is not present.\n";
    else
        cout << "Target is present in the array.\n";
    return 0;
}

