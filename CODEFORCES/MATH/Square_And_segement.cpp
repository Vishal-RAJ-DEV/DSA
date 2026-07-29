#include <bits/stdc++.h>
using namespace std;
// Overall Algorithm
// Try every possible width w from 1 to √n.
// Compute the minimum height h = ceil(n / w) using (n + w - 1) / w.
// Compute the cost w + h.
// Keep the minimum cost.
// Print the answer.

// Time Complexity: O(√n)
// Space Complexity: O(1)
void solve(){
    int n;
    cin>>n;

    int ans = INT_MAX;

    for(int w = 1 ; w * w <= n ; w++){
        int h = ( n + w - 1) / w;

        int lines = w + h;

        ans = min(ans , lines );
    }

    cout<<ans<<endl;
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