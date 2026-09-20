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

Example: intervals = [[1,4],[2,3],[3,5]]
  [1,4] & [2,3] → intersect ✓   (overlap: [2,3])
  [1,4] & [3,5] → intersect ✓   (overlap: [3,4])
  [2,3] & [3,5] → intersect ✓   (overlap: {3} point)
  Answer = 3
===========================================================================

===========================================================================
APPROACH: BINARY SEARCH + INCLUSION-EXCLUSION
===========================================================================

INTUITION:
  Brute force checks every pair — O(n²). Can we do better?

  Core observation: After sorting intervals by start time, for interval i
  and interval j (where j > i), they intersect IF AND ONLY IF end_j >= start_i.

  Why? Because after sorting by start:
    start_j >= start_i  (always true since j > i)
    For overlap we need: start_j <= end_i  AND  start_i <= end_j
    Since start_j >= start_i, the binding constraint is end_j >= start_i.

  So the QUESTION becomes: for each interval i, how many intervals j
  have end_j >= start_i?

  This is a classic binary search problem on sorted endpoints!

STEP-BY-STEP:
  1. Extract all end points into a separate array `ends`.
  2. Sort `ends`.
  3. For each interval with start_i:
       - Binary search `ends` for the first end >= start_i
       - All ends from that position onward satisfy end >= start_i
       - Add that count to `total`
  4. Apply the formula: intersecting_pairs = total - n - n*(n-1)/2

FORMULA DERIVATION:
  total = Σ (number of j where end_j >= start_i)  for all i

  This counts ORDERED pairs (i, j) including:
    - Self-pairs (i == j): always counted because end_i >= start_i → n pairs
    - Pairs where end_j >= start_i but intervals DON'T overlap:
      These have start_j > end_i (j starts after i ends). Count = totalp - intersecting.

  So:  total = n + intersecting + (totalp - intersecting)
       Hmm, that gives total = n + totalp, which isn't right.

  Actually: total counts pairs (i,j) where end_j >= start_i.
  Non-intersecting pairs have end_j < start_i (when j > i after sorting).
  So total does NOT count non-intersecting pairs at all!

  Let's recount:
    total = self-pairs(n) + ordered intersecting pairs
    ordered intersecting = total - n
    unordered intersecting = (total - n) / ??? 

  Actually the correct formula is:
    intersecting = total - n - (totalp - intersecting)
    → 2 * intersecting = total - n - totalp + intersecting
    → intersecting = total - n - totalp

  Wait, let me verify with example:
    intervals = [[1,4],[2,3],[3,5]]
    ends sorted = [3,4,5]

    [1,4]: start=1, ends >= 1 → [3,4,5] → count=3
    [2,3]: start=2, ends >= 2 → [3,4,5] → count=3
    [3,5]: start=3, ends >= 3 → [3,4,5] → count=3
    total = 9

    totalp = 3C2 = 3
    answer = 9 - 3 - 3 = 3 ✓ (correct!)

  Another example: intervals = [[1,2],[3,4]]
    ends sorted = [2,4]
    [1,2]: start=1, ends >= 1 → [2,4] → count=2
    [3,4]: start=3, ends >= 3 → [4] → count=1
    total = 3
    totalp = 1
    answer = 3 - 2 - 1 = 0 ✓ (no intersection)

TIME:  O(n log n) — sort intervals + sort ends + n binary searches
SPACE: O(n) — for the ends array
===========================================================================

*/

class Solution {
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> ends;

        // Step 1: Extract all end points
        for (auto &interval : intervals) {
            ends.push_back(interval[1]);
        }

        // Step 2: Sort end points for binary search
        sort(ends.begin(), ends.end());

        long long total = 0;

        // Step 3: For each interval, count how many ends >= its start
        for (auto &interval : intervals) {
            int start = interval[0];

            // lower_bound returns iterator to first element >= start
            // All elements from it to ends.end() satisfy end >= start
            auto it = lower_bound(ends.begin(), ends.end(), start);

            total += ends.end() - it;
        }

        // Step 4: Apply inclusion-exclusion formula
        // total  = counts ordered pairs (i,j) where end_j >= start_i (includes self)
        // n      = subtract self-pairs (i == i)
        // totalp = subtract total possible pairs to isolate intersecting count
        long long totalp = 1LL * n * (n - 1) / 2;

        return total - n - totalp;
    }
};



int main(){
    return 0;
}
