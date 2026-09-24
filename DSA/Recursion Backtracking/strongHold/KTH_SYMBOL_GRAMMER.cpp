#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// PROBLEM: K-th Symbol in Grammar
//
// We build a table of rows where:
//   Row 1: 0
//   Row 2: 0 1           (replace 0 -> 01)
//   Row 3: 0 1 1 0       (replace 0->01, 1->10)
//   Row 4: 0 1 1 0 1 0 0 1
//   ...
//
// Each row is formed by taking the previous row and replacing:
//   0 -> 01
//   1 -> 10
//
// So each character in the previous row produces TWO characters in the next row.
//
// Given row number n and position k (1-indexed), return the k-th symbol in row n.
//
// PATTERN VISUALIZATION:
//   Row 1 (len=1):   0
//   Row 2 (len=2):   0 1
//   Row 3 (len=4):   0 1 1 0
//   Row 4 (len=8):   0 1 1 0 1 0 0 1
//   Row 5 (len=16):  0 1 1 0 1 0 0 1 1 0 0 1 0 1 1 0
//
// KEY FORMULA: Length of row n = 2^(n-1)
//   Row 1: 2^0 = 1
//   Row 2: 2^1 = 2
//   Row 3: 2^2 = 4
//   Row 4: 2^3 = 8
//   ...
//
// WHY HALF = 2^(n-2):
//   The row n has length 2^(n-1). It is built from row (n-1) which has length 2^(n-2).
//   Each character in row (n-1) expands to 2 characters in row n.
//   So row n is divided into TWO HALVES:
//     - First half  (positions 1 to 2^(n-2))  comes directly from row (n-1)
//     - Second half (positions 2^(n-2)+1 to 2^(n-1)) is the INVERSE of row (n-1)
//
//   Example for Row 4 (length 8):
//     First half (positions 1-4): 0 1 1 0  -> same as Row 3
//     Second half (positions 5-8): 1 0 0 1 -> inverse (1-x) of Row 3
//
//   So half = 2^(n-2) = 1 << (n-2) is the length of row (n-1),
//   which is also the size of each half in row n.
//
// THE RECURSIVE INSIGHT:
//   If k is in the FIRST half of row n:
//     The symbol at position k in row n is THE SAME as the symbol at position k in row (n-1).
//     Because the first half is copied directly from row (n-1).
//     -> recurse with (n-1, k)
//
//   If k is in the SECOND half of row n:
//     The symbol at position k in row n is the INVERSE of the symbol at position (k - half) in row (n-1).
//     Because the second half is the inverse of row (n-1).
//     -> recurse with (n-1, k - half) and flip the result (1 - result)
//
// ============================================================================


// ============================================================================
// SOLUTION 1: RECURSIVE APPROACH
//
// How it works:
//   - Base case: Row 1 always contains just "0", so return 0.
//   - Calculate half = 2^(n-2) = length of row (n-1) = size of each half in row n.
//   - If k <= half: k is in the first half of row n.
//     The first half of row n is identical to row (n-1).
//     So the answer is the same as solve(n-1, k).
//   - If k > half: k is in the second half of row n.
//     The second half of row n is the inverse of row (n-1).
//     So we find the answer at position (k - half) in row (n-1), then flip it.
//     Flipping: if solve returns 0, we return 1; if 1, we return 0.
//     This is expressed as: 1 - solve(n-1, k - half)
//
// Example: n=4, k=5
//   half = 2^(4-2) = 4
//   k=5 > 4, so k is in second half -> return 1 - solve(3, 5-4) = 1 - solve(3, 1)
//
//   solve(3, 1):
//     half = 2^(3-2) = 2
//     k=1 <= 2, first half -> return solve(2, 1)
//
//   solve(2, 1):
//     half = 2^(2-2) = 1
//     k=1 <= 1, first half -> return solve(1, 1)
//
//   solve(1, 1):
//     n=1 -> return 0
//
//   Unwinding: solve(2,1) = 0, solve(3,1) = 0, solve(4,5) = 1 - 0 = 1
//   Verify: Row 4 = 0 1 1 0 1 0 0 1 -> position 5 is 1 ✓
// ============================================================================

class Solution1 {
public:

    int solve(int n, int k) {

        // BASE CASE: Row 1 has only one symbol which is always 0.
        // No matter what k is (it can only be 1), the answer is 0.
        if (n == 1)
            return 0;

        // half = 2^(n-2) = length of row (n-1)
        // In row n, positions 1..half are the FIRST HALF (same as row n-1)
        // Positions half+1..2^(n-1) are the SECOND HALF (inverse of row n-1)
        //
        // Why 1 << (n-2)?
        //   << is left bit shift. 1 << m means 2^m.
        //   Row n has length 2^(n-1). It is split into two halves of size 2^(n-2).
        //   So half = 2^(n-2) = 1 << (n-2).
        //
        //   n=2: half = 2^0 = 1   (row 2 has length 2, halves of size 1)
        //   n=3: half = 2^1 = 2   (row 3 has length 4, halves of size 2)
        //   n=4: half = 2^2 = 4   (row 4 has length 8, halves of size 4)
        //   n=5: half = 2^3 = 8   (row 5 has length 16, halves of size 8)
        int half = 1 << (n - 2);

        // FIRST HALF: k falls in positions 1..half
        // The first half of row n is an EXACT COPY of row (n-1).
        // So the k-th symbol in row n is the same as the k-th symbol in row (n-1).
        // Just recurse on the previous row with the same k.
        if (k <= half) {
            return solve(n - 1, k);
        }

        // SECOND HALF: k falls in positions half+1..2^(n-1)
        // The second half of row n is the INVERSE of row (n-1).
        // Position k in the second half corresponds to position (k - half) in row (n-1).
        // We find that value and FLIP it (0 becomes 1, 1 becomes 0).
        // 1 - x does the flipping: 1-0=1, 1-1=0
        return 1 - solve(n - 1, k - half);
    }

    int kthGrammar(int n, int k) {
        return solve(n, k);
    }
};

// ============================================================================
// SOLUTION 2: ITERATIVE APPROACH
//
// Same logic as the recursive approach, but done in a loop to avoid recursion overhead.
//
// Instead of recursing down from row n to row 1, we iteratively reduce n and adjust k.
//
// Key insight: We track an "ans" variable starting at 0 (the value at row 1).
// As we move from row 1 upward (or equivalently, reduce n downward),
// each time k lands in the second half, we flip the answer.
//
// Why does this work?
//   Think of it as: "How many times did we have to flip the answer while
//   tracing back from row n to row 1?"
//   Each flip toggles the answer. Even number of flips = original (0).
//   Odd number of flips = inverted (1).
//
// The "ans" variable counts the cumulative effect of all those flips.
//
// Example: n=4, k=5
//   Start: ans=0, n=4, k=5
//
//   Iteration 1 (n=4): half = 2^2 = 4
//     k=5 > 4 -> second half: k = 5-4 = 1, ans = 1-0 = 1 (flip!)
//     n-- -> n=3
//
//   Iteration 2 (n=3): half = 2^1 = 2
//     k=1 <= 2 -> first half: no flip
//     n-- -> n=2
//
//   Iteration 3 (n=2): half = 2^0 = 1
//     k=1 <= 1 -> first half: no flip
//     n-- -> n=1
//
//   n=1, loop ends. Return ans=1.
//   Verify: Row 4 = 0 1 1 0 1 0 0 1 -> position 5 is 1 ✓
//
// ============================================================================

class Solution2 {
public:

    int kthGrammar(int n, int k) {

        // ans starts at 0 because Row 1 is always "0".
        // As we trace back through rows, each time we enter the second half,
        // we flip ans (0->1 or 1->0). This accumulates all the inversions.
        int ans = 0;

        // Keep reducing n until we reach row 1 (the base case).
        // Each iteration processes one row, checking if k is in the first or second half.
        while (n > 1) {

            // half = 2^(n-2) = length of row (n-1) = size of each half in row n.
            // Same formula as the recursive solution.
            int half = 1 << (n - 2);

            // If k is in the SECOND half of row n:
            //   - Adjust k to its corresponding position in row (n-1): k = k - half
            //   - Flip the answer: the second half is the inverse of the parent row
            if (k > half) {
                k -= half;       // Map k from second half to row (n-1)'s position
                ans = 1 - ans;   // Flip: 0 becomes 1, 1 becomes 0 (accumulate inversion)
            }

            // If k is in the FIRST half:
            //   - k stays the same (first half is identical to row n-1)
            //   - ans stays the same (no flip needed)
            //   - Just move to the previous row

            // Move to the previous row (reduce n by 1)
            n--;
        }

        // When n==1, we are at Row 1 which is "0".
        // If we flipped an even number of times, ans=0 (same as row 1).
        // If we flipped an odd number of times, ans=1 (inverted from row 1).
        return ans;
    }
};

// ============================================================================
// COMPARISON:
//
//   Recursive (Solution1):  Cleaner, directly mirrors the mathematical definition.
//                           Uses call stack for backtracking. O(n) stack space.
//
//   Iterative (Solution2):  More memory efficient (no recursion stack).
//                           Uses a single variable to accumulate flips. O(1) space.
//
//   Both have TIME COMPLEXITY: O(n) - we reduce n by 1 each step, doing O(1) work.
//
// WHY THE FORMULA half = 2^(n-2) WORKS:
//
//   Row lengths grow as powers of 2:
//     Row 1: 2^0 = 1
//     Row 2: 2^1 = 2
//     Row 3: 2^2 = 4
//     Row 4: 2^3 = 8
//     Row n: 2^(n-1)
//
//   Row n (length 2^(n-1)) is built from Row n-1 (length 2^(n-2)).
//   Each character in Row n-1 expands to 2 characters in Row n.
//
//   So Row n splits perfectly into:
//     First half:  positions 1 to 2^(n-2)       -> same as Row n-1
//     Second half: positions 2^(n-2)+1 to 2^(n-1) -> inverse of Row n-1
//
//   Therefore half = 2^(n-2) = 1 << (n-2) is the pivot point.
//   It is exactly the length of Row n-1, and half the length of Row n.
// ============================================================================


int main(){
    return 0;
}
