/*
    Problem (Minimum Scaling Factor):
    Given array b[] of length n, find the smallest positive integer x
    such that for every adjacent pair (b[i], b[i+1]):
        b[i]  divides  x * b[i+1]    i.e.  b[i] | x * b[i+1]

    In other words, x is the minimum multiplier that, when applied to
    b[i+1], makes it divisible by b[i] for ALL consecutive pairs.

    ----------------------------------------------------------------
    Mathematical Derivation:

    For a single pair (b[i], b[i+1]):
        Let g = gcd(b[i], b[i+1]).
        Write b[i]   = g * p
             b[i+1] = g * q
        where p and q are coprime (gcd(p, q) = 1).

        The condition b[i] | x * b[i+1] becomes:
            g * p  |  x * g * q
            =>  p  |  x * q

        Since gcd(p, q) = 1, q cannot help. Therefore:
            p  |  x
            i.e.,  x must be a multiple of  p = b[i] / gcd(b[i], b[i+1])

        Special case: If b[i+1] % b[i] == 0, then:
            gcd(b[i], b[i+1]) = b[i]  =>  p = 1
            So x must be a multiple of 1 (no constraint).

    Since x must satisfy the condition for ALL pairs simultaneously,
    the answer is the LCM of all per-pair requirements.
    ----------------------------------------------------------------
    Algorithm:
        1. ans = 1
        2. For each i in 0..n-2:
            - If b[i+1] % b[i] == 0: continue (need = 1, no effect)
            - Else:
                g   = gcd(b[i], b[i+1])
                need = b[i] / g    (the unique factor of b[i] not in b[i+1])
                ans = lcm(ans, need)
        3. Print ans
    ----------------------------------------------------------------
    Example:
        b = [6, 15, 10]
        i=0: b[1]=15, 15%6≠0, g=gcd(6,15)=3, need=6/3=2, ans=lcm(1,2)=2
        i=1: b[2]=10, 10%15≠0, g=gcd(15,10)=5, need=15/5=3, ans=lcm(2,3)=6
        Output: 6
        Verification:
            6 | 6*15  =>  6 | 90 ✓
            15 | 6*10 => 15 | 60 ✓
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll lcm(ll a, ll b) {
    return (a / __gcd(a, b)) * b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<ll> b(n);

        for (int i = 0; i < n; i++)
            cin >> b[i];

        ll ans = 1;

        for (int i = 0; i < n - 1; i++) {

            // If b[i] already divides b[i+1], need = 1 => no impact on ans
            if (b[i + 1] % b[i] == 0)
                continue;

            // Extract the unique prime factors of b[i] not shared with b[i+1]
            ll g = __gcd(b[i], b[i + 1]);
            ll need = b[i] / g;

            // x must be a multiple of 'need' for this pair; combine via LCM
            ans = lcm(ans, need);
        }

        cout << ans << '\n';
    }

    return 0;
}