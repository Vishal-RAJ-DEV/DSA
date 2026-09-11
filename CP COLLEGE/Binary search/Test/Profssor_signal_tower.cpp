#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool canPlace(const vector<ll>& x, int k, ll d) {
    int count = 1;              // place first tower
    ll last = x[0];

    for (int i = 1; i < x.size(); i++) {
        if (x[i] - last >= d) {
            count++;
            last = x[i];

            if (count >= k)
                return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<ll> x(n);

    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    // x is already sorted according to the problem.
    // If it wasn't guaranteed, we would use:
    // sort(x.begin(), x.end());

    ll lo = 0;
    ll hi = x[n - 1] - x[0];

    ll ans = 0;

    while (lo <= hi) {
        ll mid = lo + (hi - lo) / 2;

        if (canPlace(x, k, mid)) {
            // mid is possible.
            // Try to find a larger minimum distance.
            ans = mid;
            lo = mid + 1;
        } else {
            // mid is not possible.
            // Need a smaller distance.
            hi = mid - 1;
        }
    }

    cout << ans << '\n';

    return 0;
}