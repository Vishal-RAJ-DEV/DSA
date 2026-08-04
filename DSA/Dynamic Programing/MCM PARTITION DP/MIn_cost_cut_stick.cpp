#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Partition DP (Memoization)

State:
solve(start, end)

Meaning:
Minimum cost required to perform all cuts from
index start to index end.

---------------------------------------------------------------
Recursion

For the current interval [start...end],

we try EVERY cut as the FIRST cut.

                 start          cut           end
                   |             |             |
                   v             v             v

                3 ----------- 5 ----------- 7

Choosing 'cut' first divides the current stick into
two completely independent subproblems.

Left subproblem

[start ... cut-1]

Right subproblem

[cut+1 ... end]

Total cost

Current Stick Cost
+
Left Subproblem
+
Right Subproblem

We recursively compute both sides and return the
minimum among all possible first cuts.

---------------------------------------------------------------
Base Case

If

start > end

there are no cuts left in the current interval.

Example

solve(3,2)

means

there is no cut remaining.

So no cost is required.

return 0;

---------------------------------------------------------------
Memoization

If the answer for

dp[start][end]

is already computed,

return it immediately instead of solving the same
interval again.
---------------------------------------------------------------
*/

class Solution {
public:

    int solve(int start, int end,
              vector<int>& cuts,
              vector<vector<int>>& dp) {

        // Base Case:
        // No cuts remaining in this interval.
        if (start > end)
            return 0;

        // Return the stored answer
        // if this interval is already solved.
        if (dp[start][end] != -1)
            return dp[start][end];

        // Stores the minimum cost
        // for the current interval.
        int mini = INT_MAX;

        // Try every cut as the FIRST cut.
        for (int cut = start; cut <= end; cut++) {

            // Cost of making the first cut.
            // Current stick length =
            // right boundary - left boundary.
            int currentCost =
                cuts[end + 1] - cuts[start - 1];

            // Solve the left interval recursively.
            int leftCost =
                solve(start, cut - 1, cuts, dp);

            // Solve the right interval recursively.
            int rightCost =
                solve(cut + 1, end, cuts, dp);

            // Total cost if this cut
            // is chosen first.
            int totalCost =
                currentCost +
                leftCost +
                rightCost;

            // Keep the minimum cost among
            // all possible first cuts.
            mini = min(mini, totalCost);
        }

        // Store and return the answer
        // for this interval.
        return dp[start][end] = mini;
    }

    int minCost(int n, vector<int>& cuts) {

        // Add stick boundaries.
        cuts.push_back(n);
        cuts.insert(cuts.begin(), 0);

        // Sort all cut positions.
        sort(cuts.begin(), cuts.end());

        // Number of actual cuts.
        int lastcut = cuts.size() - 2;

        // dp[start][end]
        // = Minimum cost to perform
        // cuts from start to end.
        vector<vector<int>> dp(
            cuts.size(),
            vector<int>(cuts.size(), -1));

        // Solve the entire interval.
        return solve(1, lastcut, cuts, dp);
    }
};


/*
---------------------------------------------------------------
Partition DP Intuition

dp[start][end]
= Minimum cost required to perform all cuts from
  index start to index end.

For every interval [start...end], we try every cut as
the FIRST cut.

Suppose the available cuts are

        start      cut        end
          |         |          |
          v         v          v

        3 --------- 5 --------- 7

and we choose 'cut' as the first cut.

The current stick is immediately divided into two
independent subproblems.

Left subproblem:
[start ...... cut-1]

Right subproblem:
[cut+1 ...... end]

---------------------------------------------------------------
Case 1 : cut == start

Available cuts

3   5   7

Choose first cut = 3

Before cutting

|---------------------------|

      3      5      7

After cutting

|----3|----------------------|

Left side:
No cuts are remaining.

Remaining interval becomes

[start ... start-1]

which is an INVALID interval.

In recursion this becomes

solve(start, start-1)

and the base case returns

0

Therefore in tabulation we directly write

leftCost = 0

instead of accessing dp[start][start-1].

---------------------------------------------------------------
Case 2 : cut == end

Available cuts

3   5   7

Choose first cut = 7

Before cutting

|---------------------------|

      3      5      7

After cutting

|-------------------7|------|

Right side:
No cuts are remaining.

Remaining interval becomes

[end+1 ... end]

which is again an INVALID interval.

In recursion this becomes

solve(end+1, end)

and the base case returns

0

Therefore in tabulation we directly write

rightCost = 0

instead of accessing dp[end+1][end].

---------------------------------------------------------------
Case 3 : cut is somewhere in the middle

Available cuts

3   5   7

Choose first cut = 5

Before cutting

|---------------------------|

      3      5      7

After cutting

|----------5---------------|

Left interval

[start ... cut-1]

contains cut 3

Right interval

[cut+1 ... end]

contains cut 7

Both intervals exist, so we use

leftCost  = dp[start][cut-1]

rightCost = dp[cut+1][end]

---------------------------------------------------------------
This is simply the tabulation version of the recursive calls:

solve(start, cut-1)
solve(cut+1, end)

Whenever one of these recursive calls becomes an invalid
interval (start > end), recursion returns 0.

In tabulation, instead of creating DP states for invalid
intervals, we directly use 0.
---------------------------------------------------------------
*/
class Tabulation {
public:
    int minCost(int n, vector<int>& cuts) {

        // Add the two boundaries of the stick so every interval
        // has a fixed left and right boundary.
        cuts.push_back(n);
        cuts.insert(cuts.begin(), 0);

        // Sort the cut positions.
        sort(cuts.begin(), cuts.end());

        // Number of actual cuts (excluding 0 and n).
        int lastcut = cuts.size() - 2;

        // dp[start][end]
        // = Minimum cost required to perform all cuts
        // from index start to index end.
        vector<vector<int>> dp(cuts.size(),
                               vector<int>(cuts.size(), 0));

        // Build DP from smaller intervals to larger intervals.
        // We move start backwards and end forwards so that
        // every smaller interval needed by the current state
        // has already been computed.
        for (int start = lastcut; start >= 1; start--) {

            for (int end = start; end <= lastcut; end++) {

                // Stores the minimum cost for the current interval.
                int mini = INT_MAX;

                // Try every cut in this interval as the FIRST cut.
                for (int cut = start; cut <= end; cut++) {

                    // Cost of making the first cut.
                    // Current stick length =
                    // right boundary - left boundary
                    int currentCost =
                        cuts[end + 1] - cuts[start - 1];

                    // Cost of solving the left subproblem.
                    //
                    // Remaining interval:
                    // start .... cut-1
                    //
                    // If cut == start,
                    // there are no cuts remaining on the left,
                    // which is equivalent to the recursive base case
                    // solve(start, start-1) = 0.
                    int leftCost =
                        (cut == start) ? 0
                                       : dp[start][cut - 1];

                    // Cost of solving the right subproblem.
                    //
                    // Remaining interval:
                    // cut+1 .... end
                    //
                    // If cut == end,
                    // there are no cuts remaining on the right,
                    // which is equivalent to the recursive base case
                    // solve(end+1, end) = 0.
                    int rightCost =
                        (cut == end) ? 0
                                     : dp[cut + 1][end];

                    // Total cost if 'cut' is chosen
                    // as the first cut for this interval.
                    int totalcost =
                        currentCost +
                        leftCost +
                        rightCost;

                    // Keep the minimum cost among
                    // all possible first cuts.
                    mini = min(mini, totalcost);
                }

                // Store the minimum cost for
                // the interval [start...end].
                dp[start][end] = mini;
            }
        }

        // Entire problem:
        // perform all actual cuts.
        return dp[1][lastcut];
    }
};



int main() {
    vector<int> cuts = {3, 5, 1, 4};
    int c = cuts.size();
    int n = 7;

    Tabulation sol;
    cout << "The minimum cost incurred is: " << sol.minCost(n, cuts) << endl;

    return 0;
}
