#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1000000007;

ll power(ll base, ll exp) {

    // Handle negative base
    base = (base % MOD + MOD) % MOD;

    ll ans = 1;

    while (exp > 0) {

        if (exp & 1)
            ans = (ans * base) % MOD;

        base = (base * base) % MOD;

        exp >>= 1;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {

        ll k, n;
        cin >> k >> n;

        ll sum = 0;

        for (int i = 0; i <= n; i++) {
            ll x;
            cin >> x;

            sum = (sum + x) % MOD;

            // Make sum non-negative
            if (sum < 0)
                sum += MOD;
        }

        cout << power(sum, k) << '\n';
    }

    return 0;
}