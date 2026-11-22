#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
712. Minimum ASCII Delete Sum for Two Strings⚡ Medium Priority
Companies
Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:

Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
Example 2:

Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d] + 101[e] + 101[e] to the sum.
Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.

*/
class Solution {
public:
    // =====================================================================
    // PROBLEM: 712. Minimum ASCII Delete Sum for Two Strings
    // ---------------------------------------------------------------------
    // We may delete any characters from s1 and/or s2. After the deletions
    // both strings must become EQUAL. Among all such ways, find the minimum
    // total ASCII value of the deleted characters.
    //
    // =====================================================================
    // KEY INTUITION (very important - read this first)
    // =====================================================================
    // Suppose after deleting some characters both strings become the SAME
    // string "X". That means:
    //
    //      X is a COMMON SUBSEQUENCE of s1 and s2.
    //
    // Conversely, if we pick any common subsequence X, we can delete the
    // remaining characters of s1 and s2 and both strings become X.
    //
    // So the problem is equivalent to:
    //      "Pick a common subsequence X such that
    //       (sum of all chars of s1) + (sum of all chars of s2)
    //       - 2 * (sum of all chars of X)   is MINIMISED"
    //
    // Why subtract 2 * sum(X)?
    // ------------------------
    // Let total = sum(s1) + sum(s2)   (sum of ASCII of every character of
    // both strings).
    //
    // Every character of X is kept in BOTH strings, so it is NOT deleted
    // from either string. Its ASCII value was counted ONCE in total for s1
    // and ONCE again for s2, i.e. counted TWICE, but it is deleted ZERO
    // times. So we must remove 2 * (its value) from total.
    //
    // Every character NOT in X is deleted from whichever string(s) it lies
    // in - its value stays in total exactly once per occurrence = it is
    // counted as deleted.
    //
    //   => Deleted sum = total - 2 * sum(X)
    //
    // To MINIMISE the deleted sum we must MAXIMISE sum(X), i.e. we need the
    // common subsequence with the MAXIMUM total ASCII value.
    //
    // That is exactly "Weighted Longest Common Subsequence" where the
    // WEIGHT of each matched character is its ASCII value (instead of 1
    // as in the classic LCS length problem).
    // =====================================================================
    //
    // =====================================================================
    // DP DEFINITION
    // =====================================================================
    // dp[i][j] = maximum ASCII sum of a common subsequence of
    //            s1[0..i-1]  and  s2[0..j-1]
    //            (i.e. the first i chars of s1 and first j chars of s2)
    //
    // Base case: dp[0][j] = dp[i][0] = 0
    //   If one string is empty, no character can be common -> sum = 0.
    //   This is why the table is initialised with all zeros.
    //
    // =====================================================================
    // TRANSITION (the recurrence)
    // =====================================================================
    // Case 1: s1[i-1] == s2[j-1]   (characters MATCH)
    //   We can USE this matching pair in our common subsequence.
    //   Its ASCII value is added, plus the best we could do with the
    //   remaining prefixes:
    //       dp[i][j] = s1[i-1] + dp[i-1][j-1]
    //   (Note: unlike LCS-length, here we ADD the character's ASCII value,
    //    not 1 - this is the "weighted" part.)
    //
    // Case 2: s1[i-1] != s2[j-1]   (characters DIFFER)
    //   This pair cannot both be kept together, so we DISCARD at least one
    //   of them and take the best of the two options:
    //       dp[i][j] = max( dp[i-1][j] ,   // drop s1[i-1]
    //                      dp[i][j-1] )    // drop s2[j-1]
    //   We do NOT add anything because nothing new is matched.
    //
    // =====================================================================
    // FINAL ANSWER
    // =====================================================================
    //   total   = sum of ASCII of all characters of s1 and s2
    //   answer  = total - 2 * dp[n][m]
    //
    //   dp[n][m] = max ASCII sum of common subsequence of the FULL strings
    //              = sum(X) for the best X
    //   total - 2*sum(X) = minimum ASCII sum of deleted characters.
    // =====================================================================
    //
    // =====================================================================
    // DRY RUN - Example 1: s1 = "sea", s2 = "eat"
    // =====================================================================
    // total = (s+e+a) + (e+a+t) = 115+101+97 + 101+97+116 = 627
    // Best common subsequence X = "ea"  (sum = 101 + 97 = 198)
    // answer = 627 - 2*198 = 627 - 396 = 231   <- matches expected output
    // (Deleted: 's' from "sea" = 115, 't' from "eat" = 116 -> 115+116=231)
    //
    // DRY RUN - Example 2: s1 = "delete", s2 = "leet"
    // total = (d+e+l+e+t+e) + (l+e+e+t)
    //       = (100+101+108+101+116+101) + (108+101+101+116)
    //       = 627 + 426 = 1053
    // Best common subsequence X = "let" (sum = 108+101+116 = 325)
    // answer = 1053 - 2*325 = 1053 - 650 = 403   <- matches expected output
    // (Deleted: "dee" from "delete" = 100+101+101 = 302,
    //           "e"   from "leet"     = 101        -> 302+101 = 403)
    // =====================================================================
    //
    // =====================================================================
    // COMPLEXITY
    // =====================================================================
    // Time  : O(n * m)  - two nested loops fill the (n+1)*(m+1) table
    // Space : O(n * m)  - the 2D dp table
    //         (can be optimised to O(min(n, m)) with two rolling rows,
    //          but the 2D form is kept here for clarity)
    // =====================================================================
    int minimumDeleteSum(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();

        // dp[i][j] = max ASCII sum of a common subsequence of
        //            s1[0..i-1] and s2[0..j-1]
        // All zeros => base case: empty prefix of either string -> sum 0.
        vector<vector<int>>dp( n +1 , vector<int>(m +1 , 0));

        // Fill the table row by row (increasing prefix lengths).
        // i and j start from 1 because dp[0][*] and dp[*][0] are base cases;
        // s1[i-1] / s2[j-1] are the CURRENT characters being considered.
        for(int i = 1; i <= n ; i++){
            for(int j = 1; j <= m ; j++){
                if(s1[i-1] == s2[j-1]){
                    // MATCH: keep this character in the common subsequence.
                    // Add its ASCII weight to the best answer for the
                    // remaining shorter prefixes (i-1, j-1).
                    dp[i][j] = s1[i-1] + dp[i-1][j-1];
                }else{
                    // MISMATCH: this pair cannot both be kept, so drop one
                    // of the characters and carry forward the better of the
                    // two sub-results (classic LCS "skip" choice).
                    dp[i][j] = max(dp[i-1][j] , dp[i][j-1]);
                }
            }
        }

        // total = sum of ASCII values of EVERY character in both strings.
        int total = 0 ;
        for(char ch : s1)total += ch;
        for(char ch : s2)total += ch;

        // Each character of the best common subsequence X appears in BOTH
        // strings and is kept (not deleted), so its value was counted twice
        // in `total` but deleted zero times -> subtract it twice.
        // Everything else in `total` corresponds to deleted characters.
        //
        //   Minimum delete sum = total - 2 * dp[n][m]
        return total - 2*dp[n][m];
        
    }
};


int main(){
    return 0;
}