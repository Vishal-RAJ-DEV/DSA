#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  PROBLEM: Find the N-th Prime Number
 * ================================================================
 *  Given an integer n, output the n-th prime number.
 *  (e.g., n=1 → 2, n=2 → 3, n=3 → 5, n=4 → 7, n=5 → 11, ...)
 *
 * ================================================================
 *  WHY THIS LIMIT?
 * ================================================================
 *  We need the sieve to be large enough to contain at least n primes.
 *  Prime-counting function π(x) ≈ x / ln(x).
 *
 *  For LIMIT = 8,000,000:
 *    π(8,000,000) ≈ 8,000,000 / ln(8,000,000)
 *                  ≈ 8,000,000 / 15.89 ≈ 503,000
 *  So this bound works for n up to ~500,000.
 *
 *  If n can be up to 10^6, we'd need LIMIT ≈ 15,500,000.
 *  Choose LIMIT based on the problem constraints.
 * ================================================================
 */

const int LIMIT = 8000000;  // Sieve upper bound (enough for ~500,000 primes)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    /*
     * ================================================================
     *  ALGORITHM: Sieve of Eratosthenes + Linear Scan
     * ================================================================
     *
     *  STEP 1: SIEVE OF ERATOSTHENES  —  O(LIMIT log log LIMIT)
     * ----------------------------------------------------------------
     *  Core idea: Mark composite numbers by iterating multiples of primes.
     *
     *  1. Assume ALL numbers 0..LIMIT are prime initially.
     *  2. 0 and 1 are not prime → mark them false.
     *  3. For i from 2 to sqrt(LIMIT):
     *       If i is still marked prime:
     *         All multiples of i starting from i*i are COMPOSITE
     *         (smaller multiples i*2, i*3, ..., i*(i-1) were already
     *          marked by smaller primes).
     *
     *  WHY start from i*i instead of i*2?
     *    Any composite k*i (k < i) has a prime factor smaller than i,
     *    so it was already crossed out in an earlier iteration.
     *    Example: i=5 → 5*2=10 crossed out by i=2, 5*3=15 by i=3, etc.
     *    Starting at i² avoids redundant work.
     *
     *  COMPLEXITY:
     *    The inner loop runs LIMIT/i times for each prime i.
     *    Total work = Σ_{prime p ≤ √LIMIT} LIMIT/p
     *               ≈ LIMIT * log log LIMIT   (Mertens' theorem)
     *               ≈ 8e6 * ~3 ≈ 24 million operations → very fast.
     *
     *  SPACE: O(LIMIT) ≈ 8 MB (vector<bool> is bit-packed → ~1 MB)
     * ----------------------------------------------------------------
     *
     *  STEP 2: FIND THE N-th PRIME  —  O(LIMIT) worst-case
     * ----------------------------------------------------------------
     *  1. Iterate i from 2 to LIMIT.
     *  2. If isPrime[i], increment counter.
     *  3. When counter reaches n, print i and exit.
     *
     *  Since the nth prime is always found well before LIMIT
     *  (for valid n within bounds), the second pass is fast.
     * ================================================================
     */

    // --- STEP 1: Sieve of Eratosthenes ---

    vector<bool> isPrime(LIMIT + 1, true);

    isPrime[0] = isPrime[1] = false;  // 0 and 1 are not prime

    for (int i = 2; i * i <= LIMIT; i++) {
        if (isPrime[i]) {
            /*
             * i is prime → mark all its multiples as composite.
             * Start from i*i to avoid redundant marking
             * (smaller multiples were already handled by smaller primes).
             */
            for (int j = i * i; j <= LIMIT; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // --- STEP 2: Find the n-th prime ---

    int cnt = 0;

    for (int i = 2; i <= LIMIT; i++) {
        if (isPrime[i]) {
            cnt++;
            if (cnt == n) {
                cout << i << '\n';
                return 0;
            }
        }
    }

    // If we reach here, n is larger than the number of primes up to LIMIT.
    // In a proper solution, either increase LIMIT or handle this error.
    return 0;
}
