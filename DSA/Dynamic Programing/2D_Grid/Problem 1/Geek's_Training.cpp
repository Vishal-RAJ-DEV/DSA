// =============================================================================
// GEEK'S TRAINING (Maximum Points with Constraint)
// =============================================================================
// Problem: Geek has n days. Each day he can do ONE of 3 activities:
//          - Running (0)
//          - Fighting (1)
//          - Learning (2)
//
// CONSTRAINT: Cannot do the same activity on consecutive days
//
// GOAL: Find maximum points he can earn
//
// EXAMPLE:
//   mat = [[1, 2, 5],    Day 0: Run=1, Fight=2, Learn=5
//          [3, 1, 1],    Day 1: Run=3, Fight=1, Learn=1
//          [1, 5, 3]]    Day 2: Run=1, Fight=5, Learn=3
//
//   Optimal: Learn(5) → Run(3) → Fight(5) = 13 points
//
// THREE APPROACHES:
//   1. Memoization (Top-Down)  - O(n * 4) time, O(n * 4) space
//   2. Tabulation (Bottom-Up)  - O(n * 3) time, O(n * 3) space
//   3. Space Optimization     - O(n * 3) time, O(1) space
// =============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// =============================================================================
// APPROACH 1: SPACE OPTIMIZATION (Most Optimized)
// =============================================================================
// TIME: O(n * 3)  |  SPACE: O(1)
//
// KEY INSIGHT:
//   - To compute day i, we only need day i-1
//   - No need to store entire DP table
//   - Just track 3 values: prevR, prevF, prevL
//
// HOW IT WORKS:
//   - Initialize with day 0 values
//   - For each day, compute new values using previous day
//   - Update previous day values
//
// VISUAL:
//   Day 0:  prevR=1, prevF=2, prevL=5
//           ↓
//   Day 1:  currR=3+max(2,1)=5, currF=1+max(1,5)=6, currL=1+max(1,2)=3
//           ↓
//   Day 2:  currR=1+max(6,3)=9, currF=5+max(5,3)=10, currL=3+max(5,6)=11
//           ↓
//   Answer: max(9,10,11) = 11
//
// COMPARISON:
//   ┌─────────────────┬──────────────────┬──────────────────┐
//   │     Approach    │  Tabulation      │  Space Optimized │
//   ├─────────────────┼──────────────────┼──────────────────┤
//   │ Time            │  O(n * 3)        │  O(n * 3)        │
//   │ Space           │  O(n * 3)        │  O(1)            │
//   │ DP Table        │  n × 3 matrix    │  3 variables     │
//   └─────────────────┴──────────────────┴──────────────────┘
// =============================================================================
class Solution1 {
public:
    int maximumPoints(vector<vector<int>>& mat, int n) {

        // Initialize with day 0 values
        int prevR = mat[0][0];  // Running on day 0
        int prevF = mat[0][1];  // Fighting on day 0
        int prevL = mat[0][2];  // Learning on day 0

        // Process each day from day 1 to day n-1
        for (int i = 1; i < n; i++) {

            // Today = Running: can come from Fighting or Learning yesterday
            int currR = mat[i][0] + max(prevF, prevL);

            // Today = Fighting: can come from Running or Learning yesterday
            int currF = mat[i][1] + max(prevR, prevL);

            // Today = Learning: can come from Running or Fighting yesterday
            int currL = mat[i][2] + max(prevR, prevF);

            // Update previous day values for next iteration
            prevR = currR;
            prevF = currF;
            prevL = currL;
        }

        // Answer = best activity on the last day
        return max({prevR, prevF, prevL});
    }
};

// =============================================================================
// APPROACH 2: TABULATION (Bottom-Up DP)
// =============================================================================
// TIME: O(n * 3)  |  SPACE: O(n * 3)
//
// HOW IT WORKS:
//   - Create DP table: dp[day][activity] = max points ending at (day, activity)
//   - Fill base case: Day 0 values = mat[0][activity]
//   - Fill table bottom-up: day 1 → day 2 → ... → day n-1
//   - Answer = max of last day's activities
//
// RECURRENCE:
//   dp[i][0] = mat[i][0] + max(dp[i-1][1], dp[i-1][2])  // Running
//   dp[i][1] = mat[i][1] + max(dp[i-1][0], dp[i-1][2])  // Fighting
//   dp[i][2] = mat[i][2] + max(dp[i-1][0], dp[i-1][1])  // Learning
//
// VISUAL (DP Table for mat = [[1,2,5],[3,1,1],[1,5,3]]):
//
//           Activity 0    Activity 1    Activity 2
//          (Running)     (Fighting)    (Learning)
//         ┌────────────┬────────────┬────────────┐
//   Day 0 │     1      │     2      │     5      │  ← Base case
//         ├────────────┼────────────┼────────────┤
//   Day 1 │  3+max(2,5)=8  │  1+max(1,5)=6  │  1+max(1,2)=3  │
//         ├────────────┼────────────┼────────────┤
//   Day 2 │  1+max(6,3)=9  │  5+max(8,3)=13 │  3+max(8,6)=11 │
//         └────────────┴────────────┴────────────┘
//
//   Answer = max(dp[2][0], dp[2][1], dp[2][2]) = max(9, 13, 11) = 13
// =============================================================================
class Solution2 {
public:
    int maximumPoints(vector<vector<int>>& mat, int n) {

        // DP table: dp[day][activity]
        vector<vector<int>> dp(n, vector<int>(3, 0));

        // Base case: Day 0 - points are just the activity points
        dp[0][0] = mat[0][0]; // Running
        dp[0][1] = mat[0][1]; // Fighting
        dp[0][2] = mat[0][2]; // Learning

        // Fill DP table from day 1 to day n-1
        for (int i = 1; i < n; i++) {

            // Today = Running: max of (Fight, Learn) from yesterday + today's points
            dp[i][0] = mat[i][0] +
                       max(dp[i - 1][1], dp[i - 1][2]);

            // Today = Fighting: max of (Run, Learn) from yesterday + today's points
            dp[i][1] = mat[i][1] +
                       max(dp[i - 1][0], dp[i - 1][2]);

            // Today = Learning: max of (Run, Fight) from yesterday + today's points
            dp[i][2] = mat[i][2] +
                       max(dp[i - 1][0], dp[i - 1][1]);
        }

        // Answer = best activity on the last day
        return max({
            dp[n - 1][0],
            dp[n - 1][1],
            dp[n - 1][2]
        });
    }
};

// =============================================================================
// APPROACH 3: MEMOIZATION (Top-Down DP)
// =============================================================================
// TIME: O(n * 4)  |  SPACE: O(n * 4)
//
// HOW IT WORKS:
//   - Start from last day (day n-1) with no previous activity (last=3)
//   - Recursively try all activities for each day
//   - Cache results in DP table to avoid recomputation
//   - Base case: day 0 - return max of allowed activities
//
// STATE:
//   - day: current day (0 to n-1)
//   - last: activity performed on previous day (0=Run, 1=Fight, 2=Learn, 3=None)
//
// RECURRENCE:
//   solve(day, last) = max(mat[day][act] + solve(day-1, act))
//                       for all act != last
//
// VISUAL (Recursion Tree for n=3):
//
//                        solve(2, 3)
//                       /     |     \
//                  act=0    act=1    act=2
//                 /         |         \
//           solve(1,0)  solve(1,1)  solve(1,2)
//           /    \       /    \       /    \
//      act=1  act=2  act=0  act=2  act=0  act=1
//        |      |      |      |      |      |
//    solve(0,1) solve(0,2) solve(0,0) solve(0,2) solve(0,0) solve(0,1)
//      max(2,5)  max(1,5)  max(2,5)  max(1,5)  max(2,5)  max(1,2)
//        =5       =5        =5        =5        =5        =2
//
// DP TABLE:
//           last=0   last=1   last=2   last=3
//         (Run)    (Fight)  (Learn)  (None)
//         ┌────────┬────────┬────────┬────────┐
//   Day 0 │   -    │   5    │   5    │   5    │
//         ├────────┼────────┼────────┼────────┤
//   Day 1 │   6    │   3    │   8    │   8    │
//         ├────────┼────────┼────────┼────────┤
//   Day 2 │  11    │  13    │   9    │  13    │  ← Answer
//         └────────┴────────┴────────┴────────┘
// =============================================================================
class Solution3 {
public:

    // Recursive function with memoization
    // day = current day (0 to n-1)
    // last = activity performed yesterday (0=Run, 1=Fight, 2=Learn, 3=None)
    int solve(int day, int last, vector<vector<int>>& mat,
              vector<vector<int>>& dp) {

        // Base case: Day 0
        // Return max points from allowed activities (not same as last)
        if (day == 0) {
            int maxi = 0;

            for (int activity = 0; activity < 3; activity++) {
                if (activity != last) {
                    maxi = max(maxi, mat[0][activity]);
                }
            }

            return maxi;
        }

        // Already calculated - return cached result
        if (dp[day][last] != -1) {
            return dp[day][last];
        }

        int maxi = 0;

        // Try all 3 activities for current day
        for (int activity = 0; activity < 3; activity++) {

            // Cannot perform same activity as yesterday
            if (activity != last) {

                // Points = today's points + best from previous day
                int points = mat[day][activity]
                           + solve(day - 1, activity, mat, dp);

                maxi = max(maxi, points);
            }
        }

        // Cache and return result
        return dp[day][last] = maxi;
    }

    int maximumPoints(vector<vector<int>>& mat, int n) {

        // DP table: dp[day][last]
        // last = 0,1,2 are activities
        // last = 3 means no previous activity (for first call)
        vector<vector<int>> dp(n, vector<int>(4, -1));

        // Start from last day with no previous activity
        return solve(n - 1, 3, mat, dp);
    }
};

// =============================================================================
// MAIN - Test all three approaches
// =============================================================================
int main(){
    vector<vector<int>> mat = {
        {1, 2, 5},
        {3, 1, 1},
        {1, 5, 3}
    };
    int n = 3;

    /*
    COMPARISON OF ALL THREE APPROACHES:
    
    ┌─────────────────┬──────────────────┬──────────────────┬──────────────────┐
    │     Aspect      │   Memoization    │   Tabulation     │  Space Optimized │
    ├─────────────────┼──────────────────┼──────────────────┼──────────────────┤
    │ Time            │   O(n * 4)       │   O(n * 3)       │   O(n * 3)       │
    │ Space           │   O(n * 4)       │   O(n * 3)       │   O(1)           │
    │ Direction       │   Top-Down       │   Bottom-Up      │   Bottom-Up      │
    │ Recursion       │   Yes            │   No             │   No             │
    │ DP Table Size   │   n × 4          │   n × 3          │   3 variables    │
    └─────────────────┴──────────────────┴──────────────────┴──────────────────┘
    
    KEY DIFFERENCES:
    
    1. MEMOIZATION (Top-Down):
       ✓ Start from final state, recurse backwards
       ✓ Natural recursive thinking
       ✓ Only compute needed states
       ✗ Recursion overhead, stack space
    
    2. TABULATION (Bottom-Up):
       ✓ Iterative, no recursion overhead
       ✓ Fill table in order
       ✓ Cache-friendly
       ✗ May compute unused states
    
    3. SPACE OPTIMIZED:
       ✓ Same time as tabulation
       ✓ O(1) space - only track previous day
       ✓ Best for large n
       ✗ Cannot reconstruct path
    */

    // Test all three approaches
    Solution1 sol1;  // Space Optimized
    Solution2 sol2;  // Tabulation
    Solution3 sol3;  // Memoization

    cout << "Input Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  Day " << i << ": Run=" << mat[i][0]
             << ", Fight=" << mat[i][1]
             << ", Learn=" << mat[i][2] << endl;
    }
    cout << endl;

    cout << "Approach 1 (Space Optimized): " << sol1.maximumPoints(mat, n) << endl;
    cout << "Approach 2 (Tabulation):      " << sol2.maximumPoints(mat, n) << endl;
    cout << "Approach 3 (Memoization):     " << sol3.maximumPoints(mat, n) << endl;

    return 0;
}