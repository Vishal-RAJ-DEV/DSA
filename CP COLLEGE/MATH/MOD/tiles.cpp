
/* Problem: Tiling a w x h grid
 *
 * Intuition:
 *
 * Step 1 — Patterns A & B
 *   Each row can start with Pattern A or Pattern B.
 *   Once the leftmost tile is fixed (2 choices), the remaining
 *   tiles in that row are completely forced.
 *   => Each row contributes 2 choices.  For h rows: 2^h
 *
 * Step 2 — Columns
 *   Same reasoning vertically. Each column can start with Pattern A
 *   or Pattern B, forcing the cells below.
 *   => Each column contributes 2 choices.  For w columns: 2^w
 *
 * Step 3 — Combine
 *   Row choices and column choices are independent, so multiply:
 *     2^h  ×  2^w  =  2^(h+w)
 *
 * The answer is therefore 2^(w+h) modulo 998244353.
 */

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
