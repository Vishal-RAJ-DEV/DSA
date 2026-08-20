/*
================================================================================================
                       SHORTEST PALINDROME PROBLEM - FULL EXPLANATION
================================================================================================

QUESTION:
---------
Given a string S, you can add characters ONLY in FRONT of it. Find the shortest
and lexicographically smallest palindrome that can be formed this way.

In simpler terms:
  - You have string S
  - You can prepend characters to it
  - Make it a palindrome with MINIMUM characters added
  - Return the resulting palindrome

EXAMPLES:
---------
  Example 1: S = "aacecaaa"
    The longest palindromic prefix is "aacecaa" (length 7)
    Only 'a' at the end is outside the palindrome
    Reverse of "a" = "a"
    Prepend "a" -> "aaacecaaa" ✓ palindrome
    Wait, that's wrong. Let me re-check.
    Actually: longest palindromic prefix = "aacecaa" is NOT palindrome
    Let me trace properly below.

  Example 2: S = "abcd"
    Longest palindromic prefix = "a" (length 1)
    Remaining = "bcd", reversed = "dcb"
    Answer: "dcbabcd"

------------------------------------------------------------------------------------------------

KEY INSIGHT: LONGEST PALINDROMIC PREFIX
---------------------------------------
  To make a palindrome by adding chars in FRONT, we need to find the LONGEST
  prefix of S that is already a palindrome. Everything AFTER that prefix must
  be reversed and prepended.

  Example: S = "abcd"
    Prefixes: "a" ✓palindrome, "ab" ✗, "abc" ✗, "abcd" ✗
    Longest palindromic prefix = "a" (length 1)
    Characters NOT in palindrome = "bcd"
    We need to prepend reverse("bcd") = "dcb"
    Result: "dcb" + "abcd" = "dcbabcd" ✓

  Example: S = "aacecaaa"
    Prefixes: "a" ✓, "aa" ✓, "aac" ✗, "aace" ✗, "aacec" ✗, "aaceca" ✗, "aacecaa" ✗
    Actually "aacecaa" - let me check: a==a ✓, a==a ✓, c==c ✓ -> YES it IS palindrome!
    Longest palindromic prefix = "aacecaa" (length 7)
    Characters NOT in palindrome = "a" (last char)
    Prepend reverse("a") = "a"
    Result: "a" + "aacecaaa" = "aaacecaaa" ✓

------------------------------------------------------------------------------------------------

HOW DO WE FIND THE LONGEST PALINDROMIC PREFIX?
------------------------------------------------
  We use the KMP algorithm's LPS (Longest Proper Prefix which is also Suffix) array!

  The trick:
    1. Reverse S to get rev(S)
    2. Combine: combined = S + "#" + rev(S)
       The '#' separator prevents overlapping between S and rev(S)
    3. Compute LPS array of combined
    4. The LAST value of LPS = length of longest palindromic prefix of S

  WHY DOES THIS WORK?
  ─────────────────────
    If S has a palindromic prefix of length k, then:
      - The first k chars of S = reverse of last k chars of S
      - This means first k chars of S match first k chars of rev(S)
      - In combined string: S[0..k-1] matches rev(S)[0..k-1]
      - LPS captures exactly this match!

    The '#' ensures we don't get false matches across the boundary.

------------------------------------------------------------------------------------------------

VISUAL WALKTHROUGH - Example 1: S = "aacecaaa"
================================================

  Step 1: Reverse S
  ┌──────────────────────────────────────────────────┐
  │  S    = "aacecaaa"                               │
  │  rev  = "aaacecaa"                               │
  └──────────────────────────────────────────────────┘

  Step 2: Build combined = S + "#" + rev(S)
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  combined = "aacecaaa#aaacecaa"                                         │
  │                                                                          │
  │  Index:    0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16                     │
  │  chars:   [a a c e c a a a # a  a  a  c  e  c  a  a]                    │
  │            ─────────────────   ─────────────────────                     │
  │              S (len=8)            rev(S) (len=8)                         │
  └──────────────────────────────────────────────────────────────────────────┘

  Step 3: Compute LPS array for combined
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  LPS[i] = length of longest proper prefix of combined[0..i]            │
  │           that is also a suffix of combined[0..i]                       │
  │                                                                          │
  │  combined = "aacecaaa#aaacecaa"                                         │
  │  Index:     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16          │
  │  chars:    [a  a  c  e  c  a  a  a  #  a  a  a  c  e  c  a  a]         │
  │  LPS:      [0  1  0  0  0  1  2  2  0  1  2  3  0  0  0  1  7]  <--- 7 │
  │                                                      last element = 7   │
  │                                                                          │
  │  FULL LPS TRACE (using len = previous LPS, i = current index):          │
  │                                                                          │
  │  i=0: 'a' -> LPS[0]=0 (no proper prefix)              len=0             │
  │  i=1: 'a' -> s[1]=='a'==s[0] match, len=1, LPS[1]=1   len=1             │
  │  i=2: 'c' -> s[2]!='c' (s[len=1]='a'), len=lps[0]=0  len=0, LPS[2]=0   │
  │  i=3: 'e' -> s[3]!='a' (s[len=0]), LPS[3]=0           len=0             │
  │  i=4: 'c' -> s[4]!='a' (s[len=0]), LPS[4]=0           len=0             │
  │  i=5: 'a' -> s[5]=='a'==s[0] match, len=1, LPS[5]=1   len=1             │
  │  i=6: 'a' -> s[6]=='a'==s[1] match, len=2, LPS[6]=2   len=2             │
  │  i=7: 'a' -> s[7]!='c' (s[len=2]), len=lps[1]=1       len=1             │
  │          -> s[7]=='a'==s[1] match, len=2, LPS[7]=2     len=2             │
  │  i=8: '#' -> s[8]!='c' (s[len=2]), len=lps[1]=1       len=1             │
  │          -> s[8]!='a' (s[len=1]), len=lps[0]=0         len=0, LPS[8]=0   │
  │  i=9: 'a' -> s[9]=='a'==s[0] match, len=1, LPS[9]=1   len=1             │
  │  i=10: 'a' -> s[10]=='a'==s[1] match, len=2, LPS[10]=2 len=2            │
  │  i=11: 'a' -> s[11]!='c' (s[len=2]), len=lps[1]=1     len=1             │
  │          -> s[11]=='a'==s[1] match, len=2, LPS[11]=2   len=2             │
  │  i=12: 'c' -> s[12]=='c'==s[2] match, len=3, LPS[12]=3 len=3            │
  │  i=13: 'e' -> s[13]=='e'==s[3] match, len=4, LPS[13]=4 len=4            │
  │  i=14: 'c' -> s[14]=='c'==s[4] match, len=5, LPS[14]=5 len=5            │
  │  i=15: 'a' -> s[15]=='a'==s[5] match, len=6, LPS[15]=6 len=6            │
  │  i=16: 'a' -> s[16]=='a'==s[6] match, len=7, LPS[16]=7 len=7  <--- 7   │
  │                                                                          │
  │  FINAL LPS: [0 1 0 0 0 1 2 2 0 1 2 3 0 0 0 1 7]                        │
  │                                   last element = 7                       │
  └──────────────────────────────────────────────────────────────────────────┘

  Step 4: Get longest palindromic prefix length
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  lps.back() means: the LAST element of the LPS vector                  │
  │  In C++, vector::back() returns a reference to the last element.        │
  │  lps.back() == lps[lps.size() - 1] == lps[16] == 7                     │
  │                                                                          │
  │  So longestPalPrefix = 7                                                 │
  │                                                                          │
  │  This means: first 7 chars "aacecaa" of S is a palindrome!             │
  │                                                                          │
  │  Verify: a-a-c-e-c-a-a                                                   │
  │            a==a ✓ (pos 0,6)                                              │
  │             a==a ✓ (pos 1,5)                                             │
  │              c==c ✓ (pos 2,4)                                            │
  │               e==e ✓ (pos 3,3)  -> YES, "aacecaa" IS palindrome ✓       │
  └──────────────────────────────────────────────────────────────────────────┘

  Step 5: Extract remaining and build answer
  ┌──────────────────────────────────────────────────────────────────────────┐
  │  longestPalPrefix = 7                                                     │
  │  remaining = S.substr(7) = "a"    (everything after the palindrome)      │
  │  reverse(remaining) = "a"         (only 1 char, reversing doesn't change)│
  │  Answer = "a" + "aacecaaa" = "aaacecaaa"                                │
  │                                                                          │
  │  Verify palindrome: a-a-a-c-e-c-a-a-a                                   │
  │                       a==a ✓ (0,8)                                       │
  │                        a==a ✓ (1,7)                                      │
  │                         a==a ✓ (2,6)                                     │
  │                          c==c ✓ (3,5)  -> YES, palindrome ✓             │
  └──────────────────────────────────────────────────────────────────────────┘

------------------------------------------------------------------------------------------------

VISUAL WALKTHROUGH - Example 2: S = "abcd"
============================================

  Step 1: Reverse S
  ┌──────────────────────────────────────────────────┐
  │  S    = "abcd"                                   │
  │  rev  = "dcba"                                   │
  └──────────────────────────────────────────────────┘

  Step 2: Build combined
  ┌──────────────────────────────────────────────────────────────┐
  │  combined = "abcd#dcba"                                      │
  │                                                              │
  │  Index:    0 1 2 3 4 5 6 7 8                                 │
  │  chars:   [a b c d # d c b a]                                │
  └──────────────────────────────────────────────────────────────┘

  Step 3: Compute LPS array
  ┌──────────────────────────────────────────────────────────────┐
  │  Index:  0  1  2  3  4  5  6  7  8                           │
  │  chars: [a  b  c  d  #  d  c  b  a]                          │
  │  LPS:   [0  0  0  0  0  0  0  0  1]                          │
  │                                                              │
  │  Only at i=8: 'a' matches s[0]='a', LPS[8]=1               │
  │  This means longest palindromic prefix = "a" (length 1)     │
  └──────────────────────────────────────────────────────────────┘

  Step 4: Build answer
  ┌──────────────────────────────────────────────────┐
  │  longestPalPrefix = 1                             │
  │  remaining = S.substr(1) = "bcd"                  │
  │  reverse(remaining) = "dcb"                       │
  │  Answer = "dcb" + "abcd" = "dcbabcd"              │
  │  Check: "dcbabcd" is palindrome?                  │
  │    d==d ✓, c==c ✓, b==b ✓ -> YES ✓                │
  └──────────────────────────────────────────────────┘

------------------------------------------------------------------------------------------------

VISUAL: WHY THE TRICK WORKS - The Complete Picture
====================================================

  Consider any string S with a palindromic prefix of length k:

  S = [P A L I N D R O M E] [R E M A I N I N G]
       └───── length k ─────┘
       This part is already a palindrome

  To make the whole thing a palindrome, we just need to prepend
  reverse(REMAINING):

  Answer = reverse(REMAINING) + [P A L I N D R O M E] [R E M A I N I N G]
           └── added chars ──┘   └──────────── original S ────────────────┘

  The KMP LPS trick finds k automatically:
  ┌──────────────────────────────────────────────────────────────────────┐
  │                                                                      │
  │   S     =  "a a c e c a a a"                                        │
  │   rev(S)=  "a a a c e c a a"                                        │
  │                                                                      │
  │   When we do S + "#" + rev(S), the LPS at the end finds how much    │
  │   of S's beginning matches rev(S)'s beginning.                      │
  │                                                                      │
  │   Since rev(S) is S reversed, if S[0..k-1] matches rev(S)[0..k-1], │
  │   it means S[0..k-1] = reverse(S[0..k-1]) -> it's a palindrome!    │
  │                                                                      │
  │   ┌─────────┐     ┌─────────┐                                       │
  │   │  S[0..k] │     │ rev[0..k]│                                      │
  │   │  a a c   │     │  a a a   │  (at end of rev = start of S)        │
  │   └────┬────┘     └────┬────┘                                       │
  │        │               │                                             │
  │        └───── LPS finds this match ─────┘                           │
  │                                                                      │
  └──────────────────────────────────────────────────────────────────────┘

------------------------------------------------------------------------------------------------

WHY USE '#' SEPARATOR?
-----------------------
  Without '#', consider S = "aaa", rev = "aaa"
  combined = "aaaaaa" -> LPS would find matches that cross the boundary!

  "aaa"+"aaa" = "aaaaaa"
  LPS[5] = 5, meaning it thinks 5 chars match. But we only want matches
  within the real S part.

  With '#': "aaa#aaa"
  LPS[6] = 3, correctly finding only the 3-char palindrome "aaa" ✓

  The '#' acts as a barrier - no character in S or rev(S) equals '#',
  so LPS can never cross it.

------------------------------------------------------------------------------------------------

STEP-BY-STEP ALGORITHM SUMMARY:
--------------------------------
  1. Reverse S to get rev(S)
  2. Build combined = S + "#" + rev(S)
  3. Compute LPS array of combined (KMP preprocessing)
  4. longestPalPrefix = LPS[last index]  (length of longest palindromic prefix)
  5. remaining = S.substr(longestPalPrefix)  (chars after the palindrome)
  6. Prepend reverse(remaining) to S
  7. Return reverse(remaining) + S

------------------------------------------------------------------------------------------------

LPS COMPUTATION EXPLAINED (for those unfamiliar with KMP):
------------------------------------------------------------
  LPS[i] = length of the longest proper prefix of s[0..i]
           that is also a suffix of s[0..i]

  "Proper" means it can't be the whole string itself.

  Example: s = "aabaaac"
  ┌────────────────────────────────────────────────────────────┐
  │  i=0: 'a' -> LPS[0]=0 (no proper prefix)                  │
  │  i=1: 'a' -> s[1]==s[0], LPS[1]=1 ("a" matches "a")      │
  │  i=2: 'b' -> s[2]!=s[1], len=0, LPS[2]=0                 │
  │  i=3: 'a' -> s[3]==s[0], LPS[3]=1                        │
  │  i=4: 'a' -> s[4]==s[1], LPS[4]=2                        │
  │  i=5: 'a' -> s[5]==s[2]='b'? No. len=lps[1]=1           │
  │          s[5]==s[1]='a'? Yes. len=2, LPS[5]=2            │
  │  i=6: 'c' -> s[6]!=s[2]='b', len=lps[1]=1               │
  │          s[6]!=s[1]='a', len=0, LPS[6]=0                 │
  │                                                            │
  │  Final LPS: [0 1 0 1 2 2 0]                               │
  └────────────────────────────────────────────────────────────┘

------------------------------------------------------------------------------------------------

TIME COMPLEXITY:  O(n) where n = len(S)
  - Reversing string: O(n)
  - Building combined: O(n)
  - Computing LPS: O(n)
  - Building result: O(n)

SPACE COMPLEXITY: O(n) for combined string and LPS array

------------------------------------------------------------------------------------------------

EDGE CASES:
-----------
  1. S is already palindrome -> return S (no chars needed)
  2. S is empty -> return ""
  3. S has length 1 -> return S (single char is palindrome)
  4. S has all same chars -> return S (already palindrome)
  5. S has no palindromic prefix longer than 1 -> prepend reverse of S[1:]

================================================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // KMP LPS (Longest Proper Prefix which is also Suffix) array computation
    // lps[i] = length of longest proper prefix of s[0..i] that is also a suffix
    //
    // This is the standard KMP preprocessing function.
    // It builds information about repeated patterns in the string.
    //
    // Example: s = "aabaab"
    //          LPS = [0, 1, 0, 1, 2, 3]
    //          At i=5: "aabaa" -> longest prefix=suffix = "aab" (len 3)
    vector<int> computeLPS(string& s) {
        int n = s.size();

        // lps[i] stores the length of longest proper prefix of s[0..i]
        // that is also a suffix of s[0..i]
        vector<int> lps(n, 0);

        int len = 0;  // length of previous longest prefix-suffix
        int i = 1;    // current position we're computing LPS for

        while (i < n) {

            if (s[i] == s[len]) {
                // Characters match, extend the current prefix-suffix
                len++;
                lps[i] = len;
                i++;
            }
            else {
                // Mismatch - try to fall back to a shorter prefix-suffix
                if (len != 0) {
                    // DON'T increment i here! We might still find a match
                    // at a shorter prefix-suffix length
                    // This is the key optimization of KMP over brute force
                    len = lps[len - 1];
                }
                else {
                    // No prefix-suffix exists, LPS[i] = 0
                    lps[i] = 0;
                    i++;
                }
            }
        }

        return lps;
    }

    string shortestPalindrome(string s) {

        // Step 1: Reverse the input string
        // Example: s = "aacecaaa" -> rev = "aaacecaa"
        string rev = s;
        reverse(rev.begin(), rev.end());

        // Step 2: Build combined string = s + "#" + rev(s)
        //
        // WHY this trick works:
        //   - The '#' separator prevents false matches across s and rev(s)
        //   - If s has a palindromic prefix of length k, then:
        //     s[0..k-1] == reverse(s[0..k-1]) == rev(s)[len-k..len-1]
        //   - In combined string, this means s[0..k-1] matches rev(s)[0..k-1]
        //   - The LPS array at the LAST position captures this match length!
        //
        // Example: s = "aacecaaa"
        //   combined = "aacecaaa#aaacecaa"
        //
        //   The LPS at the final position tells us: the longest prefix of s
        //   that matches a suffix of rev(s) = longest palindromic prefix of s
        string combined = s + "#" + rev;

        // Step 3: Compute LPS array of combined string
        vector<int> lps = computeLPS(combined);

        // Step 4: The LAST value in LPS = length of longest palindromic prefix
        //
        // lps.back() in C++ returns the LAST element of the vector.
        // This is the same as writing: lps[lps.size() - 1]
        //
        // Why last position?
        //   The LPS at position len(combined)-1 tells us the longest prefix
        //   of the ENTIRE combined string that is also a suffix.
        //   This prefix must come from the s part, and the suffix from rev(s).
        //   So it's exactly the length of the longest palindromic prefix of s.
        //
        // Example: s = "aacecaaa", combined = "aacecaaa#aaacecaa"
        //   LPS array = [0,1,0,0,0,1,2,2,0,1,2,3,0,0,0,1,7]
        //                                last element = 7
        //   lps.back() == lps[16] == 7
        //   meaning "aacecaa" (first 7 chars) is palindromic ✓
        int longestPalPrefix = lps.back();

        // Step 5: Extract characters AFTER the palindromic prefix
        //
        // These are the characters that need to be "fixed" by prepending
        // their reverse.
        //
        // Example: s = "aacecaaa", longestPalPrefix = 7
        //   remaining = s.substr(7) = "a"
        //   We need to prepend reverse("a") = "a"
        string remaining = s.substr(longestPalPrefix);

        // Step 6: Reverse the remaining part
        // We prepend the REVERSE of remaining to make the whole thing palindrome
        //
        // Example: remaining = "a" -> reversed = "a"
        //          Answer = "a" + "aacecaaa" = "aaacecaaa" ✓
        reverse(remaining.begin(), remaining.end());

        // Step 7: Return the shortest palindrome
        // Prepend the reversed remaining to the original string
        return remaining + s;
    }
};


int main(){
    Solution sol;

    // Test 1: s = "aacecaaa"
    // Longest palindromic prefix = "aacecaa" (length 7)
    // Remaining = "a", reverse = "a"
    // Answer = "a" + "aacecaaa" = "aaacecaaa"
    cout << sol.shortestPalindrome("aacecaaa") << endl;

    // Test 2: s = "abcd"
    // Longest palindromic prefix = "a" (length 1)
    // Remaining = "bcd", reverse = "dcb"
    // Answer = "dcb" + "abcd" = "dcbabcd"
    cout << sol.shortestPalindrome("abcd") << endl;

    return 0;
}