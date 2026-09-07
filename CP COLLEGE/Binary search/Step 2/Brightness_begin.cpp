/*
================================================================================
PROBLEM: Find the K-th Positive Integer That Is NOT a Perfect Square
================================================================================

QUESTION:
Given an integer k, find the k-th positive integer that is not a perfect square.

EXAMPLES:
- k = 1 → Answer = 2  (1st non-perfect-square)
- k = 2 → Answer = 3  (2nd non-perfect-square)
- k = 3 → Answer = 5  (3rd non-perfect-square, since 4 is a perfect square)

KEY INSIGHT:
From 1 to N, how many numbers are NOT perfect squares?
  Total numbers = N
  Perfect squares = 1, 4, 9, 16, ..., floor(sqrt(N))^2
  Count of perfect squares = floor(sqrt(N))
  Count of non-perfect-squares = N - floor(sqrt(N))

We want the smallest N such that (N - floor(sqrt(N))) >= k
This is a monotonic condition → Binary Search on Answer!

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Type alias: using int64 for long long to avoid typing long long everywhere
using int64 = long long;

int main() {
    // Fast I/O: disables synchronization between C and C++ stdio
    // and unties cin from cout for faster input/output
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // t = number of test cases
    int t;
    cin >> t;

    // Process each test case
    while (t--) {
        // k = we want to find the k-th non-perfect-square number
        int64 k;
        cin >> k;

        /*
        BINARY SEARCH SETUP:
        - low = 1: The smallest possible answer (minimum non-perfect-square is 2, but we start from 1)
        - high = k + 2000000000: Upper bound. Since perfect squares are sparse,
          the answer is roughly k + sqrt(k). Using k + 2e9 is safe for large k.
        - ans = high: Stores the best answer found so far
        */
        int64 low = 1;
        int64 high = k + 2000000000LL;
        int64 ans = high;

        /*
        BINARY SEARCH LOOP:
        We search for the smallest value of 'mid' such that:
            (mid - floor(sqrt(mid))) >= k
        This means there are at least k non-perfect-squares from 1 to mid.
        */
        while (low <= high) {
            // Calculate mid = (low + high) / 2, but written this way to avoid overflow
            int64 mid = low + (high - low) / 2;

            // Find the integer square root of mid (largest r such that r*r <= mid)
            int64 root = sqrtl(mid);

            /*
            PRECISION FIX:
            sqrtl() uses floating-point math and may give slightly wrong results
            for very large numbers. We adjust root to ensure correctness:
            - If (root+1)^2 <= mid, root is too small → increase it
            - If root^2 > mid, root is too large → decrease it
            */
            while ((root + 1) * (root + 1) <= mid)
                root++;
            while (root * root > mid)
                root--;

            /*
            COUNT NON-PERFECT-SQUARES:
            From 1 to mid, there are:
              - mid total numbers
              - root perfect squares (1^2, 2^2, ..., root^2)
              - (mid - root) non-perfect-squares
            */
            int64 on = mid - root;

            /*
            BINARY SEARCH DECISION:
            - If we have >= k non-perfect-squares, this mid could be the answer.
              Store it and try to find a smaller valid answer (search left).
            - If we have < k non-perfect-squares, we need a larger number (search right).
            */
            if (on >= k) {
                ans = mid;          // mid is a valid answer, store it
                high = mid - 1;     // Try to find something smaller
            } else {
                low = mid + 1;      // Need more non-perfect-squares, go right
            }
        }

        // Output the k-th non-perfect-square number
        cout << ans << '\n';
    }

    return 0;
}

/*
================================================================================
SUMMARY:
================================================================================
1. The problem asks for the k-th number that is NOT a perfect square.
2. For any number N, the count of non-perfect-squares from 1..N is: N - sqrt(N).
3. We use binary search to find the smallest N where (N - sqrt(N)) >= k.
4. The answer is the first N that satisfies this condition.

TIME COMPLEXITY: O(T * log(k)) where T = test cases
SPACE COMPLEXITY: O(1)
================================================================================
*/
