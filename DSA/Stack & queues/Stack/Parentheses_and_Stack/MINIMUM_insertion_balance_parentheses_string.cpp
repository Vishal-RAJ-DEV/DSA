/*
 * Problem: Minimum Insertions to Balance a Parentheses String
 *
 * Given a string s containing only '(' and ')', find the MINIMUM number
 * of insertions needed to make the string balanced.
 *
 * Balance Rule: Every '(' must be followed by EXACTLY TWO ')' characters.
 *
 * This is DIFFERENT from standard parentheses balancing!
 *   Standard:  "()"   is balanced     (1 pair)
 *   This prob: "())"  is balanced     (1 '(' needs 2 ')')
 *
 * Examples:
 *   s = "(()"        -> Output: 3
 *     Reason: Two '(' but only one ')'. Need 1 more ')' for inner '('
 *             and 2 more ')' for outer '(' = 3 insertions.
 *
 *   s = "())"        -> Output: 0
 *     Reason: One '(' matched with two ')'. Already balanced.
 *
 *   s = "))"         -> Output: 1
 *     Reason: Two ')' but no '('. Need 1 '(' before them to match.
 *
 * ================================================
 * APPROACH 1: Balance Counter (Optimal - O(1) Space)
 * ================================================
 *
 * Intuition:
 *   Instead of using a stack, we use a simple counter `balance` to track
 *   how many unmatched '(' we have seen so far.
 *   Since we only need the COUNT of unmatched '(' (not their order),
 *   a simple counter is sufficient and more memory-efficient.
 *
 * Algorithm:
 *   1. Traverse the string left to right.
 *   2. If '(': increment balance (one more unmatched '(').
 *   3. If ')': check if next char is also ')' to form "))".
 *      - If we have "))": it's a complete pair for one '('.
 *        Decrement balance (if balance > 0), else insert '('.
 *      - If only ")": insert another ')' (ans++), then treat as "))".
 *   4. After loop: every remaining '(' needs 2 ')' -> ans += balance * 2.
 *
 * Time:  O(n) - single pass
 * Space: O(1) - only variables, no stack
 *
 * ================================================
 * APPROACH 2: Stack-based Approach
 * ================================================
 *
 * Intuition:
 *   Use a stack to keep track of unmatched '(' characters.
 *   The logic is identical to Approach 1, but we use a stack
 *   instead of a counter.
 *
 * Algorithm:
 *   1. Traverse the string left to right.
 *   2. If '(': push '(' onto the stack.
 *   3. If ')': check if next char is also ')' to form "))".
 *      - If we have ")): pop one '(' from stack (if not empty),
 *        else insert '('.
 *      - If only ")": insert another ')' (ans++), then treat as "))".
 *   4. After loop: every remaining '(' in stack needs 2 ')' -> ans += stack.size() * 2.
 *
 * Time:  O(n) - single pass
 * Space: O(n) - stack can store up to n '(' characters
 *
 * ================================================
 * WHY BOTH APPROACHES WORK
 * ================================================
 *
 * Both approaches are logically IDENTICAL. The only difference:
 *   - Approach 1: uses `int balance` to count unmatched '('
 *   - Approach 2: uses `stack<char> st` to store unmatched '('
 *
 * Since we only need the COUNT of unmatched '(' (not their order),
 * a simple counter is sufficient and more memory-efficient.
 *
 * ================================================
 * KEY INSIGHT: Handling "))"
 * ================================================
 *
 * Every '(' needs TWO ')' to be balanced.
 * When we see a ')', we must check if the next char is also ')'.
 *
 * Case 1: We see "))" (two consecutive ')')
 *   -> This is a complete pair for ONE '('.
 *   -> If we have an unmatched '(', match it (balance-- or pop).
 *   -> If no unmatched '(', we need to insert '(' (ans++).
 *
 * Case 2: We see only ")" (single ')')
 *   -> This is INCOMPLETE. We need another ')'.
 *   -> Insert one ')' (ans++).
 *   -> Now treat as "))" and match with '('.
 *
 * ================================================
 * DRY RUN 1: s = "(()"
 * ================================================
 *
 * i=0, s[0]='(' -> balance = 1
 * i=1, s[1]='(' -> balance = 2
 * i=2, s[2]=')' -> check i+1: out of bounds -> only one ')'
 *                   ans++ (insert ')') -> ans = 1
 *                   balance > 0 -> balance-- -> balance = 1
 *
 * After loop: ans += balance * 2 = 1 + 1*2 = 3
 *
 * Result: 3 insertions
 *
 * ================================================
 * DRY RUN 2: s = "())"
 * ================================================
 *
 * i=0, s[0]='(' -> balance = 1
 * i=1, s[1]=')' -> check i+1: s[2]=')' -> we have "))"
 *                   i++ (skip next ')') -> i becomes 2
 *                   balance > 0 -> balance-- -> balance = 0
 *
 * i=3: loop ends
 *
 * After loop: ans += balance * 2 = 0 + 0 = 0
 *
 * Result: 0 insertions (already balanced)
 *
 * ================================================
 * DRY RUN 3: s = "))"
 * ================================================
 *
 * i=0, s[0]=')' -> check i+1: s[1]=')' -> we have "))"
 *                   i++ (skip next ')') -> i becomes 1
 *                   balance == 0 -> no '(' to match
 *                   ans++ (insert '(') -> ans = 1
 *
 * i=2: loop ends
 *
 * After loop: ans += balance * 2 = 1 + 0 = 1
 *
 * Result: 1 insertion (insert '(' before "))")
 *
 * ================================================
 * DRY RUN 4: s = "((())"
 * ================================================
 *
 * i=0, s[0]='(' -> balance = 1
 * i=1, s[1]='(' -> balance = 2
 * i=2, s[2]='(' -> balance = 3
 * i=3, s[3]=')' -> check i+1: s[4]=')' -> we have "))"
 *                   i++ (skip next ')') -> i becomes 4
 *                   balance > 0 -> balance-- -> balance = 2
 *
 * i=5: loop ends
 *
 * After loop: ans += balance * 2 = 0 + 2*2 = 4
 *
 * Result: 4 insertions (need 4 more ')' for the 2 unmatched '(')
 *
 * ================================================
 * DRY RUN 5 (Stack Approach): s = "(()"
 * ================================================
 *
 * i=0, s[0]='(' -> push '(' -> stack: ['(']
 * i=1, s[1]='(' -> push '(' -> stack: ['(', '(']
 * i=2, s[2]=')' -> check i+1: out of bounds -> only one ')'
 *                   ans++ (insert ')') -> ans = 1
 *                   stack not empty -> pop -> stack: ['(']
 *
 * After loop: ans += stack.size() * 2 = 1 + 1*2 = 3
 *
 * Result: 3 insertions
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ================================================
// APPROACH 1: Balance Counter (Optimal - O(1) Space)
// ================================================
// Uses a simple integer counter instead of a stack.
// Since we only need the COUNT of unmatched '(',
// a counter is sufficient and more memory-efficient.
class Solution {
public:
    int minInsertions(string s) {
        // `balance` tracks the number of unmatched '(' seen so far
        int balance = 0;

        // `ans` counts the total insertions needed
        int ans = 0;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(') {
                // Found an opening bracket: increment balance
                // This '(' will need two ')' to be matched
                balance++;
            }
            else { // s[i] == ')'
                // Found a closing bracket: check if next char is also ')'
                // to form a complete "))" pair

                if (i + 1 < s.size() && s[i + 1] == ')') {
                    // We found a complete "))" pair (two consecutive ')')
                    // Skip the next ')' since we've consumed it
                    i++;
                }
                else {
                    // Only one ')' found (incomplete pair)
                    // We need to INSERT another ')' to make it ")"
                    ans++;
                }

                // Now we have a complete "))" -- it should match ONE '('
                if (balance > 0) {
                    // We have an unmatched '(' available -> match it
                    balance--;
                }
                else {
                    // No '(' available to match this "))" pair
                    // We need to INSERT one '(' before this "))"
                    ans++;
                }
            }
        }

        // After processing the entire string:
        // Every remaining unmatched '(' needs TWO ')' characters
        // So insert 2 ')' for each unmatched '('
        ans += balance * 2;

        return ans;
    }
};

// ================================================
// APPROACH 2: Stack-based Approach
// ================================================
// Uses a stack to store unmatched '(' characters.
// Logically identical to Approach 1, but uses O(n) space.
class Solution {
public:
    int minInsertions(string s) {
        // Stack to keep track of unmatched '(' characters
        stack<char> st;

        // `ans` counts the total insertions needed
        int ans = 0;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(') {
                // Found an opening bracket: push onto stack
                // This '(' will need two ')' to be matched
                st.push('(');
            }
            else { // s[i] == ')'
                // Found a closing bracket: check if next char is also ')'
                // to form a complete "))" pair

                if (i + 1 < s.size() && s[i + 1] == ')') {
                    // We found a complete "))" pair (two consecutive ')')
                    // Skip the next ')' since we've consumed it
                    i++;
                }
                else {
                    // Only one ')' found (incomplete pair)
                    // We need to INSERT another ')' to make it ")"
                    ans++;
                }

                // Now we have a complete "))" -- it should match ONE '('
                if (!st.empty()) {
                    // We have an unmatched '(' in stack -> match it (pop)
                    st.pop();
                }
                else {
                    // No '(' in stack to match this "))" pair
                    // We need to INSERT one '(' before this "))"
                    ans++;
                }
            }
        }

        // After processing the entire string:
        // Every remaining '(' in stack needs TWO ')' characters
        // So insert 2 ')' for each unmatched '('
        ans += st.size() * 2;

        return ans;
    }
};

int main(){
    return 0;
}

