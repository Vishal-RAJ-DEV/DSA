/*
Problem: LeetCode 774 - Minimize Max Distance to Gas Station
Given sorted station positions on a line and k extra stations to add,
place the k stations to MINIMIZE the MAXIMUM distance between
any two consecutive stations.

Goal: minimize the largest gap after adding exactly k stations.

The file contains FOUR different approaches.

Key observation:
If a gap of length G is divided into p parts (p-1 new stations),
the max segment inside that gap = G / p.
We must distribute k stations so the largest resulting segment
is as small as possible.
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Approach 1: Brute Force Greedy (add station to largest gap)
Algorithm:
1. parts[i] = number of parts the original gap i is split into
   (starts at 1 = no extra station).
2. Repeat k times:
   - Scan all gaps, find the gap with the LARGEST current
     segment length = (gap length) / (number of parts).
   - Add one station there → parts[idx]++.
3. After placing all k stations, answer = max over all gaps of
   (gap length) / (number of parts).

Intuition:
To minimize the maximum segment, each new station should go into
the currently largest segment. Splitting the largest segment can
only reduce the maximum (or keep it the same).

Time: O(k * n) — each of the k stations scans all n-1 gaps
Space: O(n) — parts array
*/
class SolutionGreedy {
public:
    double findSmallestMaxDist(vector<int> &stations, int k) {
        int n = stations.size();

        vector<int> parts(n - 1, 1);

        for (int gas = 0; gas < k; gas++) {
            double maxLen = -1;
            int idx = -1;

            // Find the largest current segment
            for (int i = 0; i < n - 1; i++) {
                double current =
                    (stations[i + 1] - stations[i]) / (double)parts[i];

                if (current > maxLen) {
                    maxLen = current;
                    idx = i;
                }
            }

            // Add one station in this gap
            parts[idx]++;
        }

        double ans = 0;
        for (int i = 0; i < n - 1; i++) {
            ans = max(ans,
                      (stations[i + 1] - stations[i]) / (double)parts[i]);
        }

        return ans;
    }
};

/*
Approach 2: Max-Heap Greedy (optimized largest-gap selection)
Algorithm:
1. Push all gaps into a max-heap (max-heap keyed by current
   segment length). Each entry = {currentLength, gapIndex}.
2. Repeat k times:
   - Pop the gap with the LARGEST segment length (top of heap).
   - parts[idx]++ (add one station there).
   - Recompute new segment length = gap / parts[idx].
   - Push back {newLength, idx} into the heap.
3. After k placements, the top of the heap = the largest
   segment = the minimized maximum distance.

Why it's better than Approach 1:
The max-heap directly gives the largest segment in O(log n)
instead of scanning all gaps in O(n).

Time: O((n + k) * log n)
Space: O(n)
*/
class SolutionHeap {
public:
    double findSmallestMaxDist(vector<int> &stations, int k) {
        int n = stations.size();

        vector<int> parts(n - 1, 1);

        priority_queue<pair<double, int>> pq;

        for (int i = 0; i < n - 1; i++) {
            double len = stations[i + 1] - stations[i];
            pq.push({len, i});
        }

        while (k--) {
            auto it = pq.top();
            double currLen = it.first;
            int idx = it.second;
            pq.pop();

            parts[idx]++;

            double newLength =
                (stations[idx + 1] - stations[idx]) / (double)parts[idx];

            pq.push({newLength, idx});
        }

        return pq.top().first;
    }
};

/*
Approach 3: Binary Search on Answer
Instead of simulating station placement, BINARY SEARCH the answer:
"What is the smallest possible value of the maximum segment?"

Algorithm:
1. Search range: low = 0, high = max original gap.
2. For a candidate distance 'dist':
   - Check if it is FEASIBLE: can we split every gap so that
     every segment <= dist using at most k stations?
   - For a gap of length G, the number of stations needed so
     that all segments <= dist is: ceil(G / dist) - 1
     (e.g. G=10, dist=4 → 3 parts → 2 stations)
3. Binary search on dist:
   - If requiredStations(mid) <= k → dist is achievable,
     try smaller → high = mid
   - Else → need bigger max segment → low = mid
4. Stop when high - low < 1e-6 (floating point precision).
5. Return high.

Why binary search works:
The predicate "can we do it with max segment <= d" is monotonic:
if it's possible with d, it's possible with any larger d.

Time: O(n * log(high/eps)) ≈ O(n * 40) iterations
Space: O(1)
*/
class SolutionBS {
public:
    int requiredStations(vector<int> &stations, double dist) {
        int cnt = 0;

        for (int i = 0; i < stations.size() - 1; i++) {
            double gap = stations[i + 1] - stations[i];

            /*
            Detailed explanation of:  cnt += ceil(gap / dist) - 1;

            Goal of this line:
            For ONE gap of length 'gap', count how many NEW stations
            must be placed inside it so that every resulting segment
            is AT MOST 'dist' long.

            Step 1 — gap / dist:
            How many times the allowed max distance 'dist' fits into
            the gap. Example: gap = 10, dist = 4  →  10 / 4 = 2.5.

            Step 2 — ceil(gap / dist):
            The number of SEGMENTS the gap must be split into so each
            segment is <= dist. Example: ceil(2.5) = 3 segments
            (e.g. 4 + 4 + 2).

            Step 3 — ceil(gap / dist) - 1:
            Number of NEW stations = number of segments - 1.
            Example: 3 segments need only 2 new stations (one between
            each pair of adjacent segments).

            WHEN does cnt increase by one?
            For a single gap, the contribution is:
                ceil(gap/dist) - 1  stations

            This contribution increases by exactly 1 each time 'dist'
            becomes smaller than gap / m for the next integer m, i.e.
            every time a new multiple of 'dist' appears strictly
            INSIDE the gap:
                - gap <= dist           → contribution 0  (gap fits
                                          fully, no station needed)
                - dist < gap <= 2*dist  → contribution 1  (1 station
                                          splits gap into 2 segments)
                - 2*dist < gap <= 3*dist → contribution 2 (2 stations,
                                          3 segments)
                - and so on...
            In other words: each integer multiple m*dist (0 < m*dist
            < gap) needs its own station. That is exactly the count
            of points where a new segment must start.

            Logical meaning of the whole loop:
            It accumulates the TOTAL number of stations required
            across ALL gaps so that the maximum distance between any
            two consecutive stations is at most 'dist'.
            - Small 'dist'  → many multiples inside gaps → cnt is LARGE
            - Large 'dist'  → few multiples inside gaps  → cnt is SMALL

            This is the feasibility predicate for the binary search:
            if (cnt <= k) we CAN achieve max distance 'dist' with our
            k stations → try a smaller 'dist' (high = mid).
            if (cnt > k)  we CANNOT → we need a larger 'dist'
            (low = mid).
            */
            cnt += ceil(gap / dist) - 1;
        }

        return cnt;
    }

    double findSmallestMaxDist(vector<int> &stations, int k) {
        double low = 0;
        double high = 0;

        for (int i = 0; i < stations.size() - 1; i++)
            high = max(high,
                       (double)(stations[i + 1] - stations[i]));

        while (high - low > 1e-6) {
            double mid = (low + high) / 2.0;

            if (requiredStations(stations, mid) <= k)
                high = mid;
            else
                low = mid;
        }

        return high;
    }
};

/*
Approach 4: Binary Search with integer floor + exact-multiple fix
Same idea as Approach 3, but computes the required stations
using integer math to avoid floating-point ceil issues:

For gap G and max segment dist:
- need = floor(G / dist)   → number of parts - 1
- If G is an EXACT multiple of dist (G == need * dist),
  then floor gives one too many stations → need--.
  (e.g. G=10, dist=5 → need=2, but only 1 station is required
   because 2 segments of exactly 5 fit)

Equivalent to ceil(G/dist) - 1 but computed without relying
on float ceil precision.

Time: O(n * log(high/eps))
Space: O(1)
*/
class SolutionBSInt {
public:
    int requiredStations(vector<int> &stations, double dist) {
        int cnt = 0;

        for (int i = 0; i < stations.size() - 1; i++) {
            double gap = stations[i + 1] - stations[i];

            int need = (int)(gap / dist);

            // Exact multiple? Then one fewer station is needed.
            if (fabs(gap - need * dist) < 1e-9)
                need--;

            cnt += need;
        }

        return cnt;
    }

    double findSmallestMaxDist(vector<int> &stations, int k) {
        double low = 0;
        double high = 0;

        for (int i = 0; i < stations.size() - 1; i++)
            high = max(high,
                       (double)(stations[i + 1] - stations[i]));

        while (high - low > 1e-6) {
            double mid = (low + high) / 2;

            if (requiredStations(stations, mid) <= k)
                high = mid;
            else
                low = mid;
        }

        return high;
    }
};

/* Summary of all four approaches:

   Approach | Technique          | Time            | Space
   ---------+--------------------+-----------------+---------
   1        | Brute-force greedy | O(k * n)        | O(n)
   2        | Max-heap greedy    | O((n+k) log n)  | O(n)
   3        | Binary search      | O(n * log)      | O(1)
   4        | BS + int math fix  | O(n * log)      | O(1)

   Approaches 3 & 4 are preferred for large k (k up to 10^9
   in the original problem, where greedy would be too slow).
*/

int main() {
    return 0;
}
