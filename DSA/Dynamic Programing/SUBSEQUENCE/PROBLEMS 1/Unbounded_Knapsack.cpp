#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Unbounded Knapsack

    Given:
        wt[]  = weights of items
        val[] = values/profits of items
        W     = maximum capacity of knapsack

    Task:
        Find the maximum value we can collect without crossing capacity W.

    Important:
        Each item can be taken unlimited times.

    Example:
        wt  = {2, 4, 6}
        val = {5, 11, 13}
        W = 10

        One possible best answer:
            item weight 4 + item weight 4 + item weight 2
            value = 11 + 11 + 5 = 27

        Answer = 27

    Difference from 0/1 knapsack:
        0/1 knapsack:
            each item can be taken at most once.

        Unbounded knapsack:
            each item can be taken again and again.
*/

// ============================================================
// PATTERN 1:
// ind means actual index of the item we are currently allowed to use.
// State: solve(ind, capacity)
// Meaning: maximum value using items[0...ind] with capacity "capacity".
// ============================================================

// ================= PATTERN 1: MEMOIZATION =================
class Pattern1Memoization {
public:
    int solve(vector<int>& wt, vector<int>& val, int ind, int capacity,
              vector<vector<int>>& dp) {
        /*
            Algorithm:
                At every item index ind, we have two choices:

                1. notTake:
                   Do not take item ind.
                   Move to the previous item:
                       solve(ind - 1, capacity)

                2. take:
                   Take item ind if wt[ind] <= capacity.
                   Since this is unbounded knapsack, we can take the same
                   item again, so ind stays the same:
                       val[ind] + solve(ind, capacity - wt[ind])

                Answer:
                    max(notTake, take)

            Why take keeps ind same?
                Because after taking item ind once, unlimited supply lets us
                take item ind again.
        */

        /*
            Base case:
                When ind == 0, only item 0 is available.

            Since item 0 can be taken unlimited times, the best strategy is:
                take item 0 as many times as capacity allows.

            Number of times item 0 can be taken:
                capacity / wt[0]

            Total value:
                (capacity / wt[0]) * val[0]

            Example:
                wt[0] = 2, val[0] = 5, capacity = 10

                We can take item 0:
                    10 / 2 = 5 times

                Total value:
                    5 * 5 = 25
        */
        if (ind == 0) {
            return (capacity / wt[0]) * val[0];
        }

        if (dp[ind][capacity] != -1) return dp[ind][capacity];

        int notTake = solve(wt, val, ind - 1, capacity, dp);

        int take = INT_MIN;
        if (wt[ind] <= capacity) {
            take = val[ind] + solve(wt, val, ind, capacity - wt[ind], dp);
        }

        return dp[ind][capacity] = max(take, notTake);
    }

    int unboundedKnapsack(int n, int W, vector<int>& val, vector<int>& wt) {
        vector<vector<int>> dp(n, vector<int>(W + 1, -1));

        return solve(wt, val, n - 1, W, dp);
    }
};

// ================= PATTERN 1: TABULATION =================
class Pattern1Tabulation {
public:
    int unboundedKnapsack(int n, int W, vector<int>& val, vector<int>& wt) {
        /*
            dp[ind][capacity] means:
                maximum value using items[0...ind] with capacity "capacity".
        */
        vector<vector<int>> dp(n, vector<int>(W + 1, 0));

        /*
            Base case conversion:

            Memoization base case:
                if ind == 0:
                    return (capacity / wt[0]) * val[0]

            In tabulation, ind == 0 means row 0.
            So for every capacity from 0 to W:
                dp[0][capacity] = (capacity / wt[0]) * val[0]

            This fills the answer when only item 0 is available.
        */
        for (int capacity = 0; capacity <= W; capacity++) {
            dp[0][capacity] = (capacity / wt[0]) * val[0];
        }

        /*
            Recursive relation conversion:

            Memoization:
                notTake = solve(ind - 1, capacity)
                take    = val[ind] + solve(ind, capacity - wt[ind])

            Tabulation:
                notTake = dp[ind - 1][capacity]
                take    = val[ind] + dp[ind][capacity - wt[ind]]

            Notice take uses dp[ind], the same row.
            Same row means we are allowed to reuse the current item.
        */
        for (int ind = 1; ind < n; ind++) {
            for (int capacity = 0; capacity <= W; capacity++) {
                int notTake = dp[ind - 1][capacity];

                int take = INT_MIN;
                if (wt[ind] <= capacity) {
                    take = val[ind] + dp[ind][capacity - wt[ind]];
                }

                dp[ind][capacity] = max(take, notTake);
            }
        }

        return dp[n - 1][W];
    }
};

// ================= PATTERN 1: SPACE OPTIMIZATION =================
class Pattern1SpaceOptimized {
public:
    int unboundedKnapsack(int n, int W, vector<int>& val, vector<int>& wt) {
        /*
            In Pattern 1 tabulation:
                dp[ind][capacity] depends on:
                    dp[ind - 1][capacity]             -> previous row
                    dp[ind][capacity - wt[ind]]       -> current row

            So we can keep:
                prev = previous row
                curr = current row

            prev[capacity] means:
                maximum value using items processed before current item.
        */
        vector<int> prev(W + 1, 0);

        /*
            Same base case conversion as row 0:
                prev[capacity] = (capacity / wt[0]) * val[0]
        */
        for (int capacity = 0; capacity <= W; capacity++) {
            prev[capacity] = (capacity / wt[0]) * val[0];
        }

        for (int ind = 1; ind < n; ind++) {
            vector<int> curr(W + 1, 0);

            for (int capacity = 0; capacity <= W; capacity++) {
                int notTake = prev[capacity];

                int take = INT_MIN;
                if (wt[ind] <= capacity) {
                    /*
                        take comes from curr, not prev.

                        Why?
                            We stay on the same item when we take it,
                            because unlimited use is allowed.
                    */
                    take = val[ind] + curr[capacity - wt[ind]];
                }

                curr[capacity] = max(take, notTake);
            }

            prev = curr;
        }

        return prev[W];
    }
};

// ============================================================
// PATTERN 2:
// idx means number of items available, not actual array index.
// State: solve(idx, capacity)
// Meaning: maximum value using the first idx items.
// Current item is wt[idx - 1] and val[idx - 1].
// ============================================================

// ================= PATTERN 2: MEMOIZATION =================
class Pattern2Memoization {
public:
    vector<vector<int>> memo;

    int solve(vector<int>& wt, vector<int>& val, int idx, int capacity) {
        /*
            Algorithm:
                idx tells how many items are available.

                If idx = 3, available items are:
                    item 0, item 1, item 2

                Current item:
                    wt[idx - 1], val[idx - 1]

                Choices:

                1. skip:
                   Do not take current item.
                   Then only first idx - 1 items remain:
                       solve(idx - 1, capacity)

                2. take:
                   Take current item if it fits.
                   Since unlimited use is allowed, idx stays same:
                       val[idx - 1] + solve(idx, capacity - wt[idx - 1])

                Answer:
                    max(skip, take)
        */

        /*
            Base case 1:
                if capacity == 0, return 0

            Why?
                If knapsack capacity becomes 0, no more item can be added.
                So the remaining value is 0.
        */
        if (capacity == 0) return 0;

        /*
            Base case 2:
                if idx == 0, return 0

            Why?
                No items are available.
                So no value can be collected.

            Notice:
                In Pattern 2, we do not need the special:
                    (capacity / wt[0]) * val[0]

                because idx = 1 row/call naturally handles item 0 using
                the take choice and stays at idx = 1 again and again.
        */
        if (idx == 0) return 0;

        if (memo[idx][capacity] != -1) return memo[idx][capacity];

        int skip = solve(wt, val, idx - 1, capacity);

        int take = INT_MIN;
        if (wt[idx - 1] <= capacity) {
            take = val[idx - 1] + solve(wt, val, idx,
                                        capacity - wt[idx - 1]);
        }

        return memo[idx][capacity] = max(take, skip);
    }

    int unboundedKnapsack(int n, int W, vector<int>& val, vector<int>& wt) {
        memo.assign(n + 1, vector<int>(W + 1, -1));

        return solve(wt, val, n, W);
    }
};

// ================= PATTERN 2: TABULATION =================
class Pattern2Tabulation {
public:
    int unboundedKnapsack(int n, int W, vector<int>& val, vector<int>& wt) {
        /*
            dp[idx][capacity] means:
                maximum value using the first idx items.

            idx = 0 means:
                no items are available.

            idx = 1 means:
                only item 0 is available.

            idx = n means:
                all items are available.
        */
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

        /*
            Base case conversion 1:

            Memoization:
                if capacity == 0 return 0

            Tabulation:
                capacity == 0 means column 0.

            dp[idx][0] remains 0 for every idx because capacity 0 gives
            maximum value 0.
        */

        /*
            Base case conversion 2:

            Memoization:
                if idx == 0 return 0

            Tabulation:
                idx == 0 means row 0.

            dp[0][capacity] remains 0 for every capacity because no items
            are available.

            Since the dp table is initialized with 0, both base cases are
            already handled.
        */

        /*
            Recursive relation conversion:

            Memoization:
                skip = solve(idx - 1, capacity)
                take = val[idx - 1] + solve(idx, capacity - wt[idx - 1])

            Tabulation:
                skip = dp[idx - 1][capacity]
                take = val[idx - 1] + dp[idx][capacity - wt[idx - 1]]

            take uses the same row dp[idx] because the current item can be
            taken again.
        */
        for (int idx = 1; idx <= n; idx++) {
            for (int capacity = 1; capacity <= W; capacity++) {
                int skip = dp[idx - 1][capacity];

                int take = INT_MIN;
                if (wt[idx - 1] <= capacity) {
                    take = val[idx - 1] + dp[idx][capacity - wt[idx - 1]];
                }

                dp[idx][capacity] = max(take, skip);
            }
        }

        return dp[n][W];
    }
};

// ================= PATTERN 2: SPACE OPTIMIZATION =================
class Pattern2SpaceOptimized {
public:
    int unboundedKnapsack(int n, int W, vector<int>& val, vector<int>& wt) {
        /*
            From Pattern 2 tabulation:
                dp[idx][capacity] depends on:
                    dp[idx - 1][capacity]              -> previous row
                    dp[idx][capacity - wt[idx - 1]]    -> current row

            We can compress this into one 1D array.

            dp[capacity] means:
                maximum value for this capacity using items processed so far.

            For each item, we move capacity from wt[item] to W.

            Why left to right?
                Because unbounded knapsack allows using the same item many
                times.

                When we do:
                    dp[capacity] = max(dp[capacity],
                                       val[item] + dp[capacity - wt[item]])

                dp[capacity - wt[item]] may already include the current item.
                That is correct for unbounded knapsack.
        */
        vector<int> dp(W + 1, 0);

        /*
            Base case conversion:
                dp[0] = 0 because capacity 0 gives value 0.
                All other values also start from 0 because with no items,
                maximum value is 0.
        */

        for (int idx = 1; idx <= n; idx++) {
            int itemWeight = wt[idx - 1];
            int itemValue = val[idx - 1];

            for (int capacity = itemWeight; capacity <= W; capacity++) {
                dp[capacity] = max(dp[capacity],
                                   itemValue + dp[capacity - itemWeight]);
            }
        }

        return dp[W];
    }
};

int main() {
    vector<int> wt = {2, 4, 6};
    vector<int> val = {5, 11, 13};
    int W = 10;
    int n = wt.size();

    Pattern1Memoization p1Memo;
    Pattern1Tabulation p1Tab;
    Pattern1SpaceOptimized p1Space;

    Pattern2Memoization p2Memo;
    Pattern2Tabulation p2Tab;
    Pattern2SpaceOptimized p2Space;

    cout << p1Memo.unboundedKnapsack(n, W, val, wt) << endl;
    cout << p1Tab.unboundedKnapsack(n, W, val, wt) << endl;
    cout << p1Space.unboundedKnapsack(n, W, val, wt) << endl;

    cout << p2Memo.unboundedKnapsack(n, W, val, wt) << endl;
    cout << p2Tab.unboundedKnapsack(n, W, val, wt) << endl;
    cout << p2Space.unboundedKnapsack(n, W, val, wt) << endl;

    return 0;
}
