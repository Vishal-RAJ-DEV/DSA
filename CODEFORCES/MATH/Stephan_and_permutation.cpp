/*
 * ================================================================
 *  PROBLEM: Stephan and Permutation (Codeforces)
 * ================================================================
 *
 *  QUESTION:
 *  ---------
 *  You are given a permutation of numbers from 1 to n.
 *  You can perform the following operation any number of times:
 *    Choose two indices i and j (1-indexed). If |i - j| = x OR |i - j| = y,
 *    swap the elements at positions i and j.
 *
 *  Determine whether you can sort the permutation in ascending order
 *  using these operations.
 *
 *  Input:
 *    t  → number of test cases
 *    n, x, y → size of permutation, and the two allowed swap distances
 *    permutation of n numbers
 *
 *  Output: "YES" if sortable, "NO" otherwise.
 *
 *  INTUITION:
 *  ----------
 *  You are allowed to swap elements ONLY when their positions differ
 *  by exactly x or exactly y.
 *
 *  KEY INSIGHT — Reachability via GCD:
 *  ------------------------------------
 *  If you can swap positions at distance d1 and d2, then by composing
 *  swaps you can effectively move an element by any LINEAR COMBINATION
 *  of d1 and d2.
 *
 *  Example: If x = 4, y = 6:
 *    - Swap positions i and i+4 (distance 4)
 *    - Swap positions i and i+6 (distance 6)
 *    - By chaining: i ↔ i+4 and i+4 ↔ i+10 → net effect: i ↔ i+10 (distance 10 = 4+6)
 *    - More generally, any distance that is a multiple of gcd(4,6) = 2
 *      is achievable.
 *
 *  The set of all achievable distances is exactly the set of multiples
 *  of g = gcd(x, y). This is a classic result from number theory:
 *    The smallest positive integer representable as a linear combination
 *    of x and y is gcd(x, y), and every multiple of gcd(x, y) can be
 *    formed.
 *
 *  CRITICAL REALIZATION:
 *  ---------------------
 *  For the permutation to be sortable:
 *    - Element 'val' currently at position i (0-indexed) needs to move
 *      to position (val - 1) (0-indexed).
 *    - The distance it must travel = |(i+1) - val| (using 1-indexed positions).
 *    - This distance must be ACHIEVABLE, i.e., divisible by g = gcd(x, y).
 *
 *  If ALL elements can reach their correct positions (distance % g == 0),
 *  the array is sortable. Otherwise, it's not.
 *
 *  WHY does this work even without knowing the exact swap sequence?
 *  ----------------------------------------------------------------
 *  Because the allowed swaps generate a graph on indices 1..n where
 *  two indices are connected if their difference is a multiple of g.
 *  Within each connected component (all indices ≡ r mod g), you can
 *  freely permute elements. So an element can reach any position that
 *  shares the same residue modulo g.
 *
 *  An element 'val' at position i can be sorted iff
 *    i (mod g) == (val-1) (mod g)
 *    → (i+1 - val) % g == 0
 *    → ((i+1) - val) % g == 0   ✓  (matches the code)
 *
 *  ALGORITHM:
 *  ----------
 *  1. Compute g = gcd(x, y).
 *  2. For each position i (0-indexed) in the permutation:
 *       Read val = a[i].
 *       If ((i+1) - val) % g != 0:
 *         → this element cannot reach its target → output "NO".
 *  3. If all positions pass → output "YES".
 *
 *  COMPLEXITY:
 *  -----------
 *  Time  → O(n * log(min(x,y))) per test case (gcd computation + linear scan)
 *  Space → O(1)
 */

#include <bits/stdc++.h>
using namespace std;

// Euclidean algorithm to compute GCD of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    int t;                     // number of test cases
    cin >> t;

    while (t--) {
        int n, x, y;           // n = permutation size, x/y = allowed swap distances
        cin >> n >> x >> y;

        /*
         * g = gcd(x, y) determines the "step size" of movement.
         * Elements can only move distances that are multiples of g.
         */
        int g = gcd(x, y);
        bool cansort = true;   // assume sortable until proven otherwise

        /*
         * Check each element of the permutation.
         * Element 'val' is at index i (0-indexed).
         * Its correct 1-indexed position is 'val', which is at 0-indexed position (val-1).
         * Distance needed = |current_pos - target_pos| = |(i+1) - val|.
         * If this distance is NOT divisible by g, the element cannot reach
         * its correct position → permutation is NOT sortable.
         */
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;

            if (((i + 1) - val) % g != 0) {
                cansort = false;
            }
        }

        cout << (cansort ? "YES" : "NO") << endl;
    }

    return 0;
}
