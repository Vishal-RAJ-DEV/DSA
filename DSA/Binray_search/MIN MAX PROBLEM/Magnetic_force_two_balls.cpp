/*
QUESTION (LeetCode 1552 — Magnetic Force Between Two Balls):
Given n baskets at positions on a line, place m balls into them.
The magnetic force between two balls at positions x,y is |x - y|.
Maximize the MINIMUM force (distance) between any two balls.

In other words: maximize d such that we can place m balls with
every pair at least d apart.

Example:
  position = [1,2,3,4,7], m = 3
  Place at 1, 4, 7 → distances = 3, 3 → min = 3
  Can we do better? Try 1, 4, 7 with d=4? No (need 3 balls).
  Output: 3

---
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:

    // ────────────────────────────────────────────────────────────
    // canPlace(mid): can we place m balls with min gap ≥ dist?
    //
    // INTUITION:
    //   Greedy — place first ball at the leftmost basket, then
    //   always pick the earliest next basket that is ≥ dist away.
    //   This leaves the most space for the remaining balls, so
    //   if a placement exists, the greedy one always works.
    //
    //   Why greedy works here:
    //     If a feasible arrangement exists, shifting the first ball
    //     left (to an earlier basket) only makes it easier to fit
    //     the rest. So the optimal strategy is to always take the
    //     leftmost possible basket.
    //
    // LOGIC:
    //   1. Place 1st ball at position[0], count = 1, lastPos = position[0].
    //   2. Scan the rest: if position[i] - lastPos ≥ dist, place a ball
    //      (count++, update lastPos).
    //   3. If count == m → return true  (all balls placed).
    //   4. Return false (couldn't place all m).
    //
    // DRY RUN:
    //   position = [1,2,3,4,7], m = 3, dist = 3
    //     count=1, lastPos=1
    //     i=1: 2-1=1 < 3 → skip
    //     i=2: 3-1=2 < 3 → skip
    //     i=3: 4-1=3 ≥ 3 → count=2, lastPos=4
    //     i=4: 7-4=3 ≥ 3 → count=3 == m → return true  ✓
    //
    //   position = [1,2,3,4,7], m = 3, dist = 4
    //     count=1, lastPos=1
    //     i=1: 2-1=1 < 4 → skip
    //     i=2: 3-1=2 < 4 → skip
    //     i=3: 4-1=3 < 4 → skip
    //     i=4: 7-1=6 ≥ 4 → count=2
    //     End → count=2 < 3 → return false
    // ────────────────────────────────────────────────────────────

    bool canPlace(vector<int>& position, int m, int dist) {
        int count = 1;                    // first ball at position[0]
        int lastPos = position[0];

        for (int i = 1; i < position.size(); i++) {
            if (position[i] - lastPos >= dist) {
                count++;
                lastPos = position[i];

                if (count == m)
                    return true;
            }
        }

        return false;
    }

public:

    // ────────────────────────────────────────────────────────────
    // maxDistance: binary search on the answer (minimum gap)
    //
    // INTUITION:
    //   The answer d (minimum distance between balls) lies in a
    //   range [1, maxPos - minPos]. Instead of checking every d,
    //   we binary search because canPlace is monotonic:
    //
    //     If we CAN place m balls with min gap ≥ d,
    //     then we CAN also place them with min gap ≥ (d-1).
    //
    //     i.e., canPlace(d) = true  ⇒ canPlace(d-1) = true
    //
    //   This gives us a TTT...FFF pattern. We want the LAST true.
    //
    //   Binary search template: find the boundary (last feasible).
    //
    // WHY BINARY SEARCH ON d?
    //   The search space is [1, max-min] which could be 10⁹.
    //   Linear scanning is impossible. Binary search takes
    //   O(log(range)) ≈ O(log 10⁹) ≈ 30 iterations.
    //
    // WHY IS THE ANSWER AT mid WHEN canPlace IS TRUE?
    //   We maintain ans = mid whenever canPlace(mid) is true.
    //   After the loop, ans holds the largest d that worked.
    //   low moves past feasible distances, high moves below
    //   infeasible ones. ans captures the last feasible = max.
    //
    // ALGORITHM:
    //   1. Sort positions (required for canPlace greedy).
    //   2. low = 1, high = position.back() - position.front().
    //   3. While low ≤ high:
    //        mid = low + (high - low) / 2
    //        if canPlace(mid) → feasible → save ans, try larger (low = mid + 1)
    //        else             → not feasible → try smaller (high = mid - 1)
    //   4. Return ans.
    //
    // DRY RUN:
    //   position = [1,2,3,4,7], m = 3
    //   Sorted: [1,2,3,4,7]   low=1, high=6
    //
    //   mid=3: canPlace(3)=true  → ans=3, low=4
    //   mid=5: canPlace(5)=false → high=4
    //   mid=4: canPlace(4)=false → high=3
    //   Loop ends (low=4 > high=3). Return ans=3 ✓
    //
    // TIME  : O(N log N + N log R)
    //          N log N = sorting
    //          N log R = N × binary_search_iterations
    //          R = max-min (the search range)
    // SPACE : O(log N) (sorting stack)
    // ────────────────────────────────────────────────────────────

    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());

        int low  = 1;
        int high = position.back() - position.front();
        int ans  = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canPlace(position, m, mid)) {
                ans = mid;              // feasible → save and try larger
                low = mid + 1;
            } else {
                high = mid - 1;         // not feasible → reduce distance
            }
        }

        return ans;
    }
};

/*
FULL DRY RUN:
  position = [1,2,3,4,7], m = 3

  Binary search on d ∈ [1, 6]:
  ┌──────┬──────────┬───────────┬────────────┐
  │ mid  │ canPlace │   action  │   ans      │
  ├──────┼──────────┼───────────┼────────────┤
  │  3   │ true     │ ans=3, lo=4 │   3      │
  │  5   │ false    │ hi=4       │   3      │
  │  4   │ false    │ hi=3       │   3      │
  └──────┴──────────┴───────────┴────────────┘
  Return 3 ✓

  Verification:
    d=3 → [1,4,7] works (min gap = 3)
    d=4 → need 3 balls with each ≥ 4 apart:
           place 1 → need ≥5 → 7 → only 2 balls placed ✗
    So max feasible d = 3. Correct.
*/

int main() {
    Solution sol;

    vector<pair<vector<int>, int>> tests = {
        {{1,2,3,4,7}, 3},           // expected 3
        {{5,4,3,2,1,1000000000}, 2}, // expected 999999999
        {{1,2,3}, 2},               // expected 2
        {{1,2}, 2},                 // expected 1
    };

    for (auto &it : tests) {
        int res = sol.maxDistance(it.first, it.second);
        cout << "maxDistance = " << res << "\n";
    }

    return 0;
}
