#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin>>n>>k;

    if(k < n || k > 2 * n -1){
        cout<<-1<<"\n";
        return;
    }

    vector<vector<int>>a(n ,vector<int>(n , 0));

    int t = 2* n - k;

    for(int i = 0 ; i < t;i++){
        a[i][i] =  i +1;
    }

    for(int i = t ; i < n ; i++){
        a[i-1][i] = 2 * i + 1 - t;
        a[i][i] = 2 * i + 2 - t;
    }

    int curr = k + 1;

    for(int i= 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(a[i][j] == 0){
                a[i][j] = curr++;
            }
        }
    }

    for(int i = 0 ; i< n ; i++){
        for(int j =0 ; j < n ; j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n"; 
    }




}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}