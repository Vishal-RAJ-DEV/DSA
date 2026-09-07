#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
   UGLY NUMBER III — Binary Search + Inclusion-Exclusion

   Problem: Find the nth number divisible by at least one of {a, b, c}.

   INTUITION:
   - A naive approach would be to iterate numbers 1,2,3,... and count
     ugly numbers one by one, but n can be up to 10^9 so that's too slow.
   - Instead, we binary search on the ANSWER itself (the value of the nth
     ugly number). For a candidate value `mid`, we ask:
       "How many ugly numbers are <= mid?"
     If that count >= n, the answer is <= mid; otherwise answer > mid.

   KEY QUESTION: How do we count ugly numbers <= x efficiently?
   - Using Inclusion-Exclusion Principle on divisibility:
     * Numbers divisible by a:  x/a
     * Numbers divisible by b:  x/b
     * Numbers divisible by c:  x/c
     * But numbers divisible by BOTH a and b are counted twice,
       so subtract them: x/lcm(a,b)
     * Similarly for pairs (a,c) and (b,c)
     * Numbers divisible by ALL three (a,b,c) were subtracted too many
       times, so add them back: x/lcm(a,b,c)
   - This is exactly the inclusion-exclusion formula for 3 sets.

   WHY LCM?
   - A number divisible by both a and b must be divisible by lcm(a,b).
   - That's why we use LCM (not just multiply) — e.g., lcm(4,6) = 12,
     not 24.

   BINARY SEARCH BOUNDS:
   - left = 1 (smallest possible ugly number)
   - right = n * min(a,b,c) — worst case: all n ugly numbers are
     multiples of the smallest factor, so the nth one is at most n*min.
*/

class Solution {
public:

    // Compute LCM(a,b) = a*b / gcd(a,b)
    // Division first to avoid overflow: (a / gcd) * b
    long long lcm(long long a, long long b) {
        return a / __gcd(a, b) * b;
    }

    // Count how many numbers in [1, x] are divisible by a, b, or c.
    // Uses Inclusion-Exclusion Principle:
    // |A ∪ B ∪ C| = |A| + |B| + |C| - |A∩B| - |A∩C| - |B∩C| + |A∩B∩C|
    // where A = multiples of a, B = multiples of b, C = multiples of c
    long long countUgly(long long x,
                        long long a,
                        long long b,
                        long long c) {

        long long ab = lcm(a, b);   // LCM of a and b
        long long ac = lcm(a, c);   // LCM of a and c
        long long bc = lcm(b, c);   // LCM of b and c

        long long abc = lcm(ab, c); // LCM of all three a, b, c

        // Inclusion-Exclusion:
        // + singles: x/a, x/b, x/c
        // - pairs:   x/ab, x/ac, x/bc (subtracted because double-counted)
        // + triple:  x/abc (added back because over-subtracted)
        return x / a
             + x / b
             + x / c
             - x / ab
             - x / ac
             - x / bc
             + x / abc;
    }

    // Binary search on the answer space to find the nth ugly number.
    int nthUglyNumber(int n, int a, int b, int c) {

        long long left = 1;

        // Upper bound: in the worst case all ugly numbers are multiples
        // of the smallest factor, so nth ugly <= n * min(a,b,c)
        long long right =
            1LL * n * min({a, b, c});

        // Find the smallest number x such that countUgly(x) >= n
        while (left < right) {

            long long mid =
                left + (right - left) / 2;

            // If mid has at least n ugly numbers <= it,
            // the answer could be mid or smaller
            if (countUgly(mid, a, b, c) >= n) {
                right = mid;
            }
            else {
                // mid is too small, need a larger candidate
                left = mid + 1;
            }
        }

        // left == right == the nth ugly number
        return left;
    }
};


int main(){
    return 0;
}