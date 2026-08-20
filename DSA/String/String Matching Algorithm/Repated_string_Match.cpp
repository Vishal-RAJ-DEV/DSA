/*
================================================================================================
                        REPEATED STRING MATCH PROBLEM - FULL EXPLANATION
================================================================================================

QUESTION:
---------
Given two strings A and B, find the minimum number of times A has to be repeated
such that B becomes a substring of the repeated string. If B can never be a
subsequence of the repeated string, return -1.

In simpler terms:
  - You have string A
  - You keep appending A to itself: A, AA, AAA, AAAA, ...
  - At some point, does string B appear INSIDE this growing string?
  - Return the MINIMUM number of A's needed for B to appear
  - If it's impossible, return -1

EXAMPLES:
---------
  Example 1: A = "abc", B = "abcabc"
    Repeated A: "abc" -> "abcabc" -> "abcabcabc" -> ...
    B = "abcabc" is found in "abcabc" (2 repeats)  => Answer: 2

  Example 2: A = "abc", B = "def"
    Repeated A: "abc" -> "abcabc" -> "abcabcabc" -> ...
    B = "def" can NEVER appear because A has no 'd', 'e', 'f' => Answer: -1

  Example 3: A = "abcd", B = "cdabcdab"
    Repeated A: "abcd" -> "abcdabcd" -> "abcdabcdabcd" -> ...
    B = "cdabcdab" is found in "abcdabcdabcd" (3 repeats) => Answer: 3

------------------------------------------------------------------------------------------------

WHY DO WE NEED AT MOST (lenA + lenB) REPEATS?
----------------------------------------------
  The minimum number of repeats needed = ceil(len(B) / len(A))
  But we MIGHT need ONE extra repeat to catch a substring that starts
  in the middle of one A and ends in the middle of another.

  Worst case: B starts near the END of one A and ends near the START
  of a later A. So we need at most: ceil(len(B)/len(A)) + 1 repeats.

  Formula: (m + n - 1) / n  gives us ceil(m/n) using integer math
  where m = len(B), n = len(A).

------------------------------------------------------------------------------------------------

HOW THE ALGORITHM WORKS (STEP BY STEP):
----------------------------------------

  Step 1: Calculate minimum repeats needed based on lengths
          repeats = ceil(m / n) where m = len(B), n = len(A)

  Step 2: Build string S by repeating A that many times

  Step 3: Check if B is a substring of S
          - If YES, return repeats
          - If NO, go to Step 4

  Step 4: Add ONE more repeat of A (because B might span across boundaries)
          Check again
          - If YES, return repeats (now incremented)
          - If NO, return -1 (impossible)

------------------------------------------------------------------------------------------------

VISUAL WALKTHROUGH - Example 1: A = "abc", B = "abcabc"
=========================================================

  len(A) = 3, len(B) = 6
  repeats = ceil(6/3) = 2

  Step 1: Build S with 2 repeats of A
  ┌──────────────────────────────────────────────────┐
  │  A = "abc"                                       │
  │  S = "abc" + "abc" = "abcabc"                    │
  │                                                   │
  │  Index:  0 1 2 3 4 5                              │
  │  S:     [a b c a b c]                             │
  └──────────────────────────────────────────────────┘

  Step 2: Search for B = "abcabc" in S
  ┌──────────────────────────────────────────────────┐
  │  S:  [a b c a b c]                               │
  │       └─────┘ └─────┘                            │
  │       "abc"   "abc"  = "abcabc" = B!  ✓ FOUND   │
  └──────────────────────────────────────────────────┘

  Answer: 2

------------------------------------------------------------------------------------------------

VISUAL WALKTHROUGH - Example 2: A = "abc", B = "def"
=====================================================

  len(A) = 3, len(B) = 3
  repeats = ceil(3/3) = 1

  Step 1: Build S with 1 repeat of A
  ┌──────────────────────────────────────────────────┐
  │  S = "abc"                                       │
  └──────────────────────────────────────────────────┘

  Step 2: Search for B = "def" in S
  ┌──────────────────────────────────────────────────┐
  │  S:  [a b c]                                     │
  │       ✗ No 'd' found                             │
  └──────────────────────────────────────────────────┘
  NOT FOUND

  Step 3: Add one more repeat -> S = "abcabc"
  ┌──────────────────────────────────────────────────┐
  │  S:  [a b c a b c]                               │
  │       Still no 'd', 'e', 'f' anywhere! ✗         │
  └──────────────────────────────────────────────────┘
  NOT FOUND

  Answer: -1 (Impossible - B contains chars not in A)

------------------------------------------------------------------------------------------------

VISUAL WALKTHROUGH - Example 3: A = "abcd", B = "cdabcdab"
============================================================

  len(A) = 4, len(B) = 8
  repeats = ceil(8/4) = 2

  Step 1: Build S with 2 repeats
  ┌──────────────────────────────────────────────────┐
  │  S = "abcd" + "abcd" = "abcdabcd"                │
  │                                                   │
  │  Index:  0 1 2 3 4 5 6 7                          │
  │  S:     [a b c d a b c d]                         │
  └──────────────────────────────────────────────────┘

  Step 2: Search for B = "cdabcdab" in S
  ┌──────────────────────────────────────────────────┐
  │  S:  [a b c d a b c d]  (length 8)               │
  │  B:     [c d a b c d a b]  (length 8)            │
  │         ^                                     ^   │
  │         B starts at index 2, but S ends       |   │
  │         before B can finish! ✗ NOT FOUND          │
  └──────────────────────────────────────────────────┘

  Step 3: Add one more repeat -> S = "abcdabcdabcd" (len 12)
  ┌──────────────────────────────────────────────────────────────┐
  │  Index:  0 1 2 3 4 5 6 7 8 9 10 11                          │
  │  S:     [a b c d a b c d a b  c  d]                         │
  │               └─────────────────┘                            │
  │               B = "cdabcdab" starting at index 2!  ✓ FOUND  │
  └──────────────────────────────────────────────────────────────┘

  Answer: 3

------------------------------------------------------------------------------------------------

WHY +1 REPEAT MATTERS (The Key Insight):
-----------------------------------------
  Consider A = "a", B = "aa"
    repeats = ceil(2/1) = 2
    S = "aa" -> B found in 2 repeats ✓

  But consider A = "ab", B = "ba":
    repeats = ceil(2/2) = 1
    S = "ab" -> "ba" NOT found ✗
    Add one more: S = "abab" -> "ba" found at index 1 ✓

  This is because B = "ba" spans ACROSS the boundary between two A's:
    ┌─────────────────────────────────────┐
    │  S = "ab" | "ab"                    │
    │       ─────┬─────                   │
    │           "ba"  (spans boundary)    │
    └─────────────────────────────────────┘

  Without the extra repeat, the boundary is never tested!

------------------------------------------------------------------------------------------------

TIME COMPLEXITY:
  O(n + m) where n = len(A), m = len(B)
  - Building string: O(repeats * n) = O(m + n)
  - String search (find): O(m + n) on average (using efficient algo internally)

SPACE COMPLEXITY:
  O(m + n) for storing the repeated string

------------------------------------------------------------------------------------------------

EDGE CASES:
-----------
  1. B is empty string -> return 0 (empty string is substring of anything)
  2. A is empty string -> return -1 (can never build anything)
  3. B contains characters not in A -> return -1
  4. B == A -> return 1
  5. B is longer than A and spans multiple repeats -> needs ceil(m/n) or +1

================================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int repeatedStringMatch(string a, string b) {

        int n = a.size();
        int m = b.size();

        // Minimum repetitions needed based on length
        // Formula: ceil(m/n) using integer math = (m + n - 1) / n
        // This ensures we build a string long enough to potentially contain B
        int repeats = (m + n - 1) / n;

        string s = "";

        // Build the repeated string by concatenating A 'repeats' times
        // Example: A="abc", repeats=2 -> S="abcabc"
        for (int i = 0; i < repeats; i++) {
            s += a;
        }

        // Check if B exists as a substring in our built string
        // string::npos means "not found" - if find() returns anything else, B is found
        if (s.find(b) != string::npos) {
            return repeats;
        }

        // KEY INSIGHT: B might start in the middle of one A and end in
        // the middle of the NEXT A, spanning across the boundary.
        // We need ONE extra repeat to catch this case.
        //
        // Example: A="ab", B="ba"
        //   After 1 repeat: S="ab" -> "ba" NOT found
        //   After 2 repeats: S="abab" -> "ba" found at index 1!
        //   The "ba" spans across the boundary between the two A's.
        //
        //  ┌──────────┬──────────┐
        //  │    A     │    A     │
        //  │  "ab"    │  "ab"    │
        //  │     └────┼────┘     │
        //  │       "ba" (span)   │
        //  └──────────┴──────────┘
        s += a;
        repeats++;

        if (s.find(b) != string::npos) {
            return repeats;
        }

        // If still not found after minimum + 1 repeats, it's impossible.
        // This happens when B contains characters that don't exist in A.
        return -1;
    }
};


int main(){
    Solution sol;

    // Test 1: A="abc", B="abcabc"
    // S = "abcabc" (2 repeats) -> B found -> Answer: 2
    cout << sol.repeatedStringMatch("abc", "abcabc") << endl;

    // Test 2: A="abc", B="def"
    // "def" can never appear in repeating "abc" -> Answer: -1
    cout << sol.repeatedStringMatch("abc", "def") << endl;

    return 0;
}