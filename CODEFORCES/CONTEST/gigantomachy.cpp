#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n , m;
    cin>>n>>m;

    long long a  , b;
    cin>>a;

    for(int i = 1; i < n ; i++){
        long long x;
        cin>>x;
    }

    cin>>b;

    for(int i = 1; i < m ; i++){
        long long x;
        cin>>x;
    }

    long long needB = a + n - 1;
    long long needV = b + m - 1;

    if(needV <= needB){
        cout<<1<<endl;
    }else{
        cout<<2<<endl;
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