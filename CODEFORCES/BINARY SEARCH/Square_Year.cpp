#include <bits/stdc++.h>
using namespace std;

void solve(){
    string s;
    cin>>s;

    int n = stoi(s);

    int num = sqrt(n);

    if( num * num != n){
        cout<<-1<<endl;
        return;
    }

    cout<<num<<" "<<0<<endl;
    
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