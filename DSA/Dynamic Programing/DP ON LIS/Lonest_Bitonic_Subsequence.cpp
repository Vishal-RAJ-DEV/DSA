#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
                Longest Bitonic Subsequence (Dynamic Programming)
===============================================================================

A Bitonic Subsequence is a subsequence that:

    1. Strictly increases from LEFT to RIGHT.
    2. Then strictly decreases from the PEAK towards the RIGHT.

Every bitonic subsequence has exactly one "peak" element.

---------------------------------------------------------------------------
Core Idea
---------------------------------------------------------------------------

Assume every index i is the peak of the bitonic subsequence.

To compute the longest bitonic subsequence having nums[i] as the peak,
we need two DP values:

1. LIS[i]
   = Length of the Longest Increasing Subsequence ending at index i.
   (Increasing from LEFT ---> Peak)

2. LDS[i]
   = Length of the Longest Decreasing Subsequence starting from index i.
   (Decreasing from Peak ---> RIGHT)

Visual Representation

                Peak
                 │
                 ▼
1 → 3 → 5 → 8 → 6 → 4 → 2
      ↑         ↑
      │         │
 Increasing   Decreasing
(Left → Peak) (Peak → Right)

        LIS[i]      LDS[i]

or equivalently,

      Increasing Part          Decreasing Part
 (Left -------> Peak)      (Peak -------> Right)

         LIS[i]                  LDS[i]
            \                     /
             \                   /
              \                 /
               \               /
                ---- nums[i] ----
                      (Peak)

Where,

LIS[i] = Length of the Longest Increasing Subsequence
         ending at index i.

LDS[i] = Length of the Longest Decreasing Subsequence
         starting from index i.

Therefore, if index i is chosen as the peak,

        Bitonic Length = LIS[i] + LDS[i] - 1

We subtract 1 because the peak element (nums[i]) is counted
once in LIS and once in LDS.

---------------------------------------------------------------------------
Algorithm
---------------------------------------------------------------------------

Step 1:
Compute LIS for every index.

Step 2:
Compute LDS for every index by traversing from right to left.

Step 3:
Treat every index as the peak and compute

        LIS[i] + LDS[i] - 1

Step 4:
Return the maximum value among all valid peaks.

A valid bitonic subsequence must have

    LIS[i] > 1
and
    LDS[i] > 1

This guarantees that there is at least one increasing step
and one decreasing step.

---------------------------------------------------------------------------
Time Complexity : O(N²)

LIS Computation : O(N²)
LDS Computation : O(N²)

Overall : O(N²)

Space Complexity : O(N)
===============================================================================
*/

class Solution {
public:
    int longestBitonicSequence(int n, vector<int> &nums) {

        int maxlen = 0;

        // lisDP[i] stores the length of the Longest Increasing
        // Subsequence ending at index i.
        vector<int> lisDP(n, 1);

        // Compute LIS for every index.
        // For every previous element smaller than nums[i],
        // extend the increasing subsequence ending at j.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i] && lisDP[j] + 1 > lisDP[i]) {
                    lisDP[i] = lisDP[j] + 1;
                }
            }
        }

        // ldsDP[i] stores the length of the Longest Decreasing
        // Subsequence starting from index i.
        vector<int> ldsDP(n, 1);

        // Traverse from right to left so that all future states
        // (indices greater than i) are already computed.
        for (int i = n - 1; i >= 0; i--) {

            // Check every element on the right of index i.
            // If nums[j] is smaller than nums[i], it can be the
            // next element in the decreasing subsequence.
            for (int j = n - 1; j > i; j--) {

                if (nums[j] < nums[i] && ldsDP[j] + 1 > ldsDP[i]) {
                    ldsDP[i] = ldsDP[j] + 1;
                }
            }

            // Treat index i as the peak of the bitonic subsequence.
            //
            // Bitonic Length =
            // Length of Increasing Part (ending at i)
            // +
            // Length of Decreasing Part (starting from i)
            // -
            // 1 (because nums[i] is counted in both DP arrays)
            //
            // A valid peak must have both:
            // 1. A non-empty increasing part.
            // 2. A non-empty decreasing part.
            if (lisDP[i] > 1 && ldsDP[i] > 1) {
                maxlen = max(maxlen, lisDP[i] + ldsDP[i] - 1);
            }
        }

        return maxlen;
    }
};



int main(){
    return 0;
}