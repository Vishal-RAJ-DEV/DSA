/*
================================================================================
PROBLEM: Kth Smallest Sum in Row-Sorted Matrix
================================================================================

Given an m x n matrix where each ROW is sorted in non-decreasing order,
pick exactly one element from each row. The sum of these m elements forms
a total. Find the kth smallest possible total among all combinations.

Example: mat = [[1,3,11], [2,4,6], [5,8,9]], k = 3
  All possible sums:
    1+2+5=8, 1+2+8=11, 1+2+9=12, 1+4+5=10, 1+4+8=13, 1+4+9=14,
    1+6+5=12, 1+6+8=15, 1+6+9=16, 3+2+5=10, ...
  Sorted: [8, 10, 10, 11, 12, 12, 13, ...]
  Answer: 11 (3rd smallest)

================================================================================
THIS CODE: Binary Search + DFS Counting
================================================================================

HOW IT WORKS:
  1. Binary search on the answer (possible sum range).
     - low  = sum of first elements of each row (minimum possible sum).
     - high = sum of last elements of each row (maximum possible sum).

  2. For each candidate 'mid', count how many combinations have sum <= mid
     using DFS (countWays function).

  3. If count >= k → the kth smallest is <= mid, search lower.
     If count < k  → the kth smallest is > mid, search higher.

  4. When low == high, that's the answer.

countWays(mat, row, remaining):
  - Base case: if row == m, we picked from all rows → 1 valid combination.
  - For current row, try each element j:
      If mat[row][j] > remaining → break (row is sorted, rest are larger too).
      Recurse to next row with remaining -= mat[row][j].
  - Early exit: if count already >= k, stop (we only need to know if >= k).

WHY BINARY SEARCH WORKS HERE:
  - Let f(x) = number of combinations with sum <= x.
  - f(x) is non-decreasing (larger x → more combinations qualify).
  - We want the smallest x where f(x) >= k. That x is the kth smallest sum.

================================================================================
WHY THIS GETS TLE (Time Limit Exceeded) ON LEETCODE
================================================================================

PROBLEM: countWays is a RECURSIVE DFS with NO MEMOIZATION.

Worst case: m rows, n columns each.
  - At each row, we branch into up to n choices.
  - Total recursive calls ≈ O(n^m) in the worst case.
  - For m=7, n=7: up to 7^7 = 823,543 calls PER binary search iteration.
  - Binary search does ~30 iterations (sum range up to 7*1000 = 7000).
  - Total ≈ 30 * 823,543 ≈ 24 million operations — too slow for LeetCode.

THE SPECIFIC ISSUE:
  - No overlapping subproblems are cached, so the same state is recomputed.
  - The pruning (break when sum > remaining, early exit when count >= k)
    helps in practice but doesn't change the worst-case complexity.
  - With constraints m=7, n=7, k=21, this CAN pass but is borderline.
  - With larger inputs or stricter time limits, it TLEs.

================================================================================
WHY HEAP APPROACH IS BETTER
================================================================================

HEAP APPROACH (row-by-row merge with max-heap):
  - Instead of counting via DFS, we BUILD the k smallest sums directly.
  - Start with row 0 sums. For each next row, combine and keep only k smallest.
  - Use a max-heap of size k as a filter.

COMPLEXITY COMPARISON:
  Current (DFS):    O(n^m * log(sum_range))  — exponential in m
  Heap approach:    O(m * k * n * log k)      — linear in m, depends on k

WHEN HEAP IS BETTER:
  - When k is small (e.g., k=21), the heap processes only 21 candidates per row.
  - The DFS explores ALL combinations up to the threshold, which can be huge.
  - Heap approach: for each of m rows, for each of k sums, try n elements = m*k*n.
    With k=21, m=7, n=7: only 7*21*7 = 1029 operations — WAY faster.

WHEN DFS MIGHT BE BETTER:
  - When k is very large (close to n^m), the DFS with pruning can count quickly
    without enumerating. But for small k, heap wins.

BOTTOM LINE: For this problem (m<=7, n<=7, k<=21), the heap approach is the
standard and preferred solution. The DFS approach works but is fragile and
can TLE depending on test cases.

================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int m, n, k;

    /*
    --------------------------------------------------------------------------------
    countWays(mat, row, remaining): Count combinations with sum <= remaining
    --------------------------------------------------------------------------------

    Recursive DFS that tries picking one element from each row starting at 'row'.
    - At each row, iterate through elements (sorted, so break early if too big).
    - Subtract chosen element from 'remaining' budget and recurse to next row.
    - When all rows are processed (row == m), we found 1 valid combination.

    The count tells us: "how many combinations have sum <= remaining?"
    This is used by binary search to decide which half to search.

    EARLY PRUNING:
      1. break when mat[row][j] > remaining (row is sorted, no point trying bigger).
      2. return early if count >= k (we only care if count >= k, not exact number).
    --------------------------------------------------------------------------------
    */
    int countWays(vector<vector<int>>& mat, int row, int remaining) {
        if (row == m)
            return 1;  // picked one from each row → 1 valid combination

        int count = 0;

        for (int j = 0; j < n; j++) {
            if (mat[row][j] > remaining)
                break;  // row is sorted, all further elements are even larger

            // Pick mat[row][j] and recurse for remaining rows
            count += countWays(mat, row + 1, remaining - mat[row][j]);

            if (count >= k)
                return k;  // no need to count further, we already know answer >= k
        }

        return count;
    }

    /*
    --------------------------------------------------------------------------------
    kthSmallest(mat, k): Binary search on the answer
    --------------------------------------------------------------------------------

    BINARY SEARCH:
      - low  = minimum possible sum (first element of each row).
      - high = maximum possible sum (last element of each row).
      - For each mid, countWays tells us how many combinations have sum <= mid.
      - If count >= k → kth smallest is <= mid → search lower half.
      - If count < k  → kth smallest is > mid  → search upper half.

    When low == high, that value is the kth smallest sum because:
      - At least k combinations have sum <= low.
      - Fewer than k combinations have sum < low.
      - So low is exactly the kth smallest.
    --------------------------------------------------------------------------------
    */
    int kthSmallest(vector<vector<int>>& mat, int k) {
        this->m = mat.size();
        this->n = mat[0].size();
        this->k = k;

        int low = 0;
        int high = 0;

        // Calculate min and max possible sums
        for (int i = 0; i < m; i++) {
            low += mat[i][0];      // smallest element from each row
            high += mat[i][n - 1]; // largest element from each row
        }

        // Binary search on the answer (sum value)
        while (low < high) {
            int mid = low + (high - low) / 2;

            // Count combinations with sum <= mid
            if (countWays(mat, 0, mid) >= k)
                high = mid;   // kth smallest is <= mid
            else
                low = mid + 1; // kth smallest is > mid
        }

        return low; // low == high == kth smallest sum
    }
};



int main(){
    return 0;
}