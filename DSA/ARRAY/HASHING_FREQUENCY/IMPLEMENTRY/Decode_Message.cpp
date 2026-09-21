#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===========================================================================
PROBLEM: DECODE THE MESSAGE (LeetCode 2325)
===========================================================================
You are given a key string and a message string.

The key defines a substitution cipher mapping:
  - The FIRST unique character in the key maps to 'a'
  - The SECOND unique character maps to 'b'
  - The THIRD unique character maps to 'c'
  - ... and so on through 'z'
  - Spaces in the key are IGNORED (not mapped)

Using this mapping, decode the message:
  - Replace each character in the message with its mapped letter
  - Spaces in the message remain as spaces

Example:
  key   = "the quick brown fox jumps over the lazy dog"
  message = "vkbs bs tummu qrv"

  Building mapping from key (first occurrence of each unique char):
    t → a    (1st unique char)
    h → b    (2nd unique char)
    e → c    (3rd unique char)
    q → d    (4th)
    u → e    (5th)
    i → f    (6th)
    c → g    (7th)
    k → h    (8th)
    b → i    (9th)
    r → j    (10th)
    o → k    (11th)
    w → l    (12th)
    n → m    (13th)
    f → n    (14th)
    x → o    (15th)
    j → p    (16th)
    m → q    (17th)
    p → r    (18th)
    s → s    (19th)
    v → t    (20th)
    l → u    (21st)
    a → v    (22nd)
    z → w    (23rd)
    y → x    (24th)
    d → y    (25th)
    g → z    (26th)

  Decode message:
    v → t, k → h, b → i, s → s  → "this"
    (space)
    b → i, s → s                → "is"
    (space)
    t → a                       → "a"
    (space)
    t → a, u → e, m → q, m → q, u → e → "aqqqe" 

  Wait — let me re-check the actual example mapping...
  
  Actually for the standard LeetCode example:
  message "vkbs bs tummu qrv" decodes to "this is a test"
  v→t, k→h, b→i, s→s, (space), b→i, s→s, (space), 
  t→a, (space), t→a, e→c, s→s, t→a → "a acsa"?? 

  Let me use a simpler example for clarity below.
===========================================================================

===========================================================================
SIMPLER EXAMPLE:
===========================================================================
  key     = "abc abc"
  message = "xyz"

  Mapping from key (first unique chars in order):
    a → 1st unique → 'a'
    b → 2nd unique → 'b'
    c → 3rd unique → 'c'

  Decode "xyz": x→?, y→?, z→? — these aren't in the mapping!
  
  Better example:
  key     = " hello world "
  message = "heo"

  Mapping:
    h → a   (1st unique: 'h')
    e → b   (2nd unique: 'e')
    l → c   (3rd unique: 'l')
    o → d   (4th unique: 'o')
    w → e   (5th unique: 'w')
    r → f   (6th unique: 'r')
    d → g   (7th unique: 'd')

  Decode "heo":
    h → a
    e → b
    o → d
  Result: "abd"
===========================================================================

===========================================================================
APPROACH: HASH MAP SUBSTITUTION CIPHER
===========================================================================

Step 1: Build the mapping
  - Traverse the key character by character
  - Use a map<char, char> to store the substitution
  - Start with temp = 'a'
  - For each character in key:
      If it's NOT a space AND not already in the map:
          mp[key[i]] = temp
          temp++
  This ensures we only map the FIRST occurrence of each unique character

Step 2: Decode the message
  - For each character in message:
      If it's NOT a space: replace with mp[character]
      If it IS a space: keep as space

TIME:  O(n + m) where n = key length, m = message length
SPACE: O(1) — at most 26 entries in the map (a-z)
===========================================================================

*/

class Solution {
public:
    string decodeMessage(string k, string m) {

        // Step 1: Build substitution mapping from the key
        map<char, char> mp;
        char temp = 'a';  // Start mapping from 'a'

        for (int i = 0; i < k.length(); i++) {
            // Only map if: (1) not a space, (2) first time seeing this char
            if (k[i] != ' ' && mp.find(k[i]) == mp.end()) {
                mp[k[i]] = temp;  // Map this unique char to current letter
                temp++;           // Move to next letter ('b', 'c', ...)
            }
        }

        // Step 2: Decode the message using the mapping
        string res = "";

        for (int i = 0; i < m.length(); i++) {
            if (m[i] != ' ') {
                res += mp[m[i]];  // Replace character with its mapping
            }
            else {
                res += " ";       // Preserve spaces in the message
            }
        }

        return res;
    }
};


int main(){
    return 0;
}
