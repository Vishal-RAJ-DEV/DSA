/*
================================================================================================
                         COUNT PRIMES - FULL EXPLANATION
================================================================================================

QUESTION:
---------
Given an integer n, return the number of PRIME numbers that are STRICTLY LESS
than n (i.e., count primes in range [0, n)).

EXAMPLES:
---------
  Example 1: n = 10
    Primes less than 10: 2, 3, 5, 7
    Answer: 4

  Example 2: n = 0 or 1 or 2
    No primes less than these values
    Answer: 0

  Example 3: n = 20
    Primes less than 20: 2, 3, 5, 7, 11, 13, 17, 19
    Answer: 8

------------------------------------------------------------------------------------------------

WHAT IS A PRIME NUMBER?
------------------------
  A prime number is a natural number greater than 1 that has NO positive
  divisors other than 1 and itself.

  2 is the only even prime number.
  All other even numbers are divisible by 2, so they're not prime.

------------------------------------------------------------------------------------------------

APPROACH 1: BRUTE FORCE
------------------------
  For each number from 2 to n-1, check if it's prime by dividing
  by all numbers from 2 to sqrt(i).

  Time: O(n * sqrt(n))  — slow for large n
  Space: O(1)

APPROACH 2: SIEVE OF ERATOSTHENES (Optimal)
---------------------------------------------
  The main approach in this file. Eliminate multiples of each prime.

  Time: O(n log log n)  — very efficient
  Space: O(n)

APPROACH 3: SIEVE + PREFIX SUM
-------------------------------
  Build a prefix sum array after sieve, so we can answer
  "how many primes in range [0, k]" for ANY k in O(1).

  Time: O(n log log n) to build + O(1) per query
  Space: O(n)

================================================================================================
APPROACH 1: BRUTE FORCE
================================================================================================

IDEA:
  For each number i from 2 to n-1, check if any number from 2 to sqrt(i)
  divides i evenly. If none do, i is prime.

  Why only check up to sqrt(i)?
    If i = a * b, then one of a or b must be <= sqrt(i).
    So if no divisor found up to sqrt(i), none exists beyond it.

WALKTHROUGH for n = 10:
  ┌──────────────────────────────────────────────────────────────┐
  │  Check 2: divisors from 2 to sqrt(2)=1.4 -> no loop         │
  │          No divisor found -> 2 is PRIME ✓                    │
  │                                                              │
  │  Check 3: divisors from 2 to sqrt(3)=1.7 -> no loop         │
  │          No divisor found -> 3 is PRIME ✓                    │
  │                                                              │
  │  Check 4: divisors from 2 to sqrt(4)=2                       │
  │          4 % 2 == 0 -> NOT prime ✗                          │
  │                                                              │
  │  Check 5: divisors from 2 to sqrt(5)=2.2                     │
  │          5 % 2 != 0 -> 5 is PRIME ✓                         │
  │                                                              │
  │  Check 6: divisors from 2 to sqrt(6)=2.4                     │
  │          6 % 2 == 0 -> NOT prime ✗                          │
  │                                                              │
  │  Check 7: divisors from 2 to sqrt(7)=2.6                     │
  │          7 % 2 != 0 -> 7 is PRIME ✓                         │
  │                                                              │
  │  Check 8: divisors from 2 to sqrt(8)=2.8                     │
  │          8 % 2 == 0 -> NOT prime ✗                          │
  │                                                              │
  │  Check 9: divisors from 2 to sqrt(9)=3                       │
  │          9 % 2 != 0, 9 % 3 == 0 -> NOT prime ✗             │
  │                                                              │
  │  Primes: 2, 3, 5, 7 -> Count = 4                            │
  └──────────────────────────────────────────────────────────────┘

================================================================================================
APPROACH 2: SIEVE OF ERATOSTHENES (Main Code)
================================================================================================

IDEA:
  Instead of checking each number individually, we ELIMINATE multiples
  of known primes. This is much faster because one pass eliminates
  many composites at once.

ALGORITHM:
  1. Create boolean array isPrime[0..n-1], all set to true
  2. Mark 0 and 1 as false (not prime)
  3. For each number i from 2 to sqrt(n):
     - If isPrime[i] is true (i is prime):
       - Mark ALL multiples of i starting from i*i as false
       - Starting from i*i because smaller multiples (2*i, 3*i, ...)
         were already marked by smaller primes
  4. Count all indices that remain true

WHY START FROM i*i?
  ──────────────────
  When processing prime i:
    - i*2 was already marked by prime 2
    - i*3 was already marked by prime 3
    - ...
    - i*(i-1) was already marked by prime (i-1)
    - i*i is the FIRST multiple of i not yet marked

  This is a key optimization that avoids redundant work.

WALKTHROUGH for n = 20:
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  Initial: all true except 0 and 1                                      │
  │                                                                          │
  │  Index:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19    │
  │  Value:  F  F  T  T  T  T  T  T  T  T  T  T  T  T  T  T  T  T  T  T    │
  └──────────────────────────────────────────────────────────────────────────┘

  Step 1: i = 2 (prime, 2*2=4 < 20)
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  Mark multiples of 2 starting from 4: 4, 6, 8, 10, 12, 14, 16, 18     │
  │                                                                          │
  │  Index:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19    │
  │  Value:  F  F  T  T  F  T  F  T  F  T  F  T  F  T  F  T  F  T  F  T    │
  │                    ↑     ↑     ↑     ↑     ↑     ↑     ↑     ↑          │
  │                  marked by 2                                            │
  └──────────────────────────────────────────────────────────────────────────┘

  Step 2: i = 3 (prime, 3*3=9 < 20)
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  Mark multiples of 3 starting from 9: 9, 12, 15, 18                    │
  │  (Note: 6 already marked by 2)                                         │
  │                                                                          │
  │  Index:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19    │
  │  Value:  F  F  T  T  F  T  F  T  F  F  F  T  F  T  F  F  F  T  F  T    │
  │                               ↑        ↑     ↑        ↑                 │
  │                             marked by 3                                 │
  └──────────────────────────────────────────────────────────────────────────┘

  Step 3: i = 4 (NOT prime, skip)
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  i=4 is already marked false, so we skip it.                           │
  │  This is why the "if (isPrime[i])" check is important!                 │
  └──────────────────────────────────────────────────────────────────────────┘

  Step 4: i = 5 (prime, but 5*5=25 >= 20, loop ends)
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  Since 5*5 = 25 >= 20, we stop the outer loop.                         │
  │  All remaining composites are already marked.                          │
  └──────────────────────────────────────────────────────────────────────────┘

  FINAL TABLE:
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  Index:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19    │
  │  Value:  F  F  T  T  F  T  F  T  F  F  F  T  F  T  F  F  F  T  F  T    │
  │                                                                          │
  │  Primes (T): 2, 3, 5, 7, 11, 13, 17, 19                                 │
  │  Count = 8                                                              │
  └──────────────────────────────────────────────────────────────────────────┘

WHY i * i < n (not i < n)?
  ──────────────────────────
  If i >= sqrt(n), then i*i >= n.
  All multiples of i less than n (i*2, i*3, ...) have smaller factors
  and were already marked by smaller primes.
  So we only need to check up to sqrt(n).

TIME COMPLEXITY: O(n log log n)
  - Each prime p marks n/p multiples
  - Total = n/2 + n/3 + n/5 + n/7 + ... ≈ n * log(log(n))

SPACE COMPLEXITY: O(n) for the boolean array

================================================================================================
APPROACH 3: SIEVE + PREFIX SUM
================================================================================================

IDEA:
  After building the sieve, create a PREFIX SUM array where
  prefix[i] = number of primes in range [0, i).

  This allows answering "count primes less than k" in O(1)
  for any k, without re-scanning the sieve.

  prefix[0] = 0
  prefix[i] = prefix[i-1] + (1 if i-1 is prime else 0)

  Wait, let me clarify the indexing:
  prefix[i] = number of primes in range [0, i) (i.e., primes < i)

  So prefix[n] = answer to the problem.

  To answer multiple queries like "primes less than k" for different k,
  we build the prefix array once and then just return prefix[k].

WALKTHROUGH for n = 20:
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  Sieve result (isPrime):                                                │
  │  Index:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19    │
  │  Prime?  F  F  T  T  F  T  F  T  F  F  F  T  F  T  F  F  F  T  F  T    │
  │                                                                          │
  │  Build prefix sum:                                                       │
  │  prefix[0] = 0  (no primes < 0)                                        │
  │  prefix[1] = 0  (no primes < 1)                                        │
  │  prefix[2] = 0  (no primes < 2, since 2 itself is not < 2)             │
  │  prefix[3] = 1  (prime 2 is < 3)                                       │
  │  prefix[4] = 2  (primes 2,3 are < 4)                                   │
  │  prefix[5] = 2  (primes 2,3 are < 5; 4 is not prime)                   │
  │  prefix[6] = 3  (primes 2,3,5 are < 6)                                 │
  │  ...                                                                    │
  │  prefix[20] = 8 (primes 2,3,5,7,11,13,17,19 are < 20)                  │
  │                                                                          │
  │  prefix array:                                                          │
  │  [0, 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 8, 8]     │
  │                     ↑           ↑        ↑              ↑               │
  │                   prefix[3]=1  prefix[6]=3  prefix[11]=5  prefix[17]=7   │
  │                                                                          │
  │  Answer = prefix[n] = prefix[20] = 8                                    │
  └──────────────────────────────────────────────────────────────────────────┘

  WHY USEFUL?
    If we need to answer MULTIPLE queries:
      "How many primes < 5?"  -> prefix[5] = 2  (O(1))
      "How many primes < 15?" -> prefix[15] = 6 (O(1))
      "How many primes < 20?" -> prefix[20] = 8 (O(1))

    Without prefix sum, each query requires scanning the sieve: O(n)
    With prefix sum, each query is O(1).

================================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


/*
================================================================================================
APPROACH 1: BRUTE FORCE
================================================================================================

For each number i, check if any number from 2 to sqrt(i) divides it.
If no divisor found, i is prime.

Time:  O(n * sqrt(n))
Space: O(1)
*/
class CountPrimesBruteForce {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;

        int count = 0;

        // Check each number from 2 to n-1
        for (int i = 2; i < n; i++) {
            if (isPrime(i)) {
                count++;
            }
        }

        return count;
    }

private:
    // Check if a single number is prime
    // Try dividing by 2, 3, 4, ..., sqrt(i)
    // If any divides evenly -> not prime
    bool isPrime(int num) {
        if (num <= 1) return false;
        if (num <= 3) return true;  // 2 and 3 are prime
        if (num % 2 == 0 || num % 3 == 0) return false;

        // Check divisors from 5 to sqrt(num)
        // Only check odd numbers (even ones already handled)
        // Also skip multiples of 3 (already handled)
        // This is the 6k±1 optimization
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }

        return true;
    }
};


/*
================================================================================================
APPROACH 2: SIEVE OF ERATOSTHENES (Optimal)
================================================================================================

The most efficient way to count primes up to n.
Instead of checking each number, we eliminate composites in bulk.

Time:  O(n log log n)
Space: O(n)
*/
class CountPrimesSieve {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;

        // Step 1: Create boolean array, assume all are prime initially
        // isPrime[i] = true means i is considered prime (for now)
        vector<bool> isPrime(n, true);

        // 0 and 1 are NOT prime
        isPrime[0] = false;
        isPrime[1] = false;
        
          // 2 is the only even prime
        int count = 1;

        // Step 2: Sieve - mark multiples of each prime as non-prime
        // Only need to go up to sqrt(n) because:
        //   If i >= sqrt(n), then i*i >= n
        //   All multiples of i less than n were already marked by smaller primes
        for (int i = 3; i * i < n; i++) {

            // If i is still marked as prime, mark its multiples
            if (isPrime[i]) {

                // Start from i*i (not 2*i) because:
                //   i*2 was marked by prime 2
                //   i*3 was marked by prime 3
                //   ...
                //   i*(i-1) was marked by prime (i-1)
                //   i*i is the FIRST multiple of i not yet marked
                //
                // Step by i to hit all multiples: i*i, i*i+i, i*i+2i, ...
                for (int j = i * i; j < n; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        // Step 3: Count all remaining primes
        int count = 0;
        for (int i = 3; i < n; i++) {
            if (isPrime[i])
                count++;
        }

        return count;
    }
};


/*
================================================================================================
APPROACH 3: SIEVE + PREFIX SUM
================================================================================================

After building sieve, create prefix sum array.
prefix[i] = number of primes in range [0, i)

Benefits:
  - Single query: same as normal sieve
  - Multiple queries: O(1) per query after O(n log log n) preprocessing

Time:  O(n log log n) to build sieve + prefix array
Space: O(n)
*/
class CountPrimesPrefixSum {
public:

    // Build the sieve (same as Approach 2)
    vector<bool> buildSieve(int n) {
        vector<bool> isPrime(n, true);
        isPrime[0] = false;
        isPrime[1] = false;

        for (int i = 2; i * i < n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j < n; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        return isPrime;
    }

    // Build prefix sum array from sieve
    // prefix[i] = number of primes in range [0, i)
    //
    // Example: n=20
    //   isPrime: F F T T F T F T F F F T F T F F F T F T
    //   prefix:  0 0 0 1 2 2 3 3 4 4 4 5 5 6 6 6 6 7 7 8
    //                                  ↑
    //                            prefix[10] = 4 (primes 2,3,5,7 are < 10)
    vector<int> buildPrefixSum(int n) {
        vector<bool> isPrime = buildSieve(n);

        // prefix[i] = number of primes in [0, i)
        vector<int> prefix(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            // prefix[i] = prefix[i-1] + (1 if i-1 is prime else 0)
            prefix[i] = prefix[i - 1] + (isPrime[i - 1] ? 1 : 0);
        }

        return prefix;
    }

    // Count primes less than n
    int countPrimes(int n) {
        if (n <= 2) return 0;

        vector<int> prefix = buildPrefixSum(n);

        // prefix[n] = number of primes in [0, n)
        return prefix[n];
    }

    // Answer multiple queries: count primes less than each query value
    // This is where prefix sum really shines
    vector<int> countPrimesMultipleQueries(vector<int>& queries, int maxN) {
        vector<int> prefix = buildPrefixSum(maxN + 1);

        vector<int> results;
        for (int q : queries) {
            // O(1) per query!
            results.push_back(prefix[q]);
        }

        return results;
    }
};


int main(){
    CountPrimesBruteForce brute;
    CountPrimesSieve sieve;
    CountPrimesPrefixSum prefix;

    int n = 20;

    cout << "n = " << n << endl;
    cout << "Brute Force:  " << brute.countPrimes(n) << endl;
    cout << "Sieve:        " << sieve.countPrimes(n) << endl;
    cout << "Prefix Sum:   " << prefix.countPrimes(n) << endl;

    // Multiple queries example
    cout << "\n--- Multiple Queries (Prefix Sum) ---" << endl;
    vector<int> queries = {5, 10, 15, 20, 25, 30};
    vector<int> results = prefix.countPrimesMultipleQueries(queries, 30);

    for (int i = 0; i < queries.size(); i++) {
        cout << "Primes < " << queries[i] << " = " << results[i] << endl;
    }

    return 0;
}