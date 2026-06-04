#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Memoization {
public:

    int solve(int i, int W, vector<int>& val, vector<int>& wt,
              vector<vector<int>>& dp) {

        // base case
        if(i == 0 || W == 0) {
            return 0;
        }

        // already computed
        if(dp[i][W] != -1) {
            return dp[i][W];
        }

        int take = 0;
        int skip = 0;

        // take current item
        if(wt[i-1] <= W) {

            take = val[i-1] +
                   solve(i-1, W - wt[i-1], val, wt, dp);
        }

        // skip current item
        skip = solve(i-1, W, val, wt, dp);

        // store and return
        return dp[i][W] = max(take, skip);
    }

    int knapsack(int W, vector<int> &val, vector<int> &wt) {

        int n = val.size();

        vector<vector<int>> dp(n + 1,
                               vector<int>(W + 1, -1));

        return solve(n, W, val, wt, dp);
    }
};

class Tabulation {
  public:
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        // code here
        //bottom approch 
        
        int n = val.size();
        
        //why n+1 and w +1 beacuse
        //n size and W size to fill the each n items with the W weight 
        //and +1 extra to fill the base case when we have to 0 items and 0 weight
        //so at 0th index base case and 
        //index 1st ( 1 items  , 1 weight) to  n,m ( when we have n items , with W weight)
        //answer will at the index of dp[n][W]
        //when n = 1 means 1 items which at 0 the index and when at nth index means last item
        vector<vector<int>>dp( n+1 , vector<int>(W+1));
        
        //fill the base case
        //when we have 0 itemd ( row indicate the items)
        for ( int j = 0 ; j < W +1 ; j++){
            dp[0][j] = 0;
        }
        //when we have 0 weight ( column for weight)
        for( int i = 0 ; i <n +1 ; i++){
            dp[i][0] = 0;
        }
        
        //fill the rest the table 
        for( int i = 1;  i< n +1 ; i++){//numner of items ( also number of weight})
            for(int j = 1 ; j < W + 1; j++){//numbere of capacity 
                
                int take = 0 ;
                int skip = 0 ;
                
                if( wt[i -1] <= j ) {//if current weight ( like if i = 1 then weight of 0th index)
                    take = val[i-1] + dp[i-1][j - wt[i-1]];//solve(i-1 , W - w(i-1)) like recursion 
                    //take the value of current val[i-1];
                    //here j - w[i-1] here we remove the current weight w[i-1] from current max weight (J)
                }
                
                //not take 
                skip = dp[i-1][j];//previous element without decresing the W weight like recursion solve(i-1 , W)
                
                //now max from both will be the value of the current dp 
                dp[i][j] = max( take , skip);
            }
        }
        
        return dp[n][W];
        
    }
};

class SpaceOptimized {
public:

    int knapsack(int W,
                 vector<int>& val,
                 vector<int>& wt) {

        int n = val.size();

        vector<int> prev(W + 1, 0);
        vector<int> curr(W + 1, 0);

        for(int i = 1; i <= n; i++) {

            for(int j = 1; j <= W; j++) {

                int take = 0;
                int skip = 0;

                // take current item
                if(wt[i-1] <= j) {

                    take =
                        val[i-1] +
                        prev[j - wt[i-1]];
                }

                // skip current item
                skip = prev[j];

                curr[j] = max(take, skip);
            }

            // move current row into previous row
            prev = curr;
        }

        return prev[W];
    }
};

// This is type 2 of writing this code
// Here ind represents the actual index of the item.
class MemoizationType2 {
public:

    int solve(vector<int>& wt,
              vector<int>& val,
              int ind,
              int capacity,
              vector<vector<int>>& dp) {

        // base case
        if(ind == 0) {
            if(wt[0] <= capacity) {
                return val[0];
            }

            return 0;
        }

        if(dp[ind][capacity] != -1) {
            return dp[ind][capacity];
        }

        // skip
        int notTake =
            solve(wt, val, ind - 1, capacity, dp);

        // take
        int take = 0;

        if(wt[ind] <= capacity) {
            take = val[ind] +
                   solve(wt, val,
                         ind - 1,
                         capacity - wt[ind],
                         dp);
        }

        return dp[ind][capacity] =
               max(take, notTake);
    }

    int knapsack(int W, vector<int>& val, vector<int>& wt) {

        int n = val.size();

        vector<vector<int>> dp(n,
                               vector<int>(W + 1, -1));

        return solve(wt, val, n - 1, W, dp);
    }
};

class TabulationType2 {
public:

    int knapsack(int W, vector<int>& val, vector<int>& wt) {

        int n = val.size();

        vector<vector<int>> dp(n,
                               vector<int>(W + 1, 0));

        // base case
        // if we only have item 0, then we can take it
        // for every capacity greater than or equal to wt[0]
        for(int capacity = wt[0]; capacity <= W; capacity++) {
            dp[0][capacity] = val[0];
        }

        for(int ind = 1; ind < n; ind++) {

            for(int capacity = 0; capacity <= W; capacity++) {

                // skip
                int notTake = dp[ind - 1][capacity];

                // take
                int take = 0;

                if(wt[ind] <= capacity) {
                    take = val[ind] +
                           dp[ind - 1][capacity - wt[ind]];
                }

                dp[ind][capacity] = max(take, notTake);
            }
        }

        return dp[n - 1][W];
    }
};

class SpaceOptimizedType2 {
public:

    int knapsack(int W, vector<int>& val, vector<int>& wt) {

        int n = val.size();

        vector<int> prev(W + 1, 0);
        vector<int> curr(W + 1, 0);

        // base case
        for(int capacity = wt[0]; capacity <= W; capacity++) {
            prev[capacity] = val[0];
        }

        for(int ind = 1; ind < n; ind++) {

            for(int capacity = 0; capacity <= W; capacity++) {

                // skip
                int notTake = prev[capacity];

                // take
                int take = 0;

                if(wt[ind] <= capacity) {
                    take = val[ind] +
                           prev[capacity - wt[ind]];
                }

                curr[capacity] = max(take, notTake);
            }

            prev = curr;
        }

        return prev[W];
    }
};

int main(){
    SpaceOptimized s;
    vector<int> val = {60, 100, 120};
    vector<int> wt = {10, 20, 30};
    int W = 50;
    cout << s.knapsack(W, val, wt) << endl;
    
    return 0;
}
