#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; long long x;
    cin >> n >> x;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    map<long long, long long> cnt;
    cnt[0] = 1;
    long long pref = 0, ans = 0;

    for (int i = 0; i < n; i++) {
        pref += arr[i];
        ans += cnt[pref - x];  // subarrays ending at i with sum x
        cnt[pref]++;
    }

    cout << ans << "\n";

}

int main() {
    int t = 1;

    while (t--) {
        solve();
    }

    return 0;
}