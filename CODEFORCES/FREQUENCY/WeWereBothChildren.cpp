#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    /*
     * ================================================================
     *  PROBLEM (Codeforces: "We Were Both Children")
     * ================================================================
     * - There are n children standing at positions 1, 2, 3, ..., n
     * - There are n mice, each with a given landing position a[i]
     * - A child at position p can catch a mouse at position d
     *   ONLY IF d is a divisor of p  (i.e., p % d == 0)
     *   Equivalently: child p catches all mice whose positions divide p
     * - We must place ALL n children and pick ONE child that catches
     *   the maximum possible number of mice
     * - Output that maximum count
     *
     * EXAMPLE:
     *   n = 5, mice positions = [1, 2, 2, 3, 6]
     *   freq[1]=1, freq[2]=2, freq[3]=1, freq[6] ignored (> n)
     *
     *   Children:
     *     p=1: divisors of 1 are {1}            -> catches 1 mouse
     *     p=2: divisors of 2 are {1,2}          -> catches 1+2 = 3 mice
     *     p=3: divisors of 3 are {1,3}          -> catches 1+1 = 2 mice
     *     p=4: divisors of 4 are {1,2,4}        -> catches 1+2 = 3 mice
     *     p=5: divisors of 5 are {1,5}          -> catches 1+0 = 1 mouse
     *   Answer = 3
     * ================================================================
     */

    // freq[d] = how many mice landed exactly at position d (only if d <= n)
    // If a mouse lands at x > n, no child can catch it because children
    // only exist at positions 1..n and a divisor can never be > the number itself.
    // So we simply ignore those mice.
    vector<int> freq(n + 1, 0);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x <= n)
            freq[x]++;
    }

    /*
     * ================================================================
     *  KEY INSIGHT & APPROACH
     * ================================================================
     * NAIVE APPROACH (O(n^2), too slow):
     *   For each child p (1..n), iterate over all mice and check if
     *   mouse_position divides p. n up to 2e5 makes O(n^2) impossible.
     *
     * OPTIMIZED APPROACH (Divisor-Sieve, O(n log n)):
     *   Instead of checking per child, we INVERT THE PROBLEM:
     *
     *   1. A mouse at position d is caught by EVERY child whose position
     *      is a MULTIPLE of d (because d divides multiple).
     *
     *   2. So for each landing position d with freq[d] > 0, we ADD freq[d]
     *      to cnt[multiple] for all multiples of d (d, 2d, 3d, ... ≤ n).
     *
     *   3. cnt[p] ends up being: sum of freq[d] over all d that divide p.
     *      This is exactly the number of mice child p can catch.
     *
     *   This is analogous to the Sieve of Eratosthenes:
     *   - Outer loop: for d = 1 to n  (candidate divisor / mouse position)
     *   - Inner loop: for multiple = d; multiple <= n; multiple += d
     *                 (all children whose position is a multiple of d)
     *
     *   TIME COMPLEXITY: O(n log n)
     *     The inner loop runs n/d times for each d.
     *     Total iterations = n/1 + n/2 + n/3 + ... + n/n
     *                       = n * (1 + 1/2 + 1/3 + ... + 1/n)
     *                       = n * H_n            (harmonic number)
     *                       ≈ n * ln(n)          (≈ n log n)
     *
     *   SPACE COMPLEXITY: O(n)
     *     Two vectors of size n+1.
     * ================================================================
     */

    vector<int> cnt(n + 1, 0);  // cnt[p] = mice catchable by child at p
    int ans = 0;

    for (int d = 1; d <= n; d++) {
        // If no mouse landed at position d, nothing to distribute
        if (freq[d] == 0) continue;

        /*
         * freq[d] mice landed at position d.
         * They can ALL be caught by every child whose index is a
         * multiple of d: d, 2d, 3d, ..., floor(n/d)*d
         *
         * Example: d = 2, freq[2] = 3, n = 6
         *   -> add 3 to cnt[2], cnt[4], cnt[6]
         *   So children at positions 2,4,6 each catch these 3 mice.
         */
        for (int multiple = d; multiple <= n; multiple += d) {
            cnt[multiple] += freq[d];

            // Track global maximum as we go
            if (cnt[multiple] > ans)
                ans = cnt[multiple];
        }
    }

    cout << ans << '\n';
}

int main() {
    // Fast I/O — required because n can be up to 2e5 and t up to 1e4
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();
}
