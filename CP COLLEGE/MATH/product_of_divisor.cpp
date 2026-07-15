#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

using ll = long long;

// =========================================================================
// QUESTION: Product of All Divisors of n
//
// Given a positive integer n, find the product of ALL its positive
// divisors. Return the result modulo 10^9+7 or as a full integer
// (here we return full integer for explanation; in competitive coding
// you'd usually return it modulo MOD).
//
// Example: n = 12
//   Divisors = {1, 2, 3, 4, 6, 12}
//   Product  = 1 × 2 × 3 × 4 × 6 × 12 = 1728
// =========================================================================

// =========================================================================
// INTUITION — The Pairing Trick
// =========================================================================
//
// Imagine writing all divisors of n in sorted order:
//
//   n = 12  →  divisors = [1, 2, 3, 4, 6, 12]
//
// Notice a beautiful pattern:
//
//   1 × 12 = 12          (smallest × largest)
//   2 × 6  = 12          (second smallest × second largest)
//   3 × 4  = 12          (third smallest × third largest)
//
// EVERY pair multiplies to n!
//
// WHY? If d is a divisor of n, then n/d is ALSO a divisor of n.
// And d × (n/d) = n. Always.
//
// So the product of ALL divisors can be computed as:
//
//   Product = (d1 × n/d1) × (d2 × n/d2) × ... × (dk × n/dk)
//           = n × n × ... × n
//           = n^(d/2)
//
// where d = total number of divisors.
//
// =========================================================================
// SPECIAL CASE — Perfect Squares (odd number of divisors)
// =========================================================================
//
// n = 36  →  divisors = [1, 2, 3, 4, 6, 9, 12, 18, 36]
//                                            ↑
//                                     6 pairs with itself
//
//   Pairs:
//     1 × 36 = 36
//     2 × 18 = 36
//     3 × 12 = 36
//     4 × 9  = 36
//     6 × 6  = 36   ← middle element, pairs with ITSELF
//
// When n is a perfect square, √n is a divisor that pairs with itself.
// Number of divisors d is ODD (only perfect squares have odd divisor count).
//
// Product = n × n × ... × n (for the (d-1)/2 full pairs) × √n (the middle)
//         = n^((d-1)/2) × √n
//         = n^(d/2) × √n       (since integer division: (d-1)/2 == d/2)
//
// UNIFIED FORMULA:
//   Product = n^(d/2)          if d is even
//           = n^(d/2) × √n     if d is odd (n is a perfect square)
//
// =========================================================================
// WHY DOES A PERFECT SQUARE HAVE ODD DIVISOR COUNT?
//
// If n = p1^e1 × p2^e2 × ... × pk^ek:
//   divisor count d = (e1+1) × (e2+1) × ... × (ek+1)
//
// For n to be a perfect square, ALL exponents ei must be even.
// Then (ei+1) is ODD for every prime factor.
// Odd × Odd = Odd → d is odd.
//
// Example: 36 = 2^2 × 3^2  →  d = (2+1)×(2+1) = 3×3 = 9 (odd) ✓
// =========================================================================

// =========================================================================
// ALGORITHM STEPS
// =========================================================================
    
/*Intuition to Remember

Imagine writing all divisors in sorted order
1 2 3 4 6 12

The first and last always multiply to n.
The second and second-last always multiply to n.
The third and third-last always multiply to n.

So instead of multiplying every divisor individually, you count how many pairs there are.
--->>If the number of divisors is even, there are d / 2 pairs, so the product is n^(d/2).
--->>If the number of divisors is odd (which only happens for perfect squares), every pair still multiplies to n, except the middle divisor, which is √n and pairs with itself. That gives the equivalent result n^(d/2) × √n.

This pairing observation is the entire intuition behind the product of divisors formula.
*/
//
// Step 1: Compute divisor count d via prime factorization:
//           For each prime factor p with exponent e:
//             d *= (e + 1)
//
// Step 2: Compute product using the formula:
//           product = n^(d/2)               if d even
//           product = n^(d/2) × sqrt(n)     if d odd
//
//         Use fast exponentiation (binary exponentiation) for n^(d/2).
//
// EXAMPLE TRACE: n = 12
//   Prime factorization: 12 = 2^2 × 3^1
//   divisorCount = (2+1) × (1+1) = 3 × 2 = 6  (even)
//
//   product = 12^(6/2) = 12^3 = 1728 ✓
//
// EXAMPLE TRACE: n = 36
//   Prime factorization: 36 = 2^2 × 3^2
//   divisorCount = (2+1) × (2+1) = 3 × 3 = 9  (odd → perfect square)
//
//   product = 36^(9/2) × √36
//           = 36^4 × 6
//           = 1679616 × 6
//           = 10077696 ✓
//
// TIME:  O(√n) for prime factorization + O(log d) for exponentiation
// SPACE: O(1)
// =========================================================================

// Binary Exponentiation (fast power): computes base^exp in O(log exp)
ll power(ll base, ll exp) {
    ll ans = 1;
    while (exp > 0) {
        if (exp & 1)          // if current bit is set
            ans *= base;      // multiply answer by current base
        base *= base;          // square the base for next bit
        exp >>= 1;             // shift to next bit
    }
    return ans;
}

ll productOfDivisors(ll n) {

    ll original = n;           // save original n (n will be modified)
    ll divisorCount = 1;       // multiplicative identity for divisor count

    // ---- Step 1: Count divisors via prime factorization ----
    // For each prime factor p^e, multiply divisorCount by (e+1)
    for (ll i = 2; i * i <= n; i++) {

        if (n % i == 0) {      // i is a prime factor

            int cnt = 0;       // count exponent of prime i

            while (n % i == 0) {
                cnt++;
                n /= i;        // divide out this factor
            }

            divisorCount *= (cnt + 1);   // (e+1) contribution
        }
    }

    // If n > 1, remaining n is a prime factor with exponent 1
    if (n > 1)
        divisorCount *= 2;     // (1+1) = 2

    // ---- Step 2: Compute product using the pairing formula ----

    // n^(d/2) is common to both cases
    ll halfExp = divisorCount / 2;          // integer division
    ll product = power(original, halfExp);  // n^(d/2)

    if (divisorCount % 2 == 0) {
        // Even divisor count: all divisors pair perfectly
        // Product = n^(d/2)
        return product;
    } else {
        // Odd divisor count (perfect square):
        // Product = n^(d/2) × sqrt(n)
        product *= (ll)sqrt(original);
        return product;
    }
}

// =========================================================================
// MAIN — Test Cases
// =========================================================================

int main() {

    cout << "=== Product of Divisors ===\n\n";

    // ---------------------------------------------------------------
    // Test 1: n = 12  (even divisor count)
    //   Divisors = {1,2,3,4,6,12}
    //   divisorCount = 6  (even)
    //   Product = 12^(6/2) = 12^3 = 1728
    //   Verification: 1×2×3×4×6×12 = 1728 ✓
    // ---------------------------------------------------------------
    {
        ll n = 12;
        ll res = productOfDivisors(n);
        cout << "n = " << n << "  → Product = " << res
             << "  (expected: 1728)\n";
    }

    // ---------------------------------------------------------------
    // Test 2: n = 36  (odd divisor count — perfect square)
    //   Divisors = {1,2,3,4,6,9,12,18,36}
    //   divisorCount = 9  (odd)
    //   Product = 36^4 × 6 = 10077696
    // ---------------------------------------------------------------
    {
        ll n = 36;
        ll res = productOfDivisors(n);
        cout << "n = " << n << "  → Product = " << res
             << "  (expected: 10077696)\n";
    }

    // ---------------------------------------------------------------
    // Test 3: n = 1  (edge case)
    //   Divisors = {1}
    //   divisorCount = 1  (odd)
    //   Product = 1^(0) × sqrt(1) = 1 × 1 = 1
    // ---------------------------------------------------------------
    {
        ll n = 1;
        ll res = productOfDivisors(n);
        cout << "n = " << n << "  → Product = " << res
             << "  (expected: 1)\n";
    }

    // ---------------------------------------------------------------
    // Test 4: n = 6
    //   Divisors = {1,2,3,6}
    //   divisorCount = 4  (even)
    //   Product = 6^(4/2) = 6^2 = 36
    //   Verification: 1×2×3×6 = 36 ✓
    // ---------------------------------------------------------------
    {
        ll n = 6;
        ll res = productOfDivisors(n);
        cout << "n = " << n << "  → Product = " << res
             << "  (expected: 36)\n";
    }

    // ---------------------------------------------------------------
    // Test 5: n = 16 = 2^4  (perfect square)
    //   Divisors = {1,2,4,8,16}
    //   divisorCount = 5  (odd)
    //   Product = 16^2 × 4 = 256 × 4 = 1024
    //   Verification: 1×2×4×8×16 = 1024 ✓
    // ---------------------------------------------------------------
    {
        ll n = 16;
        ll res = productOfDivisors(n);
        cout << "n = " << n << "  → Product = " << res
             << "  (expected: 1024)\n";
    }

    return 0;
}
