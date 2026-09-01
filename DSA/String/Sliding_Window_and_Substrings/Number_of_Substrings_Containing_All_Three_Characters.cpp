#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
 PROBLEM: Number of Substrings Containing All Three Characters
================================================================================
 Given a string `s` consisting only of characters 'a', 'b', and 'c',
 return the number of substrings that contain at least one occurrence
 of all three characters 'a', 'b', and 'c'.

 Example 1:
   s = "abcabc"
   Output = 10
   Explanation:
     Valid substrings: "abc", "abca", "abcab", "abcabc",
                       "bca", "bcab", "bcabc",
                       "cab", "cabc",
                       "abc" (last 3 chars)
     Total = 10

 Example 2:
   s = "aaacb"
   Output = 3
   Explanation:
     Valid substrings: "aaacb", "aacb", "acb"
     Total = 3

 Example 3:
   s = "abc"
   Output = 1
   Explanation:
     Only "abc" itself is valid.

================================================================================
 INTUITION / APPROACH: SLIDING WINDOW
================================================================================

 KEY IDEA:
   Instead of checking every substring (O(n^2) or O(n^3) brute force),
   we use a SLIDING WINDOW that expands and contracts to find valid
   windows efficiently in O(n) time.

 HOW IT WORKS:
   We maintain a window [left..right] and track how many of the 3
   required characters ('a','b','c') are present in the window
   using `satisfies` counter (0, 1, 2, or 3).

   EXPAND (right++):
     - Add character at `right` to the window.
     - If this character was NOT in the window before (count was 0),
       increment `satisfies`.

   CONTRACT (while satisfies == 3):
     - When the window has all 3 characters, it's VALID.
     - KEY INSIGHT: If [left..right] is valid, then ALL substrings
       starting from any index in [left..right] and ending at `right`
       or beyond are ALSO valid.
     - So we add (n - right) to our answer. This counts:
       - substring [left..right]
       - substring [left..right+1]
       - ...
       - substring [left..n-1]
       That's (n - right) substrings in total.
     - Then we shrink from the left: move left forward, decrease
       frequency of the character leaving the window. If its count
       becomes 0, decrement `satisfies`.
     - Keep shrinking while window is still valid.

 WHY (n - right)?
   Once [left..right] contains all 3 chars, extending the RIGHT
   boundary further (to right+1, right+2, ..., n-1) still keeps
   all 3 chars. So there are (n - right) valid substrings starting
   from `left` and ending at right, right+1, ..., n-1.

   Then we move `left` forward to find the next valid window.

 TIME COMPLEXITY:  O(n) - each character is visited at most twice
                      (once by right, once by left)
 SPACE COMPLEXITY: O(1) - fixed-size map of 3 characters

================================================================================
*/

class Solution {
public:
    int numberOfSubstrings(string s) {

        // ---------------------------------------------------------------
        // n = length of the string
        // ---------------------------------------------------------------
        int n = s.size();

        // ---------------------------------------------------------------
        // left = left boundary of our sliding window
        // right = right boundary of our sliding window
        // Window is the substring s[left..right]
        // ---------------------------------------------------------------
        int left = 0;
        int right = 0;

        // ---------------------------------------------------------------
        // maxLen = our answer. Despite the name, it actually stores the
        // COUNT of valid substrings (not the maximum length). The name
        // is a bit misleading, but it accumulates the total count.
        // ---------------------------------------------------------------
        int maxLen = 0;

        // ---------------------------------------------------------------
        // mpp = hash map (frequency array) to count occurrences of each
        // character ('a', 'b', 'c') in the current window [left..right].
        // Indexed by (character - 'a'), so:
        //   mpp[0] = count of 'a' in window
        //   mpp[1] = count of 'b' in window
        //   mpp[2] = count of 'c' in window
        // ---------------------------------------------------------------
        unordered_map<int, int> mpp;

        // ---------------------------------------------------------------
        // satisfies = how many of the 3 required characters ('a','b','c')
        // are PRESENT (count > 0) in the current window.
        //   0 = none of a,b,c present
        //   1 = one of them present
        //   2 = two of them present
        //   3 = ALL three present (window is VALID)
        // ---------------------------------------------------------------
        int satisfies = 0;

        // ---------------------------------------------------------------
        // MAIN LOOP: Expand the window by moving `right` forward.
        // ---------------------------------------------------------------
        while (right < n) {

            // ===========================================================
            // STEP 1: ADD the character at `right` to the window.
            // ===========================================================

            // -----------------------------------------------------------
            // Before adding, check if this character is NEW to the window
            // (its count is currently 0). If so, we're now satisfying
            // one more required character.
            //
            // Example: window currently has {'a':2, 'b':1}, satisfies=2
            //          adding 'c' (which has count 0) -> satisfies becomes 3
            // -----------------------------------------------------------
            if (mpp[s[right] - 'a'] == 0) {
                satisfies++;
            }

            // -----------------------------------------------------------
            // Increment the frequency of this character in the window.
            // This officially "adds" it to our sliding window.
            // -----------------------------------------------------------
            mpp[s[right] - 'a']++;

            // ===========================================================
            // STEP 2: If window is VALID (has all 3 chars), COUNT and
            //         SHRINK from the left.
            // ===========================================================

            // -----------------------------------------------------------
            // While the window [left..right] contains all 3 characters,
            // it's a valid window. We count all substrings that start
            // at `left` and end at `right` or beyond, then shrink.
            // -----------------------------------------------------------
            while (satisfies == 3) {

                // ------------------------------------------------------
                // COUNTING STEP:
                // If [left..right] is valid, then ALL of these are valid:
                //   s[left..right]
                //   s[left..right+1]
                //   s[left..right+2]
                //   ...
                //   s[left..n-1]
                //
                // That's exactly (n - right) substrings.
                //
                // Example: s = "abcabc", n=6
                //   Window [0..2] = "abc" (valid)
                //   Valid substrings starting at index 0:
                //     "abc"   (ends at 2)
                //     "abca"  (ends at 3)
                //     "abcab" (ends at 4)
                //     "abcabc"(ends at 5)
                //   Count = 6 - 2 = 4
                //
                //   We add 4 to maxLen.
                // ------------------------------------------------------
                maxLen += (n - right);

                // ------------------------------------------------------
                // SHRINK from the left:
                // Remove s[left] from the window by decreasing its count.
                // ------------------------------------------------------
                mpp[s[left] - 'a']--;

                // ------------------------------------------------------
                // If after removal, the count of this character becomes 0,
                // it's no longer in the window. So we lose one satisfied
                // character. Decrement `satisfies`.
                //
                // Example: window "abca" -> removing 'a' -> "bca"
                //   'a' count goes from 2 to 1 -> still present -> no change
                //
                // Example: window "abc" -> removing 'a' -> "bc"
                //   'a' count goes from 1 to 0 -> 'a' gone -> satisfies 3->2
                // ------------------------------------------------------
                if (mpp[s[left] - 'a'] == 0) {
                    satisfies--;
                }

                // ------------------------------------------------------
                // Move left pointer forward (shrink the window).
                // ------------------------------------------------------
                left++;
            }

            // ===========================================================
            // STEP 3: Move right forward to expand the window.
            // ===========================================================
            right++;
        }

        // ---------------------------------------------------------------
        // Return the total count of valid substrings.
        // ---------------------------------------------------------------
        return maxLen;
    }
};

/*
================================================================================
 DRY RUN / TRACE TABLE
================================================================================

 Example 1: s = "abcabc", n = 6
 -----------------------------------------------

 Initial: left=0, right=0, satisfies=0, maxLen=0, mpp={}

 STEP 1: right=0, s[0]='a'
   mpp['a']=0? YES -> satisfies=1
   mpp['a'] = 1
   satisfies=1 (not 3), skip while loop
   right++ -> right=1
   Window: [0..0] = "a", satisfies=1

 STEP 2: right=1, s[1]='b'
   mpp['b']=0? YES -> satisfies=2
   mpp['b'] = 1
   satisfies=2 (not 3), skip while loop
   right++ -> right=2
   Window: [0..1] = "ab", satisfies=2

 STEP 3: right=2, s[2]='c'
   mpp['c']=0? YES -> satisfies=3
   mpp['c'] = 1
   satisfies=3 == 3, ENTER while loop:

     --- Iteration A: left=0 ---
     maxLen += (6-2) = 4     -> maxLen = 4
     mpp[s[0]] = mpp['a']-- -> mpp['a'] = 0
     mpp['a']==0? YES -> satisfies=2
     left++ -> left=1
     satisfies=2 (not 3), EXIT while loop

   right++ -> right=3
   Window: [1..2] = "bc", satisfies=2

 STEP 4: right=3, s[3]='a'
   mpp['a']=0? YES -> satisfies=3
   mpp['a'] = 1
   satisfies=3 == 3, ENTER while loop:

     --- Iteration A: left=1 ---
     maxLen += (6-3) = 3     -> maxLen = 7
     mpp[s[1]] = mpp['b']-- -> mpp['b'] = 0
     mpp['b']==0? YES -> satisfies=2
     left++ -> left=2
     satisfies=2 (not 3), EXIT while loop

   right++ -> right=4
   Window: [2..3] = "ca", satisfies=2

 STEP 5: right=4, s[4]='b'
   mpp['b']=0? YES -> satisfies=3
   mpp['b'] = 1
   satisfies=3 == 3, ENTER while loop:

     --- Iteration A: left=2 ---
     maxLen += (6-4) = 2     -> maxLen = 9
     mpp[s[2]] = mpp['c']-- -> mpp['c'] = 0
     mpp['c']==0? YES -> satisfies=2
     left++ -> left=3
     satisfies=2 (not 3), EXIT while loop

   right++ -> right=5
   Window: [3..4] = "ab", satisfies=2

 STEP 6: right=5, s[5]='c'
   mpp['c']=0? YES -> satisfies=3
   mpp['c'] = 1
   satisfies=3 == 3, ENTER while loop:

     --- Iteration A: left=3 ---
     maxLen += (6-5) = 1     -> maxLen = 10
     mpp[s[3]] = mpp['a']-- -> mpp['a'] = 0
     mpp['a']==0? YES -> satisfies=2
     left++ -> left=4
     satisfies=2 (not 3), EXIT while loop

   right++ -> right=6
   Window: [4..5] = "bc", satisfies=2

 right=6 >= n=6, LOOP ENDS.

 Final Answer: maxLen = 10 ✓

 -----------------------------------------------

 Example 2: s = "aaacb", n = 5
 -----------------------------------------------

 Initial: left=0, right=0, satisfies=0, maxLen=0

 right=0, 'a': satisfies=1, mpp={a:1}
 right=1, 'a': mpp['a']=1(not 0), mpp={a:2}, satisfies=1
 right=2, 'a': mpp['a']=2(not 0), mpp={a:3}, satisfies=1
 right=3, 'c': mpp['c']=0? YES, satisfies=2, mpp={a:3,c:1}
 right=4, 'b': mpp['b']=0? YES, satisfies=3, mpp={a:3,c:1,b:1}

   satisfies=3, ENTER while:

     left=0: maxLen += (5-4) = 1 -> maxLen = 1
             mpp['a']-- -> {a:2,c:1,b:1}, 'a' still >0, satisfies stays 3
     left=1: maxLen += (5-4) = 1 -> maxLen = 2
             mpp['a']-- -> {a:1,c:1,b:1}, 'a' still >0, satisfies stays 3
     left=2: maxLen += (5-4) = 1 -> maxLen = 3
             mpp['a']-- -> {a:0,c:1,b:1}, 'a'=0, satisfies=2
             EXIT while

 Final Answer: maxLen = 3 ✓

================================================================================
*/

int main(){
    return 0;
}
