#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve(){
    ll n , x;
    cin>>n>>x;

    vector<pair<ll,int>> a(n);
    for(int i = 0 ; i < n ; i++){
        cin >> a[i].first;
        a[i].second = i + 1; // Store original 1-based index
    }

    // Sort by value (two-pointer requires sorted array)
    sort(a.begin(), a.end());

    int l = 0, r = n - 1;
    while(l < r){
        ll sum = a[l].first + a[r].first;

        if(sum == x){
            // Print original indices (smaller first)
            cout << min(a[l].second, a[r].second) << " "
                 << max(a[l].second, a[r].second) << "\n";
            return;
        }
        else if(sum < x) l++;
        else r--;
    }

    cout << "IMPOSSIBLE" << "\n";
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--){
        solve();
    }

    return 0;
}