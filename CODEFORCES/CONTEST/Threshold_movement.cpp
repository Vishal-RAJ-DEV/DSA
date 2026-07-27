#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin>>n;

    vector<long long> w( n + 1);
    long long minodd = LLONG_MAX;
    long long maxeven = LLONG_MIN;

    for(int i = 1; i <= n ; i++){
        cin>>w[i];
        if( i % 2)minodd = min( minodd , w[i]);
        else maxeven = max(maxeven , w[i]);

    }

    if( n % 2){
        cout<<"NO"<<endl;
    }else{
        if(maxeven + 1 < minodd){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
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