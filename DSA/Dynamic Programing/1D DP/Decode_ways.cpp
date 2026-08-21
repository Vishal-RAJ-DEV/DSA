#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Decode Ways (91)
    A message consisting of letters A-Z is encoded using numerical
    values where 'A' = 1, 'B' = 2, ..., 'Z' = 26.
    Given a string of digits s, return the number of ways to decode it.

    Example:
    s = "226"
    Output: 3
    Explanation: "226" can be decoded as:
    - "BZ" (2, 26)
    - "VF" (22, 6)
    - "BBF" (2, 2, 6)

    ================================================================
    ENCODING RULES
    ================================================================

    'A' = 1    'J' = 10    'S' = 19
    'B' = 2    'K' = 11    'T' = 20
    'C' = 3    'L' = 12    'U' = 21
    'D' = 4    'M' = 13    'V' = 22
    'E' = 5    'N' = 14    'W' = 23
    'F' = 6    'O' = 15    'X' = 24
    'G' = 7    'P' = 16    'Y' = 25
    'H' = 8    'Q' = 17    'Z' = 26
    'I' = 9    'R' = 18

    Valid single digit: 1-9 (NOT 0!)
    Valid two digits: 10-26

    ================================================================
    KEY INSIGHT: AT EACH POSITION, WE HAVE CHOICES
    ================================================================

    At position i, we can:
    1. Take ONE digit: s[i] (must be '1'-'9')
    2. Take TWO digits: s[i..i+1] (must be 10-26)

    This is a classic DECISION PROBLEM → Use Dynamic Programming!

    ================================================================
    INTUITION: COUNTING DECODINGS
    ================================================================

    Let dp[i] = number of ways to decode s[i..n-1]

    At position i:
    - If s[i] = '0': cannot decode → return 0
    - Otherwise:
      - Take 1 digit: add dp[i+1] ways
      - Take 2 digits (if valid 10-26): add dp[i+2] ways

    Base case: dp[n] = 1 (empty string = 1 way to decode nothing)

    ================================================================
    VISUAL EXAMPLE: s = "226"
    ================================================================

    Positions:  0  1  2
    Digits:     2  2  6

    Starting from index 0:
    ─────────────────────
    Option 1: Take '2' (single digit) → decode rest from index 1
    Option 2: Take '22' (two digits) → decode rest from index 2

    Both are valid! So we explore both paths.

    Path 1: Take '2' → at index 1
    ──────────────────────────────
    Option 1: Take '2' (single) → at index 2
    ──────────────────────────────
    Option 1: Take '6' (single) → at index 3 ✓ DECODED!
    Option 2: Can't take '6?' (no more chars)

    Option 2: Take '26' (two digits) → at index 3 ✓ DECODED!

    Path 2: Take '22' → at index 2
    ──────────────────────────────
    Option 1: Take '6' (single) → at index 3 ✓ DECODED!

    Total: 3 ways!

    ================================================================
    WHY dp[i] = dp[i+1] + dp[i+2]?
    ================================================================

    When we take 1 digit at position i:
    - We've used s[i]
    - Remaining: s[i+1..n-1]
    - Ways to decode remaining: dp[i+1]

    When we take 2 digits at position i:
    - We've used s[i] and s[i+1]
    - Remaining: s[i+2..n-1]
    - Ways to decode remaining: dp[i+2]

    Total ways = sum of both choices!

    ================================================================
    EDGE CASES
    ================================================================

    1. '0' at start: return 0 (can't decode)
    2. "0": return 0
    3. "10": return 1 (only "10" → J)
    4. "27": return 1 (only "2","7" → BG, "27" invalid)
    5. "111": return 3 ("1","1","1" or "11","1" or "1","11")
*/

// ═══════════════════════════════════════════════════════════════════
// APPROACH 1: MEMOIZATION (Top-Down DP)
// Time: O(n) | Space: O(n)
// ═══════════════════════════════════════════════════════════════════
class Memoization {
public:

    int solve(int i, string& s, vector<int>& dp) {

        // ─────────────────────────────────────────────────────────
        // BASE CASE: Successfully decoded entire string
        // ─────────────────────────────────────────────────────────
        // If we've reached the end, we found ONE valid decoding
        if (i == s.size()) {
            return 1;
        }

        // ─────────────────────────────────────────────────────────
        // BASE CASE: '0' cannot be decoded
        // ─────────────────────────────────────────────────────────
        // '0' has no mapping (A=1, B=2, ..., no letter = 0)
        if (s[i] == '0') {
            return 0;
        }

        // ─────────────────────────────────────────────────────────
        // MEMOIZATION: Return cached result if computed
        // ─────────────────────────────────────────────────────────
        if (dp[i] != -1) {
            return dp[i];
        }

        // ─────────────────────────────────────────────────────────
        // CHOICE 1: Take ONE digit (s[i])
        // ─────────────────────────────────────────────────────────
        // Valid single digits: '1'-'9'
        // After taking s[i], decode rest from i+1
        int ways = solve(i + 1, s, dp);

        // ─────────────────────────────────────────────────────────
        // CHOICE 2: Take TWO digits (s[i..i+1])
        // ─────────────────────────────────────────────────────────
        // Must check: 1. We have at least 2 digits left
        //             2. Two-digit number is between 10-26
        if (i + 1 < s.size()) {

            // Convert two characters to integer
            int num = (s[i] - '0') * 10 +      // Tens place
                      (s[i + 1] - '0');         // Ones place

            // Valid two-digit decoding: 10 (J) to 26 (Z)
            if (num >= 10 && num <= 26) {
                // After taking s[i..i+1], decode rest from i+2
                ways += solve(i + 2, s, dp);
            }
        }

        // Cache and return total ways
        return dp[i] = ways;
    }

    int numDecodings(string s) {

        int n = s.size();

        // dp[i] = number of ways to decode s[i..n-1]
        vector<int> dp(n, -1);

        return solve(0, s, dp);
    }
};

// ═══════════════════════════════════════════════════════════════════
// APPROACH 2: TABULATION (Bottom-Up DP)
// Time: O(n) | Space: O(n)
// ═══════════════════════════════════════════════════════════════════
/*
    ================================================================
    HOW TABULATION WORKS
    ================================================================

    Instead of recursion (top-down), we build the solution iteratively
    from the END of the string to the BEGINNING.

    dp[i] = number of ways to decode s[i..n-1]

    We compute dp[n-1], dp[n-2], ..., dp[0] in order.

    ================================================================
    TRANSITION
    ================================================================

    For each position i (from right to left):

    1. If s[i] = '0': dp[i] = 0 (can't decode)

    2. Else:
       - Take 1 digit: dp[i] = dp[i+1]
       - Take 2 digits (if valid): dp[i] += dp[i+2]

    ================================================================
    VISUAL EXAMPLE: s = "226"
    ================================================================

    dp array: dp[0], dp[1], dp[2], dp[3]
    Indices:     0      1      2      3

    Base case: dp[3] = 1 (empty string)

    i=2: s[2]='6'
    - Take 1 digit: dp[2] = dp[3] = 1
    - Can't take 2 digits (i+1=3 is out of bounds)
    dp = [?, ?, 1, 1]

    i=1: s[1]='2'
    - Take 1 digit: dp[1] = dp[2] = 1
    - Take 2 digits: num=26 (valid), dp[1] += dp[3] = 1+1 = 2
    dp = [?, 2, 1, 1]

    i=0: s[0]='2'
    - Take 1 digit: dp[0] = dp[1] = 2
    - Take 2 digits: num=22 (valid), dp[0] += dp[2] = 2+1 = 3
    dp = [3, 2, 1, 1]

    Answer: dp[0] = 3
*/
class Tabulation {
public:
    int numDecodings(string s) {

        int n = s.size();

        // dp[i] = number of ways to decode s[i..n-1]
        vector<int> dp(n + 1, 0);

        // Base case: empty string = 1 way
        dp[n] = 1;

        // Build from right to left
        for (int i = n - 1; i >= 0; i--) {

            // '0' cannot be decoded
            if (s[i] == '0') {
                dp[i] = 0;
                continue;
            }

            // Take 1 digit
            dp[i] = dp[i + 1];

            // Take 2 digits if valid (10-26)
            if (i + 1 < n) {
                int num = (s[i] - '0') * 10 +
                          (s[i + 1] - '0');

                if (num >= 10 && num <= 26) {
                    dp[i] += dp[i + 2];
                }
            }
        }

        return dp[0];
    }
};

/*
    COMPARISON OF APPROACHES:
    =========================

    Approach        Time    Space   Notes
    ──────────────────────────────────────────────────
    Memoization     O(n)    O(n)    Recursive + cache
    Tabulation      O(n)    O(n)    Iterative, bottom-up

    KEY INSIGHT:
    ════════════
    This is similar to CLIMBING STAIRS problem!

    In Climbing Stairs:
    - At each step, you can climb 1 or 2 steps
    - dp[i] = dp[i+1] + dp[i+2]

    In Decode Ways:
    - At each position, you can take 1 or 2 digits
    - dp[i] = dp[i+1] + dp[i+2] (if 2-digit is valid)

    The only difference: Decode Ways has VALIDITY CHECKS:
    - Single digit: must be '1'-'9' (not '0')
    - Two digits: must be 10-26

    ══════════════════════════════════════════════════════════════════
    WHY dp[i] = dp[i+1] + dp[i+2]?
    ══════════════════════════════════════════════════════════════════

    Think of it as a TREE of choices:

                    dp[i]
                   /     \
            Take 1      Take 2
            digit       digits
            /              \
        dp[i+1]         dp[i+2]

    Total ways = Left subtree + Right subtree
               = dp[i+1] + dp[i+2]

    This is the essence of dynamic programming:
    Combine solutions of smaller subproblems!
*/

int main(){
    return 0;
}
