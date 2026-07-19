/*
QUESTION (LeetCode 2389 — Longest Subsequence With Limited Sum):
Given an array nums and an array queries, for each query find the maximum
size of a subsequence of nums whose sum ≤ query. Return an array of answers.

A subsequence can pick elements in any order (order doesn't affect sum),
so the longest subsequence for a given limit is simply formed by taking the
smallest elements first (greedy).

Example:
  nums = [4,5,2,1], queries = [3,10,21]
  Sorted nums = [1,2,4,5]   →  prefix sums = [1, 3, 7, 12]
  query=3  → [1,2] sum=3    → size 2
  query=10 → [1,2,4] sum=7  → size 3
  query=21 → [1,2,4,5] sum=12 → size 4
  Output: [2, 3, 4]

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {

        int n = (int)nums.size();

        // Sort ascending — greedily pick smallest elements for max length
        sort(nums.begin(), nums.end());

        // Prefix sums: prefix[i] = sum of first (i+1) smallest elements
        vector<int> prefix(n);
        prefix[0] = nums[0];
        for (int i = 1; i < n; i++)
            prefix[i] = prefix[i - 1] + nums[i];

        vector<int> ans;

        for (int &target : queries) {

            int low  = 0;
            int high = n - 1;

            // ────────────────────────────────────────────────────
            // INTUITION:
            //   Binary search for the RIGHTMOST index where
            //   prefix[mid] ≤ target.
            //
            //   - prefix[mid] ≤ target → mid is feasible, try larger
            //     → low = mid + 1
            //   - prefix[mid] > target → too many elements, shrink
            //     → high = mid - 1
            //
            //   When the loop exits (low > high):
            //     high = last index whose prefix sum ≤ target
            //     low  = first index whose prefix sum > target
            // ────────────────────────────────────────────────────

            while (low <= high) {

                int mid = low + (high - low) / 2;

                if (prefix[mid] <= target)
                    low = mid + 1;      // feasible → try including more elements
                else
                    high = mid - 1;     // too large → exclude this element
            }

            // ────────────────────────────────────────────────────
            // WHY IS THE ANSWER AT high + 1 ?
            //
            //   high is the 0-based index of the LAST element whose
            //   prefix sum still fits within the target.
            //
            //   Example:
            //     nums.sorted = [1, 2, 4, 5]
            //     prefix      = [1, 3, 7, 12]
            //     indices     =  0  1  2  3
            //
            //     target = 10:
            //       prefix[2] = 7  ≤ 10  → high stays ≥ 2
            //       prefix[3] = 12 > 10  → high becomes 2
            //       Loop ends: high = 2, low = 3
            //
            //     high = 2 means elements at indices [0..2] fit.
            //     That's 3 elements → answer = high + 1 = 3 ✓
            //
            //   If NO element fits (e.g. target=0 with sorted[0]=1):
            //     prefix[0] = 1 > 0 → high = -1
            //     high + 1 = 0  → answer 0 (empty subsequence) ✓
            //
            //   In short:
            //     prefix has |elements| entries (indices 0 .. n-1).
            //     high gives the last valid index, so the count of
            //     valid elements is (high - 0 + 1) = high + 1.
            // ────────────────────────────────────────────────────

            ans.push_back(high + 1);
        }

        return ans;
    }
};

/*
DRY RUN:
  nums = [4,5,2,1]
  sorted = [1,2,4,5]
  prefix = [1, 3, 7, 12]

  target = 3:
    low=0 high=3 mid=1 → prefix[1]=3 ≤ 3 → low=2
    low=2 high=3 mid=2 → prefix[2]=7 > 3 → high=1
    low=2 high=1 → exit → high+1 = 2 ✓

  target = 10:
    low=0 high=3 mid=1 → prefix[1]=3 ≤ 10 → low=2
    low=2 high=3 mid=2 → prefix[2]=7 ≤ 10 → low=3
    low=3 high=3 mid=3 → prefix[3]=12 > 10 → high=2
    low=3 high=2 → exit → high+1 = 3 ✓

  target = 21:
    low=0 high=3 mid=1 → prefix[1]=3 ≤ 21 → low=2
    low=2 high=3 mid=2 → prefix[2]=7 ≤ 21 → low=3
    low=3 high=3 mid=3 → prefix[3]=12 ≤ 21 → low=4
    low=4 high=3 → exit → high+1 = 4 ✓

  Output: [2, 3, 4]
*/

int main(){
    return 0;
}
