#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  PROBLEM: Insane Problem (Codeforces)
 * ================================================================
 *  Count pairs (x, y) such that:
 *    l1 ≤ x ≤ r1
 *    l2 ≤ y ≤ r2
 *    y = x × k^n   for some n ≥ 0
 *
 * ================================================================
 *  INTUITION & APPROACH
 * ================================================================
 *
 *  Instead of iterating over x and y (too slow), we ask:
 *    "For one fixed power p = kⁿ, how many x are valid?"
 *
 *  Given p, the equation is:  y = x × p
 *  Also:  l2 ≤ y ≤ r2  →  l2 ≤ x × p ≤ r2
 *  Dividing by p:  l2/p ≤ x ≤ r2/p
 *
 *  But x also has its own bounds:  l1 ≤ x ≤ r1
 *  So the overall valid range for x is the INTERSECTION:
 *
 *    left  = max(l1,  ceil(l2 / p))
 *    right = min(r1, floor(r2 / p))
 *
 *  If left ≤ right, then (right - left + 1) x-values work for this p.
 *  Sum this over all powers p = k⁰, k¹, k², ... while p ≤ r2.
 *
 * ----------------------------------------------------------------
 *  Why is this fast?
 * ----------------------------------------------------------------
 *  k ≥ 2 → powers grow exponentially (1, k, k², k³, ...).
 *  Since r2 ≤ 10⁹, the number of powers is at most ~30 (for k=2,
 *  2³⁰ ≈ 10⁹). So we iterate over at most ~30 powers instead of
 *  billions of (x, y) pairs.
 *
 * ----------------------------------------------------------------
 *  Special case: k = 1
 * ----------------------------------------------------------------
 *  Powers: 1, 1, 1, ...   (infinite loop!)
 *  When k=1, equation becomes y = x.
 *  Answer = length of intersection of [l1, r1] and [l2, r2].
 *
 * ----------------------------------------------------------------
 *  ceil(a / b) for integers:
 *    ceil(l2 / p)  =  (l2 + p - 1) / p   (integer division trick)
 *
 *  floor(r2 / p):
 *    Simply r2 / p  (integer division truncates down).
 * ================================================================
 */

typedef long long ll;
const ll INF = 1e9;  // maximum constraint value for r2

void solve() {
    ll k, l1, r1, l2, r2;
    cin >> k >> l1 >> r1 >> l2 >> r2;

    ll ans = 0;

    // ---- Special case: k == 1 → powers are all 1 (infinite loop) ----
    // Equation reduces to y = x.
    // Answer = overlap of [l1, r1] and [l2, r2]
    if (k == 1) {
        ll left  = max(l1, l2);
        ll right = min(r1, r2);

        if (left <= right) {
            ans = right - left + 1;
        }

        cout << ans << "\n";
        return;
    }

    // ---- General case: k ≥ 2 ----
    // Iterate over all powers p = 1, k, k², k³, ... ≤ r2
    ll power = 1;
    while (power <= INF && power <= r2) {

        // x must satisfy BOTH:
        //   l1 ≤ x ≤ r1                    (original x range)
        //   l2 / p ≤ x ≤ r2 / p           (y = x*p must be in [l2, r2])
        //
        // ceil(l2 / p) = (l2 + power - 1) / power  (integer trick)
        ll left  = max(l1, (l2 + power - 1) / power);
        ll right = min(r1, r2 / power);           // floor division

        // If a valid range exists, add all integer x values in it
        if (left <= right) {
            ans += (right - left + 1);
        }

        // Prevent overflow: if power > INF/k, multiplying by k would
        // exceed the bound, so we stop (power would be > r2 anyway).
        if (power > INF / k) {
            break;
        }
        power *= k;  // next power: k⁰ → k¹ → k² → ...
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
