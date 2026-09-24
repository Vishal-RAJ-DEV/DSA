#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n ;
    string s;
    cin>>n>>s;
    
    const int INF = 1e9;

    int dp0 = 0;
    int dp1 =INF;
    
    for(int i = 0 ; i <n ;i++){
        int ndp0 = INF;
        int ndp1 = INF;

        if(s[i] = '0'){
            ndp0 = min(ndp0 , dp0);

        }else{
            if(i > 0 ){
                ndp0 = min(ndp0 , dp0 + 1);
            }
        }

        if(s[i] = '1'){
            ndp1 = min(dp1 , dp0);
        }else{
            ndp1 = min(dp1 + 1 , dp0 + 1);
        }

        dp0 = ndp0;
        dp1 = ndp1;

    }
    cout<<min(dp0 , dp1)<<endl;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}