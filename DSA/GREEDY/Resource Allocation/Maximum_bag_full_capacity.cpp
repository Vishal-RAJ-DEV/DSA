/*
================================================================================
PROBLEM: Maximum Number of Bags with Full Capacity (LeetCode 2279)
================================================================================

You are given:
  - capacity[i]  = maximum capacity of the ith bag
  - rocks[i]     = number of rocks currently in the ith bag
  - additionalRocks = total extra rocks you can distribute freely

A bag is FULL when rocks[i] == capacity[i].

You can distribute additionalRocks among the bags in any way you want.
Return the MAXIMUM number of bags that can be full.

Example:
  capacity = [2, 3, 4, 5], rocks = [1, 2, 4, 4], additionalRocks = 2

  Bag 0: needs 2-1 = 1 more rock to be full
  Bag 1: needs 3-2 = 1 more rock to be full
  Bag 2: needs 4-4 = 0 more rocks (already full)
  Bag 3: needs 5-4 = 1 more rock to be full

  With 2 additional rocks:
    Fill bag 0 (1 rock used, 1 remaining)
    Fill bag 1 (1 rock used, 0 remaining)
    Can't fill bag 3 (no rocks left)

  Answer: 3 bags full (bags 0, 1, 2)

================================================================================
HOW THE CODE WORKS (Greedy)
================================================================================

KEY INSIGHT:
  To maximize the number of full bags, always fill the bag that needs the
  FEWEST rocks first. This is the classic greedy strategy: handle the
  cheapest/easiest case first to maximize count.

STEP 1: Convert capacity[] to "remaining space"
  capacity[i] = capacity[i] - rocks[i]
  After this, capacity[i] tells us how many more rocks bag i needs to be full.
  If capacity[i] == 0, the bag is already full.

STEP 2: Sort by remaining space
  After sorting, the bags that need the fewest rocks come first.
  This lets us greedily fill the "cheapest" bags first.

STEP 3: Greedily fill bags
  Iterate through sorted bags:
    - If bag needs <= additionalRocks: fill it, subtract cost, increment count
    - If bag needs > additionalRocks: stop (all remaining bags need even more)

WHY THIS IS OPTIMAL:
  Suppose we have rocks = 5 and two bags needing 3 and 4 rocks.
  Greedy: fill 3-rock bag first → 5-3=2 left → can't fill 4-rock bag → count=1
  Alternative: fill 4-rock bag first → 5-4=1 left → can't fill 3-rock bag → count=1
  Both give same count. But if we had rocks=7:
  Greedy: fill 3 first → 7-3=4 → fill 4 → count=2
  Alternative: fill 4 first → 7-4=3 → fill 3 → count=2
  Still same. The greedy order never does WORSE because filling smaller
  bags first preserves more rocks for subsequent bags.

TIME:  O(n log n) for sorting
SPACE: O(1) extra (in-place transform)

================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks,
                    int additionalRocks) {
        int n = capacity.size();

        // STEP 1: Transform capacity[] into "remaining space needed"
        // capacity[i] = how many more rocks bag i needs to be full
        for (int i = 0; i < n; i++)
            capacity[i] -= rocks[i];

        // STEP 2: Sort by remaining space (smallest first)
        // This puts the "cheapest" bags to fill at the front
        sort(capacity.begin(), capacity.end());

        // STEP 3: Greedily fill bags from cheapest to most expensive
        int filledBags = 0;
        for (int i = 0; i < n; i++) {
            if (capacity[i] <= additionalRocks) {
                // We have enough rocks to fill this bag
                additionalRocks -= capacity[i];  // spend the rocks
                filledBags++;                     // one more full bag
            } else {
                // Not enough rocks for this bag (and all remaining are even bigger)
                break;
            }
        }

        return filledBags;
    }
};

/*
================================================================================
VISUAL TRACE: capacity = [2,3,4,5], rocks = [1,2,4,4], additionalRocks = 2
================================================================================

  After Step 1 (remaining space):
    capacity = [1, 1, 0, 1]

  After Step 2 (sorted):
    capacity = [0, 1, 1, 1]

  Step 3 (greedy fill):
    ┌───────┬──────────┬─────────────────┬────────────────┬──────────────┐
    │   i   │ needs[i] │ additionalRocks │   Action       │ filledBags   │
    ├───────┼──────────┼─────────────────┼────────────────┼──────────────┤
    │   0   │    0     │       2         │ Already full   │      1       │
    │   1   │    1     │       2         │ Fill (2-1=1)   │      2       │
    │   2   │    1     │       1         │ Fill (1-1=0)   │      3       │
    │   3   │    1     │       0         │ Not enough     │   STOP       │
    └───────┴──────────┴─────────────────┴────────────────┴──────────────┘

  Answer: 3

================================================================================
*/

int main(){
    Solution sol;

    // Example: capacity = [2,3,4,5], rocks = [1,2,4,4], additionalRocks = 2
    vector<int> capacity = {2, 3, 4, 5};
    vector<int> rocks    = {1, 2, 4, 4};
    int additionalRocks  = 2;

    cout << "Maximum full bags: " << sol.maximumBags(capacity, rocks, additionalRocks) << endl;

    return 0;
}
