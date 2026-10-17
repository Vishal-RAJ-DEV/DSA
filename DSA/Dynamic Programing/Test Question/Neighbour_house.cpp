#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int helper(int idx , int last , vector<vector<int>>&matrix , vector<vector<int>>&dp){
    if( idx ==0)return matrix[0][last];
    if( dp[idx][last] != -1)return dp[idx][last];
    int mini = INT_MAX;

    for(int j = 0 ; j < 3 ; j++){
        if( j != last){
            mini = min( mini , matrix[idx][last] + helper(idx -1 , j , matrix , dp));
        }
    }
    return dp[idx][last] = mini;
}
void solve(){
    int n;
    cin>>n;
    vector<vector<int>>matrix(n , vector<int>(3));
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < 3 ; j++){
            cin>>matrix[i][j];
        }
    }

    vector<vector<int>>dp(n , vector<int>(3 , -1));
    int ans = INT_MAX;
    for(int j = 0 ; j < 3 ; j++){
        ans = min( ans , helper( n -1 , j , matrix , dp)); 
    }
    cout<<ans<<endl;

}

int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}