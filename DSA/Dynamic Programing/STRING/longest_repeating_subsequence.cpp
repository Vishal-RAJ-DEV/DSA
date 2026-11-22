#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int lcs(int n, string &s1, string &s2)
    {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (s1[i - 1] == s2[j - 1] && i != j)
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][n];
    }
    int longestRepSubseq(string &s)
    {
        // Code here
        int n = s.size();
        return lcs(n, s, s);
    }
};

int main()
{
    return 0;
}