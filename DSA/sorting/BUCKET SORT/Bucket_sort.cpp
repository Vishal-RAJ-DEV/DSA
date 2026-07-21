#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  ALGORITHM: Bucket Sort
 * ================================================================
 *  Bucket Sort is a distribution-based sorting algorithm that:
 *    1. Distributes elements into a fixed number of "buckets"
 *       based on their value range.
 *    2. Sorts each bucket individually (usually with insertion
 *       sort or the built-in sort).
 *    3. Concatenates all buckets in order.
 *
 *  COMPLEXITY:
 *    - Best / Average:  O(n + k)   where k = number of buckets
 *      (when elements are uniformly distributed)
 *    - Worst:           O(n²)      (when all elements go to one bucket)
 *    - Space:           O(n + k)
 *
 *  BEST USED WHEN:
 *    - Input is uniformly distributed over a known range
 *    - The number of buckets can be chosen appropriately
 * ================================================================
 */

void bucketSort(vector<int>& arr) {

    // ----------------------------------------------------------
    // n = number of elements to sort
    // ----------------------------------------------------------
    int n = arr.size();

    // ----------------------------------------------------------
    // mx = maximum element in the array.
    // This determines the value range [0, mx].
    // ----------------------------------------------------------
    int mx = *max_element(arr.begin(), arr.end());

    // ----------------------------------------------------------
    // bucketSize = range width each bucket covers.
    // Here we fix it at 10, meaning:
    //   bucket 0  → values [0, 9]
    //   bucket 1  → values [10, 19]
    //   bucket 2  → values [20, 29]
    //   ...
    // This is a simple heuristic. In practice, bucketSize can be
    // chosen dynamically (e.g., (mx - mn) / n).
    // ----------------------------------------------------------
    int bucketSize = 10;

    // ----------------------------------------------------------
    // bucketCount = number of buckets needed to cover [0, mx].
    // Formula: mx / bucketSize + 1
    // Example: mx=49, bucketSize=10 → 49/10+1 = 4+1 = 5 buckets
    //   (covering [0,9], [10,19], [20,29], [30,39], [40,49])
    // ----------------------------------------------------------
    int bucketCount = mx / bucketSize + 1;

    // ----------------------------------------------------------
    // buckets = vector of vectors. Each inner vector will hold
    // the elements that fall into that bucket's value range.
    // ----------------------------------------------------------
    vector<vector<int>> buckets(bucketCount);

    // ----------------------------------------------------------
    // DISTRIBUTION PHASE: Place each element into its bucket.
    //
    // idx = x / bucketSize determines which bucket x belongs to.
    //
    // Example: x=29 → 29/10 = 2 → bucket index 2 (range [20,29])
    //          x=3  → 3/10  = 0 → bucket index 0 (range [0,9])
    // ----------------------------------------------------------
    for (int x : arr) {
        int idx = x / bucketSize;
        buckets[idx].push_back(x);
    }

    // ----------------------------------------------------------
    // COLLECTION PHASE: Clear the original array, then gather
    // elements back from each bucket in order.
    //
    // For each bucket (in increasing index order):
    //   1. Sort the bucket internally (here we use std::sort).
    //   2. Append sorted bucket elements to the result array.
    //
    // Since buckets are processed in order (0, 1, 2, ...),
    // the final array is fully sorted.
    // ----------------------------------------------------------

    arr.clear();  // remove original unsorted elements

    // Process buckets from left (smallest values) to right (largest)
    for (auto& bucket : buckets) {

        // Sort elements within this bucket
        sort(bucket.begin(), bucket.end());

        // Append sorted bucket elements to the result
        for (int x : bucket)
            arr.push_back(x);
    }

    // arr is now sorted in ascending order.
}

int main() {

    // ----------------------------------------------------------
    // Example input: [29, 25, 3, 49, 9, 37, 21, 43]
    // ----------------------------------------------------------
    vector<int> arr = {29, 25, 3, 49, 9, 37, 21, 43};

    bucketSort(arr);

    // Output sorted array
    for (int x : arr)
        cout << x << " ";
    // Expected output: 3 9 21 25 29 37 43 49

    return 0;
}

/*
 * ================================================================
 *  DRY RUN
 * ================================================================
 *  Input: arr = [29, 25, 3, 49, 9, 37, 21, 43]
 *
 *  n = 8
 *  mx = 49
 *  bucketSize = 10
 *  bucketCount = 49/10 + 1 = 5
 *
 *  Bucket ranges:
 *    bucket 0: [0, 9]
 *    bucket 1: [10, 19]
 *    bucket 2: [20, 29]
 *    bucket 3: [30, 39]
 *    bucket 4: [40, 49]
 *
 *  --------------------------------------------------------------
 *  PHASE 1: DISTRIBUTION
 *  --------------------------------------------------------------
 *  x=29 → idx = 29/10 = 2 → bucket[2] = [29]
 *  x=25 → idx = 25/10 = 2 → bucket[2] = [29, 25]
 *  x=3  → idx = 3/10  = 0 → bucket[0] = [3]
 *  x=49 → idx = 49/10 = 4 → bucket[4] = [49]
 *  x=9  → idx = 9/10  = 0 → bucket[0] = [3, 9]
 *  x=37 → idx = 37/10 = 3 → bucket[3] = [37]
 *  x=21 → idx = 21/10 = 2 → bucket[2] = [29, 25, 21]
 *  x=43 → idx = 43/10 = 4 → bucket[4] = [49, 43]
 *
 *  Buckets after distribution:
 *    bucket[0] = [3, 9]
 *    bucket[1] = []
 *    bucket[2] = [29, 25, 21]
 *    bucket[3] = [37]
 *    bucket[4] = [49, 43]
 *
 *  --------------------------------------------------------------
 *  PHASE 2: SORT EACH BUCKET + CONCATENATE
 *  --------------------------------------------------------------
 *  i=0: sort([3, 9]) → [3, 9]   → arr = [3, 9]
 *  i=1: sort([])     → []       → arr = [3, 9]
 *  i=2: sort([29,25,21]) → [21,25,29] → arr = [3, 9, 21, 25, 29]
 *  i=3: sort([37])   → [37]     → arr = [3, 9, 21, 25, 29, 37]
 *  i=4: sort([49,43]) → [43,49] → arr = [3, 9, 21, 25, 29, 37, 43, 49]
 *
 *  --------------------------------------------------------------
 *  FINAL SORTED ARRAY:
 *    [3, 9, 21, 25, 29, 37, 43, 49]
 *  --------------------------------------------------------------
 *
 *  KEY OBSERVATIONS:
 *  - Bucket 1 was empty (no values in [10, 19]), which is fine.
 *  - Bucket 2 had 3 elements, bucket 4 had 2 — not perfectly
 *    uniform distribution, which is common with real data.
 *  - If distribution is highly skewed (all elements in one bucket),
 *    bucket sort degrades to O(n²) because one bucket does all the work.
 *  - The choice of bucket size (10 here) affects performance:
 *    too few buckets → large buckets → more work per sort
 *    too many buckets → wasted space, overhead of many small vectors
 * ================================================================
 */
