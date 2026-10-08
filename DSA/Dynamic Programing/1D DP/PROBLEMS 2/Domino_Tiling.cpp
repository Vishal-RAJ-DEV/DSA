#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const long long MOD = 1e9 + 7;

    long long solve(int n, vector<long long>& dp) {
        if (n == 0) return 1;
        if (n == 1) return 1;
        if (n == 2) return 2;

        if (dp[n] != -1)
            return dp[n];

        return dp[n] = (2 * solve(n - 1, dp) + solve(n - 3, dp)) % MOD;
    }

    int numTilings(int n) {
        vector<long long> dp(n + 1, -1);

        return solve(n, dp);
    }
};


class Solution {
public:
    int numTilings(int n) {
        const long long MOD = 1e9 + 7;

        vector<long long> dp(n + 1);

        dp[0] = 1;

        if (n >= 1)
            dp[1] = 1;

        if (n >= 2)
            dp[2] = 2;

        for (int i = 3; i <= n; i++) {
            dp[i] = (2 * dp[i - 1] + dp[i - 3]) % MOD;
        }

        return dp[n];
    }
};



class Solution {
public:
    int numTilings(int n) {
        const long long MOD = 1e9 + 7;

        if (n == 0) return 1;
        if (n == 1) return 1;
        if (n == 2) return 2;

        long long a = 1; // dp[i-3]
        long long b = 1; // dp[i-2]
        long long c = 2; // dp[i-1]

        for (int i = 3; i <= n; i++) {
            long long cur = (2 * c + a) % MOD;

            a = b;
            b = c;
            c = cur;
        }

        return c;
    }
};




int main(){
    return 0;
}