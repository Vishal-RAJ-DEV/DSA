#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// =========================================================================
// QUESTION: Sum of Proper Divisors
//
// Given a positive integer n, find the sum of its PROPER divisors.
// Proper divisors = all positive divisors of n EXCLUDING n itself.
//
// Example: n = 12
//   All divisors    = {1, 2, 3, 4, 6, 12}  → sum = 28
//   Proper divisors = {1, 2, 3, 4, 6}       → sum = 16
//                                                      (28 - 12 = 16)
// =========================================================================

// =========================================================================
// KEY DIFFERENCE from "Sum of All Divisors"
// =========================================================================
//
// Both problems use the SAME prime factorization approach:
//   n = p1^e1 * p2^e2 * ... * pk^ek
//
//   Sum of ALL divisors = (1 + p1 + p1^2 + ... + p1^e1)
//                        * (1 + p2 + p2^2 + ... + p2^e2)
//                        * ...
//                        * (1 + pk + pk^2 + ... + pk^ek)
//
//   This product includes n itself as a term (when we pick the
//   highest exponent for EVERY prime factor simultaneously:
//   p1^e1 * p2^e2 * ... * pk^ek = n).
//
// SUM OF PROPER DIVISORS = (Sum of ALL divisors) - n
//
//   Because the only divisor excluded is the number itself.
//   So we compute the full product, then SUBTRACT the original n.
//
// In the code:
//   ans = product of all GP series (sum of ALL divisors)
//   return ans - org   ← subtract n to get proper divisor sum
//
// EXAMPLE: n = 12 = 2^2 * 3
//   All divisors sum = (1+2+4) * (1+3) = 7 * 4 = 28
//   Proper sum       = 28 - 12 = 16
//   Divisors of 12 = {1,2,3,4,6,12} → proper = {1,2,3,4,6}
//   Sum of proper = 1+2+3+4+6 = 16 ✓
// =========================================================================

// =========================================================================
// FORMULA REFRESHER — GP Series for each prime factor
// =========================================================================
//
// For a prime factor p^e, the sum of its powers is a Geometric
// Progression:
//   1 + p + p^2 + ... + p^e
//
// Computed iteratively:
//   sum = 1        (p^0)
//   for j = 1 to e:
//       power *= p   → p^j
//       sum += power
//
// These GP sums are multiplied across all prime factors to get
// the sum of ALL divisors.
// =========================================================================

class Solution {
public:

    long long int divSum(int n) {

        int org = n;                  // save original n (needed for subtraction at end)
        long long ans = 1;            // multiplicative identity

        // Trial division: find prime factors up to sqrt(n)
        for (long long i = 2; i * i <= n; i++) {

            if (n % i == 0) {         // i is a prime factor of current n

                int cnt = 0;          // count exponent of prime i

                // Divide out ALL occurrences of i
                while (n % i == 0) {
                    cnt++;
                    n /= i;
                }

                // Compute GP sum: 1 + i + i^2 + ... + i^cnt
                long long currsum = 1;    // start with i^0 = 1
                long long currval = 1;    // tracks i^j

                for (int j = 1; j <= cnt; j++) {
                    currval *= i;         // currval = i^j
                    currsum += currval;   // accumulate: 1 + i + ... + i^j
                }

                ans *= currsum;           // multiply contribution of this prime
            }
        }

        // If n > 1, the remaining n is a prime factor with exponent 1
        // GP sum = 1 + n
        if (n > 1) {
            ans *= (1 + n);
        }

        // KEY DIFFERENCE from sum of ALL divisors:
        // Subtract the original number to exclude it from the sum.
        // ans currently holds sum of ALL divisors (including n).
        // Proper divisors exclude n itself, so ans = ans - org.
        return ans - org;
    }
};


// =========================================================================
// MAIN — Test Cases with comparison to Sum of All Divisors
// =========================================================================

int main() {

    cout << "=== Sum of Proper Divisors ===\n";
    cout << "(Compare with Sum of All Divisors to see the difference)\n\n";

    // Test 1: n = 12
    //   All divisors sum    = 1+2+3+4+6+12 = 28
    //   Proper divisors sum = 1+2+3+4+6    = 16  (28 - 12)
    {
        Solution s;
        int n = 12;
        int res = s.divSum(n);
        cout << "n = " << n
             << "  → Proper sum: " << res
             << "  (All sum: 28, diff: " << (28 - res) << " = n)\n";
    }

    // Test 2: n = 84 = 2^2 * 3 * 7
    //   All divisors sum    = (1+2+4)*(1+3)*(1+7) = 7*4*8 = 224
    //   Proper divisors sum = 224 - 84 = 140
    {
        Solution s;
        int n = 84;
        int res = s.divSum(n);
        cout << "n = " << n
             << "  → Proper sum: " << res
             << "  (All sum: 224, diff: " << (224 - res) << " = n)\n";
    }

    // Test 3: n = 1 (edge case)
    //   Proper divisors of 1 = {} (no positive divisor except 1 itself)
    //   All divisors sum = 1, Proper sum = 1 - 1 = 0
    {
        Solution s;
        int n = 1;
        int res = s.divSum(n);
        cout << "n = " << n
             << "  → Proper sum: " << res
             << "  (expected: 0)\n";
    }

    // Test 4: n = 6 (perfect number)
    //   Divisors = {1,2,3,6}
    //   All sum = 12, Proper sum = 12 - 6 = 6
    //   A perfect number has proper divisor sum = itself.
    {
        Solution s;
        int n = 6;
        int res = s.divSum(n);
        cout << "n = " << n
             << "  → Proper sum: " << res
             << "  (perfect number? " << (res == n ? "yes" : "no") << ")\n";
    }

    // Test 5: n = 28 (another perfect number)
    //   Divisors = {1,2,4,7,14,28}
    //   All sum = 56, Proper sum = 56 - 28 = 28
    {
        Solution s;
        int n = 28;
        int res = s.divSum(n);
        cout << "n = " << n
             << "  → Proper sum: " << res
             << "  (perfect number? " << (res == n ? "yes" : "no") << ")\n";
    }

    // Test 6: n = 9973 (prime)
    //   Divisors = {1, 9973}
    //   All sum = 9974, Proper sum = 9974 - 9973 = 1
    {
        Solution s;
        int n = 9973;
        int res = s.divSum(n);
        cout << "n = " << n
             << "  → Proper sum: " << res
             << "  (All sum: 9974, diff: " << (9974 - res) << " = n)\n";
    }

    return 0;
}
