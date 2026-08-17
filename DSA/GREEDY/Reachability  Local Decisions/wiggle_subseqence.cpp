/*
================================================================================
WIGGLE SUBSEQUENCE
================================================================================

PROBLEM:
  Given an integer array nums, return the length of the longest wiggle subsequence.
  A wiggle subsequence is where consecutive elements alternate between increasing
  and decreasing (up, down, up, down, ... or down, up, down, up, ...).

  NOTE: This is a SUBSEQUENCE (elements can be skipped), NOT a subarray (contiguous).

  Example: nums = [1,7,4,9,2,5]
    Longest wiggle subsequence: [1, 7, 4, 9, 2, 5]
    Pattern: up(1<7), down(7>4), up(4<9), down(9>2), up(2<5)
    Length = 6

================================================================================
HOW THE up/down VARIABLES WORK
================================================================================

  up   = length of longest wiggle subsequence ENDING with an UPWARD move
  down = length of longest wiggle subsequence ENDING with a DOWNWARD move

  Initialization: up = 1, down = 1 (single element is both)

  At each position i:
    if nums[i] > nums[i-1]:  (UPWARD move)
      → We can EXTEND any subsequence that ended with a downward move
      → up = down + 1

    if nums[i] < nums[i-1]:  (DOWNWARD move)
      → We can EXTEND any subsequence that ended with an upward move
      → down = up + 1

    if nums[i] == nums[i-1]: (EQUAL)
      → NOTHING changes (we just skip this element)

  Answer = max(up, down)

================================================================================
WHY NO RESET IS NEEDED (unlike Turbulent Subarray)
================================================================================

  KEY DIFFERENCE: SUBSEQUENCE vs SUBARRAY

  In Wiggle Subsequence (subsequence - can skip elements):
    - up and down store the BEST possible lengths ending at position i
    - When nums[i] > nums[i-1], we set up = down + 1
    - The OLD value of up is GONE because we found a BETTER up-ending sequence
    - We do NOT reset down because down still represents the best down-ending
      sequence from previous positions. It might be useful later if we see a
      decrease after the current increase.

  In Longest Turbulent Subarray (subarray - must be contiguous):
    - When arr[i] > arr[i-1], we MUST reset down = 1
    - Why? Because in a CONTIGUOUS subarray, if we just saw an increase,
      any future decrease can only extend from the CURRENT pair, not from
      some old decrease that happened before the increase.
    - The reset ensures we track the CURRENT alternating pattern.

  VISUAL EXAMPLE of why reset matters in Turbulent but NOT in Wiggle:

    arr = [2, 0, 2, 4]

    Turbulent (subarray - must be contiguous):
      2 → 0: DOWN, down = 2, up = 1
      0 → 2: UP,   up = down+1 = 3, **RESET down = 1** (old DOWN is no longer
                    part of the same contiguous subarray)
      2 → 4: UP,   up = down+1 = 2 (NOT 4, because reset happened)
      Answer = 3 (subarray [2, 0, 2])

    Wiggle (subsequence - can skip):
      2 → 0: DOWN, down = 2, up = 1
      0 → 2: UP,   up = down+1 = 3, down STAYS at 2
      2 → 4: UP,   NOTHING happens (equal direction, we can skip 4)
      Answer = 3 (subsequence [2, 0, 2])

  WHY EQUAL ELEMENTS DON'T NEED HANDLING IN WIGGLE:

    In Wiggle, if nums[i] == nums[i-1]:
      - We simply do nothing (no else-if branch for equality)
      - The element is SKIPPED because it doesn't change up or down
      - This is correct because a subsequence can skip elements

    In Turbulent, if arr[i] == arr[i-1]:
      - We MUST reset both up = 1 and down = 1
      - Because in a subarray, equal elements BREAK the turbulence pattern
      - We can't just skip them - they're part of the contiguous window

================================================================================
STEP-BY-STEP TRACE: nums = [1, 7, 4, 9, 2, 5]
================================================================================

  Index:   0    1    2    3    4    5
  Value:  [1]  [7]  [4]  [9]  [2]  [5]
           ↓    ↓    ↓    ↓    ↓    ↓
  Comp:    -    UP   DOWN UP   DOWN UP

  ┌───────┬─────────┬─────────┬─────────┐
  │  i    │  comp   │   up    │  down   │
  ├───────┼─────────┼─────────┼─────────┤
  │  0    │    -    │    1    │    1    │  (single element)
  │  1    │  1<7 UP │    2    │    1    │  up = down+1 = 2
  │  2    │  7>4 DN │    2    │    3    │  down = up+1 = 3
  │  3    │  4<9 UP │    4    │    3    │  up = down+1 = 4
  │  4    │  9>2 DN │    4    │    5    │  down = up+1 = 5
  │  5    │  2<5 UP │    6    │    5    │  up = down+1 = 6
  └───────┴─────────┴─────────┴─────────┘

  Answer = max(6, 5) = 6

================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();

        // up = length of longest wiggle subsequence ENDING with an upward move
        // down = length of longest wiggle subsequence ENDING with a downward move
        int up = 1;
        int down = 1;

        for(int i = 1 ; i < n ; i++){
            if(nums[i] > nums[i-1]){
                // UPWARD move: extend a subsequence that ended with a downward move
                // The old up value is implicitly discarded (we found a better one)
                up = down + 1;
                // NOTE: down is NOT reset here. It still holds the best down-ending
                // sequence from previous positions, which might be useful later.
            }
            else if(nums[i] < nums[i-1]){
                // DOWNWARD move: extend a subsequence that ended with an upward move
                // The old down value is implicitly discarded (we found a better one)
                down = up + 1;
                // NOTE: up is NOT reset here. It still holds the best up-ending
                // sequence from previous positions, which might be useful later.
            }
            // if nums[i] == nums[i-1]: do NOTHING (skip duplicate, it's a subsequence)
        }

        return max(up, down);
    }
};


/*
================================================================================
COMPARISON: WIGGLE SUBSEQUENCE vs LONGEST TURBULENT SUBARRAY
================================================================================

  ┌──────────────────────┬───────────────────────────┬───────────────────────────┐
  │      Aspect          │   Wiggle Subsequence      │  Turbulent Subarray       │
  ├──────────────────────┼───────────────────────────┼───────────────────────────┤
  │ What we find         │ SUBSEQUENCE (can skip)    │ SUBARRAY (contiguous)     │
  │ Reset on increase?   │ NO (down stays)           │ YES (down = 1)            │
  │ Reset on decrease?   │ NO (up stays)             │ YES (up = 1)              │
  │ Handle equals?       │ NO (skip, do nothing)     │ YES (reset both to 1)     │
  │ Why different?       │ Skipped elements don't    │ Contiguous window means   │
  │                      │ affect future choices     │ old values are invalid    │
  └──────────────────────┴───────────────────────────┴───────────────────────────┘

  CORE REASON:
    - Subsequence: up/down store BEST EVER seen. Old values might still be useful
      because we can skip elements and come back to them later.
    - Subarray: up/down store CURRENT pattern. Old values become INVALID when the
      pattern breaks (same direction twice or equal elements), because the
      contiguous window is broken.

================================================================================
*/

int main(){
    return 0;
}
