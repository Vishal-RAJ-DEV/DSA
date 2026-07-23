/*
 * Problem: A robot needs to travel exactly (x, y) — i.e., move x units
 * right and y units down.  Each operation is a single move vector (dx, dy)
 * where dx, dy are positive integers and each must fit within a given
 * limit k (dx <= k, dy <= k).  We may use as many moves as we like, but
 * we want to MINIMIZE the number of DISTINCT move vectors used.
 *
 * The key question: can we reach (x, y) using only ONE repeated vector?
 *
 * --------------------------------------------------------------------
 * Intuition:
 * --------------------------------------------------------------------
 *
 * 1) If we use only one move vector (dx, dy) repeated m times, then
 *    total displacement = m * (dx, dy) = (x, y).
 *    Therefore (dx, dy) = (x/m , y/m).
 *
 * 2) Since dx, dy must be integers, m must divide both x and y.
 *    To minimise the step size (so it fits within k), we MAXIMISE m.
 *    The largest possible m is gcd(x, y).
 *
 * 3) The SMALLEST possible single-step vector is therefore:
 *       dx = x / gcd(x,y)
 *       dy = y / gcd(x,y)
 *
 * 4) If even this smallest step fits within k in BOTH coordinates, then
 *    we can reach (x, y) with 1 repeated vector → answer = 1.
 *
 * 5) Otherwise, every repeated single vector will exceed k in at least
 *    one coordinate → one vector is impossible → answer = 2.
 *    (The problem guarantees that 2 distinct vectors always suffice.)
 *
 * Interview explanation for "Why GCD?":
 *   "If I use only one move vector repeatedly, the total displacement
 *    must be an integer multiple of that vector.  So the vector must
 *    divide both x and y.  To maximise repetitions (minimising step
 *    size to stay within k), I divide by the GREATEST common divisor.
 *    If even this smallest repeated move exceeds k, then no single
 *    vector can work, so I need at least two distinct vectors."
 *
 * Example:
 *   x = 6, y = 4, k = 2
 *   gcd = 2, dx = 3, dy = 2
 *   dx = 3 > k = 2  →  answer = 2
 *   (We cannot use one repeated vector because the minimal
 *    step (3,2) exceeds k in the x-coordinate.)
 *
 *   x = 6, y = 4, k = 3
 *   gcd = 2, dx = 3, dy = 2
 *   Both ≤ 3        →  answer = 1
 *   (Repeat (3,2) twice: 2*(3,2) = (6,4).)
 */

#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long x, y, k;       // target (x,y), step limit k
        cin >> x >> y >> k;

        int g = gcd(x, y);       // maximum possible repetitions
        long long dx = x / g;    // smallest valid x-step
        long long dy = y / g;    // smallest valid y-step

        // If the smallest step fits, 1 repeated vector works.
        // Otherwise, we need at least 2 distinct vectors.
        if (dx <= k && dy <= k)
            cout << 1 << '\n';
        else
            cout << 2 << '\n';
    }

    return 0;
}