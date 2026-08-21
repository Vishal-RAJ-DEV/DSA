#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Decode Ways II (639)
    A string s can contain digits '0'-'9' and wildcards '*'.
    '*' can represent any digit from '1' to '9'.

    Return the number of ways to decode s modulo 10^9 + 7.

    Example:
    s = "*"
    Output: 9
    Explanation: '*' can be '1','2',...,'9' → 9 ways

    ================================================================
    DECODING RULES (REVIEW)
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

    Valid single digit: 1-9 (NOT 0)
    Valid two digits: 10-26

    ================================================================
    HOW '*' CHANGES EVERYTHING
    ================================================================

    '*' is a WILDCARD that can be ANY digit from 1-9.

    This means:
    - '*' alone: 9 ways (1,2,3,4,5,6,7,8,9)
    - '*' followed by '*': 9 + 6 = 15 ways
      (1x where x=1-9, OR 2x where x=1-6)
    - '1*' → 9 ways (10,11,12,...,19)
    - '2*' → 6 ways (20,21,22,23,24,25,26)

    ================================================================
    THE IF-ELSE LOGIC EXPLAINED
    ================================================================

    At each position, we have TWO main choices:

    CHOICE 1: Take ONE character
    ────────────────────────────
    - If s[ind] = '*': 9 ways (1-9)
    - If s[ind] = '0': 0 ways (invalid)
    - Otherwise: 1 way

    CHOICE 2: Take TWO characters
    ──────────────────────────────
    This is where it gets complex!

    Two-digit numbers must be 10-26:
    - 10-19: First digit is '1'
    - 20-26: First digit is '2'

    CASE A: First digit is '1' or '*'
    ─────────────────────────────────
    - If second digit is '*': 9 pairs (10-19)
    - Otherwise: 1 pair (1x where x is the digit)

    CASE B: First digit is '2' or '*'
    ─────────────────────────────────
    - If second digit is '*': 6 pairs (20-26)
    - If second digit is '0'-'6': 1 pair
    - If second digit is '7'-'9': 0 pairs (invalid)

    ================================================================
    VISUAL EXAMPLES
    ================================================================

    Example 1: s = "*"
    ─────────────────
    Choice 1: Take '*' as single digit
              '*' = 9 ways (1-9)
    Choice 2: Can't take two chars (only 1 char)
    Total: 9 ways

    Example 2: s = "1*"
    ──────────────────
    Choice 1: Take '1' as single digit
              → 1 way, then decode '*' → 9 ways
              → 1 × 9 = 9 ways

    Choice 2: Take "1*" as two digits
              '1' + '*' = 10-19 → 9 ways
              → 9 ways

    Total: 9 + 9 = 18 ways

    Example 3: s = "2*"
    ──────────────────
    Choice 1: Take '2' as single digit
              → 1 way, then decode '*' → 9 ways
              → 1 × 9 = 9 ways

    Choice 2: Take "2*" as two digits
              '2' + '*' = 20-26 → 6 ways (20-26)
              → 6 ways

    Total: 9 + 6 = 15 ways

    Example 4: s = "**"
    ──────────────────
    Choice 1: Take first '*' as single digit
              → 9 ways, then decode second '*' → 9 ways
              → 9 × 9 = 81 ways

    Choice 2: Take "**" as two digits
              First '*' as '1': 1x where x=1-9 → 9 ways
              First '*' as '2': 2x where x=1-6 → 6 ways
              → 9 + 6 = 15 ways

    Total: 81 + 15 = 96 ways
*/

// ═══════════════════════════════════════════════════════════════════
// VERSION 1: MEMOIZATION (Top-Down DP)
// Time: O(n) | Space: O(n)
// ═══════════════════════════════════════════════════════════════════
class Memoization {
public:
    const int MOD = 1e9 + 7;

    int decodings(int ind, string &s, vector<int> &dp) {

        // ─────────────────────────────────────────────────────────
        // BASE CASE: Successfully decoded entire string
        // ─────────────────────────────────────────────────────────
        if (ind == s.size()) {
            return 1;
        }

        // ─────────────────────────────────────────────────────────
        // BASE CASE: '0' cannot be decoded alone
        // ─────────────────────────────────────────────────────────
        if (s[ind] == '0') {
            return 0;
        }

        // ─────────────────────────────────────────────────────────
        // MEMOIZATION: Return cached result
        // ─────────────────────────────────────────────────────────
        if (dp[ind] != -1) {
            return dp[ind];
        }

        // ═════════════════════════════════════════════════════════
        // CHOICE 1: Take ONLY ONE character
        // ═════════════════════════════════════════════════════════

        long long oneCharChoice = decodings(ind + 1, s, dp);

        // If current character is '*', it can be 1-9 (9 ways)
        // So multiply by 9
        if (s[ind] == '*') {
            oneCharChoice = (oneCharChoice * 9) % MOD;
        }

        // ═════════════════════════════════════════════════════════
        // CHOICE 2: Take TWO characters
        // ═════════════════════════════════════════════════════════

        long long twoCharChoice1 = 0;  // Case: first digit = '1'
        long long twoCharChoice2 = 0;  // Case: first digit = '2'

        // We need at least two characters remaining
        if (ind + 1 < s.size()) {

            // ─────────────────────────────────────────────────────
            // CASE A: First character can be '1' (or '*' acting as '1')
            // Valid pairs: 10, 11, 12, ..., 19
            // ─────────────────────────────────────────────────────
            if (s[ind] == '1' || s[ind] == '*') {

                twoCharChoice1 = decodings(ind + 2, s, dp);

                // If second character is '*', it can be 1-9 (9 pairs)
                if (s[ind + 1] == '*') {
                    twoCharChoice1 =
                        (twoCharChoice1 * 9) % MOD;
                }
                // Otherwise: exactly 1 pair (1x where x is the digit)
            }

            // ─────────────────────────────────────────────────────
            // CASE B: First character can be '2' (or '*' acting as '2')
            // Valid pairs: 20, 21, 22, 23, 24, 25, 26
            // ─────────────────────────────────────────────────────
            if (s[ind] == '2' || s[ind] == '*') {

                // If second character is '*', it can be 0-6 (7 pairs)
                // But wait! '2' followed by '*' means 20-26
                // '*' represents 0-6? No! '*' represents 1-9
                // So valid: 21,22,23,24,25,26 → 6 pairs
                if (s[ind + 1] == '*') {

                    twoCharChoice2 =
                        decodings(ind + 2, s, dp);

                    // '*' can only be 1-6 when paired with '2'
                    // (20 is handled by '2'+'0', not '2'+'*')
                    twoCharChoice2 =
                        (twoCharChoice2 * 6) % MOD;
                }
                // If second character is '0'-'6', it's valid
                else if (s[ind + 1] <= '6') {

                    twoCharChoice2 =
                        decodings(ind + 2, s, dp);
                }
                // If second character is '7'-'9', invalid (27+)
                // twoCharChoice2 stays 0
            }
        }

        // ═════════════════════════════════════════════════════════
        // TOTAL: Add all valid possibilities
        // ═════════════════════════════════════════════════════════
        return dp[ind] =
            (oneCharChoice +
             twoCharChoice1 +
             twoCharChoice2) % MOD;
    }

    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n, -1);
        return decodings(0, s, dp);
    }
};

// ═══════════════════════════════════════════════════════════════════
// VERSION 2: TABULATION (Bottom-Up DP)
// Time: O(n) | Space: O(n)
// ═══════════════════════════════════════════════════════════════════
/*
    ================================================================
    WHERE EACH MULTIPLICATION HAPPENS
    ================================================================

    The total ways at each position is calculated by ADDING
    contributions from all valid choices. But within each choice,
    we MULTIPLY to account for multiple possibilities.

    ┌─────────────────────────────────────────────────────────────┐
    │  FORMULA: dp[ind] = oneCharChoice + twoCharChoice1         │
    │                          + twoCharChoice2                   │
    └─────────────────────────────────────────────────────────────┘

    WHERE MULTIPLICATIONS HAPPEN:
    ═════════════════════════════

    1. ONE CHAR CHOICE: oneCharChoice = dp[ind+1] * multiplier
       ─────────────────────────────────────────────────────────
       - s[ind] = '1'-'9': multiplier = 1 (only one digit)
       - s[ind] = '*':     multiplier = 9 (can be 1-9)

       Example: s = "*3"
       oneCharChoice = dp[2] * 9
                     = 1 * 9 = 9 ways

    2. TWO CHAR CHOICE 1 (first='1'): twoCharChoice1 = dp[ind+2] * multiplier
       ─────────────────────────────────────────────────────────────────────
       - s[ind+1] = '0'-'9': multiplier = 1 (only one pair: 1x)
       - s[ind+1] = '*':     multiplier = 9 (pairs: 11-19)

       Example: s = "1*"
       twoCharChoice1 = dp[2] * 9
                      = 1 * 9 = 9 ways

    3. TWO CHAR CHOICE 2 (first='2'): twoCharChoice2 = dp[ind+2] * multiplier
       ─────────────────────────────────────────────────────────────────────
       - s[ind+1] = '0'-'6': multiplier = 1 (only one pair: 2x)
       - s[ind+1] = '*':     multiplier = 6 (pairs: 21-26)
       - s[ind+1] = '7'-'9': multiplier = 0 (invalid: 27+)

       Example: s = "2*"
       twoCharChoice2 = dp[2] * 6
                      = 1 * 6 = 6 ways

    ================================================================
    COMPLETE MULTIPLICATION TABLE
    ══════════════════════════════

    ┌─────────────┬─────────────┬───────────────┬──────────────────┐
    │ s[ind]      │ s[ind+1]    │ Choice 1      │ Choice 2         │
    │             │             │ (1 char)      │ (2 chars)        │
    ├─────────────┼─────────────┼───────────────┼──────────────────┤
    │ '0'         │ any         │ 0 (invalid)   │ 0                │
    │ '1'         │ '0'-'9'     │ 1 × dp[i+1]  │ 1 × dp[i+2]     │
    │ '1'         │ '*'         │ 1 × dp[i+1]  │ 9 × dp[i+2]     │
    │ '2'         │ '0'-'6'     │ 1 × dp[i+1]  │ 1 × dp[i+2]     │
    │ '2'         │ '7'-'9'     │ 1 × dp[i+1]  │ 0 (invalid)     │
    │ '2'         │ '*'         │ 1 × dp[i+1]  │ 6 × dp[i+2]     │
    │ '3'-'9'     │ any         │ 1 × dp[i+1]  │ 0 (invalid)     │
    │ '*'         │ '0'-'6'     │ 9 × dp[i+1]  │ (1+1) × dp[i+2] │
    │ '*'         │ '7'-'9'     │ 9 × dp[i+1]  │ 1 × dp[i+2]     │
    │ '*'         │ '*'         │ 9 × dp[i+1]  │ (9+6) × dp[i+2] │
    └─────────────┴─────────────┴───────────────┴──────────────────┘

    Note: When s[ind]='*' and s[ind+1]='0'-'6':
    - As '1': 1 pair (1x)
    - As '2': 1 pair (2x)
    - Total: 2 pairs

    ================================================================
    EXAMPLE: s = "**"
    ══════════════════

    dp[2] = 1 (base case)

    ind = 1:
    - oneCharChoice = dp[2] * 9 = 1 * 9 = 9
    - twoCharChoice1 = 0 (no s[ind+1] for '1' case)
    - twoCharChoice2 = 0 (no s[ind+1] for '2' case)
    dp[1] = 9

    ind = 0:
    - oneCharChoice = dp[1] * 9 = 9 * 9 = 81
    - twoCharChoice1 = dp[2] * 9 = 1 * 9 = 9 (as '1')
    - twoCharChoice2 = dp[2] * 6 = 1 * 6 = 6 (as '2')
    dp[0] = 81 + 9 + 6 = 96

    ================================================================
    WHY MULTIPLY BY dp[ind+2]?
    ═══════════════════════════

    When we take 2 characters, we skip 2 positions.
    The number of ways to decode the REMAINING string is dp[ind+2].

    If those 2 characters can form MULTIPLE valid pairs,
    we multiply dp[ind+2] by the number of valid pairs.

    Example: s = "1*"
    - "1*" can form 9 pairs (10-19)
    - Each pair is followed by the same remaining string
    - So: 9 × dp[ind+2] = 9 × 1 = 9 ways

    This is the MULTIPLICATION PRINCIPLE:
    If task A can be done in m ways and task B in n ways,
    then doing both A and B can be done in m × n ways.
*/
class Tabulation {
public:
    const int MOD = 1e9 + 7;

    int numDecodings(string s) {

        int n = s.size();

        // dp[i] = number of ways to decode s[i..n-1]
        vector<long long> dp(n + 1, 0);

        // Base case: empty string = 1 way
        dp[n] = 1;

        // Fill from right to left
        for (int ind = n - 1; ind >= 0; ind--) {

            // ─────────────────────────────────────────────────────
            // '0' cannot be decoded alone
            // ─────────────────────────────────────────────────────
            if (s[ind] == '0') {
                dp[ind] = 0;
                continue;
            }

            // ═══════════════════════════════════════════════════
            // CHOICE 1: Take ONE character
            // ═══════════════════════════════════════════════════

            long long oneCharChoice = dp[ind + 1];

            // '*' can represent 1-9 (9 ways)
            if (s[ind] == '*') {
                oneCharChoice =
                    (oneCharChoice * 9) % MOD;
            }

            // ═══════════════════════════════════════════════════
            // CHOICE 2: Take TWO characters
            // ═══════════════════════════════════════════════════

            long long twoCharChoice1 = 0;  // Case: first = '1'
            long long twoCharChoice2 = 0;  // Case: first = '2'

            if (ind + 1 < n) {

                // ─────────────────────────────────────────────────
                // CASE A: First character is '1' or '*' (as '1')
                // Valid: 10-19 (all valid two-digit numbers)
                // ─────────────────────────────────────────────────
                if (s[ind] == '1' || s[ind] == '*') {

                    twoCharChoice1 = dp[ind + 2];

                    // If second char is '*', multiply by 9
                    // because '*' can be 1-9
                    if (s[ind + 1] == '*') {
                        twoCharChoice1 =
                            (twoCharChoice1 * 9) % MOD;
                    }
                }

                // ─────────────────────────────────────────────────
                // CASE B: First character is '2' or '*' (as '2')
                // Valid: 20-26 (not all are valid!)
                // ─────────────────────────────────────────────────
                if (s[ind] == '2' || s[ind] == '*') {

                    // If second char is '*', valid: 21-26 (6 pairs)
                    if (s[ind + 1] == '*') {
                        twoCharChoice2 =
                            (dp[ind + 2] * 6) % MOD;
                    }
                    // If second char is '0'-'6', it's valid
                    else if (s[ind + 1] <= '6') {
                        twoCharChoice2 = dp[ind + 2];
                    }
                    // If second char is '7'-'9', invalid (27+)
                    // twoCharChoice2 stays 0
                }
            }

            // ═══════════════════════════════════════════════════
            // TOTAL: Add all valid choices
            // ═══════════════════════════════════════════════════
            dp[ind] =
                (oneCharChoice +
                 twoCharChoice1 +
                 twoCharChoice2) % MOD;
        }

        return dp[0];
    }
};

/*
    COMPARISON:
    ===========

    Approach        Time    Space   Notes
    ──────────────────────────────────────────────────
    Memoization     O(n)    O(n)    Recursive + cache
    Tabulation      O(n)    O(n)    Iterative, bottom-up

    ════════════════════════════════════════════════════════════════
    SUMMARY OF IF-ELSE LOGIC
    ════════════════════════════════════════════════════════════════

    The key insight is that '*' introduces MULTIPLE possibilities:

    1. SINGLE CHAR:
       - '1'-'9': 1 way
       - '*': 9 ways
       - '0': 0 ways

    2. TWO CHARS (first char):
       - '1': Can form 10-19 (9 pairs)
       - '2': Can form 20-26 (7 pairs)
       - '*': Can act as '1' OR '2'
              → As '1': 9 pairs
              → As '2': 6 pairs
              → Total: 9 + 6 = 15 pairs

    3. TWO CHARS (second char):
       - '0'-'9': 1 way
       - '*': When paired with '1' → 9 ways
              When paired with '2' → 6 ways

    This is why we need separate variables:
    - twoCharChoice1: for '1' case
    - twoCharChoice2: for '2' case

    They can BOTH contribute when first char is '*'!
*/




// ═══════════════════════════════════════════════════════════════════
// VERSION 3: MEMOIZATION (Alternative Cleaner Structure)
// Time: O(n) | Space: O(n)
// Uses explicit if-else for each case instead of separate variables
// ═══════════════════════════════════════════════════════════════════
class Version3_CleanerStructure {
public:
    const int MOD = 1e9 + 7;

    int solve(int i, string &s, vector<int> &dp) {
        int n = s.size();

        // Successfully decoded the complete string
        if (i == n)
            return 1;

        // '0' cannot be decoded alone
        if (s[i] == '0')
            return 0;

        // Return already computed answer
        if (dp[i] != -1)
            return dp[i];

        long long ways = 0;

        // =========================================
        // 1. Take ONE character
        // =========================================

        if (s[i] == '*') {
            // '*' can be 1 to 9 -> 9 choices
            ways = (9LL * solve(i + 1, s, dp)) % MOD;
        }
        else {
            // Normal digit -> only 1 choice
            ways = solve(i + 1, s, dp);
        }


        // =========================================
        // 2. Take TWO characters
        // =========================================

        if (i + 1 < n) {

            // Case: "**"
            if (s[i] == '*' && s[i + 1] == '*') {

                // 11-19 -> 9 ways
                // 21-26 -> 6 ways
                // Total -> 15 ways
                ways = (ways + 15LL * solve(i + 2, s, dp)) % MOD;
            }


            // Case: "*digit"
            else if (s[i] == '*') {

                if (s[i + 1] <= '6') {
                    // Example: "*3" -> 13, 23
                    // 2 valid choices
                    ways = (ways + 2LL * solve(i + 2, s, dp)) % MOD;
                }
                else {
                    // Example: "*8" -> only 18
                    // 1 valid choice
                    ways = (ways + solve(i + 2, s, dp)) % MOD;
                }
            }


            // Case: "1*"
            else if (s[i] == '1' && s[i + 1] == '*') {

                // 11 to 19 -> 9 choices
                ways = (ways + 9LL * solve(i + 2, s, dp)) % MOD;
            }


            // Case: "2*"
            else if (s[i] == '2' && s[i + 1] == '*') {

                // 21 to 26 -> 6 choices
                ways = (ways + 6LL * solve(i + 2, s, dp)) % MOD;
            }


            // Case: Two normal digits
            else {

                int num = (s[i] - '0') * 10
                        + (s[i + 1] - '0');

                // Valid number from 10 to 26
                if (num >= 10 && num <= 26) {
                    ways = (ways + solve(i + 2, s, dp)) % MOD;
                }
            }
        }

        // Store answer for index i
        return dp[i] = ways;
    }


    int numDecodings(string s) {

        int n = s.size();

        // dp[i] = ways to decode s[i ... n-1]
        vector<int> dp(n, -1);

        return solve(0, s, dp);
    }
};


int main(){
    // Test Version 2 (Tabulation)
    Tabulation sol;
    cout << "Version 2 (Tabulation):" << endl;
    cout << sol.numDecodings("*") << endl;   // 9
    cout << sol.numDecodings("1*") << endl;  // 18
    cout << sol.numDecodings("2*") << endl;  // 15

    // Test Version 3 (Cleaner Structure)
    Version3_CleanerStructure sol3;
    cout << "\nVersion 3 (Cleaner Structure):" << endl;
    cout << sol3.numDecodings("*") << endl;   // 9
    cout << sol3.numDecodings("1*") << endl;  // 18
    cout << sol3.numDecodings("2*") << endl;  // 15

    return 0;
}
