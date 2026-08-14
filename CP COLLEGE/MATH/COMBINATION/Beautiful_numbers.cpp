#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1000000007LL;

// Fast power: a^b % MOD
ll modPow(ll a, ll b) {
    ll res = 1;

    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;

        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

// Check whether x contains only digits a and b
bool isGood(ll x, int a, int b) {
    while (x > 0) {
        int digit = x % 10;

        if (digit != a && digit != b)
            return false;

        x /= 10;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, n;
    cin >> a >> b >> n;

    // factorials
    vector<ll> fact(n + 1);
    vector<ll> invFact(n + 1);

    fact[0] = 1;

    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    // inverse factorial
    invFact[n] = modPow(fact[n], MOD - 2);

    for (int i = n; i >= 1; i--) {
        invFact[i - 1] = invFact[i] * i % MOD;
    }

    // C(n, k)
    auto nCr = [&](int n, int k) -> ll {
        return fact[n] * invFact[k] % MOD
                         * invFact[n - k] % MOD;
    };

    ll ans = 0;

    for (int k = 0; k <= n; k++) {

        // k digits are b
        // n-k digits are a
        ll sum = 1LL * (n - k) * a + 1LL * k * b;

        // Is digit sum a good number?
        if (isGood(sum, a, b)) {
            ans = (ans + nCr(n, k)) % MOD;
        }
    }

    cout << ans << '\n';

    return 0;
}