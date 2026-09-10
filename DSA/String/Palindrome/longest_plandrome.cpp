// LeetCode 409 - Longest Palindrome: https://leetcode.com/problems/longest-palindrome/
//
// QUESTION:
// Given a string s which consists of lowercase or uppercase letters,
// return the length of the longest palindrome that can be built with those letters.
// Letters are case-sensitive, e.g., 'Aa' is considered two different characters.
//
// Example 1: s = "abccccdd" → Output: 7 (one longest palindrome: "dccaccd")
// Example 2: s = "a"       → Output: 1
//
// ---------------------------------------------------------------------------
// INTUITION - The Structure of a Palindrome
// ---------------------------------------------------------------------------
//
// A palindrome looks like:
//
//     A  B  C  D  C  B  A
//     ↕  ↕  ↕     ↕  ↕  ↕
//    pairs          pairs   center
//
// Every character on the left needs an identical character on the right.
// Therefore:
//   - Characters must mostly come in PAIRS.
//   - Only ONE character can be left without a pair, because it can sit in the center.
//
// Example: s = "abccccdd"
//
//   Character counts:
//     a → 1
//     b → 1
//     c → 4
//     d → 2
//
//   How many pairs can we make?
//     a → 1 → No pair ❌
//     b → 1 → No pair ❌
//     c → 4 → cc + cc → Use 4 ✅
//     d → 2 → dd     → Use 2 ✅
//
//   Total from pairs = 4 + 2 = 6
//
//   Leftover characters: a, b
//   Can we use both? ❌ No. A palindrome can have only ONE center.
//   So use one: 6 + 1 = 7
//
//   Answer = 7 → One possible palindrome: "dccaccd"
//
// ---------------------------------------------------------------------------
// KEY FORMULAS
// ---------------------------------------------------------------------------
//
// 1. ans += (count / 2) * 2;
//
//    This gives the maximum even number of characters we can use from a count.
//    Why even? Because characters must form pairs (aa, bb, cc, ...).
//
//    count = 1 → 1/2 = 0 → 0*2 = 0   (no pair)
//    count = 2 → 2/2 = 1 → 1*2 = 2   (one pair)
//    count = 3 → 3/2 = 1 → 1*2 = 2   (one pair + one leftover)
//    count = 5 → 5/2 = 2 → 2*2 = 4   (two pairs + one leftover)
//
//    So (count / 2) * 2 means:
//    "Give me the maximum number of characters from this frequency
//     that can be arranged in pairs."
//
// 2. if (count % 2 == 1) hasOdd = true;
//
//    After making all possible pairs, is there one character left?
//    If yes, that leftover can potentially become the center.
//
//    But we can use only ONE leftover overall.
//    Suppose: a → 1, b → 1, c → 1 (three odd characters)
//    We cannot use all three as centers. A palindrome has only ONE center.
//
//    So bool hasOdd doesn't COUNT how many odd characters there are.
//    It simply remembers: "Did I find at least one odd character?"
//    If yes → ans++ (add one for the center).
//
// ---------------------------------------------------------------------------

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------------
// APPROACH 1: Sorting-Based (Two Pointer / Grouping)
// ---------------------------------------------------------------------------
// Idea: Sort the string so identical characters are adjacent.
//       Then group consecutive characters and count pairs.
//
// Time Complexity:  O(n log n) due to sorting
// Space Complexity: O(1) (in-place sort, ignoring recursion stack)
// ---------------------------------------------------------------------------
class Solution {
public:
    int longestPalindrome(string s) {

        sort(s.begin(), s.end());  // Step 1: Sort so same characters are together

        int ans = 0;          // Step 2: Initialize answer (length of longest palindrome)
        bool hasOdd = false;  // Step 3: Track if any character has an odd count

        int n = s.length();

        // Step 4: Traverse the sorted string and group identical characters
        for (int i = 0; i < n; ) {

            int j = i;

            // Step 4a: Move j to the end of the current group of same characters
            while (j < n && s[j] == s[i]) {
                j++;
            }

            // Step 4b: Count = number of identical characters in this group
            int count = j - i;

            // Step 4c: Add maximum even number of characters (pairs) to answer
            //          (count / 2) * 2 gives the largest even number ≤ count
            ans += (count / 2) * 2;

            // Step 4d: If count is odd, we have a leftover character
            //          Remember that at least one odd exists (for center)
            if (count % 2 == 1) {
                hasOdd = true;
            }

            // Step 4e: Jump i to j (skip to next group)
            i = j;
        }

        // Step 5: If any character had an odd count, we can place one in the center
        if (hasOdd) {
            ans++;
        }

        return ans;
    }
};


// ---------------------------------------------------------------------------
// APPROACH 2: Hash Map (Frequency Count)
// ---------------------------------------------------------------------------
// Idea: Count frequency of each character using unordered_map.
//       Then compute pairs and check for odd counts.
//
// Time Complexity:  O(n) - single pass to count + single pass over map
// Space Complexity: O(k) - where k = number of unique characters (at most 52 for letters)
// ---------------------------------------------------------------------------
class Solution {
public:
    int longestPalindrome(string s) {

        unordered_map<char, int> freq;  // Step 1: Create a hash map to count frequencies

        // Step 2: Count frequency of each character
        for (char c : s) {
            freq[c]++;
        }

        int ans = 0;          // Step 3: Initialize answer
        bool hasOdd = false;  // Step 4: Track if any odd count exists

        // Step 5: Iterate over each character's frequency in the map
        for (auto it : freq) {
            int count = it.second;  // Get the frequency of this character

            // Step 5a: Add maximum even number (pairs) to answer
            ans += (count / 2) * 2;

            // Step 5b: If frequency is odd, mark hasOdd as true
            if (count % 2 == 1) {
                hasOdd = true;
            }
        }

        // Step 6: Add one for the center if any odd count was found
        if (hasOdd) {
            ans++;
        }

        return ans;
    }
};

// ---------------------------------------------------------------------------
// APPROACH 3: Array-Based Frequency Count (Most Optimal)
// ---------------------------------------------------------------------------
// Idea: Use a fixed-size array of 128 (ASCII size) to count frequencies.
//       This is faster than unordered_map due to no hashing overhead.
//
// Time Complexity:  O(n) - single pass to count + single pass over 128 slots
// Space Complexity: O(1) - fixed array of size 128
// ---------------------------------------------------------------------------
class Solution {
public:
    int longestPalindrome(string s) {

        int freq[128] = {};  // Step 1: Array for all ASCII characters, initialized to 0

        // Step 2: Count frequency of each character
        //         freq['a']++, freq['B']++, etc. (ASCII values used as indices)
        for (char c : s) {
            freq[c]++;
        }

        int ans = 0;          // Step 3: Initialize answer
        bool hasOdd = false;  // Step 4: Track if any odd count exists

        // Step 5: Iterate over all 128 ASCII positions
        for (int i = 0; i < 128; i++) {

            // Step 5a: Add maximum even number (pairs) to answer
            ans += (freq[i] / 2) * 2;

            // Step 5b: If frequency is odd, mark hasOdd as true
            if (freq[i] % 2 == 1) {
                hasOdd = true;
            }
        }

        // Step 6: Add one for the center if any odd count was found
        if (hasOdd) {
            ans++;
        }

        return ans;
    }
};

// ---------------------------------------------------------------------------
// APPROACH 4: Single-Pass Array Count (Compact Version)
// ---------------------------------------------------------------------------
// Time Complexity:  O(n)
// Space Complexity: O(1) - fixed array of size 128
// ---------------------------------------------------------------------------
//
// HOW DOES "ans += 2" KNOW A PAIR IS FORMED?
// -------------------------------------------
//
// Look at what happens when we see the same character repeatedly:
//
//   freq[c]++    →    1 → 2 → 3 → 4 → 5 → 6
//
// Every time frequency becomes EVEN, we have completed a NEW pair:
//
//   frequency    freq % 2    new pair?    ans
//      1            1           ❌         +0
//      2            0           ✅         +2    ← pair 1 formed
//      3            1           ❌         +0
//      4            0           ✅         +2    ← pair 2 formed
//      5            1           ❌         +0
//      6            0           ✅         +2    ← pair 3 formed
//
// So character 'c' occurring 6 times gives:
//   pair 1 → +2,  pair 2 → +2,  pair 3 → +2  →  total +6
//
// That's exactly what this does:
//   if (freq[c] % 2 == 0)  →  "I just completed a pair"
//       ans += 2;           →  "Add those 2 characters to the palindrome"
//
// ---------------------------------------------------------------------------
//
// WHY "if (ans < s.length()) ans++"?
// -----------------------------------
//
// After the loop, 'ans' = total paired characters.
// If ans < s.length(), it means there are leftover unpaired characters.
// We can use exactly ONE of them as the center.
//
// ---------------------------------------------------------------------------
//
// TRACE EXAMPLES
// --------------
//
// Example 1: s = "aaaaa"
//
//   a → freq 1 → odd  → ans = 0
//   a → freq 2 → even → ans = 2
//   a → freq 3 → odd  → ans = 2
//   a → freq 4 → even → ans = 4
//   a → freq 5 → odd  → ans = 4
//
//   After loop: ans = 4, length = 5
//   4 < 5 → true → ans++ → ans = 5
//   Palindrome: "aaaaa"
//
// Example 2: s = "abc"
//
//   a → freq 1 → odd → ans = 0
//   b → freq 1 → odd → ans = 0
//   c → freq 1 → odd → ans = 0
//
//   After loop: ans = 0, length = 3
//   0 < 3 → true → ans++ → ans = 1
//   Palindrome: "a" (or "b" or "c")
//
// Example 3: s = "aabb"
//
//   a → freq 1 → odd  → ans = 0
//   a → freq 2 → even → ans = 2
//   b → freq 1 → odd  → ans = 2
//   b → freq 2 → even → ans = 4
//
//   After loop: ans = 4, length = 4
//   4 < 4 → false → no center needed
//   Palindrome: "abba"
//
// Example 4: s = "abccccdd"
//
//   a → freq 1 → odd  → ans = 0
//   b → freq 1 → odd  → ans = 0
//   c → freq 1 → odd  → ans = 0
//   c → freq 2 → even → ans = 2
//   c → freq 3 → odd  → ans = 2
//   c → freq 4 → even → ans = 4
//   d → freq 1 → odd  → ans = 4
//   d → freq 2 → even → ans = 6
//
//   After loop: ans = 6, length = 8
//   6 < 8 → true → ans++ → ans = 7
//   Palindrome: "dccaccd"
//
// ---------------------------------------------------------------------------
//
// EASIEST WAY TO REMEMBER
// ------------------------
//
// if (freq[c] % 2 == 0)
//     ans += 2;
//
//   → "I just completed a pair → add those 2 characters."
//
// if (ans < s.length())
//     ans++;
//
//   → "If there is at least one character that didn't get paired,
//      use ONE of them as the center."
//
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

class Solution {
public:
    int longestPalindrome(string s) {

        int freq[128] = {};  // Step 1: Frequency array for ASCII characters
        int ans = 0;         // Step 2: Initialize answer (length of longest palindrome)

        // Step 3: For each character, increment its count
        for (char c : s) {

            freq[c]++;

            // Step 3a: Every time freq becomes even, we completed a new pair
            //          Odd → even transition = 1 new pair = +2 characters
            if (freq[c] % 2 == 0) {
                ans += 2;
            }
        }

        // Step 4: If ans < s.length(), at least one unpaired character exists
        //         Use ONE of them as the center of the palindrome
        if (ans < s.length()) {
            ans++;
        }

        return ans;
    }
};

int main(){
    return 0;
}