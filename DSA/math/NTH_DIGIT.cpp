#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  PROBLEM: Nth Digit (LeetCode 400)
 * ================================================================
 *  Find the n-th digit of the infinite integer sequence:
 *    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, ...
 *
 *  Example:
 *    n=1  → 1
 *    n=9  → 9
 *    n=10 → 1  (first digit of 10)
 *    n=11 → 0  (second digit of 10)
 *    n=12 → 1  (first digit of 11)
 *
 *  INTUITION:
 *    The sequence can be grouped into blocks by digit length:
 *      [1-9]        → 1-digit,  9 numbers,  9×1 = 9 digits
 *      [10-99]      → 2-digit, 90 numbers,  90×2 = 180 digits
 *      [100-999]    → 3-digit, 900 numbers, 900×3 = 2700 digits
 *      [1000-9999]  → 4-digit, 9000 numbers, 9000×4 = 36000 digits
 *      ...
 *      Block k: 9×10^(k-1) numbers, each k digits long
 *
 *    Step 1: Skip complete blocks until we find which block
 *            (digit length) contains the n-th digit.
 *    Step 2: Within that block, find which number contains it.
 *    Step 3: Within that number, find which digit position.
 * ================================================================
 */

// ================================================================
// APPROACH 1: String-based digit extraction
// ================================================================
// Identifies the target number, converts it to a string, and
// indexes into the string to get the digit.
//
// TIME:  O(log n)  — while loop runs at most ~10 iterations
//                     (since 10^10 > 2^31, digitLength ≤ 10)
// SPACE: O(log n)  — to_string creates a string of at most ~10 chars
// ================================================================

class Solution_String {
public:
    int findNthDigit(int n) {

        // ----------------------------------------------------------
        // digitLength = number of digits in the current block
        //              (1 → 1-digit, 2 → 2-digit, ...)
        // count  = how many numbers are in this block
        //          (9, 90, 900, 9000, ...)
        // start  = first number of this block
        //          (1, 10, 100, 1000, ...)
        // ----------------------------------------------------------
        long long digitLength = 1;   // current block's digit length
        long long count      = 9;    // numbers in this block
        long long start      = 1;    // first number in this block

        // ----------------------------------------------------------
        // STEP 1: Skip complete blocks
        //
        // Each block has (digitLength × count) total digits.
        // While n exceeds this block's total digits, subtract it
        // and move to the next block (more digits per number).
        // ----------------------------------------------------------
        while (n > digitLength * count) {
            n -= digitLength * count;      // consume this block's digits
            digitLength++;                 // next block: 1→2→3→...
            count *= 10;                   // next count: 9→90→900→...
            start *= 10;                   // next start: 1→10→100→...
        }

        // ----------------------------------------------------------
        // STEP 2: Find the exact number
        //
        // Now:  1 ≤ n ≤ digitLength × count
        //
        // KEY: Why (n-1) instead of n?
        // ===============================================
        // n is 1-indexed (1st digit, 2nd digit, ...).
        // But array indices and division groups are 0-indexed.
        //
        // Within a block of digitLength-digit numbers:
        //   positions 1..digitLength  → 1st number (start+0)
        //   positions digitLength+1..2*digitLength → 2nd number (start+1)
        //   ...
        //
        // Using 0-indexed offsets:
        //   offset = n - 1   (0, 1, 2, ...)
        //   numberIndex  = offset / digitLength   (which number)
        //   digitIndex   = offset % digitLength   (which digit inside number)
        //
        // EXAMPLE: digitLength=2, block=[10-99]
        //   n=1 → offset=0 → numIdx=0/2=0 → start+0=10 → digit '1'
        //   n=2 → offset=1 → numIdx=1/2=0 → start+0=10 → digit '0'
        //   n=3 → offset=2 → numIdx=2/2=1 → start+1=11 → digit '1'
        //   n=4 → offset=3 → numIdx=3/2=1 → start+1=11 → digit '1'
        //   ...
        //
        // If we used n directly:
        //   n=2 → numIdx=2/2=1 → start+1=11 ❌ (n=2 should be in 10!)
        //   n=3 → numIdx=3/2=1 → start+1=11 ✓ (wastes n=2 to fix n=3)
        //
        // The -1 shifts from 1-based to 0-based indexing so that
        // the integer division correctly groups digits per number.
        // ===============================================

        long long number = start + (n - 1) / digitLength;

        // ----------------------------------------------------------
        // STEP 3: Find the digit within the number
        //
        // (n-1) % digitLength → which digit inside the number (0-based)
        // Example: number=12, digitIndex=0 → '1', digitIndex=1 → '2'
        // ----------------------------------------------------------
        int digitIndex = (n - 1) % digitLength;

        // Convert the number to a string and pick the digit
        string s = to_string(number);
        return s[digitIndex] - '0';
    }
};

// ================================================================
// APPROACH 2: Arithmetic digit extraction
// ================================================================
// Same block-finding logic, but extracts the digit arithmetically
// instead of using strings:
//   - Shift digits right by dividing by 10 repeatedly until the
//     target digit is at the ones place, then % 10.
//
// TIME:  O(log n)  — same block walk; the inner loop also runs
//                     at most digitLength (≤10) times
// SPACE: O(1)      — no string conversion
// ================================================================

class Solution_Arithmetic {
public:
    int findNthDigit(int n) {

        long long digitLength = 1;
        long long count      = 9;
        long long start      = 1;

        // ---- STEP 1: Skip blocks (identical to Approach 1) ----
        while (n > digitLength * count) {
            n -= digitLength * count;
            digitLength++;
            count *= 10;
            start *= 10;
        }

        // ---- STEP 2: Find the number ----
        /*
         * Why (n-1)?
         * n is 1-indexed (1st digit, 2nd digit, ...).
         * We need 0-indexed offset = n-1 for correct grouping.
         *
         * With digitLength=2 (block [10-99]):
         *   offset=0 → numIdx=0/2=0 → start+0=10 (n=1)
         *   offset=1 → numIdx=1/2=0 → start+0=10 (n=2)
         *   offset=2 → numIdx=2/2=1 → start+1=11 (n=3)
         *   offset=3 → numIdx=3/2=1 → start+1=11 (n=4)
         *
         * Without -1:
         *   n=2 → numIdx=2/2=1 → start+1=11  ❌  (should be 10)
         * So (n-1) shifts 1-based → 0-based so integer division
         * correctly maps each group of digitLength positions to
         * exactly one number.
         */
        long long number = start + (n - 1) / digitLength;

        // ---- STEP 3: Find the digit arithmetically ----
        int digitIndex = (n - 1) % digitLength;

        /*
         * Instead of converting to string, we shift digits right
         * by dividing by 10 repeatedly until the target digit
         * becomes the last digit.
         *
         * Example: number=1234, digitIndex=1 (digit '2')
         *   digitLength=4, digitIndex=1
         *   shifts needed = digitLength - digitIndex - 1 = 4-1-1 = 2
         *   1234 / 100 = 12
         *   12 % 10 = 2  ← correct
         *
         * Why formula "digitLength - digitIndex - 1"?
         *   In a d-digit number, digit positions are:
         *     index 0 → leftmost (most significant)
         *     index d-1 → rightmost (least significant)
         *   To bring index i to the ones place, we need to remove
         *   (d - i - 1) digits from the right.
         */
        for (int i = 0; i < digitLength - digitIndex - 1; i++) {
            number /= 10;  // chop off rightmost digit
        }

        return number % 10;  // the target digit is now in the ones place
    }
};

/*
 * ================================================================
 *  DRY RUN (works for both approaches)
 * ================================================================
 *  n = 11
 *
 *  Sequence: 1 2 3 4 5 6 7 8 9 | 1 0 1 1 1 2 ...
 *                                       ^
 *                                       n=11 → digit '0'
 *
 *  --------------------------------------------------------------
 *  STEP 1: Skip blocks
 *  --------------------------------------------------------------
 *  Start: digitLength=1, count=9, start=1
 *
 *  Iteration 1:
 *    digitLength * count = 1 * 9 = 9
 *    n=11 > 9 → n = 11-9 = 2
 *    digitLength=2, count=90, start=10
 *
 *  Iteration 2:
 *    digitLength * count = 2 * 90 = 180
 *    n=2 ≤ 180 → STOP
 *
 *  Now: n=2, digitLength=2, start=10
 *  (We are in the 2-digit block, n=2 means the 2nd digit of this block)
 *
 *  --------------------------------------------------------------
 *  STEP 2: Find the number
 *  --------------------------------------------------------------
 *  number = start + (n-1) / digitLength
 *         = 10 + (2-1)/2
 *         = 10 + 0
 *         = 10
 *
 *  --------------------------------------------------------------
 *  STEP 3: Find the digit position
 *  --------------------------------------------------------------
 *  digitIndex = (n-1) % digitLength
 *             = (2-1) % 2
 *             = 1
 *
 *  Approach 1 (string):
 *    s = "10", s[1] = '0', return 0
 *
 *  Approach 2 (arithmetic):
 *    shifts = digitLength - digitIndex - 1 = 2 - 1 - 1 = 0
 *    number stays 10
 *    10 % 10 = 0
 *
 *  Result: 0  ✓
 * ================================================================
 */

int main() {
    // Test both implementations
    Solution_String sol1;
    Solution_Arithmetic sol2;

    cout << sol1.findNthDigit(11) << "\n";  // 0
    cout << sol2.findNthDigit(11) << "\n";  // 0

    return 0;
}
