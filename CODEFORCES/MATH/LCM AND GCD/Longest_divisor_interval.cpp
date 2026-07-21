#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  PROBLEM (Codeforces: "Longest Divisor Interval")
 * ================================================================
 *  Given an integer n, find the length of the LONGEST interval
 *  [1, k]  (i.e., starting from 1) such that n is divisible by
 *  EVERY integer in that interval.
 *
 *  In other words, find the largest k where:
 *    n % 1 == 0,
 *    n % 2 == 0,
 *    n % 3 == 0,
 *    ...,
 *    n % k == 0    (ALL hold)
 *  and then output k.
 *
 * ----------------------------------------------------------------
 *  EXAMPLE
 * ----------------------------------------------------------------
 *  n = 12
 *    12 % 1 = 0 ✓
 *    12 % 2 = 0 ✓
 *    12 % 3 = 0 ✓
 *    12 % 4 = 0 ✓
 *    12 % 5 = 2 ✗  -> STOP
 *    Answer = 4   (interval [1,4] works, [1,5] does not)
 *
 *  n = 24
 *    24 % 1 = 0 ✓
 *    24 % 2 = 0 ✓
 *    24 % 3 = 0 ✓
 *    24 % 4 = 0 ✓
 *    24 % 5 = 4 ✗  -> STOP
 *    Answer = 4
 *
 *  n = 360360 (LCM of 1..15)
 *    Divisible by 1,2,3,...,15 all the way
 *    360360 % 16 = 8 ✗  -> STOP
 *    Answer = 15
 * ================================================================
 */

void solve() {
    long long n;
    cin >> n;

    /*
     * ================================================================
     *  ALGORITHM & INTUITION
     * ================================================================
     *
     *  The condition "n is divisible by all numbers 1..k" is
     *  EQUIVALENT to: n is divisible by LCM(1, 2, 3, ..., k).
     *
     *  Since LCM(1..k) grows SUPER-EXPONENTIALLY (it roughly follows
     *  e^k), for any n up to 10^18, the maximum possible k is at
     *  most ~42 (LCM(1..42) ≈ 2.1e19 > 10^18).
     *
     *  Therefore, we can simply CHECK CONSECUTIVELY from i=1 upward
     *  until we find the FIRST number that does NOT divide n.
     *
     *  --------------------------------------------------------------
     *  Why does this greedy check work? Can't there be a gap?
     *  --------------------------------------------------------------
     *  Since we always START FROM 1, the interval is a CONTIGUOUS
     *  PREFIX [1, k]. There is no "gap" possibility — we are checking
     *  the first k consecutive positive integers. The moment one
     *  fails, the interval breaks because EVERY number up to k must
     *  divide n. You can't skip a number.
     *
     *  --------------------------------------------------------------
     *  ALGORITHM STEPS
     *  --------------------------------------------------------------
     *  1. Start i = 1
     *  2. While n % i == 0, increment i
     *  3. The loop stops at the FIRST i where n % i != 0
     *  4. Answer = i - 1  (since 1..i-1 all divided n)
     *
     *  --------------------------------------------------------------
     *  TIME COMPLEXITY: O(k) = O(1) in practice
     *    k (the answer) is at most ~42 for 64-bit integers.
     *    So the loop is effectively constant-time.
     *
     *  SPACE COMPLEXITY: O(1)
     * ----------------------------------------------------------------
     */

    int i = 1;
    while (n % i == 0) {
        i++;
    }

    /*
     * i is the first integer that does NOT divide n.
     * So the last integer that DID divide n is i-1.
     * The interval [1, i-1] has length (i-1).
     */
    cout << i - 1 << "\n";
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
