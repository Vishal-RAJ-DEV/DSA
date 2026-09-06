#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
PROBLEM: Minimum Number of Days to Make m Bouquets (LeetCode 1482)
================================================================================

Given an array bloomDay where bloomDay[i] = day flower i blooms,
m bouquets needed, each bouquet needs k adjacent flowers.

Return minimum day to make m bouquets, or -1 if impossible.

================================================================================
KEY INSIGHT: MONOTONIC PROPERTY
================================================================================

We binary search on "day" = X.

For any day X, we ask: "Can we make m bouquets by day X?"

The answer follows FALSE -> TRUE pattern:
- Small X (early days): flowers haven't bloomed yet -> can't make bouquets -> FALSE
- Large X (later days): more flowers bloomed -> can make bouquets -> TRUE

WHY?
- As days increase, MORE flowers become available
- More flowers = MORE possible bouquets
- At some threshold, we have enough bouquets -> becomes TRUE
- Once TRUE, all later days are also TRUE

THIS IS THE MONOTONIC PROPERTY: FALSE on LEFT, TRUE on RIGHT

================================================================================
WHY GO LEFT WHEN bouquets >= m (TRUE CASE)?
================================================================================

If on day X we can make >= m bouquets:
- X is a VALID answer (TRUE)
- But we want MINIMUM day (first TRUE)
- There might be an EARLIER day (smaller X) that also works!
- So search LEFT: high = mid - 1

Example: If day 10 works, maybe day 8 also works?
We need to find the EARLIEST day that works.

================================================================================
WHY GO RIGHT WHEN bouquets < m (FALSE CASE)?
================================================================================

If on day X we can make < m bouquets:
- X is NOT enough (FALSE)
- We need MORE time for more flowers to bloom
- So we need a LATER day (larger X)
- So search RIGHT: low = mid + 1

Example: If day 5 gives only 1 bouquet but we need 3,
we need more days for more flowers to bloom.

================================================================================
*/

bool possible(vector<int> &arr, int day, int m, int k) {
    int n = arr.size();
    int cnt = 0;           // Count consecutive bloomed flowers
    int noOfB = 0;         // Count bouquets formed

    for (int i = 0; i < n; i++) {
        if (arr[i] <= day) {
            // Flower has bloomed by 'day' -> can use it
            cnt++;
        } else {
            // Flower hasn't bloomed -> break consecutive sequence
            // Form bouquets from what we have: cnt / k bouquets
            noOfB += (cnt / k);
            cnt = 0;
        }
    }
    // Don't forget remaining flowers after loop
    noOfB += (cnt / k);

    // Can we make at least m bouquets?
    return noOfB >= m;
}

int roseGarden(vector<int> arr, int k, int m) {
    long long val = m * 1ll * k * 1ll;
    int n = arr.size();
    if (val > n) return -1;  // Not enough flowers total

    // Search range: [min bloom day, max bloom day]
    int mini = INT_MAX, maxi = INT_MIN;
    for (int i = 0; i < n; i++) {
        mini = min(mini, arr[i]);
        maxi = max(maxi, arr[i]);
    }

    /*
    =================================================================================
    BINARY SEARCH ON DAYS
    =================================================================================

    Range: [mini ... maxi]
           early    late

    For each day X, check: can we make m bouquets?
    Pattern: FALSE (early) -> TRUE (late)

    When bouquets >= m (TRUE):
    - Day X works! But is there an EARLIER day that works?
    - Search LEFT to find first TRUE: high = mid - 1

    When bouquets < m (FALSE):
    - Day X is too early, not enough flowers bloomed
    - Need MORE days for flowers to bloom
    - Search RIGHT to find first TRUE: low = mid + 1

    When loop ends: low = first TRUE = minimum day
    =================================================================================
    */
    int low = mini, high = maxi;
    while (low <= high) {
        int mid = (low + high) / 2;

        if (possible(arr, mid, m, k)) {
            // TRUE: Can make >= m bouquets by day 'mid'
            // 'mid' is valid, but search LEFT for EARLIER valid day
            high = mid - 1;
        } else {
            // FALSE: Can make < m bouquets by day 'mid'
            // 'mid' is too early, need MORE days -> search RIGHT
            low = mid + 1;
        }
    }

    // low = first TRUE = minimum day to make m bouquets
    return low;
}

int main()
{
    vector<int> arr = {7, 7, 7, 7, 13, 11, 12, 7};
    int k = 3;
    int m = 2;

    /*
    EXAMPLE: arr = {7, 7, 7, 7, 13, 11, 12, 7}, k = 3, m = 2
    Need 2 bouquets, each needs 3 adjacent flowers.

    FEASIBILITY CHECK:
    ------------------
    Day 7:  [7,7,7,7] bloomed -> 4 consecutive -> 4/3 = 1 bouquet
            [13,11,12,7] not bloomed -> 0
            Total = 1 bouquet -> FALSE (1 < 2)

    Day 11: [7,7,7,7] bloomed -> 4/3 = 1 bouquet
            [13,11] bloomed -> 2 consecutive
            [12] not bloomed -> break
            [7] bloomed -> 1
            Total = 1 bouquet -> FALSE (1 < 2)

    Day 12: [7,7,7,7] -> 4/3 = 1 bouquet
            [13,11,12] -> 3/3 = 1 bouquet
            [7] -> 1
            Total = 2 bouquets -> TRUE (2 >= 2) ***

    Day 13: [7,7,7,7] -> 1 bouquet
            [13,11,12,7] -> 4/3 = 1 bouquet
            Total = 2 bouquets -> TRUE

    RANGE:
    Day:    7   8   9   10  11  12  13
    Value:  F   F   F   F   F   T   T
                            |       |
                        LAST FALSE  FIRST TRUE

    Binary Search Trace:
    --------------------
    Step 1: low=7, high=13, mid=10
            possible(10)? [7,7,7,7] -> 1 bouquet, rest not bloomed -> 1 < 2 -> FALSE
            low = 11

    Step 2: low=11, high=13, mid=12
            possible(12)? [7,7,7,7] -> 1, [13,11,12] -> 1, total = 2 -> TRUE
            high = 11

    Step 3: low=11, high=11, mid=11
            possible(11)? [7,7,7,7] -> 1, [13,11] -> 0 (need 3 adjacent), total = 1 -> FALSE
            low = 12

    Step 4: low=12, high=11 -> STOP (low > high)

    Final: low = 12 (first TRUE = answer)

    VERIFY:
    -------
    Day 12: [7,7,7,7] -> 1 bouquet, [13,11,12] -> 1 bouquet
    Total = 2 bouquets >= m=2 -> SUCCESS!
    Answer = 12 (minimum day)
    */

    int ans = roseGarden(arr, k, m);
    if (ans == -1)
        cout << "We cannot make m bouquets.\n";
    else
        cout << "We can make bouquets on day " << ans << "\n";

    return 0;
}
