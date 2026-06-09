#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// This is version 1 of the memoization approach.
class Memoization1 {
public:
    /*
        Algorithm: Longest Common Substring using Recursion + Memoization

        A substring must be continuous.
        So if characters match, we can extend the current substring.
        If characters do not match, the current substring length becomes 0.

        Meaning of solve(i, j):
        - It returns the length of the common substring that ends exactly at:
              s1[i] and s2[j]

        Important:
        - solve(i, j) only gives the substring ending at i and j.
        - The longest common substring can end at any pair of indexes.
        - That is why we explore solve(i - 1, j) and solve(i, j - 1)
          also, just to visit all possible ending positions.

        Recurrence:
        1. If s1[i] == s2[j]:
              dp[i][j] = 1 + solve(i - 1, j - 1)

        2. If s1[i] != s2[j]:
              dp[i][j] = 0
           because a substring cannot continue after a mismatch.

        ans:
        - ans stores the maximum value found in the whole dp table.

        Time Complexity: O(n * m)
        Space Complexity: O(n * m) for dp + O(n + m) recursion stack
    */

    int solve(int &ans, vector<vector<int>>& dp,
              int i, int j, string& s1, string& s2) {

        // Base case
        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        // Explore all states
        solve(ans, dp, i - 1, j, s1, s2);
        solve(ans, dp, i, j - 1, s1, s2);

        //here the take variable is zero so if the character don't matches then take= 0 will store 
        //in the dp[i][j] means that there no common substring at this index 
        //but if the character matches then we will add 1 and go to the next index of the both string and that will return more value and we will update the ans variable with the maximum value of the common substring length found so far
        int take = 0;

        if (s1[i] == s2[j]) {
            take = 1 + solve(ans, dp, i - 1, j - 1, s1, s2);
            ans = max(ans, take);
        }

        return dp[i][j] = take;
    }

    int longCommSubstr(string& s1, string& s2) {

        int n = s1.size(), m = s2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));

        int ans = 0;

        solve(ans, dp, n - 1, m - 1, s1, s2);

        return ans;
    }
};

// This is the cleaner version of the memoization approach.
class Memoization2 {
public:
    /*
        Intuition:

        For longest common substring, we are not allowed to skip characters
        inside the answer. The matching part must be continuous.

        So dp[i][j] means:
        - length of the longest common substring ending at s1[i] and s2[j]

        If s1[i] == s2[j]:
        - The substring ending at these two indexes can be extended from
          the previous diagonal pair.
        - dp[i][j] = 1 + dp[i - 1][j - 1]

        If s1[i] != s2[j]:
        - The continuous chain breaks.
        - dp[i][j] = 0

        Why do we call solve(i - 1, j) and solve(i, j - 1)?
        - They are not used directly in the recurrence.
        - They are called so recursion visits every cell of the dp table.
        - Every cell is a possible ending point of the longest substring.

        Difference from Longest Common Subsequence:
        - Subsequence allows skipping, so mismatch uses max(up, left).
        - Substring does not allow skipping, so mismatch becomes 0.

        Time Complexity: O(n * m)
        Space Complexity: O(n * m) for dp + O(n + m) recursion stack
    */
    int ans = 0;

    int solve(int i, int j,
              string &s1, string &s2,
              vector<vector<int>> &dp) {

        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        // Visit all states
        solve(i - 1, j, s1, s2, dp);
        solve(i, j - 1, s1, s2, dp);

        if (s1[i] == s2[j]) {
            dp[i][j] = 1 + solve(i - 1, j - 1, s1, s2, dp);
            ans = max(ans, dp[i][j]);
        }
        else {
            dp[i][j] = 0;
        }

        return dp[i][j];
    }

    int longCommSubstr(string &s1, string &s2) {
        int n = s1.size(), m = s2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));

        solve(n - 1, m - 1, s1, s2, dp);

        return ans;
    }
};  

class Tabulation {
public:
    /* Function to find the length of 
    the Longest Common Substring (LCS) */
    int longestCommonSubstr(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
    
        // Initialize a 2D DP table with dimensions
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Initialize the answer variable
        int ans = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // Characters match, increment substring length
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    
                    /* Update the maximum substring 
                    length found so far */
                    ans = max(ans, dp[i][j]);
                } else {
                    /* Characters don't match, 
                    substring length becomes 0 */
                    dp[i][j] = 0;
                }
            }
        }
        // Return the length of Longest Common Substring
        return ans;
    }
};

class SpaceOptimized {
public:
    /*
        Algorithm: Longest Common Substring using Space Optimization

        In tabulation:
            dp[i][j] = length of common substring ending at
                       str1[i - 1] and str2[j - 1]

        To calculate dp[i][j], we only need:
            dp[i - 1][j - 1]

        That means we do not need the whole 2D table.
        We only keep:
        - prev: previous row
        - curr: current row

        If characters match:
            curr[j] = 1 + prev[j - 1]

        If characters do not match:
            curr[j] = 0
        because a substring must be continuous.

        Time Complexity: O(n * m)
        Space Complexity: O(m)
    */
    int longestCommonSubstr(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();

        vector<int> prev(m + 1, 0);
        vector<int> curr(m + 1, 0);

        int ans = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                    ans = max(ans, curr[j]);
                }
                else {
                    curr[j] = 0;
                }
            }

            prev = curr;
        }

        return ans;
    }
};



int main(){
    string s1 = "abcde";
    string s2 = "ace";
        Memoization1 obj1;
        cout << "Longest Common Substring (Memoization1): " << obj1.longCommSubstr(s1, s2) << endl;
    
        Memoization2 obj2;
        cout << "Longest Common Substring (Memoization2): " << obj2.longCommSubstr(s1, s2) << endl;
    
        Tabulation obj3;
        cout << "Longest Common Substring (Tabulation): " << obj3.longestCommonSubstr(s1, s2) << endl;
    
        SpaceOptimized obj4;
        cout << "Longest Common Substring (Space Optimized): " << obj4.longestCommonSubstr(s1, s2) << endl;
    return 0;
}
