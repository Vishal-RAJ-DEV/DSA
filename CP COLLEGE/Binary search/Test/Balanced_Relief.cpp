#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n,m;
    cin>> n >> m;

    vector<int> a(n);
    vector<int> b(m);
    for(int i=0;i<n;i++){
        cin>> a[i];
    }
    for(int i=0;i<m;i++){
        cin>> b[i];
    }
    int l, r;
    cin>> l >> r;

    sort(b.begin(), b.end());
    int ans = 0 ;

    for(int i=0;i<n;i++){
        int x = a[i];
        int low = lower_bound(b.begin(), b.end(), l-x) - b.begin();
        int high = upper_bound(b.begin(), b.end(), r-x) - b.begin();
        ans += (high - low);
    }

    cout << ans << endl;

}

int main() {
    int t = 1;

    while (t--) {
        solve();
    }

    return 0;
}