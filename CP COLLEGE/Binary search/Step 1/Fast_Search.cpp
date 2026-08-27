#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * PROBLEM: Fast Search (from CP College - Binary Search Step 1)
 * ---------------------------------------------------------------
 * Given an array of n numbers and k queries.
 * For each query (l, r), count how many elements in the array
 * fall in the range [l, r] (inclusive on both sides).
 *
 * INPUT:
 *   n = number of elements
 *   arr = n integers
 *   k = number of queries
 *   Next k lines: l r (the range for each query)
 *
 * OUTPUT:
 *   For each query, print the count of elements where l <= arr[i] <= r
 *
 * EXAMPLE:
 *   Input:
 *     6
 *     8 3 7 6 5 2
 *     3
 *     2 5
 *     3 7
 *     1 10
 *
 *   After sorting: {2, 3, 5, 6, 7, 8}
 *   Query 1: [2,5] → elements {2,3,5} → count = 3
 *   Query 2: [3,7] → elements {3,5,6,7} → count = 4
 *   Query 3: [1,10] → elements {2,3,5,6,7,8} → count = 6
 *
 *   Output: 3 4 6
 *
 * WHY THIS PROBLEM NEEDS BINARY SEARCH:
 * ---------------------------------------------------------------
 * Brute force: For each query, scan entire array → O(n * k)
 * If n=10^5 and k=10^5 → 10^10 operations → TLE!
 *
 * Binary search approach: O((n + k) * log n)
 *   - Sort once: O(n log n)
 *   - Each query: O(log n) using lower_bound and upper_bound
 *   - Total: O(n log n + k log n) → fast enough!
 *
 * KEY INSIGHT:
 * ---------------------------------------------------------------
 * Count of elements in [l, r] = (elements <= r) - (elements < l)
 *
 *   elements <= r  → upper_bound(r) gives iterator to first element > r
 *                    So: upper_bound(r) - begin = count of elements <= r
 *
 *   elements < l   → lower_bound(l) gives iterator to first element >= l
 *                    So: lower_bound(l) - begin = count of elements < l
 *
 *   Therefore: count in [l, r] = upper_bound(r) - lower_bound(l)
 *
 * VISUAL:
 *   Sorted array: {2, 3, 5, 6, 7, 8}
 *                  ↑        ↑        ↑
 *                begin   lower(l)  upper(r)
 *
 *   Elements in [l, r] = upper(r) - lower(l)
 *                      = (pointer distance between the two iterators)
 *
 * LOWER_BOUND vs UPPER_BOUND:
 * ---------------------------------------------------------------
 *   lower_bound(l) → first element >= l  (start of range)
 *   upper_bound(r) → first element > r   (one past end of range)
 *
 *   So the range [lower_bound(l), upper_bound(r)) contains
 *   exactly the elements where l <= x <= r
 */

int main() {
    int n;
    cin >> n;

    vector<long long> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // SORT is required for binary search to work
    // Without sorting, lower_bound and upper_bound give wrong results
    sort(arr.begin(), arr.end());

    int k;
    cin >> k;

    // Process each query independently
    while (k--) {
        long long l, r;
        cin >> l >> r;

        // lower_bound(l) = first element >= l
        // This is the START of our range [l, r]
        auto left = lower_bound(arr.begin(), arr.end(), l);

        // upper_bound(r) = first element > r
        // This is ONE PAST the end of our range [l, r]
        auto right = upper_bound(arr.begin(), arr.end(), r);

        // Count = distance from left to right
        // In C++, subtracting iterators gives the number of elements between them
        // This gives us exactly the count of elements where l <= arr[i] <= r
        cout << right - left << " ";
    }

    return 0;
}