#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Memoization {
public:
    /*
        Algorithm: Longest Common Subsequence using Recursion + Memoization

        A subsequence is formed by deleting zero or more characters without
        changing the order of the remaining characters.

        Idea:
        - solve(i, j) returns the length of the LCS between:
              text1[0...i] and text2[0...j]
        - We start from the last indexes of both strings and move backward.

        Recurrence:
        1. If text1[i] == text2[j], this character is part of the LCS.
           So answer = 1 + solve(i - 1, j - 1)

        2. If text1[i] != text2[j], we try both choices:
           - ignore current character of text1: solve(i - 1, j)
           - ignore current character of text2: solve(i, j - 1)
           Then take the maximum of both.

        Memoization:
        - dp[i][j] stores the result of solve(i, j).
        - This avoids solving the same subproblem again and again.

        Time Complexity: O(n * m)
        Space Complexity: O(n * m) for dp + O(n + m) recursion stack
    */
    int solve( int i , int j , const string& text1 , const string& text2 , vector<vector<int>>&dp){
        // Base case: if any string is exhausted, no common subsequence is possible.
        if( i < 0 || j < 0) return 0;

        // If this subproblem was already solved, return the stored answer.
        if( dp[i][j] != -1)return dp[i][j];

        // If both current characters match, include this character in the answer
        // and move both pointers one step backward.
        if( text1[i] == text2[j]){
            return dp[i][j] =  1 + solve( i -1 , j -1 , text1 , text2 , dp);
        }

        // If characters do not match, try removing one character from either
        // text1 or text2, then keep the choice that gives the longer LCS.
        return dp[i][j] = max( solve( i - 1 , j , text1 , text2, dp) , solve( i , j - 1 , text1 , text2 , dp));
    }
    int longestCommonSubsequence(string text1, string text2) {

        // dp[i][j] will store the LCS length for text1[0...i] and text2[0...j].
        // Initially every value is -1, meaning that subproblem is not solved yet.
        vector<vector<int>>dp(text1.size() , vector<int>(text2.size() , -1));

        // Start checking from the last character of both strings.
        int i = text1.size() - 1 ;// pointer to the last index of text1
        int j = text2.size() - 1 ;// pointer to the last index of text2

        // Return the LCS length of the complete strings.
        return solve( i , j , text1 , text2 , dp);
    }
};

class Tabulation {
public:
    /*
        Algorithm: Longest Common Subsequence using Tabulation

        In memoization, solve(i, j) works with real string indexes and uses:
            if(i < 0 || j < 0) return 0;

        In tabulation, we avoid negative indexes by shifting the DP table by 1.

        Meaning of dp[i][j]:
        - dp[i][j] stores the LCS length between:
              first i characters of text1
              first j characters of text2

        Important index shift:
        - dp[1][1] compares text1[0] and text2[0]
        - dp[i][j] compares text1[i - 1] and text2[j - 1]

        Why dp size is (n + 1) * (m + 1):
        - The extra row dp[0][j] means text1 is empty.
        - The extra column dp[i][0] means text2 is empty.
        - LCS with an empty string is always 0.

        How i < 0 / j < 0 is handled here:
        - In recursion, when i or j becomes -1, we return 0.
        - In tabulation, we never use -1 indexes.
        - Instead, dp[0][*] and dp[*][0] store that same base-case answer 0.

        Time Complexity: O(n * m)
        Space Complexity: O(n * m)
    */

    int longestCommonSubsequence(string text1,
                                 string text2) {

        // n and m are the lengths of both strings.
        int n = text1.size();
        int m = text2.size();

        // We create dp with n + 1 rows and m + 1 columns.
        // The extra row and column represent empty prefixes of the strings.
        // Because the table is initialized with 0, dp[0][*] and dp[*][0]
        // are already storing the base case: LCS with empty string = 0.
        vector<vector<int>> dp(
            n + 1,
            vector<int>(m + 1, 0)
        );

        // Start from 1 because row 0 and column 0 are the base cases.
        // i means we are considering the first i characters of text1.
        for(int i = 1; i <= n; i++) {

            // j means we are considering the first j characters of text2.
            for(int j = 1; j <= m; j++) {

                // Since dp is shifted by 1, dp[i][j] compares:
                // text1[i - 1] and text2[j - 1].
                // If both characters match, include that character in LCS.
                if(text1[i-1] == text2[j-1]) {

                    // Add 1 for the matched character and move diagonally
                    // to the answer of the smaller prefixes.
                    dp[i][j] =
                        1 + dp[i-1][j-1];
                }

                // If characters do not match, we cannot take both together.
                // So we try ignoring one character from either string.
                else {

                    // dp[i-1][j] means ignore current character of text1.
                    // dp[i][j-1] means ignore current character of text2.
                    // Take the maximum because we need the longest subsequence.
                    dp[i][j] = max(
                        dp[i-1][j],
                        dp[i][j-1]
                    );
                }
            }
        }

        // dp[n][m] stores the LCS length of the full text1 and full text2.
        return dp[n][m];
    }
};

class SpaceOptimized {
public:
    /*
        Algorithm: Longest Common Subsequence using Space Optimization

        In normal tabulation, we use a 2D dp table:
            dp[i][j] = LCS of first i characters of text1
                       and first j characters of text2

        But to calculate dp[i][j], we only need:
            dp[i - 1][j - 1]  -> previous row, previous column
            dp[i - 1][j]      -> previous row, same column
            dp[i][j - 1]      -> current row, previous column

        So instead of storing the whole 2D table, we store only two rows:

        prev:
        - Represents the previous row of the 2D dp table.
        - During the i loop, prev[j] means dp[i - 1][j].

        curr:
        - Represents the current row we are building.
        - During the i loop, curr[j] means dp[i][j].

        How it works with loops:
        - Outer loop i picks characters from text1 one by one.
        - For each i, inner loop j builds the complete current row using text2.
        - After finishing all j values for one i, curr becomes the completed row.
        - Then we copy curr into prev, so it can be used as the previous row
          for the next value of i.

        Time Complexity: O(n * m)
        Space Complexity: O(m)
    */

    int longestCommonSubsequence(string text1,
                                 string text2) {

        // n and m are the lengths of the two strings.
        int n = text1.size();
        int m = text2.size();

        // prev is the row above the current row in the original 2D dp table.
        // Size is m + 1 because column 0 represents empty text2.
        vector<int> prev(m + 1, 0);

        // curr is the row that we are calculating right now.
        // curr[0] stays 0 because LCS with empty text2 is always 0.
        vector<int> curr(m + 1, 0);

        // i means we are considering the first i characters of text1.
        for(int i = 1; i <= n; i++) {

            // j means we are considering the first j characters of text2.
            for(int j = 1; j <= m; j++) {

                // Compare the actual characters using i - 1 and j - 1
                // because dp indexing is shifted by 1.
                // If characters match, this character can be included in LCS.
                if(text1[i-1] == text2[j-1]) {

                    // In 2D dp this was:
                    // dp[i][j] = 1 + dp[i - 1][j - 1]
                    // Here, prev[j - 1] represents dp[i - 1][j - 1].
                    curr[j] =
                        1 + prev[j-1];
                }

                // If characters do not match, try skipping one character.
                else {

                    // In 2D dp this was:
                    // dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
                    //
                    // prev[j] represents dp[i - 1][j]:
                    // skip current character of text1.
                    //
                    // curr[j - 1] represents dp[i][j - 1]:
                    // skip current character of text2.
                    curr[j] = max(
                        prev[j],
                        curr[j-1]
                    );
                }
            }

            // Now the current row dp[i][*] is complete.
            // Make it prev so the next i can use it as dp[i - 1][*].
            prev = curr;
        }

        // After the last row is copied, prev[m] stores the answer for
        // the full text1 and full text2.
        return prev[m];
    }
};



class AnotherWayOfMemoization {
public:
    /*
        Another way of writing the memoization logic in iterative DP form.

        In the memoization code above:
        - solve(i, j) stores the answer for text1[0...i] and text2[0...j]
          inside dp[i][j].

        This code uses the same dp meaning:
        - dp[i][j] stores the LCS length between:
              text1[0...i]
              text2[0...j]

        Difference:
        - Memoization fills dp using recursive calls from bigger indexes
          toward smaller indexes.
        - This version fills dp directly using loops from smaller indexes
          toward bigger indexes.

        Because dp uses real indexes from 0 to n - 1 and 0 to m - 1,
        we must handle the first row and first column carefully.

        Time Complexity: O(n * m)
        Space Complexity: O(n * m)
    */
    int longestCommonSubsequence(string text1, string text2) {

        int n = text1.size();
        int m = text2.size();

        // If any string is empty, no common subsequence is possible.
        // This also prevents accessing dp[n - 1][m - 1] when n or m is 0.
        if(n == 0 || m == 0) return 0;

        // dp[i][j] stores the LCS length for text1[0...i] and text2[0...j].
        vector<vector<int>> dp(n, vector<int>(m, 0));

        for(int i = 0; i < n; i++) {

            for(int j = 0; j < m; j++) {

                // If both current characters match, we include this character.
                if(text1[i] == text2[j]) {

                    // If we are on the first row or first column, there is no
                    // diagonal previous answer, so the LCS length becomes 1.
                    if(i == 0 || j == 0)
                        dp[i][j] = 1;
                    else
                        dp[i][j] = 1 + dp[i-1][j-1];

                }
                else {

                    // If characters do not match, we try:
                    // up   -> ignore current character of text1
                    // left -> ignore current character of text2
                    int up = (i > 0) ? dp[i-1][j] : 0;
                    int left = (j > 0) ? dp[i][j-1] : 0;

                    // Keep the longer LCS from both choices.
                    dp[i][j] = max(up, left);
                }
            }
        }

        // Last cell stores the LCS length of the complete strings.
        return dp[n-1][m-1];
    }
};



int main(){ 

    Memoization obj;
    // For "abcde" and "ace", the longest common subsequence is "ace",
    // so the output will be 3.
    cout <<obj.longestCommonSubsequence("abcde" , "ace") << endl;
    

    return 0;
}

