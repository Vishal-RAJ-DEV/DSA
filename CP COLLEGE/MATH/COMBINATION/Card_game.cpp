#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1000000007;

ll power(ll a, ll b) {
    ll res = 1;

    while (b) {
        if (b & 1)
            res = res * a % MOD;

        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {

        int N, K;
        cin >> N >> K;

        vector<ll> a(N);

        for (ll &x : a)
            cin >> x;

        // Sort so that elements before a[i]
        // are guaranteed to be smaller.
        sort(a.begin(), a.end());

        vector<ll> fact(N + 1);
        vector<ll> invFact(N + 1);

        // factorial
        fact[0] = 1;

        for (int i = 1; i <= N; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        // inverse factorial
        invFact[N] = power(fact[N], MOD - 2);

        for (int i = N - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        auto nCr = [&](int n, int r) -> ll {

            if (r < 0 || r > n)
                return 0;

            return fact[n]
                   * invFact[r] % MOD
                   * invFact[n - r] % MOD;
        };

        ll ans = 0;

        for (int i = 0; i < N; i++) {

            // a[i] is fixed as maximum.
            // Choose remaining K-1 elements
            // from the i smaller elements.
            //here for ith index , there is i smaller elements and we have to choose K-1 elements from them
            ll ways = nCr(i, K - 1);

            ans = (ans + (a[i] % MOD) * ways) % MOD;
        }

        cout << "Case #" << tc << ": " << ans << '\n';
    }

    return 0;
}