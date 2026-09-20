#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===========================================================================
PROBLEM: Count the Number of Intersecting Interval Pairs
===========================================================================
Given a list of intervals [start, end], count how many pairs (i, j)
where i < j such that intervals i and j intersect (overlap).

Two intervals [a,b] and [c,d] intersect if max(a,c) <= min(b,d).

Example: intervals = [[1,3],[2,4],[5,6]]
  [1,3] & [2,4] → intersect (overlap from 2 to 3)  ✓
  [1,3] & [5,6] → do NOT intersect                  ✗
  [2,4] & [5,6] → do NOT intersect                  ✗
  Answer = 1
===========================================================================

===========================================================================
APPROACH 1: SORT + LINEAR SCAN (Brute Force)
===========================================================================

INTUITION:
  After sorting intervals by start time, for each interval i,
  check all subsequent intervals j (j > i) to see if they overlap.

  Key insight: After sorting by start, interval j (j > i) will always
  have start_j >= start_i. So they overlap if and only if:
      end_i >= start_j

  We track `prev_end` = end of interval i, then scan forward through
  intervals j = i+1, i+2, ... as long as prev_end >= start_j.

DRY RUN for intervals = [[1,4],[2,3],[3,5]]:
  After sorting by start: [[1,4],[2,3],[3,5]]
  n=3, cnt=0

  i=0, prev_end = 4
    j=1: prev_end(4) >= start(2)? YES → cnt=1, j=2
    j=2: prev_end(4) >= start(3)? YES → cnt=2, j=3 → stop
    prev_end = intervals[0][1] = 4

  i=1, prev_end = 3
    j=2: prev_end(3) >= start(3)? YES → cnt=3, j=3 → stop
    prev_end = intervals[1][1] = 3

  i=2 → loop ends (no j to check)

  Answer = 3
  Verification: [1,4]&[2,3]✓, [1,4]&[3,5]✓, [2,3]&[3,5]✓ → 3 ✓

TIME:  O(n²) worst case (every interval overlaps with every other)
SPACE: O(1) extra
===========================================================================

*/

class Solution {
public:
    int countIntersectingIntervals(vector<vector<int>>& intervals) {
        // Sort intervals by start time (and by end time if starts are equal)
        sort(intervals.begin(), intervals.end());
        int n = intervals.size();
        int cnt = 0;

        // prev_end tracks the end of the current "base" interval
        // We use it to check overlap with all subsequent intervals
        int prev_end = intervals[0][1];

        for (int i = 1; i < n; i++) {

            int j = i;
            // Scan forward: interval j overlaps with interval i
            // if interval i's end >= interval j's start
            while (j < n && prev_end >= intervals[j][0]) {
                cnt++;
                j++;
            }

            // Move to next interval as the new "base"
            prev_end = intervals[i][1];
        }

        return cnt;
    }
};


/*
===========================================================================
APPROACH 2: BINARY SEARCH + INCLUSION-EXCLUSION
===========================================================================

INTUITION:
  Instead of checking every pair (O(n²)), we use a formula to count
  intersecting pairs in O(n log n).

  KEY INSIGHT — Counting via endpoints:

  For interval i with start_i, an interval j intersects with i if
  end_j >= start_i (because after sorting, start_j >= start_i,
  so the only condition for overlap is end_j >= start_i).

  Step 1: For each interval i, count how many intervals j have
          end_j >= start_i. Use binary search on sorted `ends` array.

          count_i = number of ends >= start_i = (ends.end() - lower_bound(start_i))

  Step 2: Sum all count_i across all intervals.
          total = Σ count_i

  Step 3: What does `total` represent?
          It counts ordered pairs (i, j) where end_j >= start_i.
          This includes:
            - Self-pairs (i, i) → exactly n of these
            - Pairs where end_j >= start_i BUT intervals don't actually
              overlap (because start_j > end_i, meaning j starts after i ends)

  Step 4: How many pairs have end_j >= start_i but DON'T intersect?
          These are pairs where start_j > end_i.
          Equivalently: start_j > end_i AND end_j >= start_i.
          After sorting by start, this means j > i and start_j > end_i.

          The number of ALL possible pairs is totalp = n*(n-1)/2.
          The number of NON-intersecting pairs = totalp - intersecting.

          Rearranging: intersecting = total - n - (totalp - intersecting)... 
          
          Actually, simpler derivation:
            total = (self-pairs) + (ordered intersecting) + (ordered non-intersecting where end_j >= start_i)
            
          But it turns out that:
            intersecting_pairs = total - n - totalp
          where totalp = n*(n-1)/2

          This works because:
          - total counts pairs (i,j) with end_j >= start_i (including i=j)
          - Subtract n to remove self-pairs → ordered pairs with end_j >= start_i
          - Subtract totalp to convert ordered → unordered and remove non-intersecting

DRY RUN for intervals = [[1,4],[2,3],[3,5]]:
  ends = [4, 3, 5] → sorted: [3, 4, 5]
  n=3, total=0

  interval [1,4]: start=1
    lower_bound(ends, 1) → points to 3 (first end >= 1)
    count = ends.end() - it = 3 - 0 = 3
    total += 3 → total = 3

  interval [2,3]: start=2
    lower_bound(ends, 2) → points to 3
    count = 3
    total += 3 → total = 6

  interval [3,5]: start=3
    lower_bound(ends, 3) → points to 3
    count = 3
    total += 3 → total = 9

  totalp = 3*(3-1)/2 = 3
  answer = total - n - totalp = 9 - 3 - 3 = 3 ✓

  (All 3 pairs intersect: [1,4]&[2,3], [1,4]&[3,5], [2,3]&[3,5])

TIME:  O(n log n) — sorting + binary search per interval
SPACE: O(n) for the ends array
===========================================================================

*/

class Solution2 {
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> ends;

        // Extract all end points
        for (auto &interval : intervals) {
            ends.push_back(interval[1]);
        }

        // Sort end points for binary search
        sort(ends.begin(), ends.end());

        long long total = 0;

        // For each interval, count how many OTHER intervals have
        // end >= this interval's start (using binary search)
        for (auto &interval : intervals) {
            int start = interval[0];

            // lower_bound finds first end >= start
            // All ends from that point to the end of array satisfy end >= start
            auto it = lower_bound(ends.begin(), ends.end(), start);

            total += ends.end() - it;
        }

        // totalp = total number of unordered pairs = nC2
        long long totalp = 1LL * n * (n - 1) / 2;

        // Formula: total - n - totalp
        //   total  = sum of (ends >= start_i) for all i  [includes self-pairs]
        //   n      = remove self-pairs (i == j)
        //   totalp = remove non-intersecting pairs, convert to unordered count
        return total - n - totalp;
    }
};




int main(){
    return 0;
}
