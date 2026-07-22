#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* --------------------------------------------------------------------------
 *  Approach 1: Two Min-Heaps (available + occupied)
 * --------------------------------------------------------------------------
 *  Algorithm:
 *    1. Store each friend as {arrival, leaving, originalIndex}.
 *    2. Sort friends by arrival time (ascending).
 *    3. Use a min-heap `available` to track all chair numbers (0..n-1)
 *       that are currently free. The smallest chair is always at the top.
 *    4. Use a min-heap `occupied` to track {leavingTime, chairNumber}
 *       for currently seated friends. The chair whose occupant leaves
 *       earliest is always at the top.
 *    5. Iterate through the sorted friends. For each friend:
 *       a) Free all chairs whose occupant's leaving time <= current
 *          arrival time. Pop from `occupied` and push into `available`.
 *       b) Assign the smallest free chair (top of `available`).
 *       c) If this friend is `targetFriend`, return the chair number.
 *       d) Otherwise, push {leavingTime, chairNumber} into `occupied`.
 *    6. Return -1 (should never reach here given valid input).
 *
 *  Time  Complexity: O(n log n)  — sorting O(n log n) + heap ops O(n log n)
 *  Space Complexity: O(n)        — two heaps of size O(n)
 * -------------------------------------------------------------------------- */

class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {

        int n = times.size();

        /* Store each person as {arrival, leaving, original index} */
        vector<vector<int>> peoples;

        for (int i = 0; i < n; i++) {
            peoples.push_back({times[i][0], times[i][1], i});
        }

        /* Sort by arrival time so we process friends in the order they
         * arrive at the party */
        sort(peoples.begin(), peoples.end());

        /* ---------- Min-heap of available chairs ----------
         * Contains chair numbers that are free right now.
         * The smallest-numbered chair is always at the top. */
        priority_queue<int, vector<int>, greater<int>> available;

        /* ---------- Min-heap of occupied chairs ----------
         * Contains pairs {leavingTime, chairNumber}.
         * The chair whose occupant leaves earliest is at the top,
         * so we can quickly free chairs when people leave. */
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>> occupied;

        /* Initially all chairs from 0 to n-1 are free */
        for (int i = 0; i < n; i++) {
            available.push(i);
        }

        /* Process each friend in arrival order */
        for (int i = 0; i < n; i++) {

            int arrival     = peoples[i][0];
            int leave       = peoples[i][1];
            int friendIndex = peoples[i][2];

            /* -------- Free chairs whose occupants have left --------
             * While the earliest-leaving occupant left at or before
             * the current arrival time, reclaim that chair and make
             * it available again. */
            while (!occupied.empty() &&
                   occupied.top().first <= arrival) {

                int freeChair = occupied.top().second;
                occupied.pop();
                available.push(freeChair);
            }

            /* Assign the smallest available chair to this friend */
            int assignedChair = available.top();
            available.pop();

            /* If this is the friend we are looking for, return answer */
            if (friendIndex == targetFriend)
                return assignedChair;

            /* Otherwise mark the chair as occupied until 'leave' */
            occupied.push({leave, assignedChair});
        }

        /* Should never reach here for valid input */
        return -1;
    }
};


/* --------------------------------------------------------------------------
 *  Approach 2: std::set for Available + Min-Heap for Occupied
 * --------------------------------------------------------------------------
 *  Algorithm:
 *    1. Store each friend as {arrival, leaving, originalIndex}.
 *    2. Sort friends by arrival time (ascending).
 *    3. Use a `set<int>` to maintain all available chair numbers in
 *       sorted order. The smallest chair is always `*available.begin()`.
 *    4. Use a min-heap `occupied` of {leavingTime, chairNumber} to
 *       track currently seated friends (same as Approach 1).
 *    5. Iterate sorted friends:
 *       a) Free chairs whose occupants have left (leavingTime <= arrival).
 *          Pop from `occupied` and `insert` the chair back into `available`.
 *       b) Pick the smallest available chair via `*available.begin()`.
 *       c) Erase it from `available` (it is now occupied).
 *       d) Return it if this is `targetFriend`.
 *       e) Otherwise push {leavingTime, chairNumber} into `occupied`.
 *    6. Return -1 (fallback).
 *
 *  Note: `set` is a balanced BST (typically Red-Black Tree). Insertion,
 *        erase, and begin() each take O(log n). This makes the approach
 *        slightly heavier than the two-heap version, but both share the
 *        same asymptotic complexity.
 *
 *  Time  Complexity: O(n log n)
 *  Space Complexity: O(n)
 * -------------------------------------------------------------------------- */

class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {

        int n = times.size();

        /* Store each person as {arrival, leaving, original index} */
        vector<vector<int>> people;

        for (int i = 0; i < n; i++) {
            people.push_back({times[i][0], times[i][1], i});
        }

        /* Sort by arrival time */
        sort(people.begin(), people.end());

        /* ---------- set of available chairs ----------
         * A balanced BST keeps chair numbers sorted.
         * The smallest free chair is always *available.begin(). */
        set<int> available;

        for (int i = 0; i < n; i++)
            available.insert(i);

        /* ---------- Min-heap for occupied chairs ----------
         * {leaveTime, chairNumber} — earliest leaver at the top. */
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > occupied;

        for (auto &person : people) {

            int arrival     = person[0];
            int leave       = person[1];
            int friendIndex = person[2];

            /* Free chairs whose occupants have already left */
            while (!occupied.empty() &&
                   occupied.top().first <= arrival) {

                int chair = occupied.top().second;
                occupied.pop();
                available.insert(chair);
            }

            /* Smallest available chair */
            int chair = *available.begin();
            /* Remove it from the free pool — it is now occupied */
            available.erase(available.begin());

            /* Return if this is the target friend */
            if (friendIndex == targetFriend)
                return chair;

            /* Mark the chair as occupied until 'leave' */
            occupied.push({leave, chair});
        }

        return -1;
    }
};



int main(){
    return 0;
}