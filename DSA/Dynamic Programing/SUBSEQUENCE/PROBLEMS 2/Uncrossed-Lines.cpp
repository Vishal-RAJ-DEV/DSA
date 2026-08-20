#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Uncrossed Lines (1035)
    Given two sequences nums1 and nums2, find the maximum number of
    non-crossing lines connecting equal values between them.

    Example:
    nums1 = [1, 4, 2]
    nums2 = [1, 2, 4]

    Possible lines:
    - Line 1: nums1[0]=1 <---> nums2[0]=1
    - Line 2: nums1[1]=4 <---> nums2[2]=4
    - Line 3: nums1[2]=2 <---> nums2[1]=2

    Lines 1 and 2 are non-crossing (valid)
    Lines 1 and 3 CROSS each other (invalid)
    Maximum non-crossing lines = 2

    ================================================================
    WHY IS THIS SAME AS LONGEST COMMON SUBSEQUENCE (LCS)?
    ================================================================

    KEY INSIGHT: Non-crossing constraint = Order preservation

    When we draw a line connecting nums1[i] to nums2[j]:
    - All future connections must use elements AFTER i in nums1
    - All future connections must use elements AFTER j in nums2
    - This is EXACTLY the LCS constraint!

    LCS Problem:
    - Find longest subsequence common to both sequences
    - Subsequence preserves relative order
    - If nums1[i] == nums2[j], we take it and move to (i+1, j+1)
    - If not equal, we try max of (i+1, j) or (i, j+1)

    Uncrossed Lines Problem:
    - Find maximum non-crossing lines
    - Non-crossing means order is preserved
    - If nums1[i] == nums2[j], we can draw a line and move to (i+1, j+1)
    - If not equal, we try skipping element in either array

    THE RECURRENCE IS IDENTICAL:
    ============================
    LCS:
        if (s1[i] == s2[j])
            dp[i][j] = 1 + dp[i+1][j+1]
        else
            dp[i][j] = max(dp[i+1][j], dp[i][j+1])

    Uncrossed Lines:
        if (nums1[i] == nums2[j])
            dp[i][j] = 1 + dp[i+1][j+1]
        else
            dp[i][j] = max(dp[i+1][j], dp[i][j+1])

    VISUAL PROOF:
    =============
    nums1: 1  4  2
           |  /
           | /
    nums2: 1  2  4

    This is the same as finding LCS between [1,4,2] and [1,2,4]:
    LCS = [1, 2] or [1, 4] (length 2)
    Uncrossed lines = 2

    Both problems ask: "What is the longest subsequence that exists
    in both sequences while preserving order?"
*/

// ==========================================
// Approach 1: Memoization (Top-Down DP)
// Time: O(n * m)
// Space: O(n * m)
// ==========================================
class Memoization {
public:
    int solve(vector<int>& nums1,
              vector<int>& nums2,
              int i,
              int j,
              vector<vector<int>>& memo) {

        // Base case: If either array is exhausted, no more lines possible
        if (i == nums1.size() || j == nums2.size())
            return 0;

        // Return cached result if already computed
        if (memo[i][j] != -1)
            return memo[i][j];

        // CASE 1: Elements match - we can draw a line
        // Count this line (+1) and move both pointers forward
        // This is same as LCS: 1 + dp[i+1][j+1]
        if (nums1[i] == nums2[j]) {
            return memo[i][j] =
                1 + solve(nums1, nums2, i + 1, j + 1, memo);
        }

        // CASE 2: Elements don't match - try skipping in either array
        // Either skip nums1[i] OR skip nums2[j], take the better option
        // This is same as LCS: max(dp[i+1][j], dp[i][j+1])
        return memo[i][j] =
            max(
                solve(nums1, nums2, i + 1, j, memo),   // Skip in nums1
                solve(nums1, nums2, i, j + 1, memo)    // Skip in nums2
            );
    }

    int maxUncrossedLines(vector<int>& nums1,
                          vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        return solve(nums1, nums2, 0, 0, memo);
    }
};

// ==========================================
// Approach 2: Tabulation (Bottom-Up DP)
// Time: O(n * m)
// Space: O(n * m)
// ==========================================
class Tabulation {
public:
    int maxUncrossedLines(vector<int>& nums1,
                          vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        // dp[i][j] = maximum non-crossing lines using
        //            nums1[i..n-1] and nums2[j..m-1]
        vector<vector<int>> dp(n + 1,
                               vector<int>(m + 1, 0));

        // Build from bottom-right corner to top-left
        // (same as LCS tabulation)
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {

                // Elements match: draw a line, move both forward
                if (nums1[i] == nums2[j]) {
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                }
                // Elements don't match: skip in either array
                else {
                    dp[i][j] = max(
                        dp[i + 1][j],    // Skip nums1[i]
                        dp[i][j + 1]     // Skip nums2[j]
                    );
                }
            }
        }

        // Answer: maximum lines using all of nums1 and nums2
        return dp[0][0];
    }
};

/*
    SUMMARY:
    ========
    Uncrossed Lines IS Longest Common Subsequence!

    Both problems:
    1. Compare two sequences element by element
    2. When elements match, we "take" it and advance both pointers
    3. When elements don't match, we try skipping in either sequence
    4. Goal: Find maximum matches (LCS length = max non-crossing lines)

    The "non-crossing" constraint naturally enforces order preservation,
    which is the same constraint that defines a subsequence in LCS.

    Reference: LeetCode 1035 (Uncrossed Lines) = LeetCode 1143 (LCS)
*/

int main(){
    return 0;
}
