/*
================================================================================================
              MINIMUM BIT FLIPS TO CONVERT NUMBER - FULL EXPLANATION
================================================================================================

QUESTION:
---------
Given two integers 'start' and 'goal', return the MINIMUM number of bit flips
required to convert 'start' to 'goal'.

A "bit flip" means changing a single bit from 0 to 1 or from 1 to 0.

EXAMPLES:
---------
  Example 1: start = 10, goal = 20
    Binary: 10 = 01010, 20 = 10100
    Bits that differ: positions 1,2,3,4 (4 flips needed)
    Answer: 4

  Example 2: start = 3, goal = 4
    Binary: 3 = 011, 4 = 100
    Bits that differ: all 3 positions (3 flips needed)
    Answer: 3

------------------------------------------------------------------------------------------------

KEY INSIGHT: XOR GIVES US THE ANSWER
--------------------------------------
  XOR (^) of two numbers produces a 1 at each position where the bits DIFFER.

  start ^ goal = a number where:
    - bit is 1  ->  start and goal DIFFER at this position (needs a flip)
    - bit is 0  ->  start and goal are the SAME at this position (no flip)

  So: Minimum flips = Number of 1s in (start ^ goal)
  This is called "popcount" or "Hamming weight" or "set bit count".

------------------------------------------------------------------------------------------------

THE ALGORITHM (2 STEPS):
--------------------------
  Step 1: XOR start and goal to get a number with 1s only where bits differ
          x = start ^ goal

  Step 2: Count the number of 1s in x (set bit count)
          This count = minimum flips needed

------------------------------------------------------------------------------------------------

DETAILED WALKTHROUGH - Example 1: start = 10, goal = 20
=========================================================

  Step 1: Convert to binary
  ┌──────────────────────────────────────────────────────────────────┐
  │  start = 10 = 0 1 0 1 0                                         │
  │  goal  = 20 = 1 0 1 0 0                                         │
  │  Bit pos:      4 3 2 1 0                                         │
  └──────────────────────────────────────────────────────────────────┘

  Step 2: XOR each bit position
  ┌──────────────────────────────────────────────────────────────────┐
  │  start:    0 1 0 1 0                                             │
  │  goal:     1 0 1 0 0                                             │
  │  XOR:      1 1 1 1 0   = 30 in decimal                          │
  │            └─┘ └─┘ └─┘                                           │
  │             4 bits are 1 -> need 4 flips!                        │
  │                                                                  │
  │  Bit 4: 0 XOR 1 = 1 (DIFFER -> flip needed)                    │
  │  Bit 3: 1 XOR 0 = 1 (DIFFER -> flip needed)                    │
  │  Bit 2: 0 XOR 1 = 1 (DIFFER -> flip needed)                    │
  │  Bit 1: 1 XOR 0 = 1 (DIFFER -> flip needed)                    │
  │  Bit 0: 0 XOR 0 = 0 (SAME -> no flip)                          │
  └──────────────────────────────────────────────────────────────────┘

  Step 3: Count set bits in x = 30 (binary: 11110)
  ┌──────────────────────────────────────────────────────────────────┐
  │  Loop iteration 1: x = 11110                                    │
  │    x & 1 = 11110 & 00001 = 00000 = 0? No, it's 0...           │
  │    Wait: 11110 & 00001 = 0 (last bit is 0)                     │
  │    ans += 0, x >>= 1 -> x = 01111 (15)                         │
  │                                                                  │
  │  Loop iteration 2: x = 01111                                    │
  │    x & 1 = 01111 & 00001 = 00001 = 1                           │
  │    ans += 1 -> ans = 1, x >>= 1 -> x = 00111 (7)               │
  │                                                                  │
  │  Loop iteration 3: x = 00111                                    │
  │    x & 1 = 00111 & 00001 = 00001 = 1                           │
  │    ans += 1 -> ans = 2, x >>= 1 -> x = 00011 (3)               │
  │                                                                  │
  │  Loop iteration 4: x = 00011                                    │
  │    x & 1 = 00011 & 00001 = 00001 = 1                           │
  │    ans += 1 -> ans = 3, x >>= 1 -> x = 00001 (1)               │
  │                                                                  │
  │  Loop iteration 5: x = 00001                                    │
  │    x & 1 = 00001 & 00001 = 00001 = 1                           │
  │    ans += 1 -> ans = 4, x >>= 1 -> x = 00000 (0)               │
  │                                                                  │
  │  Loop ends (x = 0)                                              │
  │  Answer = 4                                                     │
  └──────────────────────────────────────────────────────────────────┘

  VISUAL of the counting loop:
  ┌──────────────────────────────────────────────────────────────────┐
  │  x=30 (11110) -> x&1=0, ans=0  -> x=15 (01111)                │
  │  x=15 (01111) -> x&1=1, ans=1  -> x=7  (00111)                │
  │  x=7  (00111) -> x&1=1, ans=2  -> x=3  (00011)                │
  │  x=3  (00011) -> x&1=1, ans=3  -> x=1  (00001)                │
  │  x=1  (00001) -> x&1=1, ans=4  -> x=0  (00000) STOP           │
  └──────────────────────────────────────────────────────────────────┘

------------------------------------------------------------------------------------------------

DETAILED WALKTHROUGH - Example 2: start = 3, goal = 4
======================================================

  Step 1: Convert to binary
  ┌──────────────────────────────────────────────────────────────────┐
  │  start = 3  = 0 1 1                                              │
  │  goal  = 4  = 1 0 0                                              │
  │  Bit pos:      2 1 0                                              │
  └──────────────────────────────────────────────────────────────────┘

  Step 2: XOR
  ┌──────────────────────────────────────────────────────────────────┐
  │  start:    0 1 1                                                  │
  │  goal:     1 0 0                                                  │
  │  XOR:      1 1 1   = 7 in decimal                               │
  │            └─┘                                                    │
  │            ALL 3 bits are 1 -> need 3 flips!                     │
  └──────────────────────────────────────────────────────────────────┘

  Step 3: Count set bits in x = 7 (binary: 111)
  ┌──────────────────────────────────────────────────────────────────┐
  │  x=7 (111) -> x&1=1, ans=1 -> x=3 (011)                        │
  │  x=3 (011) -> x&1=1, ans=2 -> x=1 (001)                        │
  │  x=1 (001) -> x&1=1, ans=3 -> x=0 (000) STOP                   │
  │  Answer = 3                                                     │
  └──────────────────────────────────────────────────────────────────┘

------------------------------------------------------------------------------------------------

THE TWO OPERATIONS EXPLAINED:
-------------------------------

  OPERATION 1: XOR (start ^ goal)
  ─────────────────────────────────
    XOR truth table:
    ┌───┬───┬───────┐
    │ A │ B │ A ^ B │
    ├───┼───┼───────┤
    │ 0 │ 0 │   0   │  (same -> 0)
    │ 0 │ 1 │   1   │  (different -> 1)
    │ 1 │ 0 │   1   │  (different -> 1)
    │ 1 │ 1 │   0   │  (same -> 0)
    └───┴───┴───────┘

    XOR highlights exactly where two numbers DIFFER.
    A 1 in the result means "this bit needs flipping".

  OPERATION 2: Count set bits (popcount)
  ───────────────────────────────────────
    x & 1  -> extracts the LAST bit (0 or 1)
    x >>= 1 -> right-shifts x by 1 (removes last bit)

    We repeat until x becomes 0.
    Each time x&1 == 1, we found a bit that needs flipping.

------------------------------------------------------------------------------------------------

WHY THIS WORKS - The Logic:
-----------------------------
  If two bits are the SAME (both 0 or both 1):
    XOR = 0 -> no flip needed

  If two bits are DIFFERENT (one 0, one 1):
    XOR = 1 -> flip needed

  Counting all 1s in the XOR result gives the exact number of positions
  where bits differ, which equals the minimum flips needed.

  You CANNOT do better than this because:
    - Each differing bit MUST be flipped (can't skip any)
    - Each differing bit can be fixed with exactly ONE flip
    - Same bits should NOT be flipped (that would break them)

------------------------------------------------------------------------------------------------

VISUAL SUMMARY:
───────────────
  start  ─┐
           ├─ XOR ──> result (1s = positions that differ) ──> count 1s ──> ANSWER
  goal   ─┘

------------------------------------------------------------------------------------------------

TIME COMPLEXITY:  O(log n) where n = max(start, goal)
  - The while loop runs once per bit (at most 32 for int)

SPACE COMPLEXITY: O(1) — only using a few integer variables

------------------------------------------------------------------------------------------------

ALTERNATIVE APPROACH (builtin function):
  In practice, many languages have a built-in popcount:
    C++:  __builtin_popcount(x)
    Java: Integer.bitCount(x)
    Python: bin(x).count('1')

  So the entire function can be written as:
    return __builtin_popcount(start ^ goal);

  But the manual loop is better for understanding the algorithm.

================================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minBitFlips(int start, int goal) {

        // Step 1: XOR start and goal
        // The result 'x' has a 1 at each position where bits DIFFER
        // These 1s represent the bits that NEED to be flipped
        //
        // Example: start=10 (01010), goal=20 (10100)
        //   x = 01010 ^ 10100 = 11110
        //   x has four 1s -> four flips needed
        int x = start ^ goal;

        // Step 2: Count the number of 1s in x (set bit count / popcount)
        // Each 1 in x represents one bit that needs flipping
        int ans = 0;

        // Extract each bit from right to left using & 1 and >> 1
        while (x > 0) {
            // x & 1 extracts the LAST bit of x
            // If last bit is 1 -> add 1 to count (this position needs a flip)
            // If last bit is 0 -> add 0 (this position is fine)
            ans += x & 1;

            // Right shift x by 1 to process the next bit
            // This removes the last bit we just checked
            // Example: 11110 >> 1 = 01111
            x >>= 1;
        }

        // 'ans' now contains the total number of 1s in (start ^ goal)
        // = minimum number of bit flips to convert start to goal
        return ans;
    }
};


int main(){
    Solution sol;

    // Test 1: start=10 (01010), goal=20 (10100)
    // XOR = 11110 = 30, set bits = 4
    cout << sol.minBitFlips(10, 20) << endl;   // Output: 4

    // Test 2: start=3 (011), goal=4 (100)
    // XOR = 111 = 7, set bits = 3
    cout << sol.minBitFlips(3, 4) << endl;     // Output: 3

    // Test 3: start=7 (111), goal=7 (111)
    // XOR = 000 = 0, set bits = 0 (already same)
    cout << sol.minBitFlips(7, 7) << endl;     // Output: 0

    return 0;
}