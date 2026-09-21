#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===========================================================================
PROBLEM: Check If All Characters Have Equal Occurrences
===========================================================================
Given a string s, determine if every character in the string appears
the same number of times. Return true if all characters have equal
frequency, false otherwise.

This is a string hashing / frequency counting problem.

Examples:
  s = "aabb"    → 'a':2, 'b':2 → all equal → true
  s = "aabc"    → 'a':2, 'b':1, 'c':1 → NOT all equal → false
  s = "abc"     → 'a':1, 'b':1, 'c':1 → all equal → true
  s = "aaabbb"  → 'a':3, 'b':3 → all equal → true
  s = "aaabbbccc" → 'a':3, 'b':3, 'c':3 → all equal → true
  s = "aaabbbcccd" → 'a':3, 'b':3, 'c':3, 'd':1 → false
  s = "a"       → only one character → true (trivially equal)
===========================================================================

===========================================================================
LOGIC: FREQUENCY MAP + COMPARISON
===========================================================================

Step 1: Count frequency of each character using a map
  - Iterate through string, increment count for each character

Step 2: Get the frequency of the first character as reference
  - first = mp[s[0]]

Step 3: Check if ALL other characters have the same frequency
  - If any character's count differs from `first`, return false

Step 4: If all match, return true

TIME:  O(n) — one pass to count, one pass to check
SPACE: O(1) — map stores at most 26 entries (lowercase letters)
               or 128 entries (ASCII), which is constant
===========================================================================

===========================================================================
TEST CASES:
===========================================================================

  Test 1: s = "aabb"
    Map: {'a':2, 'b':2}
    first = mp['a'] = 2
    Check: 'a'→2==2✓, 'b'→2==2✓ → return true

  Test 2: s = "aabc"
    Map: {'a':2, 'b':1, 'c':1}
    first = mp['a'] = 2
    Check: 'a'→2==2✓, 'b'→1≠2✗ → return false

  Test 3: s = "abc"
    Map: {'a':1, 'b':1, 'c':1}
    first = mp['a'] = 1
    Check: all == 1 → return true

  Test 4: s = "aaabbbccc"
    Map: {'a':3, 'b':3, 'c':3}
    first = mp['a'] = 3
    Check: all == 3 → return true

  Test 5: s = "a"
    Map: {'a':1}
    first = mp['a'] = 1
    Only one entry in map, no mismatches → return true

  Test 6: s = "aaabbbcccd"
    Map: {'a':3, 'b':3, 'c':3, 'd':1}
    first = mp['a'] = 3
    Check: 'd'→1≠3 → return false
===========================================================================

*/

class Solution {
public:
    bool areOccurrencesEqual(string s) {
        // Step 1: Build frequency map of each character
        map<char, int> mp;
        for (auto c : s) {
            mp[c]++;
        }

        // Step 2: Store the frequency of the first character as reference
        int first = mp[s[0]];

        // Step 3: Check if every character's frequency matches `first`
        for (auto pair : mp) {
            if (pair.second != first) {
                return false;  // Found a character with different frequency
            }
        }

        // Step 4: All characters have equal frequency
        return true;
    }
};

int main(){
    return 0;
}
