#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n , m;
    cin>> n >> m;

    vector<int> a(n) , b(m);
    for(auto &x : a) cin>> x;
    for(auto &x : b) cin>> x;

    if(n< 2 * m){
        cout<<"NO"<<endl;
        return;
    }

    sort(a.begin() , a.end());
    sort(b.begin() , b.end());

    bool ok = true;
    for(int i = 0 ; i < m ; i++){
        int low = a[i];
        int high= a[ n - m + i];
        if(!(low < b[i] && high > b[i] )){
            ok = false;
            break;
        }
    }

    cout<<(ok ? "YES" : "NO")<<endl;
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