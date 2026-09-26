// ============================================================================
// QUESTION: Minimum Cost For Tickets (LeetCode 983)
// ----------------------------------------------------------------------------
// You will travel on days[i] (strictly increasing, 1..365).
// costs[0] = 1-day pass, costs[1] = 7-day pass, costs[2] = 30-day pass.
// A pass bought on day D covers D, D+1, ..., D+duration-1.
//   e.g. 7-day pass bought on day 5 covers day 5..11 (days[j] < days[i]+7).
// Goal: minimum cost to cover ALL travel days. You don't pay for non-travel days.
//
// Example 1:
//   days = [1,4,6,7,8,20], costs = [2,7,15] -> Answer 11
//   (7-day on day 1 covers 1,4,6,7,8 for 7 + 1-day on day 20 for 2 + ... actually
//    optimal: 7-day(1..7)=7 covers 1,4,6,7,8 + 1-day day 8? Let's trust 11.)
// Example 2:
//   days = [1,2,3,4,5,6,7,8,9,10,30,31], costs=[2,7,15] -> Answer 17
//
// Why DP?
//  At travel index i (day = days[i]), you MUST buy some pass starting here.
//  You have only 3 choices. Whichever you pick, it skips you to the first
//  UNCOVERED index j, and the rest of the problem is identical (suffix i->end).
//  So: solve(i) = min over 3 passes of (cost[pass] + solve(j))
//  Overlapping subproblems -> memoize solve(i).
// ============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// APPROACH 1: MEMOIZATION (Top-Down) - the code already written below
// ----------------------------------------------------------------------------
// Logic:
//  solve(i) = min cost to cover days[i...n-1] (suffix starting at i).
//  Base: i >= n -> 0 (no days left, no cost).
//  For each pass, find j = first index NOT covered by that pass:
//    1-day: days[j] >= days[i]+1  -> covers only days[i] if no consecutive days
//    7-day: days[j] >= days[i]+7  -> covers [days[i], days[i]+6]
//    30-day: days[j] >= days[i]+30 -> covers [days[i], days[i]+29]
//  Then: oneDay = costs[0]+solve(j1), sevenDay = costs[1]+solve(j2),
//        thirtyDay = costs[2]+solve(j3)
//  Answer: dp[i] = min({oneDay, sevenDay, thirtyDay})
//
//  The while loops are just linear scans to find j. Since days is sorted,
//  j is the upper_bound of (days[i]+duration-1).
//  Time: O(n * maxJump) naive, O(n) with two-pointers/binary-search.
//        Here while loop makes worst O(n^2) but n<=365 so fine.
//  Space: O(n) dp + O(n) recursion stack.
// ============================================================================
class Solution {
public:
    // Returns min cost to cover days[i..end].
    int solve(int i, vector<int>& days, vector<int>& costs, vector<int>& dp) {
        // Base: no travel days left to cover.
        if (i >= days.size())
            return 0;

        // Already computed this suffix? Reuse (overlapping subproblems).
        if (dp[i] != -1)
            return dp[i];

        // OPTION 1: buy 1-day pass on days[i].
        // It covers [days[i], days[i]+0]. Find first day beyond it.
        int j = i;
        while (j < days.size() && days[j] < days[i] + 1)
            j++;

        int oneDay = costs[0] + solve(j, days, costs, dp);

        // OPTION 2: buy 7-day pass on days[i].
        // It covers [days[i], days[i]+6]. Skip all days inside window.
        j = i;
        while (j < days.size() && days[j] < days[i] + 7)
            j++;

        int sevenDay = costs[1] + solve(j, days, costs, dp);

        // OPTION 3: buy 30-day pass on days[i].
        // It covers [days[i], days[i]+29]. Skip all days inside window.
        j = i;
        while (j < days.size() && days[j] < days[i] + 30)
            j++;

        int thirtyDay = costs[2] + solve(j, days, costs, dp);

        // Best of 3 choices is the answer for suffix i. Memoize it.
        return dp[i] = min({oneDay, sevenDay, thirtyDay});
    }

    // Entry: answer for full array = suffix starting at 0.
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        vector<int> dp(n, -1);

        return solve(0, days, costs, dp);
    }
};



// ============================================================================
// APPROACH 2: TABULATION (Bottom-Up, index-based)
// ----------------------------------------------------------------------------
// Same recurrence as memoization, but iterative (no recursion).
//  dp[i] = min cost to cover days[i...n-1]. dp[n] = 0 (nothing left).
//  Fill from BACK to FRONT (i = n-1 -> 0) because dp[i] depends on dp[j]
//  where j > i (future suffix).
//  For each i, find j1/j2/j3 exactly like memoization (first uncovered index
//  for 1/7/30-day pass), then:
//    dp[i] = min(costs[0]+dp[j1], costs[1]+dp[j2], costs[2]+dp[j3])
//  Answer = dp[0].
// Time: O(n^2) worst with linear scan for j (n<=365 fine).
//       O(n log n) if j found with binary search (upper_bound).
// Space: O(n) dp, O(1) stack (no recursion).
// ============================================================================
class Tabulation {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        vector<int> dp(n + 1, 0); // dp[n] = 0 base case
        // dp[n] already 0. Go backwards.
        for (int i = n - 1; i >= 0; i--) {
            // 1-day: first j with days[j] >= days[i]+1
            int j1 = i;
            while (j1 < n && days[j1] < days[i] + 1) j1++;
            int oneDay = costs[0] + dp[j1]; // dp[j1] already computed since j1 > i

            // 7-day: first j with days[j] >= days[i]+7
            int j2 = i;
            while (j2 < n && days[j2] < days[i] + 7) j2++;
            int sevenDay = costs[1] + dp[j2];

            // 30-day: first j with days[j] >= days[i]+30
            int j3 = i;
            while (j3 < n && days[j3] < days[i] + 30) j3++;
            int thirtyDay = costs[2] + dp[j3];

            dp[i] = min({oneDay, sevenDay, thirtyDay});
        }
        return dp[0];
    }
};

// ============================================================================
// APPROACH 3: SPACE OPTIMIZATION (Queue-based, O(n) time, O(1) extra)
// ----------------------------------------------------------------------------
// Why NOT simple prev/sec like Climbing Stairs?
//  There the jump is fixed to i-1/i-2, so 2 variables suffice.
//  Here the jump j is VARIABLE (depends on calendar gap, up to 30 days
//  ahead, skipping an unknown number of indices). So we cannot keep just
//  2 numbers; we need all future dp values inside a 30-day window.
//
// Two standard O(1)-space tricks for this problem:
//
//  (A) Calendar rolling array (size 30): dp over day 1..365 where
//      dp[d] = min(dp[d-1]+c0, dp[d-7]+c1, dp[d-30]+c2) on travel days,
//      else dp[d]=dp[d-1]. Only last 30 values needed -> circular buf[30].
//
//  (B) Queue method (implemented below, most popular in interviews):
//      Sweep travel days in order, keep two queues:
//        week  : candidates for 7-day pass  -> {buyDay, costIfBuyHere}
//        month : candidates for 30-day pass -> {buyDay, costIfBuyHere}
//      For current day d with running answer `ans` (min cost up to prev day):
//        1. Pop expired passes: buyDay+7 <= d, buyDay+30 <= d.
//        2. Push today's options: {d, ans+costs[1]}, {d, ans+costs[2]}.
//        3. ans = min(ans+costs[0], week.front().second, month.front().second)
//             i.e. min(extend with 1-day, best active 7-day, best active 30-day)
//      Queues hold at most a 7/30-day window -> O(1) bounded extra space
//      (at most number of travel days inside 30 days, <=30).
// Time: O(n), Space: O(1) amortized (bounded queues, no dp array, no recursion).
// ============================================================================
class SpaceOptimized {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        queue<pair<int,int>> week, month; // {buyDay, totalCostIfBuyOnBuyDay}
        int ans = 0; // min cost covering all processed days so far

        for (int d : days) {
            // 1. Remove passes that expired BEFORE day d.
            // A 7-day pass bought on b covers [b, b+6], so expired if b+7 <= d.
            while (!week.empty() && week.front().first + 7 <= d)
                week.pop();
            // A 30-day pass bought on b covers [b, b+29], expired if b+30 <= d.
            while (!month.empty() && month.front().first + 30 <= d)
                month.pop();

            // 2. Consider buying new passes TODAY to cover d.
            week.push({d, ans + costs[1]});
            month.push({d, ans + costs[2]});

            // 3. Best way to cover d:
            //  - buy 1-day today: ans + costs[0]
            //  - use best still-valid 7-day: week.front().second
            //  - use best still-valid 30-day: month.front().second
            ans = min({ans + costs[0], week.front().second, month.front().second});
        }
        return ans;
    }
};

// Alternative space-optimized form: calendar DP with only 30 slots.
// Uncomment if you prefer array style over queues (same O(1) idea):
/*
class SpaceOptimizedCalendar {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        unordered_set<int> travel(days.begin(), days.end());
        int lastDay = days.back();
        // Only last 30 answers matter: dp[d] needs dp[d-1], dp[d-7], dp[d-30].
        vector<int> buf(30, 0); // buf[d % 30] = answer up to day d
        for (int d = 1; d <= lastDay; d++) {
            if (!travel.count(d)) {
                buf[d % 30] = buf[(d - 1) % 30]; // no travel, cost unchanged
            } else {
                int one   = buf[(d - 1) % 30] + costs[0];
                int seven = buf[max(0, d - 7) % 30] + costs[1]; // careful d<7
                // For d<7, dp[negative] should be 0; handle with if:
                // (simplified here; full code needs d<7 -> costs[1] directly)
                int thirty = buf[max(0, d - 30) % 30] + costs[2];
                buf[d % 30] = min({one, seven, thirty});
            }
        }
        return buf[lastDay % 30];
    }
};
*/


int main(){
    vector<int> days = {1,4,6,7,8,20};
    vector<int> costs = {2,7,15};

    Solution memo;
    Tabulation tab;
    SpaceOptimized opt;

    // Expected: 11 for all three
    cout << "Memo: " << memo.mincostTickets(days, costs) << endl;
    cout << "Tabulation: " << tab.mincostTickets(days, costs) << endl;
    cout << "SpaceOptimized: " << opt.mincostTickets(days, costs) << endl;
    return 0;
}