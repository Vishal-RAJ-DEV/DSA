#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Minimum Window Subsequence (727)
    Given strings s1 and s2, find the minimum window substring of s1
    such that s2 is a subsequence of the window.

    Example:
    s1 = "abcdebdde"
    s2 = "bde"
    Output: "bcde"

    ================================================================
    WHAT IS A SUBSEQUENCE?
    ================================================================
    A subsequence is a sequence derived from another sequence by
    deleting some or no elements without changing the order.

    In s1 = "abcdebdde", "bde" appears as a subsequence:
    - b at index 1, d at index 3, e at index 4 → window "bcde"
    - b at index 5, d at index 6, e at index 8 → window "bdde"
*/

// ═══════════════════════════════════════════════════════════════════
// APPROACH 1: FORWARD SCAN + BACKWARD SHRINK
// Time: O(n * m) | Space: O(1)
// ═══════════════════════════════════════════════════════════════════
/*
    INTUITION:
    1. Scan forward to find any valid window (may be too large)
    2. Scan backward to find the tightest start for that window
    3. Repeat for all possible windows

    VISUAL EXAMPLE:
    s1 = a b c d e b d d e
         0 1 2 3 4 5 6 7 8
    s2 = b d e

    Forward: a b c d e → found match ending at 4
             ↑ ↑ ↑ ↑
             b d e

    Backward: a b c d e → find tightest start at 1
                ↑ ↑ ↑ ↑
                b d e

    Window: [b c d e] = "bcde"
*/
class Approach1_ForwardBackward {
public:
    string minWindow(string &s1, string &s2) {

        int n = s1.size();
        int m = s2.size();

        int minLen = INT_MAX;
        int startIndex = -1;

        int i = 0;

        while (i < n) {

            int j = 0;

            // PHASE 1: FORWARD SCAN - find s2 as subsequence
            while (i < n) {
                if (s1[i] == s2[j]) {
                    j++;
                }
                if (j == m) {
                    break;
                }
                i++;
            }

            // Could not find complete s2
            if (j != m) {
                break;
            }

            // Current valid window ends at i
            int end = i;

            // PHASE 2: BACKWARD SHRINK - find minimum start
            j = m - 1;

            while (j >= 0) {
                if (s1[i] == s2[j]) {
                    j--;
                }
                i--;
            }

            // i went one position before the actual start
            int start = i + 1;

            int len = end - start + 1;

            // Update minimum window (strictly smaller to keep leftmost)
            if (len < minLen) {
                minLen = len;
                startIndex = start;
            }

            // Continue searching after the start
            i = start + 1;
        }

        if (startIndex == -1) {
            return "";
        }

        return s1.substr(startIndex, minLen);
    }
};

// ═══════════════════════════════════════════════════════════════════
// APPROACH 2: 2D DYNAMIC PROGRAMMING
// Time: O(n * m) | Space: O(n * m)
// ═══════════════════════════════════════════════════════════════════
/*
    ================================================================
    INTUITION: WHAT DOES dp[i][j] REPRESENT?
    ================================================================

    dp[i][j] = the STARTING INDEX of the subsequence s2[0...j]
               that ends at position i in s1

    If dp[i][j] = -1, it means no valid subsequence exists.

    ================================================================
    WHY THIS DEFINITION WORKS
    ================================================================

    Instead of tracking "can we match s2[0..j] ending at s1[i]?",
    we track "WHERE does the match START?"

    This is powerful because:
    - If we know the start and end of a valid subsequence,
      we can directly calculate the window length!
    - Window length = end_index - start_index + 1

    ================================================================
    BASE CASE: j = 0 (first character of s2)
    ================================================================

    For each position i in s1:
    - If s1[i] == s2[0], we can start a match at position i
      → dp[i][0] = i
    - If s1[i] != s2[0], we inherit from previous position
      → dp[i][0] = dp[i-1][0]

    Example: s1 = "abcde", s2 = "bde"

    i=0: s1[0]='a' ≠ 'b' → dp[0][0] = -1
    i=1: s1[1]='b' = 'b' → dp[1][0] = 1
    i=2: s1[2]='c' ≠ 'b' → dp[2][0] = dp[1][0] = 1
    i=3: s1[3]='d' ≠ 'b' → dp[3][0] = dp[2][0] = 1
    i=4: s1[4]='e' ≠ 'b' → dp[4][0] = dp[3][0] = 1

    dp[*][0] = [-1, 1, 1, 1, 1]
               a   b  c  d  e

    ================================================================
    TRANSITION: j > 0 (matching s2[j])
    ================================================================

    For each position i in s1 and j in s2:

    CASE 1: s1[i] == s2[j] (characters match)
    ─────────────────────────────────────────
    We can extend the subsequence s2[0..j-1] that ended at i-1.

    dp[i][j] = dp[i-1][j-1]

    Why? Because:
    - dp[i-1][j-1] is the start of s2[0..j-1] ending at i-1
    - Since s1[i] = s2[j], we can add s1[i] to the subsequence
    - The start remains the same (dp[i-1][j-1])

    CASE 2: s1[i] != s2[j] (characters don't match)
    ────────────────────────────────────────────────
    We can't use s1[i] for s2[j], so inherit from previous position.

    dp[i][j] = dp[i-1][j]

    Why? Because:
    - The subsequence s2[0..j] ending at i must have ended at i-1
    - We just carry forward the start index

    ================================================================
    VISUAL EXAMPLE: Building dp table
    ================================================================

    s1 = "abcde", s2 = "bde"

    dp[i][j] = starting index of s2[0..j] ending at s1[i]

         j=0  j=1  j=2
         'b'  'd'  'e'
    i=0  -1   -1   -1    (a: no match)
    i=1   1   -1   -1    (b: match s2[0], start=1)
    i=2   1   -1   -1    (c: inherit from above)
    i=3   1    1   -1    (d: match s2[1], start=dp[2][0]=1)
    i=4   1    1    1    (e: match s2[2], start=dp[3][1]=1)

    When i=4, j=2 (last column): dp[4][2] = 1
    → Subsequence "bde" ending at index 4 starts at index 1
    → Window: s1[1..4] = "bcde"
    → Length = 4 - 1 + 1 = 4

    ================================================================
    FINDING MINIMUM WINDOW
    ================================================================

    For each row i, check if dp[i][m-1] != -1:
    - If yes, we have a complete subsequence ending at i
    - Start = dp[i][m-1], End = i
    - Length = i - dp[i][m-1] + 1
    - Update minimum if this is smaller
*/
class Approach2_2D_DP {
public:
    string minWindow(string &s1, string &s2) {

        int n = s1.size();
        int m = s2.size();

        // dp[i][j] = starting index of subsequence s2[0..j] ending at s1[i]
        vector<vector<int>> dp(n, vector<int>(m, -1));

        // ─────────────────────────────────────────────────────────
        // BASE CASE: Match first character of s2 (j = 0)
        // ─────────────────────────────────────────────────────────
        for (int i = 0; i < n; i++) {

            // If current character matches s2[0], start a new match
            if (s1[i] == s2[0]) {
                dp[i][0] = i;
            }
            // Otherwise, inherit from previous position
            else if (i > 0) {
                dp[i][0] = dp[i - 1][0];
            }
        }

        int minLen = INT_MAX;
        int startIndex = -1;

        // ─────────────────────────────────────────────────────────
        // FILL DP TABLE: For each character in s1 and s2
        // ─────────────────────────────────────────────────────────
        for (int i = 1; i < n; i++) {

            for (int j = 1; j < m; j++) {

                // CASE 1: Characters match
                // Extend the subsequence from previous positions
                if (s1[i] == s2[j]) {
                    // Start index comes from matching s2[0..j-1] at i-1
                    dp[i][j] = dp[i - 1][j - 1];
                }
                // CASE 2: Characters don't match
                // Inherit from previous row
                else {
                    dp[i][j] = dp[i - 1][j];
                }
            }

            // ─────────────────────────────────────────────────────
            // CHECK IF COMPLETE SUBSEQUENCE FOUND
            // ─────────────────────────────────────────────────────
            if (dp[i][m - 1] != -1) {

                int start = dp[i][m - 1];  // Start of subsequence
                int len = i - start + 1;    // Window length

                // Update minimum window
                if (len < minLen) {
                    minLen = len;
                    startIndex = start;
                }
            }
        }

        if (startIndex == -1) {
            return "";
        }

        return s1.substr(startIndex, minLen);
    }
};

// ═══════════════════════════════════════════════════════════════════
// APPROACH 3: 1D DP (SPACE OPTIMIZED)
// Time: O(n * m) | Space: O(m)
// ═══════════════════════════════════════════════════════════════════
/*
    ================================================================
    HOW IS THIS OPTIMIZED FROM 2D TO 1D?
    ================================================================

    In the 2D DP approach:
    - dp[i][j] depends on dp[i-1][j-1] and dp[i-1][j]
    - We only need the PREVIOUS ROW to compute current row

    Key Observation:
    ───────────────
    When computing dp[i][j], we need:
    - dp[i-1][j-1] (previous row, previous column)
    - dp[i-1][j] (previous row, same column)

    If we update from RIGHT TO LEFT:
    - dp[j-1] still holds value from previous iteration (dp[i-1][j-1])
    - dp[j] still holds value from previous iteration (dp[i-1][j])

    This is the same trick used in 0/1 Knapsack!

    ================================================================
    WHY RIGHT TO LEFT?
    ================================================================

    When we update dp[j], we need dp[j-1] to be from the PREVIOUS row.

    If we go left to right:
    - dp[j-1] is already updated to current row → WRONG!

    If we go right to left:
    - dp[j-1] is still from previous row → CORRECT!

    Example:
    ────────
    Old dp: [-1, 1, 1, 1, 1]

    Updating left to right:
    dp[0] = ? (uses old dp[-1] - invalid)
    dp[1] = dp[0] (uses NEW dp[0] - WRONG!)

    Updating right to left:
    dp[4] = dp[3] (uses OLD dp[3] - correct)
    dp[3] = dp[2] (uses OLD dp[2] - correct)
    dp[2] = dp[1] (uses OLD dp[1] - correct)
    dp[1] = dp[0] (uses OLD dp[0] - correct)

    ================================================================
    VISUAL EXAMPLE
    ================================================================

    s1 = "abcde", s2 = "bde"

    Initial dp: [-1, -1, -1]
                  b   d   e

    Process s1[0] = 'a':
    - 'a' ≠ s2[2]='e', 'a' ≠ s2[1]='d' → no updates
    - 'a' ≠ s2[0]='b' → no update
    dp: [-1, -1, -1]

    Process s1[1] = 'b':
    - Update from right: j=2: 'b'≠'e' → skip
                        j=1: 'b'≠'d' → skip
    - 'b' = s2[0]='b' → dp[0] = 1
    dp: [1, -1, -1]

    Process s1[2] = 'c':
    - Update from right: j=2: 'c'≠'e' → skip
                        j=1: 'c'≠'d' → skip
    - 'c' ≠ s2[0]='b' → no update
    dp: [1, -1, -1]

    Process s1[3] = 'd':
    - Update from right: j=2: 'd'≠'e' → skip
                        j=1: 'd'='d' → dp[1] = dp[0] = 1
    - 'd' ≠ s2[0]='b' → no update
    dp: [1, 1, -1]

    Process s1[4] = 'e':
    - Update from right: j=2: 'e'='e' → dp[2] = dp[1] = 1
                        j=1: 'e'≠'d' → skip
    - 'e' ≠ s2[0]='b' → no update
    dp: [1, 1, 1]

    When dp[2] = 1 (last position of s2):
    → Complete subsequence found!
    → Start = dp[2] = 1, End = i = 4
    → Window = s1[1..4] = "bcde"
*/
class Approach3_1D_DP {
public:
    string minWindow(string &s1, string &s2) {

        int n = s1.size();
        int m = s2.size();

        // dp[j] = starting index of subsequence s2[0..j]
        //         ending at current position in s1
        vector<int> dp(m, -1);

        int minLen = INT_MAX;
        int startIndex = -1;

        for (int i = 0; i < n; i++) {

            // ─────────────────────────────────────────────────────
            // UPDATE FROM RIGHT TO LEFT
            // (Same as 0/1 Knapsack space optimization)
            // ─────────────────────────────────────────────────────
            // This ensures dp[j-1] is from previous iteration
            for (int j = m - 1; j >= 1; j--) {

                // If current char matches s2[j],
                // extend subsequence from dp[j-1]
                if (s1[i] == s2[j]) {
                    dp[j] = dp[j - 1];
                }
            }

            // ─────────────────────────────────────────────────────
            // MATCH FIRST CHARACTER (j = 0)
            // ─────────────────────────────────────────────────────
            // Do this AFTER updating j > 0 to avoid overwriting
            // dp[j-1] before it's used
            if (s1[i] == s2[0]) {
                dp[0] = i;
            }

            // ─────────────────────────────────────────────────────
            // CHECK IF COMPLETE SUBSEQUENCE FOUND
            // ─────────────────────────────────────────────────────
            if (dp[m - 1] != -1) {

                int start = dp[m - 1];
                int len = i - start + 1;

                if (len < minLen) {
                    minLen = len;
                    startIndex = start;
                }
            }
        }

        if (startIndex == -1) {
            return "";
        }

        return s1.substr(startIndex, minLen);
    }
};

/*
    COMPARISON OF ALL APPROACHES:
    ============================

    Approach              Time        Space     Notes
    ─────────────────────────────────────────────────────────────
    1. Forward+Backward   O(n*m)      O(1)      Intuitive, two scans
    2. 2D DP              O(n*m)      O(n*m)    Clear state definition
    3. 1D DP              O(n*m)      O(m)      Space optimized

    KEY INSIGHTS:
    ═════════════

    1. Forward+Backward:
       - Forward finds ANY valid window
       - Backward shrinks to MINIMUM window
       - Simple but effective

    2. 2D DP:
       - dp[i][j] = START index of s2[0..j] ending at s1[i]
       - If we know start and end, we know the window!
       - Transition: extend or inherit

    3. 1D DP:
       - Same as 2D, but only keep one row
       - Update RIGHT TO LEFT to avoid overwriting
       - Same trick as 0/1 Knapsack optimization

    WHY dp[j] = dp[j-1] WHEN CHARACTERS MATCH?
    ════════════════════════════════════════════
    - dp[j-1] holds the START of s2[0..j-1] from previous iteration
    - If s1[i] = s2[j], we can extend this subsequence
    - The START remains the same (dp[j-1])
    - So dp[j] = dp[j-1]

    This is elegant: the START index propagates through the dp array!
*/

int main(){
    return 0;
}
