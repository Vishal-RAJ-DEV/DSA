#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int x;
    cin >> n >> x;

    vector<int> arr(n);
    for(int i =0 ; i < n; i++) {
        cin >> arr[i];
    }

    int left =0;
    int sum = 0;
    int cnt = 0;

    for(int right =0; right <n ; right++){
        sum +=arr[right];
        while(sum> x && left <= right){
            sum -=arr[left];
            left++;
        }

        if(sum == x){
            cnt++;
            sum -=arr[left];
            left++;
        }
    }

    cout << cnt << endl;
}

int main() {
    int t = 1;

    while (t--) {
        solve();
    }

    return 0;
}