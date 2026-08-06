#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ============================================================================
   PROBLEM : Lexicographically Smallest Palindrome

   You are given a string s. You may change ANY character to any other
   character. Return the LEXICOGRAPHICALLY SMALLEST palindrome string that can
   be obtained by changing the MINIMUM number of characters.

   KEY LOGIC:
   - A palindrome needs  s[i] == s[n-1-i]  for every symmetric pair.
   - For a mismatched pair, we MUST change at least one side to make them
     equal. One change per pair is the minimum possible.
   - To make the result lexicographically smallest, we always replace the
     LARGER character with the SMALLER one (i.e. both become min(a, b)).
     Replacing the smaller char with the larger one would give a
     lexicographically BIGGER result, which we must avoid.

   Example:  s = "egcfe"
     pair (e, e) -> same, no change
     pair (g, f) -> g > f, so change g to f  ->  "efcfe"
     middle c    -> unchanged
   Result: "efcfe"  (a palindrome, and the smallest possible)

   Complexity (both versions): O(n) time, O(1) extra space.
   ============================================================================ */


/* ============================================================================
   VERSION 1 : TWO-POINTER  (converted from the original Java code)

   Uses two pointers moving towards the centre and fixes one pair at a time.
   This is the direct C++ translation of the Java logic.
   ============================================================================ */
class Solution1 {
public:
    string makeSmallestPalindrome(string s) {
        int n = s.size();

        int left = 0;
        int right = n - 1;

        // Move pointers towards each other until they meet in the middle
        while (left < right) {
            // If the symmetric characters differ, fix the pair
            if (s[left] != s[right]) {
                // Keep the SMALLER character on both sides:
                // replace the larger one with the smaller one
                s[left] = s[right] = min(s[left], s[right]);
            }

            // Move inward to the next pair
            left++;
            right--;
        }

        // The string is now a palindrome and lexicographically smallest
        return s;
    }
};


/* ============================================================================
   VERSION 2 : SINGLE-LOOP (compact one-liner per pair)

   Iterates i over the WHOLE string instead of just half.

   WHY DOES THIS STILL WORK?
   - For i in the first half [0, n/2), each symmetric pair is fixed once.
   - For i in the second half (n/2, n), the same pair is visited AGAIN, but
     now both characters are already equal, so min(a, a) = a -> no change.
     The assignment is idempotent, so re-processing a pair is harmless.
   - It only does redundant work, never wrong work.
   - Middle character (odd length): maps to itself, min(x, x) = x -> no change.

   So it is correct, just runs ~2x iterations compared to Version 1.
   ============================================================================ */
class Solution2 {
public:
    string makeSmallestPalindrome(string s) {
        int n = s.size();

        // Loop over every index (first half does the real work)
        for (int i = 0; i < n; i++) {
            // Set BOTH sides of the symmetric pair to the smaller character
            s[i] = s[n - 1 - i] = min(s[i], s[n - 1 - i]);
        }

        return s;
    }
};


int main(){
    return 0;
}
