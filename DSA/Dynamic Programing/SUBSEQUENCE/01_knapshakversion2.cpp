#include <bits/stdc++.h>
using namespace std;

// ================= VERSION 1 : BASE CASE i < 0 =================
// In this version, memoization uses:
// if (i < 0 || W == 0) return 0;
//
// The matching tabulation uses an extra row:
// dp[0][w] means no item is available.

class MemoizationVersion1
{
public:
    int solve(int i,
              int W,
              vector<int> &val,
              vector<int> &wt,
              vector<vector<int>> &dp)
    {

        // base case
        if (i < 0 || W == 0)
            return 0;

        // already computed
        if (dp[i][W] != -1)
            return dp[i][W];

        int take = 0;

        // take current item
        if (wt[i] <= W)
        {

            take = val[i] +
                   solve(i - 1,
                         W - wt[i],
                         val,
                         wt,
                         dp);
        }

        // skip current item
        int skip = solve(i - 1,
                         W,
                         val,
                         wt,
                         dp);

        // store answer
        return dp[i][W] = max(take, skip);
    }

    int knapsack(int W,
                 vector<int> &val,
                 vector<int> &wt)
    {

        int n = val.size();

        vector<vector<int>> dp(
            n,
            vector<int>(W + 1, -1));

        return solve(n - 1,
                     W,
                     val,
                     wt,
                     dp);
    }
};

class TabulationVersion1
{
public:
    int knapsack(int W,
                 vector<int> &val,
                 vector<int> &wt)
    {

        int n = val.size();

        /*
            This tabulation matches Version 1 memoization base case:

            if (i < 0 || W == 0)
                return 0;

            In recursion, i < 0 means no items are left.
            But an array cannot have index -1.

            So in tabulation, we shift the item index by 1:
            dp[i][w] means:
            maximum value using first i items with capacity w.

            i = 0 means no items are available.
            Therefore dp[0][w] = 0 for all w.

            w = 0 means capacity is 0.
            Therefore dp[i][0] = 0 for all i.

            Because vector is initialized with 0, both base cases are
            handled automatically.
        */
        vector<vector<int>> dp(
            n + 1,
            vector<int>(W + 1, 0));

        for (int i = 1; i <= n; i++)
        {

            for (int w = 1; w <= W; w++)
            {

                /*
                    Since dp row i means first i items,
                    the current actual item index is i - 1.
                */
                int itemIndex = i - 1;

                int take = 0;

                // take current item if it fits
                if (wt[itemIndex] <= w)
                {
                    take = val[itemIndex] +
                           dp[i - 1][w - wt[itemIndex]];
                }

                // skip current item
                int skip = dp[i - 1][w];

                dp[i][w] = max(take, skip);
            }
        }

        return dp[n][W];
    }
};




// ================= VERSION 2 : BASE CASE i == 0 =================
// In this version, memoization uses:
// if (i == 0), directly decide whether item 0 can be taken.
//
// The matching tabulation manually fills row 0 first.

class MemoizationVersion2
{
public:
    int solve(int i,
              int W,
              vector<int> &val,
              vector<int> &wt,
              vector<vector<int>> &dp)
    {

        /*
            This base case matches Version 2 tabulation code.

            In tabulation, row 0 is filled like this:
            if only item 0 is available, then:
            - if wt[0] <= current capacity, we can take item 0
            - otherwise, we cannot take anything

            So in memoization also, when i == 0, we directly answer
            using only the first item.
        */
        if (i == 0)
        {
            if (wt[0] <= W)
                return val[0];

            return 0;
        }

        // If capacity becomes 0, no more value can be added.
        if (W == 0)
            return 0;

        if (dp[i][W] != -1)
            return dp[i][W];

        int take = 0;

        // take current item if it fits in remaining capacity
        if (wt[i] <= W)
        {
            take = val[i] +
                   solve(i - 1,
                         W - wt[i],
                         val,
                         wt,
                         dp);
        }

        // skip current item
        int skip = solve(i - 1,
                         W,
                         val,
                         wt,
                         dp);

        return dp[i][W] = max(take, skip);
    }

    int knapsack(int W,
                 vector<int> &val,
                 vector<int> &wt)
    {

        int n = val.size();

        vector<vector<int>> dp(
            n,
            vector<int>(W + 1, -1));

        return solve(n - 1,
                     W,
                     val,
                     wt,
                     dp);
    }
};

class TabulationVersion2
{
public:
    int knapsack(int W,
                 vector<int> &val,
                 vector<int> &wt)
    {

        int n = val.size();

        vector<vector<int>> dp(
            n,
            vector<int>(W + 1, 0));

        /*
        here using this base case
        if(i == 0){
            if(wt[0] <= W)
            return val[0];

            return 0;
}
*/
        // base case for first item
        for (int w = wt[0]; w <= W; w++)
        {

            dp[0][w] = val[0];
        }

        // fill dp table
        for (int i = 1; i < n; i++)
        {

            for (int w = 0; w <= W; w++)
            {

                int take = 0;

                // take current item
                if (wt[i] <= w)
                {

                    take = val[i] +
                           dp[i - 1][w - wt[i]];
                }

                // skip current item
                int skip = dp[i - 1][w];

                dp[i][w] = max(take, skip);
            }
        }

        return dp[n - 1][W];
    }
};

// ================= DRIVER CODE =================

int main()
{

    vector<int> val = {60, 100, 120};
    vector<int> wt = {10, 20, 30};

    int W = 50;

    MemoizationVersion1 memoV1;
    TabulationVersion1 tabV1;
    MemoizationVersion2 memoV2;
    TabulationVersion2 tabV2;

    cout << "Version 1 Memoization Answer : "
         << memoV1.knapsack(W, val, wt)
         << endl;

    cout << "Version 1 Tabulation Answer : "
         << tabV1.knapsack(W, val, wt)
         << endl;

    cout << "Version 2 Memoization Answer : "
         << memoV2.knapsack(W, val, wt)
         << endl;

    cout << "Version 2 Tabulation Answer : "
         << tabV2.knapsack(W, val, wt)
         << endl;

    return 0;
}
