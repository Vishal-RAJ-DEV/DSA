#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

using ll = long long;

// =========================================================================
// QUESTION: Sum of All Divisors of n
//
// Given a positive integer n, find the sum of ALL its positive divisors.
// Example: n = 12
//   Divisors = {1, 2, 3, 4, 6, 12}
//   Sum = 1 + 2 + 3 + 4 + 6 + 12 = 28
// =========================================================================

// =========================================================================
// FORMULA — Sum of Divisors using Prime Factorization
// =========================================================================
//
// By the Fundamental Theorem of Arithmetic:
//   n = p1^e1 * p2^e2 * ... * pk^ek
//
// Every divisor of n is of the form:
//   p1^f1 * p2^f2 * ... * pk^fk    where 0 <= fi <= ei
//
// The SUM of all divisors can be written as a PRODUCT of sums:
//
//   sum = (1 + p1 + p1^2 + ... + p1^e1)
//       * (1 + p2 + p2^2 + ... + p2^e2)
//       * ...
//       * (1 + pk + pk^2 + ... + pk^ek)
//
// WHY THIS WORKS — Expanding the product:
//   When you multiply all these brackets, you get every possible
//   combination of exponents (f1, f2, ..., fk) exactly once.
//   Each term in the expansion is p1^f1 * p2^f2 * ... * pk^fk,
//   which is exactly one divisor of n. Summing them = sum of divisors.
//
// EXAMPLE: n = 12 = 2^2 * 3^1
//   sum = (1 + 2 + 2^2) * (1 + 3^1)
//       = (1 + 2 + 4) * (1 + 3)
//       = 7 * 4
//       = 28 ✓
// =========================================================================

// =========================================================================
// GEOMETRIC PROGRESSION (GP) SERIES
// =========================================================================
//
// Each bracket (1 + p + p^2 + ... + p^e) is a Geometric Progression.
//   - First term (a) = 1
//   - Common ratio (r) = p
//   - Number of terms = e + 1
//
// CLOSED-FORM FORMULA:
//   Sum of GP = a * (r^(e+1) - 1) / (r - 1)
//             = 1 * (p^(e+1) - 1) / (p - 1)
//
// Example: p = 2, e = 2
//   Sum = (2^3 - 1) / (2 - 1) = (8 - 1) / 1 = 7 = 1 + 2 + 4 ✓
//
// In the code below, instead of using the closed-form formula (which
// would need pow/power function), we compute the GP sum ITERATIVELY:
//
//   sum = 1        (p^0)
//   power = 1
//   for j = 1 to cnt:
//       power *= p       → power = p^j
//       sum += power      → accumulate: 1 + p + p^2 + ... + p^cnt
//
// This is O(cnt) per prime factor, which is fine since total cnt
// across all factors is O(log n).
// =========================================================================

// =========================================================================
// ALGORITHM WALKTHROUGH
// =========================================================================
//
// Step 1: Initialize ans = 1 (multiplicative identity).
//
// Step 2: For i = 2 to sqrt(n):
//           If i divides n:
//             cnt = 0
//             While i divides n: n /= i, cnt++   (extract prime factor)
//
//             Compute GP sum = 1 + i + i^2 + ... + i^cnt
//               power = 1
//               for j = 1 to cnt:
//                   power *= i     → i^j
//                   sum += power
//
//             ans *= sum
//
// Step 3: After loop, if n > 1:
//           The remaining n is a prime factor with exponent 1.
//           GP sum = 1 + n^1 = 1 + n
//           ans *= (1 + n)
//
// Step 4: Return ans.
//
// EXAMPLE TRACE: n = 84 = 2^2 * 3 * 7
//
//   ans = 1
//
//   i = 2:
//     84 % 2 == 0 → cnt = 0
//       while: cnt=1, n=42
//       while: cnt=2, n=21
//       → cnt = 2
//     GP sum for 2^2: power=1
//       j=1: power=2,  sum=1+2=3
//       j=2: power=4,  sum=3+4=7
//     ans *= 7 → ans = 7
//
//   i = 3:
//     21 % 3 == 0 → cnt = 0
//       while: cnt=1, n=7
//       → cnt = 1
//     GP sum for 3^1: power=1
//       j=1: power=3,  sum=1+3=4
//     ans *= 4 → ans = 28
//
//   i = 4: 4*4=16 > 7 → loop exits
//
//   n = 7 > 1 → leftover prime 7 with exponent 1
//     GP sum = 1 + 7 = 8
//     ans *= 8 → ans = 224
//
//   Result: 224
//   Verification: divisors of 84 = {1,2,3,4,6,7,12,14,21,28,42,84}
//                 sum = 224 ✓
//
// TIME:  O(sqrt(n)) — same as divisor count algorithm
// SPACE: O(1)
// =========================================================================

ll sumOfDivisors(ll n)
{
    ll ans = 1;                   // start with multiplicative identity

    // Trial division up to sqrt(current n)
    // n shrinks as we divide out factors → loop may end early
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)           // i is a prime factor of current n
        {
            int cnt = 0;          // count exponent of prime i

            // Divide out ALL occurrences of i from n
            while (n % i == 0)
            {
                cnt++;
                n /= i;
            }

            // Compute GP sum: 1 + i + i^2 + ... + i^cnt
            ll sum = 1;           // start with i^0 = 1
            ll power = 1;         // tracks i^j as j increments

            for (int j = 1; j <= cnt; j++)
            {
                power *= i;       // power = i^j
                sum += power;     // accumulate: 1 + i + ... + i^j
            }

            ans *= sum;           // multiply contribution of this prime
        }
    }

    // If n > 1, the remaining n is a prime factor with exponent 1.
    // Its GP sum = 1 + n^1 = 1 + n.
    // This is the same as the formula: ans *= (n^(1+1) - 1) / (n - 1)
    //                                = (n^2 - 1) / (n - 1)
    //                                = n + 1
    if (n > 1)
    {
        ans *= (1 + n);
    }

    return ans;
}

// =========================================================================
// MAIN — Test Cases
// =========================================================================

int main()
{
    // Test 1: n = 12
    //   Prime: 12 = 2^2 * 3
    //   Sum = (1+2+4) * (1+3) = 7 * 4 = 28
    {
        ll n = 12;
        ll res = sumOfDivisors(n);
        cout << "n = " << n << ", sum of divisors = " << res
             << " (expected: 28)\n";
    }

    // Test 2: n = 84
    //   Prime: 84 = 2^2 * 3 * 7
    //   Sum = (1+2+4) * (1+3) * (1+7) = 7 * 4 * 8 = 224
    {
        ll n = 84;
        ll res = sumOfDivisors(n);
        cout << "n = " << n << ", sum of divisors = " << res
             << " (expected: 224)\n";
    }

    // Test 3: n = 1 (edge case)
    //   No prime factors, loop doesn't execute, n > 1 is false.
    //   ans = 1 → sum of divisors of 1 = 1
    {
        ll n = 1;
        ll res = sumOfDivisors(n);
        cout << "n = " << n << ", sum of divisors = " << res
             << " (expected: 1)\n";
    }

    // Test 4: n = 28
    //   Prime: 28 = 2^2 * 7
    //   Sum = (1+2+4) * (1+7) = 7 * 8 = 56
    //   Divisors of 28 = {1,2,4,7,14,28}, sum = 56
    {
        ll n = 28;
        ll res = sumOfDivisors(n);
        cout << "n = " << n << ", sum of divisors = " << res
             << " (expected: 56)\n";
    }

    // Test 5: n = 9973 (prime number)
    //   Prime: 9973^1
    //   Sum = 1 + 9973 = 9974
    {
        ll n = 9973;
        ll res = sumOfDivisors(n);
        cout << "n = " << n << ", sum of divisors = " << res
             << " (expected: 9974)\n";
    }

    return 0;
}
