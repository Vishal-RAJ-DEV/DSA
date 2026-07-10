#include <bits/stdc++.h>
using namespace std;

/*
======================================================================
PROBLEM: H-Index II (LeetCode 275)
======================================================================

Given a sorted array citations[] (non-decreasing), where citations[i]
is the number of citations for the i-th paper, find the maximum h-index.

What is h-index?
  h-index = h if the researcher has at least h papers, and each of those
  h papers has at least h citations.

Constraint: Must run in O(log n) time → Binary Search.

======================================================================
KEY OBSERVATION (why Binary Search works)
======================================================================

Since the array is sorted in ascending order:

  At index i, there are exactly (n - i) papers from i to n-1 (inclusive).
  Every one of those papers has at least citations[i] citations (because
  the array is sorted — elements to the right are >= citations[i]).

So, the condition to check at any index i is:

    citations[i] >= (n - i)

If this is TRUE:
  The (n - i) papers from index i onward each have at least (n - i)
  citations. This means (n - i) is a VALID h-index.

Our goal: find the LARGEST valid h-index.

======================================================================
MONOTONIC BEHAVIOR (Binary Search Applicability)
======================================================================

citations[i] INCREASES as i increases (sorted ascending).
n - i DECREASES as i increases.

The pattern of the condition citations[i] >= n - i looks like:

    i →    0      1      2      3      4      5
    ------------------------------------------------
    citation[i]  |  0  |  1  |  3  |  5  |  6  |  8  |
    n - i        |  6  |  5  |  4  |  3  |  2  |  1  |
    condition    |  F  |  F  |  F  |  T  |  T  |  T  |
    ------------------------------------------------
                false...false → true...true   (MONOTONIC)

Since the condition transitions from false to true exactly once,
we can binary search for the FIRST index where it becomes true.

======================================================================
BINARY SEARCH ALGORITHM
======================================================================

1. Set low = 0, high = n-1, ans = 0
2. While low <= high:
     mid = low + (high - low) / 2
     papers = n - mid

     if (citations[mid] >= papers):
         // citations[mid] >= (n-mid) → papers is a valid h-index
         ans = papers          // store candidate
         high = mid - 1        // search LEFT for larger h-index
                               // (smaller i → larger n-i)
     else:
         low = mid + 1         // search RIGHT (need higher citations)

3. Return ans

Why move left when condition is true?
  If citations[mid] >= n - mid, then (n-mid) is valid.
  But we want the LARGEST valid h-index.
  Since (n - i) gets larger as i gets smaller, we search the left half.

Why move right when condition is false?
  If citations[mid] < n - mid, no valid h-index can exist here.
  We need larger citations, so go right (higher index → higher citations).

======================================================================
COMPLEXITY
======================================================================
  Time: O(log n) — Binary Search
  Space: O(1)
*/

// ============================================================
// Approach 1: Binary Search (iterative)
// ============================================================
class HIndexBinarySearch {
    /*
    * At every index mid, ask: "Can the remaining (n-mid) papers each
    * have at least (n-mid) citations?"
    *
    * If yes → (n-mid) is a valid h-index; save it and try for a larger
    *          h-index by going left (smaller mid → larger n-mid).
    * If no  → go right (need higher citations at higher indices).
    */
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        int low = 0;
        int high = n - 1;
        int ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // papers = number of papers from mid to end (n-mid papers)
            // Condition: each of these (n-mid) papers has >= (n-mid) citations
            if (citations[mid] >= n - mid) {
                // This (n-mid) is a valid h-index. Store it.
                ans = n - mid;
                // Try to find a LARGER h-index by moving LEFT.
                // Smaller index → more papers remaining → larger n-mid.
                high = mid - 1;
            } else {
                // Condition false: citations[mid] too small.
                // Need higher citations, so move RIGHT.
                low = mid + 1;
            }
        }

        return ans;
    }
};

// ============================================================
// Approach 2: Binary Search (Alternative — search on answer space)
// ============================================================
class HIndexSearchOnAnswer {
    /*
    Instead of checking citations[mid] >= n-mid, we can directly
    binary search on the h-index value itself (0 to n).

    For a candidate h, count how many papers have >= h citations.
    If count >= h, h is valid; try larger h.
    If count < h,  h is invalid; try smaller h.

    This approach works on UNSORTED arrays too (but costs O(log n * n)
    without sorting). For sorted arrays, it's still O(log n).
    */
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        int low = 0, high = n, ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Count papers with >= mid citations
            // Since array is sorted, we can use binary search for count
            int idx = lower_bound(citations.begin(), citations.end(), mid)
                      - citations.begin();
            int count = n - idx;

            if (count >= mid) {
                ans = mid;        // mid is valid
                low = mid + 1;   // try larger h
            } else {
                high = mid - 1;  // try smaller h
            }
        }

        return ans;
    }
};

int main() {
    vector<int> citations = {0, 1, 3, 5, 6, 8};

    HIndexBinarySearch sol1;
    cout << "Binary Search (citations[mid] >= n-mid): " << sol1.hIndex(citations) << endl;

    HIndexSearchOnAnswer sol2;
    cout << "Binary Search on answer: " << sol2.hIndex(citations) << endl;

    return 0;
}