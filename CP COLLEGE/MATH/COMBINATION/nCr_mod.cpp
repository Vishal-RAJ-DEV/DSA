#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;

// Fast Power: calculates (a^b) % MOD
ll power(ll a, ll b) {
    ll result = 1;

    while (b > 0) {

        // If b is odd
        if (b & 1) {
            result = result * a % MOD;
        }

        // Square a
        a = a * a % MOD;

        // Divide b by 2
        b >>= 1;
    }

    return result;
}

int main() {

    int N = 1000000;

    // fact[i] = i!
    vector<ll> fact(N + 1);

    // invFact[i] = (i!)^(-1) mod MOD
    vector<ll> invFact(N + 1);

    // --------------------------------
    // Step 1: Calculate factorials
    // --------------------------------

    fact[0] = 1;

    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    // --------------------------------
    // Step 2: Calculate inverse of N!
    // Using Fermat:
    //
    // (N!)^(-1) = (N!)^(MOD - 2)
    // --------------------------------

    invFact[N] = power(fact[N], MOD - 2);

    // --------------------------------
    // Step 3: Calculate all inverse
    // factorials
    // --------------------------------

    for (int i = N; i >= 1; i--) {
        invFact[i - 1] = invFact[i] * i % MOD;
    }

    // --------------------------------
    // Step 4: Calculate nCr
    // --------------------------------

    int n = 5;
    int r = 2;

    if (r > n) {
        cout << 0 << endl;
    }
    else {

        ll answer =
            fact[n]
            * invFact[r] % MOD
            * invFact[n - r] % MOD;

        cout << answer << endl;
    }

    return 0;
}