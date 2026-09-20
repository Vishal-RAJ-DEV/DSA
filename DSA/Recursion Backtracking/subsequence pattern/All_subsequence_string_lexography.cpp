#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
=============================================================================
KEY DIFFERENCES BETWEEN THE THREE APPROACHES
=============================================================================

| Feature            | Approach 1          | Approach 2            | Approach 3            |
|--------------------|---------------------|-----------------------|-----------------------|
| Recursion Style    | Loop-based          | Binary (Include/      | Loop-based            |
|                    | backtracking        | Exclude) recursion    | backtracking          |
| Base Case          | Implicit (loop      | Explicit (idx == n)   | Explicit              |
|                    | ends naturally)     |                       | (idx == s.size())     |
| When res is pushed | At START of each    | At LEAF NODES only    | At LEAF NODES only    |
|                    | call (all nodes)    |                       |                       |
| Includes ""?       | YES (empty string   | YES (all excludes     | NO (loop never        |
|                    | is pushed first)    | path gives "")        | enters with "")       |
| Total output       | 2^n strings         | 2^n strings           | 2^n - 1 strings       |
| Function params    | 4 (no n param)      | 5 (passes n)          | 4 (no n param)        |

SUMMARY:
- Approach 1 and 3 are structurally similar (loop-based backtracking),
  but differ in WHERE res is captured (all nodes vs leaf nodes only).
- Approach 2 is fundamentally different — binary branching without loops.
- All three produce O(2^n) subsequences with O(n * 2^n) total characters.
- Time Complexity: O(n * 2^n) for all (including sorting).
- Space Complexity: O(n) for recursion stack + O(2^n * n) for output storage.
=============================================================================
*/

/*
=============================================================================
APPROACH 1: ITERATIVE BACKTRACKING WITH LOOP (No Base Case)
=============================================================================
- Uses a for-loop to decide which character to pick next from index `start`.
- Pushes current `res` into ans at the START of every recursive call
  (meaning every partial result is a valid subsequence).
- Does NOT have an explicit base case (the loop condition `i < s.size()`
  naturally stops recursion when no more characters are available).
- Key Idea: "At each level, try picking each remaining character one by one."

Example trace for "abc":
  Call 1: res="" -> push ""
    i=0: res="a" -> Call 2
      push "a", i=1: res="ab" -> Call 3
        push "ab", i=2: res="abc" -> Call 4
          push "abc", loop ends, return
        pop 'c', back to Call 3
      pop 'b', back to Call 2
      i=2: res="ac" -> Call 3
        push "ac", loop ends, return
      pop 'c', back to Call 2
    pop 'a', back to Call 1
    i=1: res="b" -> Call 2
      push "b", i=2: res="bc" -> Call 3
        push "bc", loop ends, return
      pop 'c', back to Call 2
    pop 'b', back to Call 1
    i=2: res="c" -> Call 2
      push "c", loop ends, return
    pop 'c', back to Call 1

Time Complexity:  O(2^n) — each character is either included or not, 
                   total 2^n subsequences (including empty string).
                   Sorting adds O(2^n * n * log(2^n)) = O(n * 2^n).
Space Complexity: O(n) recursion stack depth (max depth = n).
                  O(2^n * n) for storing all subsequences in ans vector.
=============================================================================
*/
class Solution {
public:
    void generate(int start, string &s, string &res, vector<string> &ans) {
        // Every current res is a valid subsequence
        ans.push_back(res);

        for (int i = start; i < s.size(); i++) {
            res.push_back(s[i]);

            generate(i + 1, s, res, ans);

            res.pop_back();   // backtrack
        }
    }

    vector<string> AllPossibleStrings(string s) {
        vector<string> ans;
        string res = "";

        generate(0, s, res, ans);
        sort(ans.begin(), ans.end());  // Sort final results lexicographically

        return ans;
    }
};


/*
=============================================================================
APPROACH 2: CLASSIC INCLUDE/EXCLUDE BINARY RECURSION
=============================================================================
- At each index, makes exactly 2 binary choices: INCLUDE s[idx] or EXCLUDE s[idx].
- Has an explicit base case: when idx == n (reached end of string), push res to ans.
- No for-loop — pure binary branching recursion tree.
- Key Idea: "For each character, either take it or skip it."

Example trace for "abc":
  generate(0, "", ...):
    Choice 1: Include 'a' -> generate(1, "a", ...)
      Choice 1: Include 'b' -> generate(2, "ab", ...)
        Choice 1: Include 'c' -> generate(3, "abc", ...) -> idx==3, push "abc"
        Choice 2: Exclude 'c' -> generate(3, "ab", ...) -> idx==3, push "ab"
      Choice 2: Exclude 'b' -> generate(2, "a", ...)
        Choice 1: Include 'c' -> generate(3, "ac", ...) -> idx==3, push "ac"
        Choice 2: Exclude 'c' -> generate(3, "a", ...)  -> idx==3, push "a"
    Choice 2: Exclude 'a' -> generate(1, "", ...)
      Choice 1: Include 'b' -> generate(2, "b", ...)
        Choice 1: Include 'c' -> generate(3, "bc", ...) -> idx==3, push "bc"
        Choice 2: Exclude 'c' -> generate(3, "b", ...)  -> idx==3, push "b"
      Choice 2: Exclude 'b' -> generate(2, "", ...)
        Choice 1: Include 'c' -> generate(3, "c", ...) -> idx==3, push "c"
        Choice 2: Exclude 'c' -> generate(3, "", ...)  -> idx==3, push ""

Time Complexity:  O(2^n) — binary tree with n levels, 2^n leaf nodes.
                   Sorting adds O(2^n * n * log(2^n)) = O(n * 2^n).
Space Complexity: O(n) recursion stack depth (max depth = n).
                  O(2^n * n) for storing all subsequences in ans vector.
=============================================================================
*/
class Solution {
  public:
    void generate(int idx, int n, string &s, string &res, vector<string> &ans) {
        if (idx == n) {
            ans.push_back(res);
            return;
        }

        // Choice 1: Include s[idx]
        res.push_back(s[idx]);
        generate(idx + 1, n, s, res, ans);
        res.pop_back(); // Backtrack

        // Choice 2: Exclude s[idx]
        generate(idx + 1, n, s, res, ans);
    }

    vector<string> powerSet(string &s) {
        int n = s.size();

        vector<string> ans;
        string res = "";

        generate(0, n, s, res, ans);

        // Sort final results lexicographically
        sort(ans.begin(), ans.end());

        return ans;
    }
};

/*
=============================================================================
APPROACH 3: ITERATIVE BACKTRACKING WITH EXPLICIT BASE CASE
=============================================================================
- Similar to Approach 1 (uses a for-loop), but adds an EXPLICIT base case
  (idx == s.size()) to push res and return.
- The difference from Approach 1: Approach 1 pushes res at the START of each
  call (before the loop), while Approach 3 pushes res only at the BASE CASE
  (leaf nodes of recursion tree).
- Key Idea: "Same loop-based backtracking as Approach 1, but only captures
  subsequences at leaf nodes (complete paths)."

Example trace for "abc":
  generate(0, "", ...):
    i=0: res="a" -> generate(1, ...)
      i=1: res="ab" -> generate(2, ...)
        i=2: res="abc" -> generate(3, ...)
          idx==3, push "abc", return
        pop 'c'
      pop 'b'
      i=2: res="ac" -> generate(3, ...)
        idx==3, push "ac", return
      pop 'c'
    pop 'a'
    i=1: res="b" -> generate(2, ...)
      i=2: res="bc" -> generate(3, ...)
        idx==3, push "bc", return
      pop 'c'
    pop 'b'
    i=2: res="c" -> generate(3, ...)
      idx==3, push "c", return
    pop 'c'

    NOTE: Empty string "" is NOT included in output (unlike Approach 1 & 2),
    because we only push at leaf nodes, and no character is added means
    we never reach the base case with res="" through the loop.

Time Complexity:  O(2^n) — same recursion structure as Approach 1.
                   Sorting adds O(2^n * n * log(2^n)) = O(n * 2^n).
Space Complexity: O(n) recursion stack depth (max depth = n).
                  O(2^n * n) for storing all subsequences in ans vector.
=============================================================================
*/
class Solution {
public:
    void generate(int idx, string &s, string &res, vector<string> &ans) {
        
        if (idx == s.size()) {
            ans.push_back(res);
            return;
        }

        for (int i = idx; i < s.size(); i++) {
            res.push_back(s[i]);

            generate(i + 1, s, res, ans);

            res.pop_back();
        }
    }

    vector<string> AllPossibleStrings(string s) {
        vector<string> ans;
        string res = "";

        generate(0, s, res, ans);

        sort(ans.begin(), ans.end());

        return ans;
    }
};



int main(){
    return 0;
}