/*
    This file demonstrates exponentiation (power) computation using
    Binary Exponentiation (also called Fast Exponentiation / Exponentiation
    by Squaring), with three variants:

      1. Integer power (exact result)
      2. Double power (handles negative exponents)
      3. Last-digit power (computes a^b % 10 using modular exponentiation)

    Binary Exponentiation Intuition:
    ---------------------------------
    Any exponent n can be written in binary. Example: n = 13 = 1101₂ = 8+4+1
    So  base^13  =  base^(8+4+1)  =  base^8 * base^4 * base^1

    We iterate through bits of exponent from LSB to MSB:
      - If current bit is 1: multiply ans by current base
      - Square the base for the next bit position
      - Shift exponent right by 1
    This gives O(log n) time instead of O(n).
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ----------------------------------------------------------------
// Approach 1: Integer Binary Exponentiation (exact result)
//
// Computes base^exp for non-negative integer exp.
// Uses binary exponentiation: O(log exp) time, O(1) space.
//
// Intuition:
//   Any exponent can be expressed as sum of powers of 2 (binary).
//   Example: exp = 13 = 1101_2 = 8 + 4 + 1
//   So base^13 = base^8 * base^4 * base^1
//
//   We process bits from LSB (rightmost) to MSB (leftmost):
//     1. If current LSB is 1: multiply ans by current base value
//     2. Square base (prepares it for the next higher bit position)
//     3. Right-shift exp by 1 (discard the bit we just processed)
//   This works because each bit position i represents base^(2^i).
//   After squaring i times, base = base^(2^i).
//
// Right-shift (>>) explanation:
//   exp >>= 1  shifts all bits of exp one position to the right.
//   It's equivalent to integer division by 2: exp = exp / 2.
//   The LSB is dropped after checking it via (exp & 1).
//   Example: exp = 13 = 1101_2
//     Iteration 1: exp & 1 = 1101 & 0001 = 1  -> use this bit
//                  exp >>= 1 -> 1101 -> 0110 = 6  (LSB dropped)
//     Iteration 2: exp & 1 = 0110 & 0001 = 0
//                  exp >>= 1 -> 0110 -> 0011 = 3
//     Iteration 3: exp & 1 = 0011 & 0001 = 1  -> use this bit
//                  exp >>= 1 -> 0011 -> 0001 = 1
//     Iteration 4: exp & 1 = 0001 & 0001 = 1  -> use this bit
//                  exp >>= 1 -> 0001 -> 0000 = 0  (loop ends)
//
// DETALED DRY RUN: power_int(2, 13)
//   base = 2, exp = 13 (1101_2), ans = 1
//   ┌──────┬────────┬─────────────┬────────────┬──────────┐
//   │ Iter │ exp    │ exp & 1     │ ans        │ base     │
//   │      │ (binary)│ (use bit?)  │            │ (squared)│
//   ├──────┼────────┼─────────────┼────────────┼──────────┤
//   │  1   │ 13=1101│ 1 (YES)     │ 1*2  = 2   │ 2^2 = 4  │
//   │  2   │  6=0110│ 0  (NO)     │ 2          │ 4^2 = 16 │
//   │  3   │  3=0011│ 1 (YES)     │ 2*16 = 32  │ 16^2=256 │
//   │  4   │  1=0001│ 1 (YES)     │ 32*256=8192│ 256^2    │
//   │  5   │  0=0000│ (loop ends) │            │          │
//   └──────┴────────┴─────────────┴────────────┴──────────┘
//   Result: 8192 = 2^13 ✓
//
//   Why ans = 2 * 16 * 256 = 8192?
//   13 in binary is 1101 -> bits at positions 0,2,3 are set
//   Position 0: base^(2^0) = base^1   = 2^1
//   Position 2: base^(2^2) = base^4   = 2^4 = 16
//   Position 3: base^(2^3) = base^8   = 2^8 = 256
//   Product = 2^1 * 2^4 * 2^8 = 2^(1+4+8) = 2^13 ✓
//
//   After each iteration, base squares: base, base^2, base^4, base^8...
//   These are exactly the values base^(2^i) for i = 0,1,2,3...
//   We multiply ans by the current base only when the corresponding
//   bit of exp is 1.
// ----------------------------------------------------------------
ll power_int(ll base, ll exp) {
    ll ans = 1;
    while (exp > 0) {
        if (exp & 1)          // current LSB is 1? multiply ans
            ans *= base;
        base *= base;          // square base for next bit position
        exp >>= 1;             // discard processed bit (exp = exp / 2)
    }
    return ans;
}

// ----------------------------------------------------------------
// Approach 2: Double Power (handles negative exponents)
//
// Computes x^n where n can be negative.
// Uses a variant of binary exponentiation with decrement approach.
//
// Intuition:
//   - If n < 0, compute x^|n| first, then take reciprocal (1/result).
//   - If nn is odd:  subtract 1 from nn, multiply ans by x
//   - If nn is even: divide nn by 2,   square x
//   This works because:
//     x^n = (x^2)^(n/2)    when n is even
//     x^n = x * x^(n-1)    when n is odd
// ----------------------------------------------------------------
double myPow(double x, int n) {
    double ans = 1.0;
    long long nn = n;

    if (nn < 0)
        nn = -nn;             // work with positive exponent first

    while (nn) {
        if (nn % 2) {         // odd exponent
            ans = ans * x;
            nn = nn - 1;
        } else {              // even exponent
            x = x * x;
            nn = nn / 2;
        }
    }

    if (n < 0)
        ans = 1.0 / ans;      // x^(-n) = 1 / x^n

    return ans;
}

// ----------------------------------------------------------------
// Approach 3: Last Digit of a^b (Modular Exponentiation % 10)
//
// Computes the last digit of a^b.
// Last digit = a^b % 10. Use modular exponentiation with mod = 10.
//
// Intuition:
//   Same binary exponentiation but every multiplication is done
//   modulo 10, so numbers never overflow.
//   The last digit of a^b depends only on (a % 10)^b.
// ----------------------------------------------------------------
ll last_digit_pow(ll a, ll b) {
    ll ans = 1;
    a %= 10;                  // last digit depends only on a % 10

    while (b > 0) {
        if (b & 1)
            ans = (ans * a) % 10;
        a = (a * a) % 10;
        b >>= 1;
    }

    return ans;
}

// Helper: extract last digit of any number
ll findlast(ll num) {
    return num % 10;
}

int main() {
    // Test: integer binary exponentiation
    ll base = 2, exp = 18;
    ll result = power_int(base, exp);
    cout << "2^18 = " << result << endl;
    cout << "Last digit of 2^18 = " << findlast(result) << endl;

    // Test: last-digit power using modular exponentiation
    cout << "Last digit of 2^18 (modular) = " << last_digit_pow(2, 18) << endl;

    // Test: double power
    cout << "2.0^(-3) = " << myPow(2.0, -3) << endl;

    return 0;
}

