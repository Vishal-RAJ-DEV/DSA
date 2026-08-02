#include <bits/stdc++.h>
using namespace std;

void solve(){
    string s;
    cin>> s;

    int n = s.size();

    int idx = -1;
    for(int i = 0 ; i + 1 < n ; i++){
        if( s[i] == '0' && s[i+1] == '1'){
            idx= i;
            break;
        }
    }

    if(idx == -1){
        idx = s.find_last_of('0');
    }
    s.erase(s.begin() + idx);

    int m = s.size();
    int idx2 = -1;
    for(int i = 0 ; i + 1 < m ; i++){
        if(s[i] =='1' && s[i+1] == '0'){
            idx2 = i;
            break;
        }
    }
    if( idx2 == -1){
        idx2 = s.find_last_of('1');
    }

    s.erase(s.begin() + idx2);

    cout<<s<<endl;
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