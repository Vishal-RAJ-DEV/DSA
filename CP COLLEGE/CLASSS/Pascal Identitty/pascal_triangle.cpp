#include <iostream>
#include <bits/stdc++.h>
using namespace std;

long long C(int n, int r) {
    vector<vector<long long>> dp(n + 1, vector<long long>(r + 1));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;

        for (int j = 1; j <= min(i, r); j++) {
            if (j == i)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
        }
    }

    return dp[n][r];
}


int main(){
    return 0;
}