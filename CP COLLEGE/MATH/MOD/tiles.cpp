
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 998244353;

// Binary exponentiation: computes base^exp % MOD in O(log exp)
ll power(ll base, ll exp) {
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

    ll w, h;
    cin >> w >> h;

    // Answer = 2^(w+h) mod 998244353
    cout << power(2, w + h) << '\n';

    return 0;
}
