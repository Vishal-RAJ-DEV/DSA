/*
    Problem: Modular Exponentiation (x^y mod n)

    Given integers x, y, n, compute  x^y mod n  efficiently.
    Used in many cryptographic operations.

    Input:
        - First line:  c  (number of datasets)
        - Next c lines: x y n  (positive integers)
        - Last line:   0  (terminator)

    Constraints:
        1 < x, n < 2^15 = 32768
        0 < y < 2^31 = 2147483648

    Output:
        For each dataset, print  x^y mod n

    Algorithm: Binary Exponentiation (Exponentiation by Squaring)
    -------------------------------------------------------------
    Instead of multiplying x by itself y times (O(y)), we use the
    binary representation of y to compute in O(log y).

    Intuition:
        Any exponent y can be written in binary. Example: y = 13 = 1101_2
        x^13 = x^(8+4+1) = x^8 * x^4 * x^1

        Iterate bits of y from LSB to MSB:
        - If current bit is 1: multiply result by current power of x
        - Square the base (mod n) for the next bit position
        - Shift y right by 1

        All operations are done modulo n to keep numbers small.

    Sample Input:
        2
        2 3 5
        2 2147483647 13
        0

    Sample Output:
        3
        11

    Explanation:
        2^3 mod 5 = 8 mod 5 = 3
        2^2147483647 mod 13 = 11
*/

#include <iostream>
using namespace std;

using ll = long long;

// Computes x^y mod n using binary exponentiation
ll modexp(ll x, ll y, ll n) {
    ll res = 1;
    x %= n;                     // handle x >= n

    while (y > 0) {
        if (y & 1)              // current LSB is 1 => include this power
            res = (res * x) % n;
        x = (x * x) % n;        // square x for the next bit position
        y >>= 1;                // shift to next bit
    }

    return res;
}

int main() {
    int c;
    while (cin >> c) {
        if (c == 0) break;      // terminator

        for (int i = 0; i < c; i++) {
            ll x, y, n;
            cin >> x >> y >> n;
            cout << modexp(x, y, n) << '\n';
        }
    }

    return 0;
}
