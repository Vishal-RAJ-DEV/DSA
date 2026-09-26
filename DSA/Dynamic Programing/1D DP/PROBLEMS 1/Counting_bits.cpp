#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
================================================================================
PROBLEM: Counting Bits (DP)
================================================================================

Given an integer n, return an array ans of length n+1 where ans[i] is the
number of 1's in the binary representation of i.

Example: n=5
  0 = 000  -> 0 ones
  1 = 001  -> 1 one
  2 = 010  -> 1 one
  3 = 011  -> 2 ones
  4 = 100  -> 1 one
  5 = 101  -> 2 ones
  Answer: [0, 1, 1, 2, 1, 2]

================================================================================
HOW BINARY AND BITS WORK
================================================================================

Every integer can be written in binary (base-2) using only 0s and 1s.
Each position in binary represents a power of 2.

  Decimal -> Binary -> Breakdown
    0     ->   0    -> 0
    1     ->   1    -> 1
    2     ->  10    -> 2 + 0
    3     ->  11    -> 2 + 1
    4     -> 100    -> 4 + 0 + 0
    5     -> 101    -> 4 + 0 + 1
    6     -> 110    -> 4 + 2 + 0
    7     -> 111    -> 4 + 2 + 1
    8     ->1000    -> 8 + 0 + 0 + 0

The "1's" in binary are called SET BITS.
  5 = 101 has 2 set bits (the two 1s at positions 0 and 2)

================================================================================
HOW RIGHT SHIFT (>>) WORKS
================================================================================

The right shift operator >> shifts all bits one position to the RIGHT.

  i >> 1  means: "shift bits of i one position right"
  This is the SAME as integer division by 2:  i >> 1 == i / 2

Why? Because shifting right drops the LAST (least significant) bit:

  i = 13 -> binary: 1101
  i >> 1 = 6 -> binary: 0110   (last bit '1' dropped, everything shifted right)

  i = 10 -> binary: 1010
  i >> 1 = 5 -> binary: 0101   (last bit '0' dropped)

  i = 7  -> binary: 111
  i >> 1 = 3  -> binary: 011   (last bit '1' dropped)

VISUAL:
  ┌──────────────────────────────────────────────────┐
  │  Original:  1  1  0  1      (binary of 13)       │
  │              \  \  \  \                           │
  │               v  v  v  v   shift each bit right   │
  │              _  1  1  0  1   (1 is discarded)     │
  │                                                  │
  │  Result:    0  1  1  0      (binary of 6)        │
  └──────────────────────────────────────────────────┘

KEY INSIGHT: When you right shift by 1 (i >> 1):
  - You REMOVE the last bit of i
  - The remaining bits form the number i/2
  - So the count of 1-bits in (i >> 1) is ALREADY COMPUTED in ans[i >> 1]

================================================================================
HOW (i & 1) WORKS - CHECKING THE LAST BIT
================================================================================

The AND operator & compares bits:
  - i & 1 checks ONLY the last bit of i
  - If last bit is 1 -> i & 1 = 1 (number is ODD)
  - If last bit is 0 -> i & 1 = 0 (number is EVEN)

  Why? Because 1 in binary is ...0001, so AND with 1 keeps only the last bit.

  i=5 (101):  101 & 001 = 001 = 1  (odd, last bit is 1)
  i=4 (100):  100 & 001 = 000 = 0  (even, last bit is 0)
  i=7 (111):  111 & 001 = 001 = 1  (odd, last bit is 1)
  i=6 (110):  110 & 001 = 000 = 0  (even, last bit is 0)

================================================================================
THE DP FORMULA: ans[i] = ans[i >> 1] + (i & 1)
================================================================================

This is the KEY insight. For ANY number i:

  Number of 1-bits in i = Number of 1-bits in (i/2) + Is last bit of i a 1?

WHY?
  Any number i can be split into TWO parts:
    [all bits except last] + [last bit]
    i = (i >> 1)            + (i & 1)

  So:  count_ones(i) = count_ones(i >> 1) + (i & 1)

  Since i >> 1 = i/2, and we compute answers in ORDER from 0 to n,
  ans[i/2] is ALREADY COMPUTED when we reach i.

EXAMPLE TRACE for n=7:

  i=0: ans[0] = 0                     (base case: 0 has no 1-bits)
       Binary: 000, ones = 0

  i=1: ans[1] = ans[1>>1] + (1&1)
             = ans[0]    + 1
             = 0         + 1 = 1
       Binary: 001, ones = 1
       WHY: 1 = (1 >> 1) + last_bit = (0) + 1 -> 0 ones + 1 = 1

  i=2: ans[2] = ans[2>>1] + (2&1)
             = ans[1]    + 0
             = 1         + 0 = 1
       Binary: 010, ones = 1
       WHY: 2 = (1) + 0 -> 1 one + 0 = 1

  i=3: ans[3] = ans[3>>1] + (3&1)
             = ans[1]    + 1
             = 1         + 1 = 2
       Binary: 011, ones = 2
       WHY: 3 = (1) + 1 -> 1 one + 1 = 2

  i=4: ans[4] = ans[4>>1] + (4&1)
             = ans[2]    + 0
             = 1         + 0 = 1
       Binary: 100, ones = 1
       WHY: 4 = (2) + 0 -> 1 one + 0 = 1

  i=5: ans[5] = ans[5>>1] + (5&1)
             = ans[2]    + 1
             = 1         + 1 = 2
       Binary: 101, ones = 2
       WHY: 5 = (2) + 1 -> 1 one + 1 = 2

  i=6: ans[6] = ans[6>>1] + (6&1)
             = ans[3]    + 0
             = 2         + 0 = 2
       Binary: 110, ones = 2
       WHY: 6 = (3) + 0 -> 2 ones + 0 = 2

  i=7: ans[7] = ans[7>>1] + (7&1)
             = ans[3]    + 1
             = 2         + 1 = 3
       Binary: 111, ones = 3
       WHY: 7 = (3) + 1 -> 2 ones + 1 = 3

  FINAL: [0, 1, 1, 2, 1, 2, 2, 3]

VISUAL RELATIONSHIP TREE:
                    i=0 (0 ones)
                    /
                  i=1 (1) --------\
                  /                 \
              i=2 (1)             i=3 (2)
              /                      \
          i=4 (1)                   i=5 (2)
          /                            \
      i=6 (2)                       i=7 (3)

  Each node i gets its count from parent i/2, plus 1 if i is odd.

================================================================================
WHY THIS IS DP
================================================================================

We reuse PREVIOUSLY COMPUTED results:
  - ans[i] depends on ans[i/2] which was computed EARLIER (i/2 < i)
  - We fill the array left to right (0 to n), so dependencies are ready
  - Time: O(n) - one pass through 0 to n
  - Space: O(n) - for the answer array

Without this DP insight, you'd need to count bits for EACH number
individually (O(n * log(n))). This DP approach is O(n).
*/

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ans(n + 1);

        for (int i = 1; i <= n; i++) {
            ans[i] = ans[i >> 1] + (i & 1);
        }

        return ans;
    }
};


int main(){
    return 0;
}