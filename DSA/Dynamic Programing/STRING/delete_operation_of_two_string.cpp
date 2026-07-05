#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*

Given two strings word1 and word2, return the minimum number of steps required to make word1 and word2 the same.
In one step, you can delete exactly one character in either string.

Example 1:

Input: word1 = "sea", word2 = "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
Example 2:

Input: word1 = "leetcode", word2 = "etco"
Output: 4*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        //first we calculate the common subsequence between the both the string 
        vector<vector<int>>dp( n + 1 , vector<int>( m + 1,0 ));

        for( int i = 1; i <= n ; i++){
            for( int j = 1; j <= m ; j++){
                if(word1[i-1] == word2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }else{
                    dp[i][j] = max(dp[i][j-1] , dp[i-1][j]);
                }
            }
        }

        //at dp[n][m] we have the common subseqence 
        //to  count no of delete operatinons 
        //we remove the count of the common subseqence of the both the string and add it up 

        //delete in the word1
        int delete1 = n - dp[n][m];
        int delete2 = m - dp[n][m];

        return delete1 + delete2;
    }
};



int main(){
    string word1 = "sea";
    string word2 = "eat";
    Solution obj;
    int ans = obj.minDistance(word1 , word2);
    cout<<"The minimum number of delete operations to make the two strings equal is: "<<ans<<endl;

    return 0;
}
