#include <iostream>
using namespace std;

/*
 * PROBLEM: Packing Rectangles
 * ---------------------------------------------------------------
 * Given: rectangle of size w × h, and we need to pack n such
 *        rectangles into a SQUARE without rotating.
 * Find:  the MINIMUM side length of the square that can fit
 *        at least n rectangles.
 *
 * INPUT:  w h n (width, height of rectangle, number needed)
 * OUTPUT: minimum square side length
 *
 * EXAMPLE: w=2, h=3, n=10
 *   Square side = 9:
 *     Horizontally: 9 / 2 = 4 rectangles per row
 *     Vertically:   9 / 3 = 3 rows
 *     Total: 4 × 3 = 12 >= 10  ✅
 *
 *   Square side = 8:
 *     Horizontally: 8 / 2 = 4
 *     Vertically:   8 / 3 = 2
 *     Total: 4 × 2 = 8 < 10  ❌
 *
 *   Answer = 9
 *
 * HOW RECTANGLES FIT IN THE SQUARE:
 * ---------------------------------------------------------------
 * If square side = x:
 *
 *   Rectangles per row (horizontal)  = x / w  (integer division)
 *   Number of rows    (vertical)     = x / h  (integer division)
 *   Total rectangles that fit        = (x/w) × (x/h)
 *
 * Visual for x=9, w=2, h=3:
 *
 *   +---------+
 *   |RR RR RR R|  ← 4 rectangles (9/2=4)
 *   |RR RR RR R|
 *   |RR RR RR R|
 *   |         |
 *   |RR RR RR R|  ← row 2
 *   |RR RR RR R|
 *   |RR RR RR R|
 *   |         |
 *   |RR RR RR R|  ← row 3
 *   |RR RR RR R|
 *   |RR RR RR R|
 *   +---------+
 *   3 rows (9/3=3), 4 per row = 12 total
 *
 * THE MONOTONIC PROPERTY:
 * ---------------------------------------------------------------
 * If a square of side x can fit n rectangles,
 * then any square larger than x can ALSO fit n rectangles.
 *
 *   x=1 → ❌ (too small)
 *   x=2 → ❌
 *   ...
 *   x=8 → ❌
 *   x=9 → ✅
 *   x=10 → ✅
 *   x=11 → ✅
 *   ...
 *
 * Pattern: ❌ ❌ ❌ ❌ ❌ ❌ ❌ ❌ ✅ ✅ ✅ ✅
 *          ← all NO →|← all YES →
 *
 * This is a MONOTONIC condition: once TRUE, stays TRUE forever.
 * This is WHY we can use Binary Search on the answer.
 *
 * BINARY SEARCH ON ANSWER:
 * ---------------------------------------------------------------
 * Unlike searching in a sorted ARRAY, here we search over
 * POSSIBLE VALUES of the answer (square side length).
 *
 * We don't have a sorted array to search in.
 * Instead, we binary search over the range [0, very large].
 *
 * For each guess (mid):
 *   - Check: can mid-sized square fit n rectangles?
 *   - If YES → mid works, but maybe smaller works too → search left
 *   - If NO  → mid too small, need bigger → search right
 *
 *   Binary Search on square side x:
 *
 *           NO                YES
 *   ---------|------------------------>
 *            ↑
 *         answer (minimum x that works)
 *
 * FINDING THE RIGHT BOUNDARY:
 * ---------------------------------------------------------------
 * We start with right = 1 and double it until it's big enough.
 * Why? We don't know the upper bound of the answer.
 * Doubling finds a valid right boundary in O(log(answer)) steps.
 *
 *   right = 1 → too small → double → 2
 *   right = 2 → too small → double → 4
 *   right = 4 → too small → double → 8
 *   ...
 *   right = 16 → big enough! → stop
 *
 * Now we binary search in [0, 16] for minimum valid size.
 *
 * THE CONDITION:
 * ---------------------------------------------------------------
 *   (mid / w) * (mid / h) >= n
 *
 *   If true:  mid-sized square fits n rectangles
 *   If false: mid too small, need larger square
 */

int main() {
    long long w, h, n;
    cin >> w >> h >> n;

    long long left = 0;
    long long right = 1;

    // FIND RIGHT BOUNDARY: double until square is big enough
    // This ensures (right / w) * (right / h) >= n
    // We don't know the answer's upper bound, so we find it dynamically
    while ((right / w) * (right / h) < n) {
        right *= 2;
    }

    // BINARY SEARCH: find minimum square side in [left, right]
    while (left < right) {
        long long mid = left + (right - left) / 2;

        // CHECK: can a mid × mid square fit n rectangles?
        // (mid / w) = rectangles per row
        // (mid / h) = number of rows
        // Product = total rectangles that fit
        if ((mid / w) * (mid / h) >= n) {
            // mid works! But maybe smaller also works.
            // Search LEFT half for smaller valid answer
            right = mid;
        } else {
            // mid is too small, need larger square
            // Search RIGHT half
            left = mid + 1;
        }
    }

    // When left == right, that's the minimum valid square side
    cout << left << '\n';

    return 0;
}