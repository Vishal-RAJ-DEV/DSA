#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int k;
    cin >> n >> k;

    vector<int>arr(n);

    for(int i = 0 ; i < n ;i++){
        cin>>arr[i];
    }

    int left = 0;
    int sum = 0;
    int cnt = 0;
    for(int right = 0 ; right < n ; right++){
        sum += arr[right];

        if(right - left + 1 > k){
            if(sum % k == 0)cnt++;
            sum -= arr[left];
            left++;

        }

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