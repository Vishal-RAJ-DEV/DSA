#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//tabulation approch 

int tabulation( int n){
    vector<int> dp(n + 1);
    dp[0] = 1; //base case
    dp[1] = 1; //base case
    //both give the same result because we can take 1 step from 0 to 1 and we can take 2 steps from 0 to 2 or we can take 1 step from 0 to 1 and then 1 step from 1 to 2 so both give the same resultx

    for( int i = 2 ; i <= n ; i++){
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

//memoization approach
class Solution
{
public:
    int solve(int n, vector<int> &dp)
    {
        if (n <= 2)
            return n;

        if (dp[n] != -1)
            return dp[n];

        return dp[n] = solve(n - 1, dp) + solve(n - 2, dp);
    }
    int climbStairs(int n)
    {
        vector<int> dp(n + 1, -1);
        return solve(n, dp);
    }
};
int main()
{
    Solution sol;
    int n = 5;
    cout << sol.climbStairs(n) << endl;
    return 0;
}