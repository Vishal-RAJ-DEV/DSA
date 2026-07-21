#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Problem: Sherlock and his Girlfriend (CF 776B)
// ============================================================
//
// Statement:
//   Sherlock has n items. The i-th item has price = i+1 (i.e.,
//   prices range from 2 to n+1). He needs to color the items
//   such that if the price of one item is a PRIME DIVISOR of
//   the price of another item, the two items must have
//   different colors. Find the minimum number of colors needed
//   and output the color for each item (prices 2..n+1).
//
// Example:
//   n = 3  →  prices = {2, 3, 4}
//   2 is a prime divisor of 4 → they need different colors.
//   3 has no prime divisor relationship with 2 or 4.
//   So 2 colors suffice: primes → 1, composites → 2.
//
// ============================================================
// Intuition & Reasoning
// ============================================================
//
// Key observations:
//   - A prime number cannot be a prime divisor of another prime
//     (unless they are equal, but items have distinct prices).
//     So no two primes conflict.
//   - A composite number always has at least one prime divisor,
//     so it conflicts with every prime that divides it.
//     But two composites generally do NOT conflict, because
//     composite A dividing composite B does not make A a
//     "prime divisor" of B — a prime divisor must be prime.
//
// Therefore the conflict graph is BIPARTITE:
//   Primes on one side, composites on the other.
//   Edges only go from a prime to the composites it divides.
//
//   → Minimum colors needed = 2 (when both primes and composites
//     exist), else 1 (when there are only primes, i.e., n ≤ 2).
//
//   n = 1 → prices {2}          → only primes  → 1 color
//   n = 2 → prices {2, 3}       → only primes  → 1 color
//   n ≥ 3 → prices have both
//           primes & composites  → 2 colors
//
// ============================================================
// Prime Checking Algorithms (both provided in this file)
// ============================================================

// --- Method 1: Trial Division (used in solve()) ---
//   Check divisibility from 2 to sqrt(n).
//   Time: O(√n) per query. Good for single / few checks.
//   Space: O(1)
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// --- Method 2: Sieve of Eratosthenes (provided but unused) ---
//   Precompute all primes up to a limit in O(N log log N).
//   Idea:
//     1. Assume all numbers ≥ 2 are prime.
//     2. Start from 2 — mark all multiples of 2 as composite.
//     3. Move to next unmarked number (3) — mark its multiples.
//     4. Repeat up to √limit.
//   Time: O(N log log N)  — nearly linear.
//   Space: O(N) for the boolean array.
//
//   Best when you need many prime checks in a range.
vector<bool> sieve(int limit, vector<bool> &isPrime) {
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= limit; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

// --- Method 3: Optimized Trial Division ---
//   Same as Method 1 but handle 2 separately then check only
//   odd numbers, halving the iterations.
//   Time: O(√n / 2) — constant-factor improvement.
bool isPrimeOptimized(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}
// ============================================================
// Solution
// ============================================================
//
// The coloring follows directly from our bipartite observation:
//   - If n ≤ 2: only primes exist → 1 color (all 1's)
//   - Otherwise: primes get 1, composites get 2
//
// We check primality using trial division (isPrime) for each
// number from 2 to n+1.

void solve() {
    int n;
    cin >> n;

    if (n <= 2) {
        cout << 1 << endl;
        for (int i = 1; i <= n; i++) {
            cout << 1 << " ";
        }
        cout << endl;
        return;
    }

    cout << 2 << endl;
    for (int i = 2; i <= n + 1; i++) {
        if (isPrime(i)) {
            cout << 1 << " ";
        } else {
            cout << 2 << " ";
        }
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
