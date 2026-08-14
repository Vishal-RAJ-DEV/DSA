// LeetCode 316: Remove Duplicate Letters
// Given a string s, remove duplicate letters so that every letter appears
// once and only once. You must make sure your result is the smallest in
// lexicographical order among all possible results.
//
// ============================================================
// INTUITION:
// ============================================================
// - We need each letter exactly once → use a used[] array to track
// - We want smallest lexicographic order → use a MONOTONIC INCREASING STACK
// - KEY INSIGHT: If a character is smaller than stack's top, and the top
//   character appears LATER in the string, we can POP the top to get
//   a smaller result. This is because we can re-add the top character later.
//
// ============================================================
// CORE LOGIC (Same for both approaches):
// ============================================================
// 1. Count total frequency of each character (how many times it appears)
// 2. Iterate through the string:
//    a. Decrement frequency (we've processed one occurrence)
//    b. If character already in stack → skip (avoid duplicates)
//    c. While stack top > current char AND stack top appears later (freq > 0):
//       → Pop the top (remove it to make room for smaller current char)
//    d. Push current character, mark as used
// 3. Return stack content as string
//
// ============================================================
// DRY RUN (s = "bcabc"):
// ============================================================
// freq initially: a=1, b=2, c=2
//
// Step 1: c='b', freq[b]=1, used[b]=false
//   → stack empty, push 'b'. stack=[b]
//
// Step 2: c='c', freq[c]=1, used[c]=false
//   → 'c' > 'b', no pop. push 'c'. stack=[b,c]
//
// Step 3: c='a', freq[a]=1, used[a]=false
//   → 'c' > 'a' but freq[c]=0 → can't pop (no more 'c' later)
//   → 'b' > 'a' and freq[b]=1>0 → POP 'b' (will appear later)
//   → push 'a'. stack=[a]
//
// Step 4: c='b', freq[b]=0, used[b]=false
//   → push 'b'. stack=[a,b]
//
// Step 5: c='c', freq[c]=0, used[c]=false
//   → push 'c'. stack=[a,b,c]
//
// Result: "abc" (lexicographically smallest with all distinct letters)
//
// ============================================================
// APPROACH 1: Monotonic Stack with String as Stack
// ============================================================
// - Uses a string directly as the stack (st.back(), st.pop_back())
// - Cleaner implementation, no conversion needed
// - Time: O(n), Space: O(1) extra (string is the result)
//
// ============================================================
// APPROACH 2: Monotonic Stack with Actual Stack
// ============================================================
// - Uses stack<char> st (st.top(), st.pop())
// - Needs reverse at end to convert stack to string
// - Time: O(n), Space: O(n) extra (stack + result string)
//
// Both approaches are O(n) time and produce the same result.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// APPROACH 1: Monotonic Stack with String as Stack (Cleaner)
// ============================================================
class Solution1 {
public:
    string removeDuplicateLetters(string s) {
        vector<int> freq(26, 0);     // count remaining occurrences of each character
        vector<bool> used(26, false); // track which characters are already in result

        // Step 1: Count total frequency of each character
        for (char c : s)
            freq[c - 'a']++;

        string st;  // string used as a stack (st.back() = top, st.pop_back() = pop)

        // Step 2: Process each character
        for (char c : s) {
            freq[c - 'a']--;  // decrement remaining frequency

            if (used[c - 'a'])  // if already in result, skip it
                continue;

            // Step 3: Pop larger characters that appear later
            // While stack is not empty, top > current, and top appears later in string
            while (!st.empty() &&
                   st.back() > c &&
                   freq[st.back() - 'a'] > 0) {

                used[st.back() - 'a'] = false;  // mark as unused (will be re-added later)
                st.pop_back();  // remove from stack
            }

            st.push_back(c);  // push current character
            used[c - 'a'] = true;  // mark as used
        }

        return st;  // string is already in correct order (no reverse needed)
    }
};

// ============================================================
// APPROACH 2: Monotonic Stack with Actual Stack
// ============================================================
class Solution2 {
public:
    string removeDuplicateLetters(string s) {
        vector<int> freq(26, 0);  // count remaining occurrences

        // Step 1: Count total frequency of each character
        for (char c : s) {
            freq[c - 'a']++;
        }

        stack<char> st;  // actual stack
        vector<bool> used(26, false);  // track which characters are in result

        // Step 2: Process each character
        for (char c : s) {
            freq[c - 'a']--;  // decrement remaining frequency

            if (used[c - 'a']) {  // already in answer, skip
                continue;
            }

            // Step 3: Remove bigger characters if they can appear again later
            while (!st.empty() &&
                   st.top() > c &&
                   freq[st.top() - 'a'] > 0) {

                used[st.top() - 'a'] = false;  // mark as unused
                st.pop();  // remove from stack
            }

            st.push(c);  // push current character
            used[c - 'a'] = true;  // mark as used
        }

        // Step 4: Convert stack to string (stack is LIFO, so reverse)
        string ans;
        while (!st.empty()) {
            ans += st.top();
            st.pop();
        }

        reverse(ans.begin(), ans.end());  // reverse to get correct order

        return ans;
    }
};

int main(){
    // Example usage:
    // Solution1 sol;
    // cout << sol.removeDuplicateLetters("bcabc") << endl;  // Output: "abc"
    // cout << sol.removeDuplicateLetters("cbacdcbc") << endl;  // Output: "acdb"
    return 0;
}