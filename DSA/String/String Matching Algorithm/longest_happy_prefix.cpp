/*
================================================================================================
                    LONGEST HAPPY PREFIX PROBLEM - FULL EXPLANATION
================================================================================================

QUESTION:
---------
A "happy prefix" is a non-empty prefix of a string that is also a suffix
of the string, BUT the prefix and suffix must NOT overlap entirely
(i.e., it must be a PROPER prefix — not the whole string itself).

Given a string S, find the LONGEST happy prefix. If none exists, return "".

In simpler terms:
  - Find the longest prefix of S that is also a suffix of S
  - The prefix and suffix can overlap partially, but can't be the entire string
  - Return that prefix as a string (or "" if no such prefix exists)

EXAMPLES:
---------
  Example 1: S = "level"
    Prefixes: "l", "le", "lev", "leve", "level"
    Suffixes: "l", "el", "vel", "evel", "level"
    Common proper prefix=suffix: "l" (length 1)
    Answer: "l"

  Example 2: S = "ababab"
    Prefixes: "a", "ab", "aba", "abab", "ababa", "ababab"
    Suffixes: "b", "ab", "bab", "abab", "babab", "ababab"
    Common proper prefix=suffix: "abab" (length 4)
    Answer: "abab"

  Example 3: S = "leetcode"
    No proper prefix is also a suffix
    Answer: ""

  Example 4: S = "aabaab"
    Common proper prefix=suffix: "aab" (length 3)
    Answer: "aab"

------------------------------------------------------------------------------------------------

WHAT IS THE LPS ARRAY?
-----------------------
  LPS[i] = length of the longest PROPER prefix of s[0..i]
           that is also a SUFFIX of s[0..i]

  "Proper" means it can't be the entire substring s[0..i] itself.

  This is the same LPS (Longest Proper Prefix which is also Suffix) array
  used in the KMP string matching algorithm. It's the CORE of KMP.

  The answer to this problem is simply: s[0 .. lps[n-1]-1]

------------------------------------------------------------------------------------------------

VISUAL WALKTHROUGH - Example: S = "ababab"
=============================================

  Step 1: Build LPS array using KMP technique
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  s = "ababab"  (length 6)                                               │
  │                                                                          │
  │  We need to compute LPS[i] for each position i.                         │
  │  LPS[i] = longest proper prefix of s[0..i] that is also a suffix        │
  │                                                                          │
  │  Algorithm: Two pointers i (current position) and j (current match len) │
  └──────────────────────────────────────────────────────────────────────────┘

  LPS COMPUTATION TRACE:
  ┌──────────────────────────────────────────────────────────────────────────┐
  │                                                                          │
  │  i=0: Initialize, skip (LPS[0] = 0 always)                             │
  │                                                                          │
  │  i=1, j=0: s[1]='b' vs s[0]='a'                                       │
  │            'b' != 'a' -> mismatch, j=0 so LPS[1]=0, i=2                │
  │                                                                          │
  │  i=2, j=0: s[2]='a' vs s[0]='a'                                       │
  │            'a' == 'a' -> match! j=1, LPS[2]=1, i=3                     │
  │                                                                          │
  │  i=3, j=1: s[3]='b' vs s[1]='b'                                       │
  │            'b' == 'b' -> match! j=2, LPS[3]=2, i=4                     │
  │                                                                          │
  │  i=4, j=2: s[4]='a' vs s[2]='a'                                       │
  │            'a' == 'a' -> match! j=3, LPS[4]=3, i=5                     │
  │                                                                          │
  │  i=5, j=3: s[5]='b' vs s[3]='b'                                       │
  │            'b' == 'b' -> match! j=4, LPS[5]=4, i=6                     │
  │                                                                          │
  │  DONE (i reached n)                                                      │
  │                                                                          │
  │  LPS array: [0, 0, 1, 2, 3, 4]                                         │
  │                                                                          │
  │  Index:      0  1  2  3  4  5                                           │
  │  chars:     [a  b  a  b  a  b]                                           │
  │  LPS:       [0  0  1  2  3  4]  <--- last element = 4                   │
  │                                                                          │
  └──────────────────────────────────────────────────────────────────────────┘

  Step 2: Extract result
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  lps[n-1] = lps[5] = 4                                                  │
  │  Answer = s.substr(0, 4) = "abab"                                       │
  │                                                                          │
  │  Verify: "abab" is both a prefix AND a suffix of "ababab"              │
  │                                                                          │
  │  s = "ababab"                                                           │
  │        └──┘  prefix = "abab"                                            │
  │           └──┘  suffix = "abab"                                         │
  │  They overlap but that's OK (proper prefix, not the whole string)       │
  └──────────────────────────────────────────────────────────────────────────┘

------------------------------------------------------------------------------------------------

VISUAL WALKTHROUGH - Example: S = "aabaab"
============================================

  s = "aabaab"  (length 6)

  LPS COMPUTATION TRACE:
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  i=1, j=0: s[1]='a' vs s[0]='a' -> match! j=1, LPS[1]=1, i=2         │
  │  i=2, j=1: s[2]='b' vs s[1]='a' -> mismatch, j=lps[0]=0              │
  │            s[2]='b' vs s[0]='a' -> mismatch, j=0, LPS[2]=0, i=3       │
  │  i=3, j=0: s[3]='a' vs s[0]='a' -> match! j=1, LPS[3]=1, i=4         │
  │  i=4, j=1: s[4]='a' vs s[1]='a' -> match! j=2, LPS[4]=2, i=5         │
  │  i=5, j=2: s[5]='b' vs s[2]='b' -> match! j=3, LPS[5]=3, i=6         │
  │                                                                          │
  │  LPS: [0, 1, 0, 1, 2, 3]                                               │
  │  lps[5] = 3                                                             │
  │  Answer = s.substr(0, 3) = "aab"                                        │
  │                                                                          │
  │  Verify: "aab" is prefix of "aabaab" ✓                                 │
  │          "aab" is suffix of "aabaab" ✓                                  │
  └──────────────────────────────────────────────────────────────────────────┘

------------------------------------------------------------------------------------------------

VISUAL WALKTHROUGH - Example: S = "leetcode"
================================================

  s = "leetcode"  (length 8)

  LPS COMPUTATION TRACE:
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  i=1, j=0: s[1]='e' vs s[0]='l' -> mismatch, j=0, LPS[1]=0, i=2      │
  │  i=2, j=0: s[2]='e' vs s[0]='l' -> mismatch, j=0, LPS[2]=0, i=3      │
  │  i=3, j=0: s[3]='t' vs s[0]='l' -> mismatch, j=0, LPS[3]=0, i=4      │
  │  i=4, j=0: s[4]='c' vs s[0]='l' -> mismatch, j=0, LPS[4]=0, i=5      │
  │  i=5, j=0: s[5]='o' vs s[0]='l' -> mismatch, j=0, LPS[5]=0, i=6      │
  │  i=6, j=0: s[6]='d' vs s[0]='l' -> mismatch, j=0, LPS[6]=0, i=7      │
  │  i=7, j=0: s[7]='e' vs s[0]='l' -> mismatch, j=0, LPS[7]=0, i=8      │
  │                                                                          │
  │  LPS: [0, 0, 0, 0, 0, 0, 0, 0]                                         │
  │  lps[7] = 0                                                             │
  │  Answer = s.substr(0, 0) = ""  (empty string)                          │
  │  No happy prefix exists!                                                 │
  └──────────────────────────────────────────────────────────────────────────┘

------------------------------------------------------------------------------------------------

HOW THE TWO-POINTER ALGORITHM WORKS:
--------------------------------------

  We use two pointers:
    i = current position we're computing LPS for (starts at 1)
    j = length of current matching prefix-suffix (starts at 0)

  At each step:
  ┌──────────────────────────────────────────────────────────────────────────┐
  │                                                                          │
  │  CASE 1: s[i] == s[j]  (characters match)                              │
  │  ┌────────────────────────────────────────┐                             │
  │  │  The current prefix-suffix extends by 1│                             │
  │  │  j++, LPS[i] = j, i++                 │                             │
  │  │                                        │                             │
  │  │  Example: s="abab", i=3, j=2           │                             │
  │  │    s[3]='b' == s[2]='a'? No...        │                             │
  │  │    Actually s[3]='b' == s[2]='a'?      │                             │
  │  │    Let's use a better example:         │                             │
  │  │    s="abab", i=2, j=1                  │                             │
  │  │    s[2]='a' == s[1]='b'? No...        │                             │
  │  │    OK let me just show the idea:       │                             │
  │  │    If s[i]==s[j], we extend the match │                             │
  │  │    prefix of length j+1 is now also    │                             │
  │  │    a suffix ending at position i       │                             │
  │  └────────────────────────────────────────┘                             │
  │                                                                          │
  │  CASE 2: s[i] != s[j]  (characters don't match)                        │
  │  ┌────────────────────────────────────────┐                             │
  │  │  Sub-case 2a: j > 0                    │                             │
  │  │    We can't extend, but maybe we can   │                             │
  │  │    fall back to a shorter prefix.       │                             │
  │  │    Set j = lps[j-1] and try again.     │                             │
  │  │    (DON'T move i!)                      │                             │
  │  │                                         │                             │
  │  │  Sub-case 2b: j == 0                    │                             │
  │  │    No prefix matches at all.           │                             │
  │  │    LPS[i] = 0, move to next i.         │                             │
  │  └────────────────────────────────────────┘                             │
  │                                                                          │
  └──────────────────────────────────────────────────────────────────────────┘

  THE KEY INSIGHT - Why j = lps[j-1] on mismatch?
  ─────────────────────────────────────────────────
    Consider s = "aabaaab"
    At some point: prefix matched up to j=3 ("aab"), but s[i] doesn't match.

    Instead of starting over from j=0, we know:
    - The first 3 chars "aab" matched
    - lps[2] = 1 means "a" (length 1) is a proper prefix=suffix of "aab"
    - So we can fall back to j=1 and check if s[i] matches s[1]

    This is the KMP optimization - we NEVER go backwards on i!

------------------------------------------------------------------------------------------------

WHY LPS[i-1] GIVES THE ANSWER:
-------------------------------
  The LAST element of LPS (lps[n-1]) tells us:
  "What is the longest proper prefix of the ENTIRE string that is also
   a suffix?"

  This is exactly what the problem asks for!

  Answer = s.substr(0, lps[n-1])

  If lps[n-1] == 0, no happy prefix exists -> return ""

------------------------------------------------------------------------------------------------

TIME COMPLEXITY:  O(n) where n = len(s)
  - Each character is visited at most twice (i increments every iteration,
    j only decreases and never goes below 0)

SPACE COMPLEXITY: O(n) for the LPS array

------------------------------------------------------------------------------------------------

EDGE CASES:
-----------
  1. s has length 1 -> return "" (no proper prefix)
  2. s = "aaaa" -> LPS = [0,1,2,3], answer = "aaa"
  3. s = "abacabab" -> LPS = [0,0,1,0,1,2,3,2], answer = "ab"
  4. All characters same -> answer = s.substr(0, n-1)
  5. All characters different -> answer = ""

------------------------------------------------------------------------------------------------

CONNECTION TO KMP:
------------------
  This problem is essentially asking: "Compute the LPS array of S and
  return the prefix represented by the last element."

  The LPS array is the heart of the KMP (Knuth-Morris-Pratt) algorithm.
  In KMP, when a mismatch occurs during string matching, the LPS array
  tells us how far we can skip ahead without re-checking characters.

  In this problem, we're just using the LPS computation standalone,
  without the full KMP matching part.

================================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestPrefix(string s) {
        int n = s.size();

        // LPS array: lps[i] = length of longest proper prefix of s[0..i]
        //            that is also a suffix of s[0..i]
        // lps[0] = 0 always (a single char has no proper prefix)
        vector<int> lps(n, 0);

        // i = current position we're computing LPS for (starts at 1)
        // j = length of current longest prefix-suffix match
        int i = 1;
        int j = 0;

        while (i < n) {

            // CASE 1: Characters match — extend the current prefix-suffix
            if (s[i] == s[j]) {
                // The prefix of length j+1 is also a suffix ending at i
                j++;
                lps[i] = j;
                i++;
            }

            // CASE 2: Characters don't match
            else {

                if (j > 0) {
                    // KEY INSIGHT: Don't restart from 0!
                    // Fall back to the next shorter prefix-suffix
                    // lps[j-1] tells us: "what's the next best prefix
                    // length to try?" This avoids re-checking characters.
                    //
                    // Example: s = "aabaaab", j=3, mismatch at s[i]
                    //   lps[2] = 1, so fall back to j=1
                    //   Now check s[i] vs s[1] instead of s[0]
                    //   We NEVER move i backward — that's the KMP optimization!
                    j = lps[j - 1];
                }
                else {
                    // No prefix matches at all starting from this position
                    // LPS[i] = 0, move to next character
                    lps[i] = 0;
                    i++;
                }
            }
        }

        // lps[n-1] = length of longest proper prefix of the ENTIRE string
        //            that is also a suffix
        // Return that prefix as a substring
        //
        // If lps[n-1] == 0, substr(0,0) returns "" (no happy prefix)
        // Example: s="ababab", lps[5]=4, return s.substr(0,4)="abab"
        // Example: s="leetcode", lps[7]=0, return s.substr(0,0)=""
        return s.substr(0, lps[n - 1]);
    }
};


int main(){
    Solution sol;

    // Test cases:
    cout << sol.longestPrefix("level") << endl;      // "l"
    cout << sol.longestPrefix("ababab") << endl;     // "abab"
    cout << sol.longestPrefix("leetcode") << endl;   // ""
    cout << sol.longestPrefix("aabaab") << endl;     // "aab"
    cout << sol.longestPrefix("aaaa") << endl;       // "aaa"

    return 0;
}