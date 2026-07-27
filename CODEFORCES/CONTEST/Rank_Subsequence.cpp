#include <bits/stdc++.h>
using namespace std;

bool check( int m , const vector<array<int,4>>&a){
    int match =0;
    for(auto &x : a){
        if(match == m)break;

        int j = match + 1;
        bool badleft = (x[0] <= j && j <= x[1]);
        int rightrank = m - j + 1;
        bool badright = (x[2] <= rightrank && rightrank <= x[3]);

        if(!badleft && !badright)match++;
    }

    return match == m;
}
void solve(){
    int n;
    cin>>n;

    vector<array<int , 4>>a(n);
    for(int i = 0 ; i < n ; i++){
        cin>>a[i][0]>>a[i][1]>>a[i][2]>>a[i][3];
    }

    int low = 0;
    int high = n;
    while(low < high){
        int mid = (low + high + 1) / 2;
        if( check(mid  , a)){
            low = mid;
        }else{
            high = mid - 1;
        }
    }

    cout<<low<<endl;
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