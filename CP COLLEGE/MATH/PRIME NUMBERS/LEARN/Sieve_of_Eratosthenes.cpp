#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  This file contains TWO sieve-based algorithms:
 *
 *  1. Standard Sieve of Eratosthenes
 *     → finds all prime numbers up to n
 *
 *  2. SPF (Smallest Prime Factor) Sieve
 *     → finds the smallest prime factor of every number up to n
 * ================================================================
 */

// ================================================================
// CLASS: Sieve
// Contains both sieve implementations as static methods.
// ================================================================
class Sieve {
public:

    // ------------------------------------------------------------
    // METHOD 1: classicSieve(n)
    //
    //  Standard Sieve of Eratosthenes
    //  Marks all composite numbers up to n as false.
    //  Returns a vector<bool> where isPrime[i] is true if i is prime.
    //
    //  ALGORITHM:
    //    1. Assume all numbers 0..n are prime.
    //    2. 0 and 1 are not prime.
    //    3. For i from 2 to sqrt(n):
    //         If i is prime, mark all multiples of i starting from
    //         i*i as composite (smaller multiples i*2, i*3, ..., i*(i-1)
    //         were already marked by smaller primes).
    //    4. Return the boolean array.
    //
    //  TIME:  O(n log log n)
    //  SPACE: O(n)
    // ------------------------------------------------------------
    static vector<bool> classicSieve(int n) {

        // Assume every number is prime
        vector<bool> isPrime(n + 1, true);

        // 0 and 1 are not prime
        isPrime[0] = false;
        isPrime[1] = false;

        // Only iterate until sqrt(n)
        for (int i = 2; i * i <= n; i++) {

            // If current number is prime
            if (isPrime[i]) {

                // Start marking from i*i because
                // smaller multiples have already
                // been marked by smaller primes.
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        return isPrime;
    }

    // ------------------------------------------------------------
    // METHOD 2: spfSieve(n)
    //
    //  Smallest Prime Factor (SPF) Sieve
    //  For each number i up to n, finds the smallest prime that
    //  divides i. Useful for fast prime factorization.
    //
    //  ALGORITHM:
    //    1. Initialize spf[i] = i for all i (each number is its own SPF).
    //    2. For i from 2 to sqrt(n):
    //         If spf[i] == i (i is prime):
    //           Mark multiples of i starting from i*i.
    //           For each multiple j, if spf[j] is still j (unmarked),
    //           set spf[j] = i.
    //    3. Return the spf array.
    //
    //  TIME:  O(n log log n)
    //  SPACE: O(n)
    // ------------------------------------------------------------
    static vector<int> spfSieve(int n) {

        vector<int> spf(n + 1);

        // Initially, every number is its own SPF
        for (int i = 0; i <= n; i++)
            spf[i] = i;

        // Process all primes
        for (int i = 2; i * i <= n; i++) {

            // i is prime if it has not been changed
            if (spf[i] == i) {

                // Mark multiples starting from i*i
                for (int j = i * i; j <= n; j += i) {

                    // Assign SPF only once (first prime factor wins)
                    if (spf[j] == j)
                        spf[j] = i;
                }
            }
        }

        return spf;
    }
};

int main() {
    int n = 20;

    // --- Call Sieve of Eratosthenes ---
    vector<bool> isPrime = Sieve::classicSieve(n);

    cout << "Prime Numbers:\n";
    for (int i = 2; i <= n; i++) {
        if (isPrime[i])
            cout << i << " ";
    }
    cout << endl;

    // --- Call SPF Sieve ---
    vector<int> spf = Sieve::spfSieve(n);

    for (int i = 2; i <= n; i++) {
        cout << "SPF[" << i << "] = " << spf[i] << "\n";
    }

    return 0;
}
