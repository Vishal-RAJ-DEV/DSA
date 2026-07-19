/*
QUESTION (LeetCode 436 — Find Right Interval):
Given an array of intervals intervals[i] = [start_i, end_i], for each interval i
find the index j of the interval that has the smallest start_j >= end_i (the
"right interval" of i). If no such interval exists, answer = -1.

You may assume start_i < end_i, and the array is not necessarily sorted.

Example:
Input:  intervals = [[3,4], [2,3], [1,2]]
Output: [-1, 0, 1]
Explanation:
  [1,2] → smallest start ≥ 2 is [2,3] at index 1
  [2,3] → smallest start ≥ 3 is [3,4] at index 0
  [3,4] → no start ≥ 4 → -1

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// APPROACH 1: Binary Search on Sorted Start Values
//
// Intuition:
//   For each interval we need the smallest start >= its end.
//   If we sort all (start, original_index) pairs by start, we
//   can binary search to find the answer for every interval.
//
// Algorithm:
//   1. Build a vector 'starts' of (start, original_index) pairs.
//   2. Sort 'starts' by start.
//   3. For each interval 'i' (original index):
//        Binary search on sorted 'starts' to find the first
//        element with start >= intervals[i][1] (its end).
//        - If found → ans[i] = starts[mid].second
//        - Otherwise → ans[i] = -1
//   4. Return ans.
//
// Dry Run:
//   intervals = [[3,4], [2,3], [1,2]]
//   starts = [(3,0), (2,1), (1,2)] → sorted = [(1,2), (2,1), (3,0)]
//
//   i=0: end=4, binary search → no start ≥ 4 → ans[0]=-1
//   i=1: end=3, binary search → start[2]=3≥3 at idx 2 → ans[1]=starts[2].second=0
//   i=2: end=2, binary search → start[1]=2≥2 at idx 1 → ans[2]=starts[1].second=1
//   Result: [-1, 0, 1] ✓
//
// Time  : O(N log N)  — sorting + binary search for each interval
// Space : O(N)         — starts vector + ans
// ============================================================

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {

        int n = (int)intervals.size();

        // Pair each start with its original index
        vector<pair<int,int>> starts(n);
        for (int i = 0; i < n; i++)
            starts[i] = {intervals[i][0], i};

        // Sort by start value (needed for binary search)
        sort(starts.begin(), starts.end());

        vector<int> ans(n, -1);

        for (int i = 0; i < n; i++) {

            int target = intervals[i][1];       // end of current interval

            // Binary search: find first start >= target
            int low = 0, high = n - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;

                if (starts[mid].first >= target) {
                    ans[i] = starts[mid].second;    // store original index
                    high = mid - 1;                 // try to find smaller start
                } else {
                    low = mid + 1;                  // need larger start
                }
            }
        }

        return ans;
    }
};


// ============================================================
// APPROACH 2: Two Pointers (Simultaneous Scan)
//
// Intuition:
//   Sort both starts and ends separately (keeping original indices).
//   Since both are sorted, we can use two pointers to match each end
//   with the nearest valid start in a single pass.
//
//   For any end, the right interval's start is the first start that
//   satisfies start >= end. As we move to larger ends, the required
//   start can only move forward (never backward) — so a single pass
//   with pointer i (on starts) works for all ends processed in order.
//
// Algorithm:
//   1. Build:
//        starts = [(start, orig_idx), ...]
//        ends   = [(end,   orig_idx), ...]
//   2. Sort both by their value.
//   3. i = 0 (pointer on starts), j = 0 (pointer on ends)
//   4. While i < n and j < n:
//        If starts[i].first >= ends[j].first:
//          → ends[j]'s interval has found its right interval
//          → ans[ends[j].second] = starts[i].second
//          → j++  (move to next end)
//        Else:
//          → i++  (this start is too small, try next larger start)
//   5. Remaining ends (if any) already have ans = -1 (default).
//   6. Return ans.
//
// Dry Run:
//   intervals = [[3,4], [2,3], [1,2]]
//   starts = [(1,2), (2,1), (3,0)]    (sorted by start)
//   ends   = [(2,2), (3,1), (4,0)]    (sorted by end)
//
//   i=0 start=(1,2)   j=0 end=(2,2)   1>=2? ✗ → i=1
//   i=1 start=(2,1)   j=0 end=(2,2)   2>=2? ✓ → ans[2]=1, j=1
//   i=1 start=(2,1)   j=1 end=(3,1)   2>=3? ✗ → i=2
//   i=2 start=(3,0)   j=1 end=(3,1)   3>=3? ✓ → ans[1]=0, j=2
//   i=2 start=(3,0)   j=2 end=(4,0)   3>=4? ✗ → i=3  (i == n → loop ends)
//
//   ans = [-1, 0, 1]  ✓
//
// Time  : O(N log N)  — dominated by sorting
// Space : O(N)
// ============================================================

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {

        int n = (int)intervals.size();

        vector<pair<int,int>> starts(n);
        vector<pair<int,int>> ends(n);

        for (int i = 0; i < n; i++) {
            starts[i] = {intervals[i][0], i};
            ends[i]   = {intervals[i][1], i};
        }

        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        vector<int> ans(n, -1);

        int i = 0;      // pointer on starts
        int j = 0;      // pointer on ends

        while (i < n && j < n) {

            if (starts[i].first >= ends[j].first) {
                // start[i] is the right interval for end[j]
                ans[ends[j].second] = starts[i].second;
                j++;                        // this end is resolved
            } else {
                i++;                        // need a larger start
            }
        }

        // Any unresolved ends already have ans = -1 (set by default)

        return ans;
    }
};


int main(){
    return 0;
}
