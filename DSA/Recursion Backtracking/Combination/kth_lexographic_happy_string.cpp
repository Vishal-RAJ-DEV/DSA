#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
===========================================================================
PROBLEM: Kth Lexicographically Smallest Happy String
===========================================================================
A "happy string" is a string that:
  1. Contains only characters 'a', 'b', 'c'
  2. No two adjacent characters are the same

Given n (length) and k (1-indexed position), find the kth happy string
in lexicographic order. If fewer than k exist, return "".

Example: n=3 → all happy strings in order:
  "aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb",
  "cab", "cac", "cba", "cbc"
  → k=1 → "aba", k=5 → "bab", k=10 → "cac"
===========================================================================

===========================================================================
APPROACH 1: BRUTE FORCE — Generate All, Then Pick kth
===========================================================================
Idea:
  - Generate every possible happy string of length n using recursion.
  - Since we try 'a' → 'b' → 'c' in order, results are naturally
    in lexicographic order.
  - Store all results in a vector, then return result[k-1].

Flow:
  solve(n, current, result)
    if current.length == n:
        push current into result, return
    for ch in {'a','b','c'}:
        if ch == last char of current → skip (adjacent rule)
        push ch → recurse → pop_back (backtrack)

  getHappyString(n, k):
    solve(..., result)
    if result.size() < k → return ""
    return result[k-1]

Pros: Simple and correct.
Cons: Generates ALL happy strings even if k=1 (wasteful for large n).
       Space: O(26^n) worst case to store all strings.
===========================================================================

===========================================================================
APPROACH 2: EARLY TERMINATION — Stop As Soon As kth Is Found
===========================================================================
Idea:
  - Instead of generating all strings, maintain a running `count`.
  - Each time a complete string is formed (length == n), increment count.
  - When count == k, save the result and STOP exploring further.

This is a performance optimization — we avoid generating strings after
the kth one is found.

Key question: WHY is pop_back() called BEFORE the early-termination check?

  The function explores branches like this:

    for ch in {'a','b','c'}:
        push ch            // DO
        recurse            // EXPLORE
        pop_back           // UNDO (backtrack)
        if result found → return   // STOP

  The pop_back() MUST happen before the check because:

  1. BACKTRACK FIRST: We must always undo the state change before
     deciding whether to stop. If we checked BEFORE pop_back, the
     string would still contain the character we just explored, and
     the state would be inconsistent for any remaining logic.

  2. PROPAGATION: When the kth string is found deep in recursion,
     result gets assigned. Then every parent call returns here,
     sees result is non-empty, and also returns — unwinding the
     entire call stack instantly.

  Dry run for n=2, k=3:

    solve(n=2, current="", count=0, k=3, result="")
    │
    ├─ push 'a' → solve(n=2, current="a", ...)
    │   ├─ push 'b' → solve(n=2, current="ab", ...)  → length==2, count=1
    │   │   pop_back → current="a", result still ""
    │   │   result empty → continue loop
    │   ├─ push 'c' → solve(n=2, current="ac", ...)  → length==2, count=2
    │   │   pop_back → current="a", result still ""
    │   │   result empty → continue loop
    │   │   loop ends
    │   pop_back → current="", result still ""
    │   result empty → continue loop
    │
    ├─ push 'b' → solve(n=2, current="b", ...)
    │   ├─ push 'a' → solve(n=2, current="ba", ...)  → length==2, count=3 == k!
    │   │   result = "ba"  ← FOUND!
    │   │   return
    │   pop_back → current="b"
    │   ★ result NOT empty → return immediately! (skip 'c' branch)
    │
    pop_back → current=""
    ★ result NOT empty → return immediately! (skip remaining iterations)

    Final result: "ba"  ✓  (3rd happy string: "ab", "ac", "ba")

  The early termination saved us from generating:
    "bc", "ca", "cb" — completely skipped!
===========================================================================

*/

class Solution {
public:

    // ---------- APPROACH 1: Generate all, pick kth ----------

    void solve(int n, string &current, vector<string> &result) {

        // BASE CASE: string is complete, store it
        if (current.length() == n) {
            result.push_back(current);
            return;
        }

        // Try 'a', 'b', 'c' in order (ensures lexicographic order)
        for (char ch = 'a'; ch <= 'c'; ch++) {

            // RULE: Adjacent characters cannot be equal
            if (!current.empty() && current.back() == ch) {
                continue;
            }

            // DO: Add character to current string
            current.push_back(ch);

            // EXPLORE: Recurse to fill the next position
            solve(n, current, result);

            // UNDO (backtrack): Remove last character so we can try next option
            current.pop_back();
        }
    }

    string getHappyString(int n, int k) {

        string current;
        vector<string> result;

        // Generate ALL happy strings (in lex order)
        solve(n, current, result);

        // If fewer than k happy strings exist, return empty
        if (result.size() < k) {
            return "";
        }

        // k is 1-indexed, so return (k-1)th element
        return result[k - 1];
    }
};

class Solution2 {
public:

    // ---------- APPROACH 2: Early termination when kth is found ----------

    void solve(int n, string &current, int &count, int k, string &result) {

        // BASE CASE: string of length n is complete
        if (current.length() == n) {

            count++;  // Count this as a valid happy string

            // If this is the kth one, save it
            if (count == k) {
                result = current;
            }

            return;
        }

        // Try 'a', 'b', 'c' in order (lexicographic order)
        for (char ch = 'a'; ch <= 'c'; ch++) {

            // RULE: Adjacent characters cannot be equal
            if (!current.empty() && current.back() == ch) {
                continue;
            }

            // DO: Add character
            current.push_back(ch);

            // EXPLORE: Recurse to next position
            solve(n, current, count, k, result);

            // UNDO (backtrack): Remove character before checking termination
            // This ensures the string state is clean before we decide to stop
            current.pop_back();

            // EARLY STOP: If result is already found, stop exploring
            // remaining branches. This propagates up the entire call stack,
            // aborting all pending iterations in parent calls too.
            if (!result.empty()) {
                return;
            }
        }
    }

    string getHappyString(int n, int k) {

        string current;
        string result;    // Single string, not a vector

        int count = 0;    // Tracks how many happy strings we've seen so far

        solve(n, current, count, k, result);

        return result;    // Returns "" if k was too large
    }
};




int main(){
    return 0;
}
