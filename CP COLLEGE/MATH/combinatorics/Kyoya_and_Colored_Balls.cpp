#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;
const int MAXN = 1005;

ll fact[MAXN];
ll invFact[MAXN];

// Fast modular exponentiation
ll power(ll a, ll b) {
    ll result = 1;

    while (b > 0) {
        if (b & 1) {
            result = result * a % MOD;
        }

        a = a * a % MOD;
        b >>= 1;
    }

    return result;
}

// Calculate nCr modulo MOD
ll nCr(int n, int r) {
    if (r < 0 || r > n)
        return 0;

    return fact[n] * invFact[r] % MOD
                   * invFact[n - r] % MOD;
}

int main() {
    int k;
    cin >> k;

    vector<int> c(k);

    for (int i = 0; i < k; i++) {
        cin >> c[i];
    }

    // Precompute factorials
    fact[0] = 1;

    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    // Precompute inverse factorials
    invFact[MAXN - 1] = power(fact[MAXN - 1], MOD - 2);

    for (int i = MAXN - 2; i >= 0; i--) {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }

    ll answer = 1;

    // Number of balls already processed
    int previousBalls = c[0];

    for (int i = 1; i < k; i++) {

        // Choose positions for (c[i] - 1) balls
        // among previousBalls + c[i] - 1 positions
        answer = answer *
                 nCr(previousBalls + c[i] - 1, c[i] - 1)
                 % MOD;

        previousBalls += c[i];
    }

    cout << answer << '\n';

    return 0;
}