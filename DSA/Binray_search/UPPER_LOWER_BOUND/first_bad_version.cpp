/*
QUESTION (LeetCode 278 — First Bad Version):
You are a product manager. An API bool isBadVersion(version) tells you whether
a version is bad. All versions after a bad version are also bad.

Find the first bad version (minimize API calls).

Example:
  n = 5, first bad = 4
  isBadVersion(3) → false
  isBadVersion(4) → true
  isBadVersion(5) → true
  Output: 4

---
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ───────────────────────────────────────────────────────────────────
// MOCK isBadVersion API (for local testing)
//
// In LeetCode, this function is provided by the judge.
// Here we define it ourselves so the code compiles and runs locally.
//
// INTUITION:
//   The bad versions start at some fixed version B (the first bad).
//   Since all subsequent versions are also bad:
//     isBadVersion(v) = (v >= B)
//
// We use a global variable `firstBad` to simulate the unknown first
// bad version. The function simply checks: version >= firstBad.
//
// In a real LeetCode environment, this function is hidden and calls
// the internal test API — you only interact with it through the
// `isBadVersion(version)` call.
// ───────────────────────────────────────────────────────────────────

static int firstBad = 1;           // change this to test different cases

bool isBadVersion(int version) {
    // Returns true once version >= the first bad version.
    // All versions before firstBad are good, all from firstBad onward are bad.
    return version >= firstBad;
}

/*
HOW THE API WORKS:

  Suppose firstBad = 4.

  Version:  1    2    3    4    5    6  ...
             ├────┼────┼────┼────┼────┼──>
          GOOD     │  BAD
                   │
            firstBad = 4

  isBadVersion(1) → 1 >= 4? → false  (GOOD)
  isBadVersion(3) → 3 >= 4? → false  (GOOD)
  isBadVersion(4) → 4 >= 4? → true   (BAD)
  isBadVersion(5) → 5 >= 4? → true   (BAD)

  The binary search uses this monotonic property
  (false → false → ... → false → true → true → ...)
  to find the transition point efficiently in O(log n).
*/

class Solution {
public:
    int firstBadVersion(int n) {

        // ──────────────────────────────────────────────────────────
        // INTUITION:
        //   Binary search with the "lower bound" / "find first" pattern.
        //
        //   The array [1 .. n] transitions from GOOD → BAD at some point.
        //   We want the first index where isBadVersion() == true.
        //
        //   Maintain the invariant:
        //     low  = first index we have NOT yet confirmed as GOOD
        //     high = last index we have NOT yet confirmed as BAD
        //
        //   - isBadVersion(mid) == false → mid & everything left is GOOD
        //     → low = mid + 1   (move past the good region)
        //
        //   - isBadVersion(mid) == true  → mid is BAD, but first bad may
        //     be earlier → high = mid    (keep mid as candidate)
        //
        //   When low == high, that single index must be the first bad.
        // ──────────────────────────────────────────────────────────

        int low  = 1;       // versions are 1-indexed
        int high = n;

        while (low < high) {                    // stop when low == high

            int mid = low + (high - low) / 2;   // avoids overflow

            if (isBadVersion(mid))
                high = mid;                     // mid is bad → first bad ≤ mid
            else
                low = mid + 1;                  // mid is good → first bad > mid
        }

        // ──────────────────────────────────────────────────────────
        // WHY IS THE ANSWER AT low?
        //
        // When the loop exits, low == high.
        //
        // At every step we kept the invariant:
        //   - Everything in [1, low-1] is confirmed GOOD
        //     (we moved low past every good version)
        //   - Everything in [high+1, n] is confirmed BAD
        //     (we know a bad exists at mid, but moved high down to
        //      probe earlier versions)
        //
        // The only index that satisfies both is low (= high):
        //   it's the first index NOT proven good → must be the first bad.
        //
        // ──────────────────────────────────────────────────────────

        return low;
    }
};

/*
DRY RUN: n = 5, first bad = 4

  low=1, high=5
    mid=3: isBad(3)=false → low=4    (3 is good, discard [1,3])
  low=4, high=5
    mid=4: isBad(4)=true  → high=4   (4 is bad, search left)
  low=4, high=4 → loop exits

  return low = 4 ✓


DRY RUN: n = 5, first bad = 1

  low=1, high=5
    mid=3: isBad(3)=true  → high=3   (3 is bad, search left)
  low=1, high=3
    mid=2: isBad(2)=true  → high=2
  low=1, high=2
    mid=1: isBad(1)=true  → high=1
  low=1, high=1 → loop exits

  return low = 1 ✓
*/

int main(){

    // ── Test the Solution with different firstBad values ──

    vector<pair<int,int>> tests = {
        {5, 4},     // n=5, firstBad=4  → expected 4
        {5, 1},     // n=5, firstBad=1  → expected 1
        {5, 5},     // n=5, firstBad=5  → expected 5
        {1, 1},     // n=1, firstBad=1  → expected 1
        {10, 7}     // n=10, firstBad=7 → expected 7
    };

    Solution sol;

    for (auto &test : tests) {
        firstBad = test.second;                    // set the mock
        int result = sol.firstBadVersion(test.first);
        cout << "n=" << test.first
             << ", firstBad=" << test.second
             << " → result=" << result
             << (result == test.second ? "  ✓" : "  ✗")
             << "\n";
    }

    return 0;
}
