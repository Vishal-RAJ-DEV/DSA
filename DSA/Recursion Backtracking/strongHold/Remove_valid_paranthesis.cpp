#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
 * PROBLEM: Remove Invalid Parentheses (LeetCode 301)
 * 
 * Given a string s containing parentheses and letters, remove the minimum number of
 * invalid parentheses to make the input string valid. Return all possible results.
 * 
 * APPROACH: Backtracking with pruning
 * 
 * KEY INSIGHTS:
 * 1. First pass: Count minimum removals needed (leftRemove, rightRemove)
 *    - Traverse string, track unmatched '(' count
 *    - When seeing ')', if there's unmatched '(', match it; else it's an extra ')'
 * 
 * 2. Second pass: Backtrack to generate all valid strings
 *    - At each index, we have 2 choices: REMOVE or KEEP the character
 *    - Only explore paths that can lead to valid results
 *    - Prune duplicates: skip consecutive same parentheses when removing
 * 
 * PRUNING OPTIMIZATIONS:
 * - Skip removing '(' if previous char was also '(' (avoids duplicate results)
 * - Skip removing ')' if previous char was also ')' (avoids duplicate results)
 * - Only keep ')' if balance > 0 (can't have more ')' than '(' at any point)
 * - At end: only accept if leftRemove==0, rightRemove==0, balance==0
 */

class Solution {
public:
    vector<string> ans;  // Stores all valid results

    /**
     * Recursive backtracking function
     * @param s: Input string
     * @param idx: Current index in string
     * @param leftRemove: Number of '(' still needed to remove
     * @param rightRemove: Number of ')' still needed to remove
     * @param balance: Current open parentheses count (unmatched '(')
     * @param curr: Current string being built
     */
    void solve(string& s, int idx, int leftRemove, int rightRemove, int balance, string& curr) {

        // BASE CASE: Reached end of string
        if (idx == s.size()) {
            // Valid result only if all removals used AND parentheses balanced
            if (leftRemove == 0 && rightRemove == 0 && balance == 0) {
                ans.push_back(curr);
            }
            return;
        }

        char ch = s[idx];

        // ============================================
        // OPTION 1: REMOVE current character
        // ============================================
        
        // Remove '(' if we still need to remove left parentheses
        // PRUNING: Skip if previous char was also '(' (avoids duplicates)
        // Check: idx==0 (first char) OR prev char in s != '(' OR curr empty OR last char in curr != '('
        if (ch == '(' && leftRemove > 0) {
            if (idx == 0 || s[idx - 1] != '(' || curr.empty() || curr.back() != '(') {
                solve(s, idx + 1, leftRemove - 1, rightRemove, balance, curr);
            }
        }

        // Remove ')' if we still need to remove right parentheses
        // PRUNING: Skip if previous char was also ')' (avoids duplicates)
        if (ch == ')' && rightRemove > 0) {
            if (idx == 0 || s[idx - 1] != ')' || curr.empty() || curr.back() != ')') {
                solve(s, idx + 1, leftRemove, rightRemove - 1, balance, curr);
            }
        }

        // ============================================
        // OPTION 2: KEEP current character
        // ============================================
        
        if (ch == '(') {
            // Keep '(': add to curr, increase balance
            curr.push_back('(');
            solve(s, idx + 1, leftRemove, rightRemove, balance + 1, curr);
            curr.pop_back();  // Backtrack

        }
        else if (ch == ')') {
            // Keep ')': ONLY if balance > 0 (valid to close)
            // Can't have more ')' than '(' at any point
            if (balance > 0) {
                curr.push_back(')');
                solve(s, idx + 1, leftRemove, rightRemove, balance - 1, curr);
                curr.pop_back();  // Backtrack
            }
            // If balance == 0, keeping this ')' would make string invalid, so skip

        }
        else {
            // Non-parenthesis character: always keep (letters don't affect validity)
            curr.push_back(ch);
            solve(s, idx + 1, leftRemove, rightRemove, balance, curr);
            curr.pop_back();  // Backtrack
        }
    }

    /**
     * Main function to remove invalid parentheses
     * @param s: Input string with parentheses and letters
     * @return: Vector of all valid strings with minimum removals
     */
    vector<string> removeInvalidParentheses(string s) {

        // ============================================
        // PASS 1: Calculate minimum removals needed
        // ============================================
        int leftRemove = 0;   // Count of '(' to remove
        int rightRemove = 0;  // Count of ')' to remove

        for (char ch : s) {
            if (ch == '(') {
                leftRemove++;  // Potential unmatched '('
            }
            else if (ch == ')') {
                if (leftRemove > 0) {
                    leftRemove--;  // Match with previous '('
                }
                else {
                    rightRemove++;  // Extra ')' with no matching '('
                }
            }
        }
        // After this loop:
        // leftRemove = number of unmatched '(' to remove
        // rightRemove = number of unmatched ')' to remove

        // ============================================
        // PASS 2: Backtrack to generate all valid results
        // ============================================
        string curr;
        solve(s, 0, leftRemove, rightRemove, 0, curr);

        // ============================================
        // POST-PROCESSING: Remove duplicates & sort
        // ============================================
        // The duplicate pruning in solve() handles most cases,
        // but this ensures complete uniqueness
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        return ans;
    }
};


int main(){
    return 0;
}