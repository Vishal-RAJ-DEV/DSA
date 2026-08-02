#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/* ====================================================================================
   MAXIMUM NUMBER OF NON-OVERLAPPING SUBSTRINGS  (LeetCode 1520)
   ====================================================================================

   PROBLEM
   -------
   Given a string s, find the MAXIMUM number of NON-OVERLAPPING substrings such that
   for EVERY character c present inside a substring, ALL occurrences of c in the whole
   string must also lie inside that same substring.
   (No character may "leak out" of its own substring.)

   ====================================================================================
   CORE INTUITION (remember this!)
   ====================================================================================
   1) Whenever you include a character in a substring, you are COMMITTING to include
      EVERY occurrence of that character. This may force the substring to EXPAND to
      the right (up to that character's LAST occurrence).
   2) While expanding, you may ENCOUNTER NEW characters, which in turn force FURTHER
      expansion (their last occurrence may be even further right). So we repeatedly
      push the interval's right end outward:  end = max(end, last[newChar]).
   3) If during expansion you discover a character whose FIRST occurrence lies BEFORE
      your chosen start i, then this interval can NEVER be valid → discard it.
      (A substring starting at i must contain all occurrences of s[i]; a character
       that appeared before i can never be pulled inside, so NO valid substring can
       ever start at i.)
   4) After constructing all minimal valid intervals, the problem reduces to:
      "Select the maximum number of NON-OVERLAPPING intervals" → the classic GREEDY
      INTERVAL SCHEDULING strategy (always prefer the interval that ends earliest).

   => This seemingly complex string problem is actually a combination of
      INTERVAL CONSTRUCTION  +  INTERVAL SCHEDULING.

   ====================================================================================
   WORKED EXAMPLE  s = "adefaddaccc"
   ====================================================================================

   index :  0   1   2   3   4   5   6   7   8   9   10
   char  :  a   d   e   f   a   d   d   a   c   c   c
            |________________________|        |_______|
              first[a]=0, last[a]=7            first[c]=8, last[c]=10

   first[] : a=0, c=8, d=1, e=2, f=3        (first occurrence of each letter)
   last[]  : a=7, c=10, d=6, e=2, f=3       (last  occurrence of each letter)

   ---- STEP A : build intervals, only starting at a char's FIRST occurrence ----

   i=0 (char 'a', first=0):  start [0, last[a]=7]
     expand j=0..7 : a d e f a d d a  → all first[] ≥ 0  → VALID  [0,7] = "adefadda"
     no overlap yet → PUSH "adefadda",  prevEnd = 7

   i=1 (char 'd', first=1):  start [1, last[d]=6]
     expand j=1..6 : at j=4 we hit 'a' whose first[a]=0 < 1 → NEVER valid → DISCARD

   i=2 (char 'e', first=2):  start [2, last[e]=2]  → VALID  [2,2] = "e"
     overlaps prev (2 ≤ 7) → REPLACE "adefadda" with "e" (ends earlier → better)
     prevEnd = 2

   i=3 (char 'f', first=3):  start [3, last[f]=3]  → VALID  [3,3] = "f"
     i=3 > prevEnd=2 → PUSH "f",  prevEnd = 3

   i=8 (char 'c', first=8):  start [8, last[c]=10]
     expand j=8..10 : all 'c'  → VALID  [8,10] = "ccc"
     i=8 > prevEnd=3 → PUSH "ccc",  prevEnd = 10

   ANSWER : ["e", "f", "ccc"]   →  maximum count = 3   ✔
   (verify: 'e' only at 2, 'f' only at 3, 'c' only at 8..10 — nothing leaks, none overlap)

   ---- WHY THE REPLACE-STEP IS SAFE (greedy correctness) ----
   Intervals are processed in increasing START order. If a new valid interval [i,end]
   has i ≤ prevEnd, then position i lies INSIDE the previously chosen interval, which
   (by its own validity) already contains ALL occurrences of s[i], so
   end = last[s[i]] ≤ prevEnd, and every expansion keeps end ≤ prevEnd. Hence the new
   interval starts later AND ends earlier → strictly better. Replacing keeps the count
   the same while leaving MORE room for future intervals → never hurts optimality.

   TIME  : O(26 * n) ≈ O(n)    (only first-occurrence positions can start an interval,
                                at most 26 starts, each scanned over ≤ n positions)
   SPACE : O(n) for the answer arrays (first/last are O(26))
   ==================================================================================== */

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        /* first[i] = index of FIRST occurrence of character i  (n if never present)
           last[i]  = index of LAST  occurrence of character i  (-1 if never present) */
        vector<int> first(26, n), last(26, -1);

        // Single pass over the string to record both arrays.
        // NOTE: first[x] is updated with min() only at the very first sighting,
        //       last[x] is overwritten every time, so it ends at the final sighting.
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<string> ans;    // stores the chosen non-overlapping substrings
        int prevEnd = -1;      // right boundary of the most recently chosen interval

        /* ---- STEP A : INTERVAL CONSTRUCTION ----
           Try to build a valid interval starting from EVERY character's FIRST
           occurrence only. If i is not the first occurrence of s[i], then the
           substring "starting at i" would still have to contain ALL occurrences
           of s[i], which include first[s[i]] < i → impossible → skip. */
        for (int i = 0; i < n; i++) {

            if (i != first[s[i] - 'a'])
                continue;                     // only first occurrences may start an interval

            /* Minimum interval: from i up to the LAST occurrence of s[i]
               (committing to s[i] forces us to cover all of its occurrences). */
            int end = last[s[i] - 'a'];
            bool valid = true;

            /* ---- EXPANSION ----
               Walk from i to end. Every new character met inside must have its
               FIRST occurrence ≥ i (else interval can never be valid), and it may
               force us to push `end` further right to cover its LAST occurrence. */
            for (int j = i; j <= end; j++) {

                int ch = s[j] - 'a';

                // If this character started before our interval, it can never be
                // brought inside → this interval is invalid, discard it.
                if (first[ch] < i) {
                    valid = false;
                    break;
                }

                // Commit to all occurrences of this new character:
                // extend the right boundary if its last occurrence is further out.
                end = max(end, last[ch]);
            }

            if (!valid)
                continue;                     // this start i can never form a substring

            /* ---- STEP B : GREEDY INTERVAL SCHEDULING ----
               Intervals are discovered in increasing START order (i increases).
               - If this interval starts AFTER the previous chosen one ended
                 (i > prevEnd) → no overlap → safely PUSH it.
               - Else it overlaps the previous interval. By the proof above its
                 end ≤ prevEnd, so it is strictly better (later start, earlier end);
                 REPLACE the previous answer to leave maximum room for future picks. */
            if (i > prevEnd) {
                ans.push_back(s.substr(i, end - i + 1));
            }
            else {
                // Current interval ends earlier → replace previous one with it.
                ans.back() = s.substr(i, end - i + 1);
            }

            prevEnd = end;                    // update right boundary for future checks
        }

        return ans;
    }
};



int main(){
    return 0;
}