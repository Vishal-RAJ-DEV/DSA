/*
 * Problem: Given an array a[1..n], we can change a[i] to gcd(a[i], i)
 * at cost (n - i + 1).  Find the minimum total cost to make the GCD
 * of the entire array equal to 1.
 *
 * ================================================================
 * Approach 1 — Greedy / Observation (O(n))
 * ================================================================
 *
 * Intuition:
 * - The cheapest position to change is the last one (i = n, cost = 1),
 *   then the second-last (i = n-1, cost = 2), and so on.
 * - Try the cheapest options first.
 *
 * Why does changing BOTH the last two positions ALWAYS work?
 *
 *   If we change a[n-1] → gcd(a[n-1], n-1)
 *   and      a[n]   → gcd(a[n],   n)
 *
 *   The overall GCD must divide both of these new values.
 *   Hence it must divide (n-1) and n as well.
 *   Since gcd(n-1, n) = 1  (consecutive integers are always coprime),
 *   the overall GCD of the whole array becomes 1.
 *
 *   So the answer is AT MOST 3.
 *
 * Algorithm:
 *   Cost 0: Already GCD = 1.
 *   Cost 1: Try changing only position n.
 *   Cost 2: Try changing only position n-1.
 *   Cost 3: Change both n-1 and n — guaranteed to work.
 *
 * ================================================================
 * Approach 2 — Brute Force Bitmask (O(n * 2^n))
 * ================================================================
 *
 * Intuition:
 * - For each of the n positions, we have 2 choices: keep original,
 *   or replace with gcd(a[i], i) at cost (n-i+1).
 * - Try all 2^n subsets of positions to change via a bitmask.
 * - Track the running GCD and cumulative cost.
 * - Record the minimum cost that achieves GCD = 1.
 *
 * This is the naïve exhaustive verification of Approach 1 —
 * it checks every possible combination and is only feasible
 * for small n (n ≤ 20 or so).
 */

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int arrayGCD(vector<int>& a) {
    int g = 0;
    for (int x : a)
        g = gcd(g, x);
    return g;
}

// ---------------------------------------------------------------
// Approach 1: Greedy — check cheapest positions (cost 1, 2, 3)
// ---------------------------------------------------------------
void solve_greedy() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        // Cost 0: already GCD = 1
        if (arrayGCD(a) == 1) {
            cout << 0 << '\n';
            continue;
        }

        // Cost 1: change only position n (last element, 0‑based index n-1)
        vector<int> b = a;
        b[n - 1] = gcd(b[n - 1], n);
        if (arrayGCD(b) == 1) {
            cout << 1 << '\n';
            continue;
        }

        // Cost 2: change only position n-1 (second-last)
        b = a;
        b[n - 2] = gcd(b[n - 2], n - 1);
        if (arrayGCD(b) == 1) {
            cout << 2 << '\n';
            continue;
        }

        // Cost 3: change both n-1 AND n
        // This ALWAYS works because gcd(n-1, n) = 1.
        // The overall GCD must divide (n-1) and n → must be 1.
        cout << 3 << '\n';
    }
}

// ---------------------------------------------------------------
// Approach 2: Brute force — try all subsets with a bitmask
// ---------------------------------------------------------------
void solve_bruteforce() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        // 1‑indexed for readability (cost = n - i + 1)
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        int ans = INT_MAX;

        // Try all 2^n subsets: bit j = 1 means "change position j+1"
        for (int mask = 0; mask < (1 << n); mask++) {

            int g = 0;      // running GCD
            int cost = 0;   // total cost of changed positions

            for (int i = 1; i <= n; i++) {
                int val;

                if (mask & (1 << (i - 1))) {
                    // Change a[i] → gcd(a[i], i), pay (n - i + 1)
                    val = gcd(a[i], i);
                    cost += (n - i + 1);
                } else {
                    val = a[i];
                }

                g = gcd(g, val);
            }

            if (g == 1)
                ans = min(ans, cost);
        }

        cout << ans << '\n';
    }
}

// ---------------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment the approach you want:
    // solve_greedy();
    // solve_bruteforce();

    return 0;
}
