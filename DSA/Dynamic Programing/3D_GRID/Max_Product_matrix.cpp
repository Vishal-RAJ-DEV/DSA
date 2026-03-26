#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    typedef long long ll;
    int MOD = 1e9 + 7;
    int maxProductPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        //create the 2d matrix that stores the value of the pair
        vector<vector<pair<ll,ll>>>dp( n , vector<pair<ll, ll>>(m));
        //hrer dp[i][j] = {maxval , minval} to reach the (0,0)  to (i, j);

        //initally store the base case value in the dp 
        dp[0][0] = { grid[0][0] , grid[0][0]};
        //filling the base row value 0th row 
        for(int j = 1 ; j < m ; j++){
            dp[0][j].first = grid[0][j] * dp[0][j-1].first;//maxvalue 
            dp[0][j].second = grid[0][j] * dp[0][j-1].second;//minvalue
        }
        //filling the base column value 0th col val 
        for(int i = 1 ; i < n ;i++){
            dp[i][0].first = grid[i][0] * dp[i-1][0].first;
            dp[i][0].second = grid[i][0] * dp[i-1][0].second;

        }

        //now filling the rest of of hte cell from (1,1);
        for( int i = 1 ; i < n ; i++){
            for(int j = 1; j<m; j++){
                //all the value from the right and left with the product with the currrent cell grid[i][j]
                //from up
                ll upMaxVal = dp[i-1][j].first * grid[i][j];
                ll upMinVal = dp[i-1][j].second * grid[i][j];

                //from left
                ll leftMaxVal = dp[i][j-1].first * grid[i][j];
                ll leftMinVal = dp[i][j-1].second * grid[i][j]; 

                //now store store the maxval and minval among them in  the maxval of current [i][j]
                dp[i][j].first = max({upMaxVal,upMinVal,leftMaxVal,leftMinVal});
                dp[i][j].second = min({upMaxVal,upMinVal,leftMaxVal,leftMinVal});
            }
        }

        //value at (n-1 , m-1) has the last final maxval and minval 
        ll maxProd = dp[n-1][m-1].first;
        ll minProd = dp[n-1][m-1].second;

        return maxProd >= 0 ? maxProd % MOD : -1;
    }
};

class Solution {
public:
    typedef long long ll;
    int MOD = 1e9 + 7;

    vector<vector<pair<ll,ll>>> dp;

    pair<ll,ll> solve(int i, int j, vector<vector<int>>& grid, int n, int m){
        if(i == n-1 && j == m-1){
            return {grid[i][j], grid[i][j]};
        }

        if(dp[i][j].first != LLONG_MIN) return dp[i][j];

        ll maxprod = LLONG_MIN;
        ll minprod = LLONG_MAX;

        // right
        if(j + 1 < m){
            pair<ll,ll> result = solve(i, j+1, grid, n, m);
            ll rMax = result.first;
            ll rMin = result.second;

            ll a = grid[i][j] * rMax;
            ll b = grid[i][j] * rMin;

            maxprod = max(maxprod, max(a,b));
            minprod = min(minprod, min(a,b));
        }

        // down
        if(i + 1 < n){
            pair<ll,ll> result = solve(i+1, j, grid, n, m);
            ll dMax = result.first;
            ll dMin = result.second;

            ll a = grid[i][j] * dMax;
            ll b = grid[i][j] * dMin;

            maxprod = max(maxprod, max(a,b));
            minprod = min(minprod, min(a,b));
        }

        return dp[i][j] = {maxprod, minprod};
    }

    int maxProductPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        dp.assign(n, vector<pair<ll,ll>>(m, {LLONG_MIN, LLONG_MIN}));

        pair<ll,ll> result = solve(0, 0, grid, n, m);
        ll maxprod = result.first;
        ll minprod = result.second;

        return maxprod >= 0 ? maxprod % MOD : -1;
    }
};


int main(){
    vector<vector<int>> grid = {
        {1, -2, 1},
        {1, -2, 1},
        {3, -4, 1}
    };
    Solution sol;
    cout << sol.maxProductPath(grid) << endl;
    
    return 0;
}