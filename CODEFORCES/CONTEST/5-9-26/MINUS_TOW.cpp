#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin>>n;

    int odd = 0;
    int m1= 0;
    int m2 = 0;

    for(int i  =0 ; i < n; i++){
        long long x;
        cin>>x;

        if(x%2==1){
            odd++;
        }
        else if(x% 4== 0){
            m1++;
        }else{
            m2++;
        }
    }

    cout<<max({odd , m1 , m2})<<endl;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}