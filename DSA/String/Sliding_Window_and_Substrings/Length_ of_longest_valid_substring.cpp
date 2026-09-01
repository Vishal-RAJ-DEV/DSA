#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
 PROBLEM: Length of the Longest Valid Substring
================================================================================
 You are given a string `word` and an array of strings `forbidden`.
 A valid substring is a substring that:
   - Does NOT contain any string from `forbidden` as a substring.
   - (Typically) has length >= 2.

 Return the length of the longest valid substring.

 Example 1:
   word = "cbaaaabc", forbidden = ["aaa","cb"]
   Output = 4
   Explanation: Longest valid substring = "baaa" (length 4)

 Example 2:
   word = "cbezbbb", forbidden = ["bzb","baz"]
   Output = 4
   Explanation: Longest valid substring = "eabb" (length 4)

================================================================================
 KEY CONSTRAINT
================================================================================
 Every forbidden string has length AT MOST 10.

 This is the critical observation that makes the solution efficient.
 Since forbidden strings are short (max 10 chars), when we are at
 position `right` in the string, we only need to look BACK at most
 9 characters to check if any forbidden substring ENDS at `right`.

================================================================================
 INTUITION / APPROACH: SLIDING WINDOW + BACKWARD CHECK
================================================================================

 We use a sliding window [left..right]. For each `right`:

 1. We need to check: does any substring ending at `right` violate
    the forbidden list? If yes, we must move `left` past it.

 2. Since forbidden strings have max length 10, we only need to check
    substrings of length 1 to 10 that END at position `right`.

 3. We scan BACKWARD from `right` for at most 9 characters (covering
    substrings of length 1 to 10 ending at `right`).

 4. If we find a forbidden substring that starts at position `i` and
    ends at `right`, then the new left boundary must be `i + 1`
    (we must exclude position `i` from our valid window).

 5. After processing all backward checks, update the answer with
    the current window size: `right - left + 1`.

 WHY SCAN BACKWARD (not forward)?
   - Because the window grows to the RIGHT. When we add a new character
     at `right`, the only NEW forbidden substrings that could appear
     are those that END at `right`.
   - We don't need to check substrings ending at `right-1` because
     those were already handled in the previous iteration.

 WHY ONLY 9 STEPS BACK?
   - Forbidden strings have max length 10.
   - A forbidden substring ending at `right` can start at earliest
     `right - 9` (for a length-10 forbidden string).
   - So we only check positions `right, right-1, ..., right-9`.

 TIME COMPLEXITY:  O(n * 10) = O(n) - for each position, we do at most
                     10 backward checks, each building a string of max
                     length 10. So effectively O(n).
 SPACE COMPLEXITY: O(f) where f = total characters in forbidden strings
                     (for the hash set)

================================================================================
*/

class Solution {
public:
    int longestValidSubstring(string word, vector<string>& forbidden) {

        // ---------------------------------------------------------------
        // Step 1: Store all forbidden strings in a hash set for O(1)
        // lookup. We need to quickly check if a substring is forbidden.
        // ---------------------------------------------------------------
        unordered_set<string> bad(forbidden.begin(), forbidden.end());

        // ---------------------------------------------------------------
        // n = length of the input string `word`.
        // ---------------------------------------------------------------
        int n = word.size();

        // ---------------------------------------------------------------
        // left = left boundary of our sliding window [left..right].
        // The window [left..right] represents the current valid substring.
        // If a forbidden substring is found, we move `left` past it.
        // ---------------------------------------------------------------
        int left = 0;

        // ---------------------------------------------------------------
        // ans = length of the longest valid substring found so far.
        // ---------------------------------------------------------------
        int ans = 0;

        // ===============================================================
        // OUTER LOOP: Expand the window by moving `right` from 0 to n-1.
        // At each step, `right` adds one new character to the window.
        // ===============================================================
        for (int right = 0; right < n; right++) {

            // ===========================================================
            // INNER LOOP: Scan BACKWARD from `right` to check if any
            // forbidden substring ENDS at position `right`.
            // ===========================================================
            //
            // WHY THIS INNER LOOP EXISTS:
            //   When we add word[right] to the window, the only NEW
            //   forbidden substrings that could appear are those that
            //   END at `right`. All substrings ending before `right`
            //   were already checked in previous iterations.
            //
            // WHAT IT DOES:
            //   It builds substrings ending at `right` by scanning
            //   backward: word[right], word[right-1..right],
            //   word[right-2..right], ..., up to 10 characters back.
            //
            //   For each such substring, it checks if it's in the
            //   forbidden set. If found, `left` jumps past the start.
            //
            // WHY ONLY 9 STEPS BACK (right - 9)?
            //   Forbidden strings have MAX length 10. So a forbidden
            //   substring ending at `right` can start at earliest
            //   `right - 9`. There's no point checking further back.
            //
            // Example: right=7, forbidden max length=10
            //   Check substrings ending at 7:
            //     word[7]           (length 1)
            //     word[6..7]        (length 2)
            //     word[5..7]        (length 3)
            //     ...
            //     word[max(left,7-9)..7]  (length up to 10)
            //
            // ===========================================================

            // -----------------------------------------------------------
            // `cur` accumulates the substring being checked, built by
            // prepending characters as we scan backward.
            //
            // We start with empty and prepend word[i] each iteration,
            // so `cur` grows: "c", "bc", "abc", etc. (from right to left)
            // -----------------------------------------------------------
            string cur = "";

            // -----------------------------------------------------------
            // Scan backward from `right` to `max(left, right - 9)`.
            //
            // - We go backward: i = right, right-1, right-2, ...
            // - We stop at `max(left, right - 9)` because:
            //   a) We can't go left of `left` (that's outside the window)
            //   b) We don't need to go more than 9 steps back (max
            //      forbidden length is 10, so positions beyond that
            //      can't form a forbidden substring ending at `right`)
            //
            // The loop goes: i = right, right-1, right-2, ..., max(left, right-9)
            // -----------------------------------------------------------
            for (int i = right; i >= max(left, right - 9); i--) {

                // ------------------------------------------------------
                // Prepend word[i] to `cur`.
                // Since we're scanning backward, we build the substring
                // from RIGHT to LEFT:
                //
                //   i=right:    cur = word[right]
                //   i=right-1:  cur = word[right-1] + word[right]
                //   i=right-2:  cur = word[right-2..right]
                //   ...
                //
                // So `cur` always represents word[i..right].
                // ------------------------------------------------------
                cur = word[i] + cur;

                // ------------------------------------------------------
                // CHECK: Is this substring forbidden?
                // If word[i..right] is in the forbidden set, then any
                // valid window must NOT include position `i`.
                // So we move `left` to `i + 1`.
                //
                // We use `break` because once we move `left`, we don't
                // need to check further backward — those positions are
                // already excluded from the window.
                // ------------------------------------------------------
                if (bad.count(cur)) {
                    left = i + 1;
                    break;
                }
            }

            // ===========================================================
            // UPDATE ANSWER:
            // After handling the inner loop, the window [left..right]
            // is guaranteed to be valid (no forbidden substrings).
            // Update the maximum length.
            // ===========================================================
            ans = max(ans, right - left + 1);
        }

        // ---------------------------------------------------------------
        // Return the length of the longest valid substring.
        // ---------------------------------------------------------------
        return ans;
    }
};

/*
================================================================================
 DRY RUN / TRACE TABLE
================================================================================

 Example: word = "cbaaaabc", forbidden = ["aaa", "cb"]
 bad = {"aaa", "cb"}

 n = 8, left = 0, ans = 0

 =============================================================
 Iteration: right = 0, word[0] = 'c'
 =============================================================
 Inner loop: i = 0 (only 1 step back, max(0, 0-9)=0)
   cur = "c"
   "c" in bad? NO
 Window: [0..0] = "c"
 ans = max(0, 0-0+1) = 1

 =============================================================
 Iteration: right = 1, word[1] = 'b'
 =============================================================
 Inner loop: i = 1, then i = 0 (max(0, 1-9)=0)
   i=1: cur = "b", "b" in bad? NO
   i=0: cur = "cb", "cb" in bad? YES! -> left = 0+1 = 1, BREAK
 Window: [1..1] = "b"
 ans = max(1, 1-1+1) = 1

 =============================================================
 Iteration: right = 2, word[2] = 'a'
 =============================================================
 Inner loop: i = 2, then i = 1 (max(1, 2-9)=1)
   i=2: cur = "a", "a" in bad? NO
   i=1: cur = "ba", "ba" in bad? NO
 Window: [1..2] = "ba"
 ans = max(1, 2-1+1) = 2

 =============================================================
 Iteration: right = 3, word[3] = 'a'
 =============================================================
 Inner loop: i = 3, then i = 2 (max(1, 3-9)=1... wait, max(1, -6)=1)
   i=3: cur = "a", "a" in bad? NO
   i=2: cur = "aa", "aa" in bad? NO
 Window: [1..3] = "baa"
 ans = max(2, 3-1+1) = 3

 =============================================================
 Iteration: right = 4, word[4] = 'a'
 =============================================================
 Inner loop: i = 4, then i = 3, then i = 2
   i=4: cur = "a", "a" in bad? NO
   i=3: cur = "aa", "aa" in bad? NO
   i=2: cur = "aaa", "aaa" in bad? YES! -> left = 2+1 = 3, BREAK
 Window: [3..4] = "aa"
 ans = max(3, 4-3+1) = 3

 =============================================================
 Iteration: right = 5, word[5] = 'a'
 =============================================================
 Inner loop: i = 5, then i = 4, then i = 3
   i=5: cur = "a", "a" in bad? NO
   i=4: cur = "aa", "aa" in bad? NO
   i=3: cur = "aaa", "aaa" in bad? YES! -> left = 3+1 = 4, BREAK
 Window: [4..5] = "aa"
 ans = max(3, 5-4+1) = 3

 =============================================================
 Iteration: right = 6, word[6] = 'b'
 =============================================================
 Inner loop: i = 6, then i = 5 (max(4, 6-9)=4... max(4,-3)=4)
   i=6: cur = "b", "b" in bad? NO
   i=5: cur = "ab", "ab" in bad? NO
   i=4: cur = "aab", "aab" in bad? NO
 Window: [4..6] = "aab"
 ans = max(3, 6-4+1) = 3

 =============================================================
 Iteration: right = 7, word[7] = 'c'
 =============================================================
 Inner loop: i = 7, then i = 6, then i = 5
   i=7: cur = "c", "c" in bad? NO
   i=6: cur = "bc", "bc" in bad? NO
   i=5: cur = "abc", "abc" in bad? NO
 Window: [4..7] = "aabc"
 ans = max(3, 7-4+1) = 4

 =============================================================
 FINAL: ans = 4
 =============================================================

 The longest valid substring is "aabc" (length 4).
 It contains no "aaa" and no "cb" as substrings.

================================================================================

 Example 2: word = "cbezbbb", forbidden = ["bzb", "baz"]
 bad = {"bzb", "baz"}

 n = 7, left = 0, ans = 0

 =============================================================
 right=0, 'c':  cur="c" (not bad)        -> [0..0], ans=1
 right=1, 'b':  cur="b","cb"(not bad)    -> [0..1], ans=2
 right=2, 'e':  cur="e","be","cbe"(ok)   -> [0..2], ans=3
 right=3, 'z':  cur="z","ez","bez"(ok)   -> [0..3], ans=4
 right=4, 'b':  cur="b","zb"(not bad)    -> [0..4], ans=5
 right=5, 'b':  cur="b","bb","zbb"(ok)   -> [0..5], ans=6
 right=6, 'b':  cur="b","bb","bbb",
                     "zbbb"(ok)           -> [0..6], ans=7

 Wait - let me re-check: is "bzb" a substring of "cbezbbb"?
 "cbezbbb" -> c-b-e-z-b-b-b
 Positions: 0:c 1:b 2:e 3:z 4:b 5:b 6:b
 "bzb" would need b-z-b at consecutive positions.
 Position 1:b, 2:e (not z) -> No "bzb" found.
 "baz" -> b-a-z -> no 'a' in string -> No "baz" found.

 So answer = 7 ✓ (the whole string is valid)

================================================================================
*/

int main(){
    return 0;
}
