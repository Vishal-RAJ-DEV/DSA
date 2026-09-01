#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
 PROBLEM: Swap One Character to Get Longest Repeated Character Substring
================================================================================
 Given a string `text`, you can swap at most ONE character with any other
 character in the string. Return the length of the longest substring
 containing only one repeated character you can achieve.

 Example:
   text = "ababa"
   Answer = 4  (swap 'b' at index 1 with 'a' -> "aaaba" -> "aaaa" length 4)
                                  OR swap 'b' at index 3 with 'a'

 Example:
   text = "aaabaaa"
   Answer = 6  (swap 'b' with 'a' -> "aaaaaaa" -> "aaaaaa" length 6)

================================================================================
 INTUITION / APPROACH
================================================================================
 KEY IDEA: We use GROUP-CONSECUTIVE-CHARACTERS approach.

 Instead of checking every possible swap (O(n^2) brute force), we:
   1. Group the string into blocks of consecutive identical characters.
      e.g., "aaabbaaa" -> groups: [(a,3), (b,2), (a,3)]

   2. For each group of character `ch` with length `len1`, we consider TWO cases:

      CASE 1: Extend the current group by bringing ONE more `ch` from elsewhere.
      ---------------------------------------------------------------
      - After grouping, if there are still `ch` characters left in the string
        (not part of this group), we can swap one of those into position
        right next to this group, extending it by 1.
      - BUT the total length cannot exceed the total count of `ch` in the string.
      - Result: min(len1 + 1, total[ch])

      CASE 2: Merge two groups of `ch` separated by exactly ONE different char.
      -----------------------------------------------------------------
      - If the pattern is: [group of ch] [ONE different char] [group of ch]
        e.g., "aaa b aaa" (two groups of 'a' separated by single 'b')
      - We can SWAP that single different character with a `ch` from elsewhere
        (or from the second group), effectively joining the two groups.
      - The merged length = len1 + len2 + 1 (the +1 is the swapped position)
      - BUT total length cannot exceed total count of `ch`.
      - Result: min(len1 + len2 + 1, total[ch])

   3. We take the maximum answer across all groups and both cases.

 WHY THIS WORKS:
   - We never need to swap more than once, so we only look for at most
     ONE gap (one different character) between two groups.
   - The `min()` with `total[ch]` ensures we don't claim more characters
     than actually exist in the string.
   - By processing consecutive groups, we cover every possible location
     where a long repeated substring could be formed.

 TIME COMPLEXITY:  O(n) - single pass to group characters
 SPACE COMPLEXITY: O(1) - only a fixed-size array of 26 integers

================================================================================
*/

class Solution {
public:
    int maxRepOpt1(string text) {

        // ---------------------------------------------------------------
        // n = length of the input string
        // ---------------------------------------------------------------
        int n = text.size();

        // ---------------------------------------------------------------
        // total[26] stores the total count of each character ('a' to 'z')
        // in the entire string. This is needed to know how many of a
        // character are available to "bring in" via a swap.
        // ---------------------------------------------------------------
        int total[26] = {0};

        // ---------------------------------------------------------------
        // Count total occurrences of every character in the string.
        // For "aaabaaa", total['a'-'a'] = 6, total['b'-'a'] = 1
        // ---------------------------------------------------------------
        for (char c : text) {
            total[c - 'a']++;
        }

        // ---------------------------------------------------------------
        // ans = our answer, tracks the maximum length found so far.
        // ---------------------------------------------------------------
        int ans = 0;

        // ---------------------------------------------------------------
        // MAIN LOOP: Process consecutive groups of identical characters.
        // We iterate through the string, but instead of moving one char
        // at a time, we JUMP over entire groups (groups of same char).
        //
        // Example walkthrough for "aaabbaaa":
        //   i=0: group = "aaa" (len=3), then jump i to 3
        //   i=3: group = "bb"  (len=2), then jump i to 5
        //   i=5: group = "aaa" (len=3), then jump i to 8
        // ---------------------------------------------------------------
        for (int i = 0; i < n; ) {

            // -----------------------------------------------------------
            // j starts at i, and we advance j until we find a different
            // character. This identifies the current group [i, j).
            // After the while loop, text[i..j-1] are all the same char.
            // -----------------------------------------------------------
            int j = i;

            // -----------------------------------------------------------
            // Expand j while the characters keep matching text[i].
            // This finds the boundary of the current consecutive group.
            // -----------------------------------------------------------
            while (j < n && text[j] == text[i]) {
                j++;
            }

            // -----------------------------------------------------------
            // len1 = length of the current consecutive group.
            // e.g., if text[i..j-1] = "aaa", then len1 = 3
            // -----------------------------------------------------------
            int len1 = j - i;

            // -----------------------------------------------------------
            // idx = numeric index (0-25) of the current group's character.
            // e.g., 'a' -> 0, 'b' -> 1, etc.
            // -----------------------------------------------------------
            int idx = text[i] - 'a';

            // ===========================================================
            // CASE 1: Bring ONE same character from outside this group.
            // ===========================================================
            // We have a group of length `len1`. If there are more of this
            // character elsewhere in the string, we can swap one in right
            // next to this group, making it `len1 + 1`.
            //
            // HOWEVER, we can never have more than `total[idx]` of this
            // character in any substring, so we cap it with min().
            //
            // Example: "aaab" -> group "aaa" (len1=3), total['a']=3
            //   min(3+1, 3) = 3  (can't get 4 a's since only 3 exist)
            //
            // Example: "aaabb" -> group "aaa" (len1=3), total['a']=3
            //   min(3+1, 3) = 3  (same reasoning)
            //
            // Example: "baaab" -> group "aaa" (len1=3), total['a']=3
            //   min(3+1, 3) = 3
            //
            // Example: "aaabaa" -> group "aaa" (len1=3), total['a']=5
            //   min(3+1, 5) = 4  (swap one 'a' from the second group)
            // ===========================================================
            ans = max(ans, min(len1 + 1, total[idx]));

            // ===========================================================
            // CASE 2: Merge two groups of same char separated by ONE diff.
            // ===========================================================
            // After the current group ends at index j, we check:
            //   - Is there a SINGLE different character at position j?
            //   - Is there another group of the SAME character right after
            //     that single different character (at position j+1)?
            //
            // If yes, we have the pattern: [ch group][1 diff char][ch group]
            // We can SWAP that single different character with a `ch` from
            // somewhere else, effectively joining the two groups.
            //
            // Example: "aaabaaa"
            //   First group: "aaa" (len1=3), index j=3
            //   text[j] = 'b' (single different char)
            //   text[j+1] = 'a' (start of second group)
            //   Second group: "aaa" (len2=3)
            //   Merged = min(3 + 3 + 1, total['a']) = min(7, 6) = 6
            //
            // The "+1" accounts for the position that gets swapped.
            // We scan the second group with pointer k.
            // ===========================================================
            if (j + 1 < n && text[j + 1] == text[i]) {

                // -------------------------------------------------------
                // k starts at the beginning of the second group.
                // We scan forward to find how long this second group is.
                // -------------------------------------------------------
                int k = j + 1;

                // -------------------------------------------------------
                // Expand k while characters match text[i] (same char).
                // This identifies the second group's boundary.
                // -------------------------------------------------------
                while (k < n && text[k] == text[i]) {
                    k++;
                }

                // -------------------------------------------------------
                // len2 = length of the second group.
                // e.g., second "aaa" -> len2 = 3
                // -------------------------------------------------------
                int len2 = k - (j + 1);

                // -------------------------------------------------------
                // Merge both groups + 1 position for the swap.
                // Cap with total count of this character.
                //
                // Why +1? Because the single different character at position
                // j gets swapped with a same character, so it becomes part
                // of the merged group too.
                //
                // Why min with total[idx]?
                // We cannot have more consecutive chars than what exists
                // in the entire string.
                // -------------------------------------------------------
                ans = max(ans, min(len1 + len2 + 1, total[idx]));
            }

            // -----------------------------------------------------------
            // Move i to j (start of next group). We skip the entire
            // current group and process the next one in the outer loop.
            // -----------------------------------------------------------
            i = j;
        }

        // ---------------------------------------------------------------
        // Return the maximum length achievable.
        // ---------------------------------------------------------------
        return ans;
    }
};

/*
================================================================================
 DRY RUN / TRACE TABLE
================================================================================

 Example 1: text = "aaabaaa"
 -----------------------------------------------

 total['a'] = 6, total['b'] = 1

 Processing:

  i=0, j expands: text[0]='a', text[1]='a', text[2]='a', text[3]='b'(stop)
  Group 1: len1=3, idx='a'=0

    CASE 1: min(3+1, 6) = 4    -> ans = 4
    CASE 2: j+1=4, text[4]='a'==text[0]? YES
            k=4, expand: text[4]='a', text[5]='a', text[6]='a'(stop)
            len2 = 7 - 4 = 3
            min(3+3+1, 6) = min(7, 6) = 6  -> ans = 6

  i=3, j expands: text[3]='b', text[4]='a'(stop)
  Group 2: len1=1, idx='b'=1

    CASE 1: min(1+1, 1) = 1    -> ans = 6 (no change)
    CASE 2: j+1=5, text[5]='a'=='b'? NO

  i=4, j expands: text[4]='a', text[5]='a', text[6]='a'(stop, j=7)
  Group 3: len1=3, idx='a'=0

    CASE 1: min(3+1, 6) = 4    -> ans = 6 (no change)
    CASE 2: j+1=8 >= n, so NO

  i=7 >= n, loop ends.

  Final Answer: 6

  Visual: "aaabaaa" -> swap 'b' with 'a' -> "aaaaaaa" -> longest = 6 ✓

 -----------------------------------------------

 Example 2: text = "ababa"
 -----------------------------------------------

 total['a'] = 3, total['b'] = 2

 Processing:

  i=0, j=1 (group "a")
  Group 1: len1=1, idx='a'=0

    CASE 1: min(1+1, 3) = 2    -> ans = 2
    CASE 2: j+1=2, text[2]='a'=='a'? YES
            k=2, expand: text[2]='a', text[3]='b'(stop)
            len2 = 3 - 2 = 1
            min(1+1+1, 3) = 3  -> ans = 3

  i=1, j=2 (group "b")
  Group 2: len1=1, idx='b'=1

    CASE 1: min(1+1, 2) = 2    -> ans = 3 (no change)
    CASE 2: j+1=3, text[3]='b'=='b'? YES
            k=3, expand: text[3]='b', text[4]='a'(stop)
            len2 = 4 - 3 = 1
            min(1+1+1, 2) = 2  -> ans = 3 (no change)

  i=2, j=3 (group "a")
  Group 3: len1=1, idx='a'=0

    CASE 1: min(1+1, 3) = 2    -> ans = 3 (no change)
    CASE 2: j+1=4, text[4]='a'=='a'? YES
            k=4, expand: text[4]='a'(stop, k=5)
            len2 = 5 - 4 = 1
            min(1+1+1, 3) = 3  -> ans = 3 (no change)

  i=3, j=4 (group "b")
  Group 4: len1=1, idx='b'=1

    CASE 1: min(1+1, 2) = 2    -> ans = 3 (no change)
    CASE 2: j+1=5 >= n, NO

  i=4, j=5 (group "a")
  Group 5: len1=1, idx='a'=0

    CASE 1: min(1+1, 3) = 2    -> ans = 3 (no change)
    CASE 2: j+1=6 >= n, NO

  Final Answer: 3

  Visual: "ababa" -> swap index 1('b') with index 0('a')
                     -> "aabaa" -> "aaa" length 3 ✓

================================================================================
*/

int main(){
    return 0;
}
