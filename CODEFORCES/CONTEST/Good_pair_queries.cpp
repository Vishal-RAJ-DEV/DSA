#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n ,q;
    cin>>n>>q;

    string s , t;
    cin>>s>>t;
    s = " " + s;
    t = " " + t;
    

    vector<int>p1(n + 1, 0 ) , p2(n + 1 , 0);
    for(int i = 1; i <= n ; i++){
        p1[i] = p1[i-1] + ((s[i] == '0' && t[i] == '1') ? 1 : 0);  
        p2[i] = p2[i-1] + ((s[i] == '1' && t[i] =='0') ? 1 : 0);
    }

    string res;
    res.reserve((size_t)q * 4);
    
    for(int i = 0 ; i < q ; i++){
        int l , r;
        cin>>l>>r;

        int c1 = p1[r] - p1[l-1];
        int c2 = p2[r] - p2[l -1];

        int len = r - l + 1;
        long long m = max(c1 , c2);

        if( 2 * m <= len ){
            res += "YES\n";
        }else{
            res += "NO\n";
        }
    }
    cout << res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}