#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===========================================================================
DRY RUN FOR INPUT: "a1b"
===========================================================================

ASCII for 'a' = 97 (binary: 01100001)
ASCII for 'A' = 65 (binary: 01000001)
Difference: bit 5 (value 32) is the only difference between upper/lower.

Toggle trick: s[i] ^= (1 << 5)   --> XOR with 32 flips that one bit
  'a' ^ 32 = 'A'    (97 ^ 32 = 65)
  '1' is not alpha, so no toggle

RECURSION TREE (index i starts at 0):

backtrack("a1b", i=0)
│
├─► backtrack("a1b", i=1)                  // keep 'a' as-is
│   │
│   ├─► backtrack("a1b", i=2)              // keep '1' as-is (not alpha)
│   │   │
│   │   ├─► backtrack("a1b", i=3)          // keep 'b' as-is
│   │   │   └─► i==3 == size, push "a1b"   ✓ RESULT 1
│   │   │
│   │   └─► toggle 'b' → 'B'
│   │       └─► backtrack("a1B", i=3)      // i==3 == size, push "a1B" ✓ RESULT 2
│   │
│   └─► (s[1]='1' is NOT alpha, no toggle branch)
│
└─► toggle 'a' → 'A'
    └─► backtrack("A1b", i=1)              // 'a' flipped to 'A'
        │
        ├─► backtrack("A1b", i=2)          // keep '1' as-is
        │   │
        │   ├─► backtrack("A1b", i=3)      // keep 'b' as-is
        │   │   └─► push "A1b"             ✓ RESULT 3
        │   │
        │   └─► toggle 'b' → 'B'
        │       └─► push "A1B"             ✓ RESULT 4
        │
        └─► (s[1]='1' is NOT alpha, no toggle branch)

FINAL OUTPUT: ["a1b", "a1B", "A1b", "A1B"]
===========================================================================
*/

class Solution {
    void backtrack(string &s, int i, vector<string> &res) {
        // BASE CASE: we have processed all characters
        if (i == s.size()) {
            res.push_back(s);      // store the current permutation
            return;
        }

        // BRANCH 1: Keep the current character AS-IS, move to next index
        backtrack(s, i + 1, res);

        // BRANCH 2: If current character is a letter, TOGGLE its case
        // and explore that branch too
        if (isalpha(s[i])) {
            // XOR with 32 (1 << 5) toggles bit 5, flipping a↔A, b↔B, etc.
            s[i] ^= (1 << 5);
            backtrack(s, i + 1, res);
        }

        // BACKTRACK: The string is passed by reference, so after toggling
        // and returning from the recursive call, the character must be
        // restored.  XOR is its own inverse: toggling again restores it.
        // We need an explicit toggle-back here because the toggle was
        // done AFTER the first recursive call (branch 1).
        s[i] ^= (1 << 5);
    }
public:
    vector<string> letterCasePermutation(string S) {
        vector<string> res;
        backtrack(S, 0, res);
        return res;
    }
};



int main(){
    return 0;
}
