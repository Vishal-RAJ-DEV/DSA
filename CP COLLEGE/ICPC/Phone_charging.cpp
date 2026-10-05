#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, a , b;
    cin>>n>>a>>b;

    int ans = 0;

    if(n < 80){
        ans = (80 - n) * a + 20 * b;
    }else{
        ans = (100 - n ) * b;
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