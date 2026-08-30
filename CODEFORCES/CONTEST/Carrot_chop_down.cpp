#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin>>n>>m;

    vector<int>freq(m + 2 , 0);

    for(int i= 0 ; i < n ; i++){
        int x;
        cin>>x;
        freq[x]++;
    }

    vector<int>g(m + 1, 0);

    for(int x = m - 1; x >= 1; x--){
        g[x] = g[x + 1] + freq[x + 1];
    }

    int ans = 0;
    for(int x = 1; x <= m ; x++){
        int curr = freq[x] + g[x];

        if(2 * x <= m ){
            curr += freq[2 * x];
        }

        ans = max(ans , curr);
    }
    cout<<ans<<endl;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}