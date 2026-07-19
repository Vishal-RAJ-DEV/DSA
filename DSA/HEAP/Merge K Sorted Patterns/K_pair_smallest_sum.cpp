/*
QUESTION:
Given two sorted integer arrays nums1 and nums2, and an integer k, return the
k smallest pairs (u, v) where u ∈ nums1, v ∈ nums2, ordered by sum (u + v).
If two pairs have the same sum, any order is acceptable.

Example 1:
Input:  nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: Smallest sums: 1+2=3, 1+4=5, 1+6=7 (then 7+2=9, 7+4=11, ...)

Example 2:
Input:  nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [[1,1],[1,1]]
Explanation: (1+1=2) appears twice, then (1+2=3) or (2+1=3).

INTUITION:
  The pairs can be visualized as rows of a matrix where each row i has sums
  nums1[i] + nums2[0], nums1[i] + nums2[1], nums1[i] + nums2[2], ...
  Each row is increasing because nums2 is sorted.

  This is a k-way merge problem: we have |nums1| sorted rows; we want the
  k smallest sums across all rows. Use a min-heap of the current frontier
  (one (sum, i, j) per active row). Always pop the smallest sum, record
  the pair, and advance that row by incrementing j.

  Optimization: we only need to seed the first min(k, |nums1|) rows because
  any row beyond k cannot contribute to the first k pairs (nums1 is sorted,
  so nums1[k] + nums2[0] ≥ nums1[0] + nums2[0] + ...).

ALGORITHM:
  1. Edge cases: if either array empty or k == 0 → return {}.
  2. Push (nums1[i] + nums2[0], i, 0) for i = 0 to min(k, |nums1|) - 1.
  3. While k > 0 and heap not empty:
       a. Pop smallest (sum, i, j).
       b. Add (nums1[i], nums2[j]) to answer.
       c. If j + 1 < |nums2|, push (nums1[i] + nums2[j+1], i, j+1).
       d. k--.
  4. Return answer.

DRY RUN:
  nums1 = [1,7,11], nums2 = [2,4,6], k = 3

  Initial heap (value, i, j):   Pop → ans              Push
  ────────────────────────────────────────────────────────────────
  (3,0,0) (9,1,0) (13,2,0)    → (3,0,0) → [[1,2]]     (5,0,1)
  (5,0,1) (9,1,0) (13,2,0)    → (5,0,1) → [[1,2],[1,4]]   (7,0,2)
  (7,0,2) (9,1,0) (13,2,0)    → (7,0,2) → [[1,2],[1,4],[1,6]]
  k exhausted → return [[1,2],[1,4],[1,6]] ✓

TIME  : O(k log min(k, |nums1|))
SPACE : O(min(k, |nums1|))
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Custom struct — avoids tuple + greater<tuple> runtime issues on MSVC.
    struct Element {
        int sum, i, j;      // sum = nums1[i] + nums2[j]
    };

    struct MinHeap {
        // Returns true if a has lower priority than b
        // (a goes after b), so smaller sum sits on top.
        bool operator()(const Element &a, const Element &b) const {
            return a.sum > b.sum;
        }
    };

public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1,
                                       vector<int>& nums2,
                                       int k) {

        vector<vector<int>> ans;

        if (nums1.empty() || nums2.empty() || k == 0)
            return ans;

        // Min-heap using explicit comparator
        priority_queue<Element, vector<Element>, MinHeap> pq;

        // Seed: first element of each row i (i.e., pair with nums2[0]).
        // Only first min(k, nums1.size()) rows can contribute to the answer.
        int rows = min((int)nums1.size(), k);
        for (int i = 0; i < rows; i++)
            pq.push({nums1[i] + nums2[0], i, 0});

        while (k-- && !pq.empty()) {

            Element cur = pq.top();
            pq.pop();

            ans.push_back({nums1[cur.i], nums2[cur.j]});

            // Advance within the same row (same i, next j)
            if (cur.j + 1 < (int)nums2.size())
                pq.push({nums1[cur.i] + nums2[cur.j + 1], cur.i, cur.j + 1});
        }

        return ans;
    }
};

int main(){
    return 0;
}
