#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement: Given an array/list of length 'N', where the array/list
represents the boards and each element represents the length of each board.
'K' painters are available. Each unit of board takes 1 unit of time to paint.
Return the minimum time to paint all boards such that each painter paints
only continuous sections.

Example: N = 4, boards[] = {10, 20, 30, 40}, k = 2
Result: 60
Explanation: Split [10,20,30] and [40] -> max(60, 40) = 60
*/

// ===================================================================================
// METHOD 1: Using 'result' variable to store answer (original approach)
// ===================================================================================
class PainterPartition {
public:
    int countPainters(vector<int> &boards, int time) {
        int painters = 1;
        long long boardsPainter = 0;
        for (int i = 0; i < boards.size(); i++) {
            if (boardsPainter + boards[i] <= time) {
                boardsPainter += boards[i];
            } else {
                painters++;
                boardsPainter = boards[i];
            }
        }
        return painters;
    }

    int findLargestMinDistance(vector<int> &boards, int k) {
        int low = *max_element(boards.begin(), boards.end());
        int high = accumulate(boards.begin(), boards.end(), 0);
        int result = high;

        while (low <= high) {
            int mid = (low + high) / 2;
            int painters = countPainters(boards, mid);

            if (painters > k) {
                low = mid + 1;
            } else {
                result = mid;
                high = mid - 1;
            }
        }
        return result;
    }
};

// ===================================================================================
// METHOD 2: Using 'low' as answer with detailed monotonic property explanation
// ===================================================================================
class PainterPartitionLow {
public:
    // Helper: count painters needed if each can paint at most 'maxTime' units
    int countPainters(vector<int> &boards, int maxTime) {
        int painters = 1;
        long long currentSum = 0;
        for (int board : boards) {
            if (currentSum + board <= maxTime) {
                currentSum += board;
            } else {
                painters++;
                currentSum = board;
            }
        }
        return painters;
    }

    /*
    =================================================================================
    MONOTONIC PROPERTY EXPLANATION
    =================================================================================

    We binary search on answer X = "maximum time allowed per painter".

    For any X, we ask: "Can we paint all boards with <= k painters,
    where each painter paints at most X units?"

    KEY INSIGHT: This forms a FALSE -> TRUE pattern!

    Why? Because:
    - If X is very SMALL: each painter can paint very little
      -> We need MORE painters -> might exceed k -> FALSE
    - If X is very LARGE: each painter can paint a lot
      -> We need FEWER painters -> within k -> TRUE

    As X increases:
    - Number of painters NEEDED decreases (monotonic)
    - At some threshold, painters needed drops to <= k -> becomes TRUE
    - Once TRUE, all larger X values are also TRUE

    THIS IS THE MONOTONIC PROPERTY: FALSE on LEFT, TRUE on RIGHT

    =================================================================================
    EXAMPLE: boards = [10, 20, 30, 40], k = 2
    =================================================================================

    Range: low = 40 (max element), high = 100 (total sum)

    Let's check feasibility for different maxTime values:

    maxTime = 40: [10,20]=30, [30]=30, [40]=40 -> 3 painters -> FALSE (3 > 2)
    maxTime = 50: [10,20,30]=60 > 50, so [10,20]=30, [30]=30, [40]=40 -> 3 -> FALSE
    maxTime = 60: [10,20,30]=60, [40]=40 -> 2 painters -> TRUE  (2 <= 2) *** FIRST TRUE!
    maxTime = 70: [10,20,30]=60, [40]=40 -> 2 painters -> TRUE
    maxTime = 80: [10,20,30]=60, [40]=40 -> 2 painters -> TRUE
    ...
    maxTime = 100: [10,20,30,40]=100 -> 1 painter -> TRUE

    VISUAL REPRESENTATION OF THE RANGE:
    ---------------------------------------------------------------
    maxTime:  40   50   60   70   80   90   100
    Value:     F    F    T    T    T    T     T
                     |         |
                  LAST FALSE  FIRST TRUE
                     |         |
                   50         60
    ---------------------------------------------------------------

    PATTERN: FALSE -> TRUE (monotonic!)
    - LEFT side (40, 50): FALSE - can't paint with 2 painters
    - RIGHT side (60, 70, ...): TRUE - can paint with 2 painters
    - TRANSITION POINT: 60 (first TRUE = answer)

    =================================================================================
    HOW LOW POINTS TO THE FIRST TRUE
    =================================================================================

    Binary Search Trace:
    --------------------
    Step 1: low=40, high=100, mid=70
            countPainters(70) = 2 -> TRUE
            Search LEFT for first TRUE: high = 69

    Step 2: low=40, high=69, mid=54
            countPainters(54) = 3 -> FALSE
            Search RIGHT for first TRUE: low = 55

    Step 3: low=55, high=69, mid=62
            countPainters(62) = 2 -> TRUE
            Search LEFT for first TRUE: high = 61

    Step 4: low=55, high=61, mid=58
            countPainters(58) = 3 -> FALSE
            Search RIGHT for first TRUE: low = 59

    Step 5: low=59, high=61, mid=60
            countPainters(60) = 2 -> TRUE
            Search LEFT for first TRUE: high = 59

    Step 6: low=59, high=59, mid=59
            countPainters(59) = 3 -> FALSE
            Search RIGHT for first TRUE: low = 60

    Step 7: low=60, high=59 -> STOP (low > high)

    FINAL STATE:
    - low = 60 (points to FIRST TRUE)
    - high = 59 (points to LAST FALSE)
    - Answer = low = 60

    WHY low = first TRUE?
    ----------------------
    When loop ends (low > high):
    - All values < low were checked: some FALSE (high side), some TRUE (saved)
    - low = smallest value that wasn't marked FALSE
    - low = the TRANSITION POINT = first TRUE

    At the end:
    - high = 59 (last FALSE)
    - low = 60 (first TRUE)
    - They are always adjacent: low = high + 1

    CONCLUSION: Return low = 60 = minimum time to paint all boards

    =================================================================================
    */
    int findLargestMinDistance(vector<int> &boards, int k) {
        int low = *max_element(boards.begin(), boards.end());
        int high = accumulate(boards.begin(), boards.end(), 0);

        // Binary search for FIRST TRUE (minimum feasible maxTime)
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (countPainters(boards, mid) <= k) {
                // mid is TRUE (feasible), but we want FIRST TRUE
                // Search LEFT for smaller TRUE
                high = mid - 1;
            } else {
                // mid is FALSE (not feasible), first TRUE is on RIGHT
                // Search RIGHT
                low = mid + 1;
            }
        }

        // When loop ends:
        // low = first TRUE (minimum feasible maxTime)
        // high = last FALSE (one less than answer)
        // Return low!
        return low;
    }
};

int main() {
    vector<int> boards = {10, 20, 30, 40};
    int k = 2;

    // Method 1: Using result variable
    PainterPartition pp;
    int ans1 = pp.findLargestMinDistance(boards, k);
    cout << "Method 1 (result variable): " << ans1 << "\n";

    // Method 2: Using low as answer
    PainterPartitionLow ppl;
    int ans2 = ppl.findLargestMinDistance(boards, k);
    cout << "Method 2 (low as answer):   " << ans2 << "\n";

    /*
    SUMMARY:
    --------
    Both methods return 60.

    boards = [10, 20, 30, 40], k = 2

    All possible splits:
    [10] [20,30,40] -> max(10, 90) = 90
    [10,20] [30,40] -> max(30, 70) = 70
    [10,20,30] [40] -> max(60, 40) = 60  <-- MINIMUM = ANSWER

    Minimum time = 60 (confirmed!)
    */

    return 0;
}
