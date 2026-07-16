/*
 * Problem: Insert one distinct integer, choose x > 0. In one op, add x to one element.
 * Make all n+1 elements equal with minimum ops.
 *
 * Intuition:
 * - Target >= max (can't decrease). Pick Target = mx.
 * - An element can reach Target iff (Target - a[i]) % x == 0.
 * - To minimize ops, x must be the largest divisor of all differences → GCD(mx - a[i]).
 * - Existing ops = sum((mx - a[i]) / x).
 * - Inserted number must be ≡ mx (mod x). Closest missing below mx minimizes its ops.
 *
 * Algo:
 * 1. Find mx = max element.
 * 2. g = gcd of all (mx - a[i]).
 * 3. ans = sum((mx - a[i]) / g) for existing elements.
 * 4. Store all elements in a set.
 * 5. cur = mx - g; while cur is in set, cur -= g.
 * 6. ans += (mx - cur) / g for the inserted element.
 * 7. Print ans.
 *
 * TC: O(n + log(max)) per test case — O(n) for reading/gcd/sum, O(n) for set insert,
 *     while loop runs at most O(n) steps → overall O(n). Space: O(n).
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {

        int n;
        cin >> n;

        vector<long long> a(n);

        long long mx = LLONG_MIN;

        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
        }

        // Edge case: only one element
        if (n == 1) {
            cout << 1 << '\n';
            continue;
        }

        long long g = 0;

        for (int i = 0; i < n; i++) {
            g = __gcd(g, mx - a[i]);
        }

        long long ans = 0;

        for (int i = 0; i < n; i++) {
            ans += (mx - a[i]) / g;
        }

        set<long long> st(a.begin(), a.end());

        long long cur = mx - g;

        while (st.count(cur))
            cur -= g;

        ans += (mx - cur) / g;

        cout << ans << '\n';
    }

    return 0;
}