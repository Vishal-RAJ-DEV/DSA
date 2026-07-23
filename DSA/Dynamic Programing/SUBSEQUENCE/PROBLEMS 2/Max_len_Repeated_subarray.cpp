#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// PROBLEM: Maximum Length of Repeated Subarray
// Given two integer arrays nums1 and nums2, return the maximum length of a subarray
// that appears in BOTH arrays. Note: SUBARRAY means CONTIGUOUS elements (unlike subsequence).

// INTUITION:
// This is a classic DP problem similar to Longest Common Substring (in strings).
// The key difference from Longest Common Subsequence is CONTIGUITY.
// - In subsequence: if chars match, dp[i][j] = dp[i-1][j-1] + 1; if not, take max of dp[i-1][j], dp[i][j-1]
// - In subarray (this problem): if chars match, dp[i][j] = dp[i-1][j-1] + 1; if not, dp[i][j] = 0
//   Because contiguity breaks when characters don't match, so we reset to 0.

// DP DEFINITION:
// dp[i][j] = length of longest common subarray ENDING at nums1[i-1] and nums2[j-1]
// (i.e., the subarray must include these two elements as its last elements)

// RECURRENCE:
// If nums1[i-1] == nums2[j-1]:
//     dp[i][j] = dp[i-1][j-1] + 1   (extend the common subarray)
// Else:
//     dp[i][j] = 0                   (contiguity broken, reset)

// ANSWER:
// ans = max(dp[i][j]) over all i, j  (the longest common subarray could end anywhere)

// ALGORITHM:
// 1. Let m = nums1.size(), n = nums2.size()
// 2. Create 2D DP table dp of size (m+1) x (n+1), initialized to 0
// 3. Initialize ans = 0
// 4. For i from 1 to m:
//      For j from 1 to n:
//          If nums1[i-1] == nums2[j-1]:
//              dp[i][j] = dp[i-1][j-1] + 1
//              ans = max(ans, dp[i][j])
//          Else:
//              dp[i][j] = 0
// 5. Return ans

// TIME: O(m * n), SPACE: O(m * n)

class Solution { // 344 ms, faster than 21.07% — 2D DP approach
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();        // get lengths of both arrays
        vector<vector<int>> dp(m+1, vector<int>(n+1)); // dp table: dp[i][j] = longest common subarray ending at nums1[i-1] and nums2[j-1]
        int ans = 0;                                   // variable to track max length found

        for (int i = 1; i <= m; ++i) {                 // iterate over nums1 (1-indexed for DP)
            for (int j = 1; j <= n; ++j) {             // iterate over nums2 (1-indexed for DP)
                if (nums1[i-1] == nums2[j-1])          // if current elements match
                    dp[i][j] = dp[i-1][j-1] + 1;       // extend the common subarray by 1
                else dp[i][j] = 0;                     // else, contiguity breaks, reset to 0
                ans = max(ans, dp[i][j]);              // update global max
            }
        }
        return ans;                                    // return the maximum length found
    }
};


// SPACE OPTIMIZED VERSION:
// We only need dp[i-1][j-1] (previous row's previous column) to compute dp[i][j].
// So we can replace (m+1)*(n+1) table with two 1D arrays of size (n+1).

// ALGORITHM (Space Optimized):
// 1. Let m = nums1.size(), n = nums2.size()
// 2. Ensure nums1 is the larger array (to minimize inner loop space)
// 3. Create dp (current row) and prevDP (previous row), both size n+1, initialized to 0
// 4. ans = 0
// 5. For i from 1 to m:
//      For j from 1 to n:
//          If nums1[i-1] == nums2[j-1]:
//              dp[j] = prevDP[j-1] + 1
//              ans = max(ans, dp[j])
//          Else:
//              dp[j] = 0
//      Swap dp and prevDP for next iteration
// 6. Return ans

// TIME: O(m * n), SPACE: O(min(m, n))

class Solution { // 272 ms, faster than 48.13% — Space optimized 1D DP approach
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if (m < n) return findLength(nums2, nums1); // ensure nums1 is longer to minimize inner loop size

        vector<int> dp(n+1), prevDP(n+1);           // dp = current row, prevDP = previous row
        int ans = 0;

        for (int i = 1; i <= m; ++i) {              // iterate over rows (nums1)
            for (int j = 1; j <= n; ++j) {           // iterate over columns (nums2)
                if (nums1[i-1] == nums2[j-1])        // if current elements match
                    dp[j] = prevDP[j-1] + 1;         // extend from top-left diagonal (previous row, previous column)
                else dp[j] = 0;                      // else reset to 0
                ans = max(ans, dp[j]);               // track global max
            }
            dp.swap(prevDP);                         // swap: prevDP becomes current row for next i iteration
        }
        return ans;
    }
};


int main(){
    return 0;
}
