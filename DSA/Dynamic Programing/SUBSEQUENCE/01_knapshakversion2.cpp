#include <bits/stdc++.h>
using namespace std;

// ================= MEMOIZATION =================

class Memoization
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

// ================= TABULATION =================

class Tabulation
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

    Memoization memo;
    Tabulation tab;

    cout << "Memoization Answer : "
         << memo.knapsack(W, val, wt)
         << endl;

    cout << "Tabulation Answer : "
         << tab.knapsack(W, val, wt)
         << endl;

    return 0;
}