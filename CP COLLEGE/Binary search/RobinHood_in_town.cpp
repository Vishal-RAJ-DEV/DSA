#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Check whether Robin Hood will appear after adding x gold
bool canMakeRobinHood(ll x, const vector<int>& a, ll sum, int n) {

    // New total wealth after adding x to the richest person
    ll newSum = sum + x;

    int unhappy = 0;

    // A person is unhappy if:
    //
    // wealth < (newSum / n) / 2
    //
    // Instead of using floating point,
    // multiply both sides by (2*n):
    //
    // wealth < newSum / (2*n)
    //
    // becomes
    //
    // wealth * 2 * n < newSum
    //
    // This avoids precision errors.
    for (int wealth : a) {
        if (2LL * wealth * n < newSum)
            unhappy++;
    }

    // Robin Hood appears if
    // unhappy people > half the population
    return unhappy > n / 2;
}

void solve() {

    int n;
    cin >> n;

    // For n = 1 or n = 2,
    // it is impossible because the richest person
    // can never be unhappy.
    if (n <= 2) {

        vector<int> dummy(n);
        for (int i = 0; i < n; i++)
            cin >> dummy[i];

        cout << -1 << '\n';
        return;
    }

    vector<int> a(n);

    ll sum = 0;
    int mx = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        mx = max(mx, a[i]);
    }

    ll low = 0;
    ll high = 1e18;
    ll ans = -1;

    while (low <= high) {

        ll mid = low + (high - low) / 2;

        if (canMakeRobinHood(mid, a, sum, n)) {

            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    cout << ans << '\n';
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--)
        solve();

    return 0;
}