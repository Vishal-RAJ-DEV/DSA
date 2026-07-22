/* ==========================================================================
 *  PROBLEM: Find the Median in an n×n Multiplication Table (no extra space)
 *  ==========================================================================
 *
 *  We have an n×n multiplication table (implicit, not stored):
 *
 *     1   2   3   ...   n
 *     2   4   6   ...  2n
 *     3   6   9   ...  3n
 *     ...              ...
 *     n  2n  3n   ...  n²
 *
 *  The matrix is row-wise and column-wise sorted (each row: i, 2i, ..., n*i)
 *  We need to find the MEDIAN element.
 *
 *  For an n×n matrix, total elements = n².
 *  Median position (1-indexed) = n²/2 + 1   (the (n²/2 + 1)-th smallest)
 *
 *  We cannot build the matrix (too large), so we use BINARY SEARCH ON VALUE.
 *
 * ==========================================================================
 *  INTUITION
 * ==========================================================================
 *  Instead of asking "what value is at position k?", we ask the reverse:
 *    "For a given value X, how many elements are <= X in the table?"
 *
 *  This count is MONOTONIC with respect to X:
 *    - If X increases, count(X) never decreases.
 *    - Therefore we can binary search the smallest X such that
 *      count(X) >= medianPosition.
 *
 *  Counting function count(X):
 *    For each row i (1 to n):
 *      - Row i contains: i, 2i, 3i, ..., n*i  (multiples of i)
 *      - The number of elements in row i that are <= X is:
 *            min(n, X / i)
 *      - Why?  The largest multiple of i that is <= X is  i * (X / i).
 *        The count of multiples is floor(X / i). But we cannot exceed
 *        n columns per row, so we cap at n.
 *
 *  Example: n = 3, X = 5
 *    Row 1: multiples ≤ 5  →  1,2,3,4,5  →  min(3, 5/1=5) = 3  ✓
 *    Row 2: multiples ≤ 5  →  2,4        →  min(3, 5/2=2) = 2
 *    Row 3: multiples ≤ 5  →  3          →  min(3, 5/3=1) = 1
 *    Total count = 3 + 2 + 1 = 6
 *
 * ==========================================================================
 *  BINARY SEARCH DETAILS
 * ==========================================================================
 *  - Search space: values from 1 to n²  (all possible values in the table)
 *  - For each mid, compute count(mid).
 *  - If count(mid) >= medianPosition:
 *        mid is a POSSIBLE answer (or too high). Save it and try lower.
 *        high = mid - 1
 *    Else:
 *        count(mid) < medianPosition → need bigger value.
 *        low = mid + 1
 *  - At the end, ans is the smallest value with count >= medianPosition,
 *    which IS the median.
 *
 *  Why does this give EXACTLY a value that exists in the table?
 *    - When binary search narrows down, it converges to a value that
 *      actually appears. The counting function jumps only at values
 *      that are present in the table, so the first X with count >= need
 *      is guaranteed to be an element of the table.
 *
 *  Example trace: n = 3  (table: 1 2 3 / 2 4 6 / 3 6 9)
 *    need = 9/2 + 1 = 5   (5th smallest element = median = 3)
 *
 *    low=1, high=9
 *
 *    mid=5, count(5)=6 ≥ 5 → ans=5, high=4
 *    mid=2, count(2)=3 < 5 → low=3
 *    mid=3, count(3)=5 ≥ 5 → ans=3, high=2
 *    mid=2 → low=3, loop ends.
 *    ans = 3  ✓
 *
 *  Time  Complexity: O(n log(n²)) = O(n log n)
 *        Counting takes O(n) per check × O(log(n²)) = O(log n) iterations
 *  Space Complexity: O(1)
 * ========================================================================== */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n;
    cin >> n;

    /* Median position (1-indexed) in the sorted order of all n² elements */
    ll need = (n * n) / 2 + 1;

    /* Binary search on the VALUE range of the table */
    ll low = 1;
    ll high = n * n;
    ll ans = high;

    while (low <= high) {

        ll mid = low + (high - low) / 2;   // candidate value X

        /* Count how many elements in the table are <= mid */
        ll cnt = 0;

        for (ll i = 1; i <= n; i++) {
            /* In row i, columns go: i, 2i, 3i, ..., n*i
             * Number of multiples of i that are <= mid = mid / i
             * But there are only n columns, so cap at n */
            cnt += min(n, mid / i);
        }

        if (cnt >= need) {
            /* mid is a valid candidate (or too large), try to find smaller */
            ans = mid;
            high = mid - 1;
        } else {
            /* Not enough elements ≤ mid, need a larger value */
            low = mid + 1;
        }
    }

    cout << ans;
}