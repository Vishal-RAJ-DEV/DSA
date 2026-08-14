// Problem: Count permutations of N zeros and M ones that start with 1
// https://www.hackerrank.com/challenges/sherlock-and-permutations/problem
//
// KEY INSIGHT:
// We need strings with N zeros and M ones that start with 1.
// Fix the first character as 1, then we have:
//   - N zeros to place
//   - M-1 ones remaining
//   - N + M - 1 total remaining positions
//
// So the answer is C(N + M - 1, N) = (N+M-1)! / (N! * (M-1)!)
// This is equivalent to C(N + M - 1, M - 1) since C(n, r) = C(n, n-r).
//
// EXAMPLE: N=2 zeros, M=3 ones
// Fix 1:  1 _ _ _ _
// Place 2 zeros in 4 positions: C(4, 2) = 6
// Valid strings: 10011, 10101, 10110, 11001, 11010, 11100

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const int MAXN = 2005; // Maximum N + M value

// Fast exponentiation: computes a^b mod MOD using binary exponentiation
// Time: O(log b)
// Used for modular inverse via Fermat's Little Theorem: a^(MOD-2) = a^(-1) mod MOD
ll power(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % MOD;
        }

        a = (a * a) % MOD;
        b >>= 1;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute factorials and inverse factorials up to MAXN
    // This allows O(1) combination queries after O(MAXN) precomputation
    vector<ll> fact(MAXN);
    vector<ll> invFact(MAXN);

    // fact[i] = i! mod MOD
    fact[0] = 1;

    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    // Compute inverse factorials using Fermat's Little Theorem:
    // invFact[MAXN-1] = fact[MAXN-1]^(MOD-2) mod MOD
    //
    // Then work backwards using the relation:
    //   1/i! = (i+1) / (i+1)!
    //   invFact[i] = invFact[i+1] * (i+1) mod MOD
    //
    // This computes ALL inverse factorials in O(MAXN) instead of
    // doing modular exponentiation for each one (which would be O(MAXN * log MOD))
    invFact[MAXN - 1] = power(fact[MAXN - 1], MOD - 2);

    for (int i = MAXN - 2; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        // After fixing the first 1, we have N+M-1 positions left
        // and need to choose N positions for zeros
        int n = N + M - 1;
        int r = N;

        // Compute C(n, r) = n! / (r! * (n-r)!)
        // Using precomputed factorials: n! * invFact[r] * invFact[n-r] mod MOD
        ll ans = fact[n];

        ans = (ans * invFact[r]) % MOD;
        ans = (ans * invFact[n - r]) % MOD;

        cout << ans << '\n';
    }

    return 0;
}

// COMPLEXITY ANALYSIS:
// Let MAXN = N + M <= 2000
//
// Precomputation:
//   Factorials:       O(MAXN)
//   Inverse factorials: O(MAXN)
//
// Each test case:
//   Computing nCr: O(1) - just 2 multiplications using precomputed values
//
// Total for T test cases: O(MAXN + T)
// Since MAXN ~ 2000, this is extremely fast even for large T.