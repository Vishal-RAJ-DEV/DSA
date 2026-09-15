#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
PROBLEM: Find Kth Bit in Nth Binary String (LeetCode 1545)
================================================================================

Given two integers n and k, return the kth bit (1-indexed) in the nth binary
string S_n.

The binary strings are built as follows:
  S1 = "0"
  Si = Si-1 + "1" + reverse(invert(Si-1))   for i > 1

Example:
  S1 = "0"
  S2 = "0" + "1" + "1"         = "011"
  S3 = "011" + "1" + "00"      = "0111001"
  S4 = "0111001" + "1" + "1100100" = "011100111100100"

Each Si has length = 2^i - 1

================================================================================
APPROACH 1: PURE RECURSION (Optimal - No String Building)
================================================================================

INTUITION:
  Instead of building the entire string, we use the structure of the string
  to find the answer directly through recursion.

  Each string Sn has this structure:
  |<--- Sn-1 --->| 1 |<-- reverse(invert(Sn-1)) --->|
       left         mid           right

  Length of Sn = 2^n - 1
  Mid position = 2^(n-1)  (the middle '1')

  So we have 3 cases:
    CASE 1: k == mid  -->  the answer is '1' (the middle bit is always '1')
    CASE 2: k < mid   -->  k falls in the LEFT part (Sn-1), so recurse on Sn-1
    CASE 3: k > mid   -->  k falls in the RIGHT part (reverse(invert(Sn-1)))

  For CASE 3:
    The right part is reverse(invert(Sn-1)).
    If we want the kth bit in this right part, we need to find which position
    in the original Sn-1 it maps to.

    The right part has length = 2^(n-1) - 1
    Position in right part = k - mid
    Position in original Sn-1 (before reverse and invert):
      After reverse: position becomes (2^(n-1) - 1) - (k - mid) + 1 = (2^n - 1) - k
      After invert: the bit is flipped (0->1, 1->0)

    So: findKthBit(n, k) = invert( findKthBit(n-1, (2^n) - k) )

DRY RUN for n=3, k=5:
  S3 = "0111001"  -->  index 5 (1-based) = '0'

  Step 1: findKthBit(3, 5)
    n=3, k=5
    mid = 2^(3-1) = 4
    k=5 > mid=4  -->  CASE 3 (right part)
    Recurse: findKthBit(n-1=2, (2^3) - 5) = findKthBit(2, 3)
    Then flip the result.

  Step 2: findKthBit(2, 3)
    n=2, k=3
    mid = 2^(2-1) = 2
    k=3 > mid=2  -->  CASE 3 (right part)
    Recurse: findKthBit(n-1=1, (2^2) - 3) = findKthBit(1, 1)
    Then flip the result.

  Step 3: findKthBit(1, 1)
    n=1  -->  BASE CASE, return '0'

  Back to Step 2: result of findKthBit(1,1) = '0', flip it --> '1'
  Back to Step 1: result of findKthBit(2,3) = '1', flip it --> '0'

  Final answer: '0'  ✓  (matches S3[5] = '0')

DRY RUN for n=4, k=11:
  S4 = "011100111100100"  -->  index 11 (1-based) = '0'

  Step 1: findKthBit(4, 11)
    mid = 2^3 = 8
    k=11 > 8  -->  CASE 3
    Recurse: findKthBit(3, 16-11) = findKthBit(3, 5), then flip.

  Step 2: findKthBit(3, 5)
    mid = 4
    k=5 > 4  -->  CASE 3
    Recurse: findKthBit(2, 8-5) = findKthBit(2, 3), then flip.

  Step 3: findKthBit(2, 3)
    mid = 2
    k=3 > 2  -->  CASE 3
    Recurse: findKthBit(1, 4-3) = findKthBit(1, 1), then flip.

  Step 4: findKthBit(1, 1)
    n=1  -->  return '0'

  Back to Step 3: flip('0') = '1'
  Back to Step 2: flip('1') = '0'
  Back to Step 1: flip('0') = '1'

  Final answer: '1'  ✓  (matches S4[11] = '1')

TIME COMPLEXITY:  O(n)  - at most n recursive calls
SPACE COMPLEXITY: O(n)  - recursion stack depth

================================================================================
APPROACH 2: BUILD STRING USING RECURSION
================================================================================

INTUITION:
  Build the actual string S_n recursively using the formula:
    Si = Si-1 + "1" + reverse(invert(Si-1))

  Then directly access s[k-1].

  We start with s = "0" and build up to Sn.

DRY RUN for n=3:
  Start: s = "0"  (S1)

  i=2:  rev = "0" -> invert -> "1"
        s = "0" + "1" + "1" = "011"  (S2)

  i=3:  rev = "011" -> reverse -> "110" -> invert -> "001"
        s = "011" + "1" + "001" = "0111001"  (S3)

  For k=5: return s[4] = '0'

TIME COMPLEXITY:  O(2^n)  - string length is 2^n - 1
SPACE COMPLEXITY: O(2^n)  - storing the full string

This approach is slower but more intuitive.

================================================================================
APPROACH 3: BUILD STRING USING ITERATION (Iterative Loop)
================================================================================

INTUITION:
  Same as Approach 2 but uses a for-loop instead of recursion.
  Build Sn iteratively by repeatedly applying:
    s = s + "1" + reverse(invert(s))

DRY RUN for n=3:
  Start: s = "0"

  i=2:  rev = "0" -> invert -> "1"
        s = "0" + "1" + "1" = "011"

  i=3:  rev = "011" -> reverse -> "110" -> invert -> "001"
        s = "011" + "1" + "001" = "0111001"

  For k=5: return s[4] = '0'

TIME COMPLEXITY:  O(2^n)  - string length is 2^n - 1
SPACE COMPLEXITY: O(2^n)  - storing the full string

Same complexity as Approach 2, just iterative instead of recursive build.

================================================================================
COMPARISON:
  Approach 1 (Pure Recursion):   O(n) time,  O(n) space  --> OPTIMAL
  Approach 2 (Recursive Build):  O(2^n) time, O(2^n) space
  Approach 3 (Iterative Build):  O(2^n) time, O(2^n) space
================================================================================
*/

// ======================== APPROACH 1: PURE RECURSION ========================
class Solution1 {
public:
    /*
     * RECURSIVE HELPER: Finds kth bit in Sn without building the string.
     *
     * Structure of Sn:
     *   |<--- Sn-1 --->| '1' |<--- reverse(invert(Sn-1)) --->|
     *        LEFT          MID                RIGHT
     *
     * Length of Sn = 2^n - 1
     * Mid position = 2^(n-1)
     *
     * CASE 1: k == mid       --> return '1' (middle is always '1')
     * CASE 2: k < mid        --> k is in LEFT part, recurse on Sn-1
     * CASE 3: k > mid        --> k is in RIGHT part
     *                             Position maps to (2^n - k) in Sn-1
     *                             Then invert the result
     */
    char findKthBit(int n, int k) {
        // BASE CASE: S1 = "0", so the only bit is '0'
        if (n == 1) {
            return '0';
        }

        // mid = 2^(n-1) = the position of the middle '1' in Sn
        // Length of Sn = 2^n - 1, so mid is at index 2^(n-1) (1-based)
        int mid = 1 << (n - 1);  // 1 << (n-1) is same as 2^(n-1)

        // CASE 1: k is exactly at the middle position
        // The middle bit is always '1' in every Sn
        if (k == mid) {
            return '1';
        }

        // CASE 2: k is in the LEFT part (which is just Sn-1)
        // So we simply recurse on Sn-1 with the same k
        if (k < mid) {
            return findKthBit(n - 1, k);
        }

        // CASE 3: k is in the RIGHT part
        // Right part = reverse(invert(Sn-1))
        //
        // If k is at position (k - mid) in the right part,
        // then after reverse, it maps to position:
        //   (2^(n-1) - 1) - (k - mid) + 1 = (2^n - 1) - (k - mid)
        // Simplified: (2^n) - k
        //
        // After finding that bit in Sn-1, we invert it (flip 0<->1)
        char ans = findKthBit(n - 1, (1 << n) - k);

        // Invert the result: '0' becomes '1', '1' becomes '0'
        return ans == '0' ? '1' : '0';
    }
};

// ======================== APPROACH 2: RECURSIVE STRING BUILD =================
class Solution2 {
public:
    /*
     * RECURSIVE BUILD: Constructs Sn using the recursive formula.
     *
     * Formula: Si = Si-1 + "1" + reverse(invert(Si-1))
     *
     * We build the string from S1 up to Sn, then access s[k-1].
     */
    void build(string &s, int i, int n) {
        // BASE CASE: We've built up to Sn, stop
        if (i > n) {
            return;
        }

        // Make a copy of current string and reverse it
        string rev = s;
        reverse(rev.begin(), rev.end());

        // Invert every bit in the reversed copy (0->1, 1->0)
        for (char &c : rev) {
            c = (c == '0' ? '1' : '0');
        }

        // Append: "1" + inverted-reversed copy
        s = s + "1" + rev;

        // Recurse to build the next level
        build(s, i + 1, n);
    }

    char findKthBit(int n, int k) {
        // Start with S1 = "0"
        string s = "0";

        // Build from S2 up to Sn
        build(s, 2, n);

        // Return the kth bit (1-indexed, so s[k-1])
        return s[k - 1];
    }
};

// ======================== APPROACH 3: ITERATIVE STRING BUILD ================
class Solution3 {
public:
    /*
     * ITERATIVE BUILD: Same as Approach 2 but uses a for-loop.
     *
     * Formula: Si = Si-1 + "1" + reverse(invert(Si-1))
     *
     * We build the string from S1 up to Sn iteratively.
     */
    char findKthBit(int n, int k) {
        // Start with S1 = "0"
        string s = "0";

        // Build from S2 up to Sn
        for (int i = 2; i <= n; i++) {
            // Make a copy and reverse it
            string rev = s;
            reverse(rev.begin(), rev.end());

            // Invert every bit in the reversed copy
            for (char &c : rev) {
                c = (c == '0' ? '1' : '0');
            }

            // Append: current string + "1" + inverted-reversed copy
            s = s + "1" + rev;
        }

        // Return the kth bit (1-indexed, so s[k-1])
        return s[k - 1];
    }
};

int main(){
    return 0;
}
