#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;
    int org = n;

    int ans = 1;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            int cnt = 0;
            while(n % i == 0){
                cnt++;
                n /= i;
            }
            int currsum = 1;
            int currval = 1;
            for(int c = 1; c <= cnt; c++){
                currval *= i;
                currsum += currval;
            }
            ans *= currsum;
        }
    }
    if(n > 1){
        ans *= (1 + n);
    }
    cout << ans - org << "\n";
}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}