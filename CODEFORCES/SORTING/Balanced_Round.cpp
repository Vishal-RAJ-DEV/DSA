#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n , k;
    cin>> n >> k;

    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin>> a[i];
    }
    if(n <= 1){
        cout<< 0 << endl;
        return;
    }

    sort(a.begin(), a.end());

    // Find the longest contiguous segment where adjacent differences <= k
    int max_Seg = 1;  // longest valid segment found so far
    int cnt = 1;       // current segment length
    for(int i = 1; i < n; i++){
        if( a[i] - a[i - 1] <= k ){
            cnt++;  // extend current segment
        }else{
            max_Seg = max(max_Seg, cnt);  // segment ended, update max
            cnt = 1;                      // start new segment
        }   
    }

    max_Seg = max(max_Seg, cnt);  // handle last segment

    // Minimum removals = total problems - max keepable problems
    cout<<n - max_Seg << endl;
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
