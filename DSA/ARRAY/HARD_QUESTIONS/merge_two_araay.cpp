#include <iostream>
#include <vector>
using namespace std;

/*
===========================================================================
PROBLEM: Merge Two Sorted Arrays (In-Place / Gap Method)
===========================================================================
Given two sorted arrays nums1 and nums2, merge them into a single
sorted array. The approach uses the "Gap Method" (Shell Sort technique)
to sort the concatenated array without needing a separate merge step.

Example:
  nums1 = [1, 4, 8, 10]    (sorted)
  nums2 = [2, 3, 9]        (sorted)
  Merged = [1, 2, 3, 4, 8, 9, 10]

===========================================================================

===========================================================================
ALGORITHM: GAP METHOD (INSPIRED BY SHELL SORT)
===========================================================================

INTUITION:
  Instead of merging two arrays using the classic two-pointer merge
  (which needs O(m+n) extra space), we:
    1. Concatenate both arrays into one array
    2. Use Shell Sort's gap-based comparison to sort it in-place

  Shell Sort works by comparing elements that are `gap` apart, swapping
  if they're out of order, then reducing the gap. After gap reaches 1,
  the array is fully sorted.

  Key formula: gap = ceil(gap/2) each iteration
    Implemented as: gap = (gap / 2) + (gap % 2)

DRY RUN for nums1 = [1, 4, 8, 10], nums2 = [2, 3, 9]:

  merged = [1, 4, 8, 10, 2, 3, 9], len = 7
  Initial gap = ceil(7/2) = 4

  ──────────────────────────────────────────────────────────
  GAP = 4:
    Compare pairs (left, right) where right = left + 4:
      (0,4): 1 vs 2 → 1 < 2, no swap
      (1,5): 4 vs 3 → 4 > 3, SWAP  → [1, 3, 8, 10, 2, 4, 9]
      (2,6): 8 vs 9 → 8 < 9, no swap
    New gap = ceil(4/2) = 2

  ──────────────────────────────────────────────────────────
  GAP = 2:
    Compare pairs (left, right) where right = left + 2:
      (0,2): 1 vs 8 → no swap
      (1,3): 3 vs 10 → no swap
      (2,4): 8 vs 2 → 8 > 2, SWAP  → [1, 3, 2, 10, 8, 4, 9]
      (3,5): 10 vs 4 → 10 > 4, SWAP → [1, 3, 2, 4, 8, 10, 9]
      (4,6): 8 vs 9 → no swap
    New gap = ceil(2/2) = 1

  ──────────────────────────────────────────────────────────
  GAP = 1 (final pass — standard bubble/insertion sort):
    Compare adjacent pairs:
      (0,1): 1 vs 3 → no swap
      (1,2): 3 vs 2 → 3 > 2, SWAP  → [1, 2, 3, 4, 8, 10, 9]
      (2,3): 3 vs 4 → no swap
      (3,4): 4 vs 8 → no swap
      (4,5): 8 vs 10 → no swap
      (5,6): 10 vs 9 → 10 > 9, SWAP → [1, 2, 3, 4, 8, 9, 10]
    gap == 1 → break

  Final merged = [1, 2, 3, 4, 8, 9, 10] ✓

TIME:  O((m+n) × log(m+n)) — log(m+n) gap values, each pass is O(m+n)
SPACE: O(m+n) for the temporary merged array
===========================================================================

*/

void merge(vector<long long>& nums1, vector<long long>& nums2) {
    int m = nums1.size(), n = nums2.size();
    int len = m + n;

    // Step 1: Concatenate both arrays into a single merged array
    vector<long long> merged(len);
    for (int i = 0; i < m; i++) merged[i] = nums1[i];
    for (int i = 0; i < n; i++) merged[m + i] = nums2[i];

    // Step 2: Initialize gap to ceil(len/2)
    // (gap / 2) + (gap % 2) is a way to compute ceiling division
    int gap = (len / 2) + (len % 2);

    // Step 3: Shell Sort — compare elements `gap` apart, swap if out of order
    while (gap > 0) {
        int left = 0, right = left + gap;

        // Compare all pairs separated by `gap`
        while (right < len) {
            if (merged[left] > merged[right]) {
                swap(merged[left], merged[right]);
            }
            left++;
            right++;
        }

        // Stop after gap=1 pass is complete
        if (gap == 1) break;

        // Reduce gap: ceil(gap / 2)
        gap = (gap / 2) + (gap % 2);
    }

    // Step 4: Print the sorted merged array
    for (int i = 0; i < len; i++) cout << merged[i] << " ";
    cout << endl;
}

int main() {
    vector<long long> arr1 = {1, 4, 8, 10};
    vector<long long> arr2 = {2, 3, 9};

    cout << "Merged array: ";
    merge(arr1, arr2);
    for(auto it : arr1) cout<<it<<" ";
    cout<<endl;
    for(auto it : arr2) cout<<it<<" ";
    cout<<endl;
    return 0;
}
