// ============================================================================
// QUESTION: Maximum Length of Pair Chain (LeetCode 646)
// ----------------------------------------------------------------------------
// You are given n pairs, pairs[i] = [start, end] with start < end.
// One pair [c, d] may FOLLOW [a, b] only if  b < c
// (the new pair starts strictly AFTER the previous one ends).
//
// A chain = sequence of pairs where every pair follows the previous one.
// You may pick pairs in ANY order and you may SKIP pairs
// (it is a subsequence of the pairs, not necessarily adjacent ones).
// Return the LENGTH of the longest chain you can form.
//
// Examples:
//   pairs = [[1,2],[2,3],[3,4]]
//     [1,2] then [2,3]?  2 < 2 is FALSE -> cannot.
//     best chain: [1,2] -> [3,4]   => answer 2
//   pairs = [[1,2],[7,8],[4,5]]
//     [1,2] -> [4,5] -> [7,8] => answer 3
//   pairs = [[1,10],[2,3],[3,4],[4,5]]
//     [2,3] -> [4,5] (or [2,3]->[3,4]...) => answer 2
//
// ----------------------------------------------------------------------------
// HOW THE LOGIC WORKS (the existing code = TABULATION / bottom-up DP)
// ----------------------------------------------------------------------------
// It is LIS in disguise:
//   LIS      : sort ascending, extend when nums[j] <  nums[i]
//   This one : sort by start,  extend when pairs[j].end < pairs[i].start
//
// Step 1: SORT pairs by start. After sorting, if a chain ends at pair j and
//         pair i can follow it, then necessarily j < i (chain order never
//         goes backwards in the sorted array) - so we only look at j < i.
//
// Step 2: dp[i] = length of the LONGEST chain that ENDS exactly at pairs[i].
//         Every chain ends somewhere, so the answer = max over all dp[i].
//         Base: dp[i] = 1 (pairs[i] alone is already a chain of length 1).
//
// Step 3: transition (same shape as LIS O(n^2)):
//           if pairs[j][1] < pairs[i][0]     // pairs[j] can be followed by pairs[i]
//               dp[i] = max(dp[i], dp[j] + 1) // attach pairs[i] after chain at j
//
// DRY RUN: pairs = [[1,2],[2,3],[3,4]] (already sorted)
//   dp = [1, 1, 1]
//   i=1: j=0 -> pairs[0].end=2 < pairs[1].start=2 ? NO   -> dp[1] = 1
//   i=2: j=0 -> 2 < 3 ? YES -> dp[2] = 1+1 = 2
//        j=1 -> 3 < 3 ? NO                          -> dp[2] = 2
//   answer = max(1,1,2) = 2
//
// Complexity: Time O(n^2) (nested loops after O(n log n) sort), Space O(n).
// ============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// APPROACH 1: TABULATION (Bottom-Up 1D DP) - the original code
// ----------------------------------------------------------------------------
// dp[i] = longest chain ENDING at pairs[i].
// Fill i from 0..n-1; when computing dp[i] every dp[j] (j < i) is already
// known, so no recursion is needed. Answer = max(dp[i]) tracked on the fly.
// Time O(n^2), Space O(n).
// ============================================================================
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        if (n == 0) return 0; // empty input -> no chain possible

        // sort by start (lexicographic: first by [0], then by [1])
        sort(pairs.begin(), pairs.end());

        // dp[i] = longest chain that ENDS exactly at pairs[i]
        vector<int> dp(n, 1); // every single pair is a chain of length 1

        int ans = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {

                // pairs[j] can be followed by pairs[i] only if its END
                // is strictly before pairs[i]'s START
                if (pairs[j][1] < pairs[i][0]) {
                    // either start fresh at i, or extend the chain ending at j
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }

            ans = max(ans, dp[i]); // best chain may end at any index
        }

        return ans;
    }
};



// ============================================================================
// APPROACH 2: MEMOIZATION (Top-Down Recursion + DP)
// ----------------------------------------------------------------------------
// Same recurrence, but computed on demand from the top:
//   solve(i) = longest chain ENDING at pairs[i]   (pairs already sorted)
//   Base   : solve(i) >= 1  (pairs[i] alone)
//   Choice : for every j < i with pairs[j][1] < pairs[i][0],
//                solve(i) = max(solve(i), solve(j) + 1)
//   Memo   : store solve(i) in dp[i] (-1 = not computed yet), so each
//            subproblem is solved exactly once even though many i's
//            ask for the same j.
//
// We loop i = 0..n-1 in the entry function to make sure EVERY dp[i] is
// computed, then take the max (the longest chain can end at any pair).
//
// DRY RUN: pairs = [[1,2],[2,3],[3,4]]
//   solve(0) = 1
//   solve(1): j=0 fails (2<2 false)           -> 1
//   solve(2): j=0 ok  -> 1 + solve(0) = 2
//             j=1 fail                          -> 2
//   answer = 2
//
// Time O(n^2) (n states, each scans up to n predecessors), Space O(n) dp
// + O(n) recursion stack.
// ============================================================================
class Memoization {
public:
    // Returns longest chain ENDING at pairs[i] (pairs sorted by start).
    int solve(int i, vector<vector<int>>& pairs, vector<int>& dp) {
        // subproblem already solved earlier -> reuse it (overlapping problems:
        // many later pairs j > i ask for the same dp[i])
        if (dp[i] != -1) return dp[i];

        int best = 1; // chain consisting of pairs[i] alone

        for (int j = 0; j < i; j++) {
            // if pairs[j] can be followed by pairs[i], try extending that chain
            if (pairs[j][1] < pairs[i][0]) {
                best = max(best, solve(j, pairs, dp) + 1);
            }
        }

        return dp[i] = best; // memoize before returning
    }

    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        if (n == 0) return 0;

        sort(pairs.begin(), pairs.end()); // same preprocessing as tabulation

        vector<int> dp(n, -1); // -1 = not computed yet

        int ans = 1;
        for (int i = 0; i < n; i++) {
            ans = max(ans, solve(i, pairs, dp)); // chain may end at any pair
        }
        return ans;
    }
};



// ============================================================================
// APPROACH 3: SPACE OPTIMIZATION (Greedy, O(1) extra space)
// ----------------------------------------------------------------------------
// WHY THE dp[] ARRAY CANNOT BE SHRUNK TO A FEW ROLLING VARIABLES:
//   dp[i] depends on dp[j] for EVERY j < i (any earlier pair may be the best
//   predecessor - unlike Climbing Stairs where j is only i-1/i-2). So the
//   full DP table is unavoidable for the DP formulation...
//
// ...BUT this problem is also classic ACTIVITY SELECTION: pairs are intervals
//   and we want the maximum number of NON-OVERLAPPING compatible intervals.
//   The greedy proof (exchange argument) says:
//     Sort intervals by their END. Take the one that finishes first; it can
//     never hurt: any optimal chain that starts with a later-ending interval
//     can swap in this earliest-ending one and stay valid (it ends <= the
//     replaced one, so everything after still fits). Repeat on the rest.
//   => greedy is OPTIMAL here, no DP table at all.
//
// Algorithm:
//   1. sort pairs by END (second element) ascending
//   2. take pairs[0]; last_end = pairs[0].end, count = 1
//   3. for each next pair: if pair.start > last_end (strict, same rule as DP)
//          count++, last_end = pair.end   // take it
//
// DRY RUN: pairs = [[1,2],[2,3],[3,4]] sorted by end (unchanged)
//   take [1,2]  -> last_end = 2, count = 1
//   [2,3]: 2 > 2 ? NO  (same strictness as pairs[j].end < pairs[i].start)
//   [3,4]: 3 > 2 ? YES -> count = 2, last_end = 4
//   answer = 2  (matches DP)
//
// Time  : O(n log n) for the sort (beats both O(n^2) DP versions)
// Space : O(1) extra (only count + last_end; sort may be in-place)
// ============================================================================
class SpaceOptimized {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        if (n == 0) return 0;

        // sort by ENDING point - the key to the greedy (earliest finish first)
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int count = 1;       // we always take the earliest-ending pair
        int last_end = pairs[0][1]; // end of the last pair in our chain

        for (int i = 1; i < n; i++) {
            // strict compatibility, exactly the DP condition pairs[j].end < pairs[i].start
            if (pairs[i][0] > last_end) {
                count++;
                last_end = pairs[i][1]; // extend the chain
            }
            // else: overlaps the taken pair -> skip it
        }

        return count;
    }
};



int main(){
    vector<vector<pair<int,int>>> tests = {
        {{1,2},{2,3},{3,4}},
        {{1,2},{7,8},{4,5}},
        {{1,10},{2,3},{3,4},{4,5}},
        {{-6,5},{1,7},{2,3},{5,6},{2,4}}
    };

    Solution tab;
    Memoization memo;
    SpaceOptimized greedy;

    for (auto& t : tests) {
        vector<vector<int>> pairs;
        for (auto& p : t) pairs.push_back({p.first, p.second});

        int a = tab.findLongestChain(pairs);
        int b = memo.findLongestChain(pairs);
        int c = greedy.findLongestChain(pairs);

        cout << "Tabulation=" << a << " Memoization=" << b << " Greedy=" << c << endl;
        if (a != b || b != c) {
            cout << "  MISMATCH!" << endl;
            return 1;
        }
    }
    cout << "All approaches match on every test case." << endl;
    return 0;
}
