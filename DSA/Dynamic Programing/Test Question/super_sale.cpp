#include <bits/stdc++.h>
using namespace std;

int helper(int idx , int cap ,  vector<int>&val , vector<int>&wt , vector<vector<int> >&dp){
    if( idx ==0)return 0;
    if(cap == 0)return 0;
    if( dp[idx][cap] != -1)return dp[idx][cap];

    int notake = helper(idx -1 , cap , val , wt , dp);
    int take = 0;
    if( cap >= wt[idx -1]){
        take = val[idx -1] + helper(idx -1 , cap - wt[idx -1] , val , wt , dp);
    }
    return dp[idx][cap] = max(notake , take);
}
void solve() {
    int n;
    cin>>n;
    vector<int>val(n);
    vector<int>wt(n);
    for(int i = 0 ; i < n ; i++){
        cin>>val[i];
        cin>>wt[i];

    }
    int g;
    cin>>g;
    int ans = 0;
    while(g--){
        int cap;
        cin>>cap;
        vector<vector<int> >dp(n + 1 , vector<int>(cap + 1 , -1));
        ans += helper(n, cap , val , wt , dp);
    }

    cout<<ans<<endl;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}