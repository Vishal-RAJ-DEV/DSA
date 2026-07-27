#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// PROBLEM INTUITION:
//
// We have two time series, each represented as a list of
// [timestamp, value] pairs sorted by timestamp.
//
// Each data point [t, v] means: "at time t, the value changes TO v".
// The value holds until the NEXT timestamp changes it again.
// This is a RIGHT-CONTINUOUS step function (the new value takes
// effect at time t exactly).
//
// Example series:  [[1, 10], [3, 20], [5, 15]]
//   t ∈ [1, 3)  → value = 10
//   t ∈ [3, 5)  → value = 20
//   t ∈ [5, ∞)  → value = 15
//   t < 1       → value = 0 (no data yet)
//
// GOAL: Combine the two series into ONE, where at EACH UNIQUE
// timestamp present in either series, we output:
//   [timestamp, sum_of_both_values_at_that_time]
//
// Why aggregate at every unique timestamp? Because that's where
// at least one series changes, so the sum might change.
//
// Example:
//   series1 = [[1,10], [3,20], [5,15]]
//   series2 = [[2,5],  [4,25], [6,10]]
//
//   Result:
//     t=1 → v1=10, v2=0  (series2 hasn't started)    → [1, 10]
//     t=2 → v1=10, v2=5                                → [2, 15]
//     t=3 → v1=20, v2=5                                → [3, 25]
//     t=4 → v1=20, v2=25                               → [4, 45]
//     t=5 → v1=15, v2=25                               → [5, 40]
//     t=6 → v1=15, v2=10                               → [6, 25]
//
// KEY INSIGHT: This is essentially a MERGE of two step functions.
// We collect ALL timestamps (merge the sorted time axes),
// then for each timestamp, we compute each series' value using
// a "ceiling lookup" — find the first data point whose time >= t.
// The pointers advance monotonically since times are increasing,
// making this O(n + m) overall.
// ============================================================

class Solution {
public:
    vector<vector<int>> aggregateTimeSeries(vector<vector<int>>& series1, vector<vector<int>>& series2) {
        int n = series1.size();
        int m = series2.size();
        vector<vector<int>> ans;                     // Result: list of [timestamp, sum] pairs
        vector<int> times;                           // Will hold ALL unique timestamps from both series
        int i = 0; int j = 0;                        // Pointers for merging the two sorted time axes

        // ── STEP 1: Merge all unique timestamps (like merging two sorted lists) ──
        while(i < n && j < m) {
            if(series1[i][0] == series2[j][0]) {     // Same timestamp appears in both
                times.push_back(series1[i][0]);      // Add it once (unique)
                i++; j++;                            // Advance both pointers
            }
            else if(series1[i][0] < series2[j][0]) { // series1 has an earlier timestamp
                times.push_back(series1[i][0]);
                i++;
            }
            else {                                   // series2 has an earlier timestamp
                times.push_back(series2[j][0]);
                j++;
            }
        }
        // Flush remaining timestamps from either series
        while(i < n) times.push_back(series1[i++][0]);
        while(j < m) times.push_back(series2[j++][0]);

        // ── STEP 2: For each unique timestamp, compute the sum of both series ──
        int p1 = 0; int p2 = 0;                      // Pointers into each series

        for(int t : times) {                         // Iterate over all unique timestamps in order

            // Advance p1 to the FIRST data point with timestamp >= t
            // This skips entries that are STRICTLY before t because their
            // value is no longer valid once we reach t (the value changed at t)
            while(p1 < n && series1[p1][0] < t) p1++;
            // Advance p2 similarly
            while(p2 < m && series2[p2][0] < t) p2++;

            // Get the value from each series at time t:
            //   - If a data point with timestamp >= t exists, use its value
            //   - Otherwise, the series has no more data → value = 0
            int v1 = (p1 < n) ? series1[p1][1] : 0;
            int v2 = (p2 < m) ? series2[p2][1] : 0;

            // Record the aggregated result at this timestamp
            ans.push_back({t, v1 + v2});
        }

        // NOTE: Pointers p1, p2 only move FORWARD (monotonic).
        // Since both 'times' and each series are sorted, we never backtrack.
        // This gives O(n + m) time and O(n + m) space.

        return ans;
    }
};



int main(){
    return 0;
}
