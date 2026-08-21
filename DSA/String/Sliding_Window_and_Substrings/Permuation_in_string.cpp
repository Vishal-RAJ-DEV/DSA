#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Permutation in String (567)
    Given two strings s1 and s2, return true if s2 contains a
    permutation of s1, or false otherwise.

    Example:
    s1 = "ab", s2 = "eidbaooo"
    Output: true
    Explanation: s2 contains "ba", which is a permutation of "ab"

    ================================================================
    KEY INSIGHT: PERMUTATION = SAME CHARACTER FREQUENCIES
    ================================================================

    A string is a permutation of another if and only if both have
    the SAME CHARACTER FREQUENCIES.

    Example:
    s1 = "aab" → freq: a=2, b=1
    "aba" → freq: a=2, b=1 ✓ (permutation)
    "baa" → freq: a=2, b=1 ✓ (permutation)
    "abb" → freq: a=1, b=2 ✗ (not permutation)

    ================================================================
    INTUITION: SLIDING WINDOW
    ================================================================

    Instead of generating ALL permutations of s1 (which is O(n!)),
    we can use a SLIDING WINDOW approach:

    1. Count character frequencies of s1
    2. Create a window of size |s1| on s2
    3. For each window position, check if frequencies match
    4. If any window matches, return true

    WHY SLIDING WINDOW?
    - We need to find if ANY substring of s2 (of length |s1|)
      has the same character frequencies as s1
    - Sliding window lets us check all such substrings in O(n)

    VISUAL EXAMPLE:
    s1 = "ab" (length 2)
    s2 = "eidbaooo"

    Window positions to check:
    [ei] → freq: e=1, i=1 ≠ s1 → no
    [id] → freq: i=1, d=1 ≠ s1 → no
    [db] → freq: d=1, b=1 ≠ s1 → no
    [ba] → freq: b=1, a=1 = s1 → YES! ✓

    ================================================================
    ALGORITHM STEPS
    ================================================================

    1. Build frequency array for s1 (what we're looking for)
    2. Initialize sliding window on s2
    3. For each character in s2:
       a. Add it to window (increment frequency)
       b. If window size > |s1|, remove leftmost character
       c. If window size == |s1|, check if frequencies match
       d. If match found, return true
    4. If no match found, return false
*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {

        // Frequency array for s1 (target pattern)
        // freq[i] = count of character ('a' + i) in s1
        vector<int> freq(26, 0);

        // Frequency array for current window in s2
        // check[i] = count of character ('a' + i) in current window
        vector<int> check(26, 0);

        // Build frequency array for s1
        for (char ch : s1) {
            freq[ch - 'a']++;
        }

        int l = 0;  // Left pointer of window
        int r = 0;  // Right pointer of window (expands)

        // Slide window across s2
        while (r < s2.size()) {

            // Add current character to window
            check[s2[r] - 'a']++;

            // If window size exceeds |s1|, shrink from left
            if (r - l + 1 > s1.size()) {
                check[s2[l] - 'a']--;  // Remove leftmost character
                l++;                   // Shrink window
            }

            // If window size equals |s1|, check if it's a permutation
            if (r - l + 1 == s1.size()) {
                // Compare frequency arrays
                // If equal, current window is a permutation of s1
                if (freq == check) {
                    return true;
                }
            }

            r++;  // Expand window
        }

        // No permutation found in s2
        return false;
    }
};

/*
    COMPLEXITY ANALYSIS:
    ====================

    Time Complexity: O(n)
    - We traverse s2 once with the sliding window
    - Frequency comparison is O(26) = O(1) per window
    - Total: O(n)

    Space Complexity: O(1)
    - Two fixed-size arrays of size 26
    - Total: O(26) = O(1)

    ================================================================
    WHY NOT BRUTE FORCE?
    ================================================================

    Brute Force Approach:
    - Generate ALL permutations of s1 → O(|s1|!) permutations
    - For each permutation, check if it exists in s2 → O(|s2|)
    - Total: O(|s1|! * |s2|) - VERY SLOW!

    Sliding Window Approach:
    - Just compare character frequencies in each window
    - Total: O(|s2|) - MUCH FASTER!

    The key insight is that we don't need to generate permutations.
    We just need to check if ANY substring of s2 has the same
    character frequencies as s1.

    ================================================================
    EDGE CASES
    ================================================================

    1. s1 is longer than s2 → return false (can't fit)
    2. s1 is empty → return true (empty string is permutation of empty)
    3. s1 has characters not in s2 → return false
    4. s1 and s2 are the same → return true (s1 is permutation of itself)
*/

int main(){
    return 0;
}
