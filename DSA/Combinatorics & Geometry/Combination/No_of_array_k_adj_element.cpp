#include <iostream>
#include <bits/stdc++.h>
using namespace std;



class Solution {
public:
    static const int MOD = 1e9 + 7;

    long long power(long long a, long long b) {
        long long result = 1;

        while (b > 0) {
            if (b & 1) {
                result = result * a % MOD;
            }

            a = a * a % MOD;
            b >>= 1;
        }

        return result;
    }

    int countGoodArrays(int n, int m, int k) {

        // Precompute factorials
        vector<long long> fact(n);
        vector<long long> invFact(n);

        fact[0] = 1;

        for (int i = 1; i < n; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        // Modular inverse of factorial
        invFact[n - 1] = power(fact[n - 1], MOD - 2);

        for (int i = n - 2; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        // Calculate C(n - 1, k)
        long long combinations =
            fact[n - 1] *
            invFact[k] % MOD *
            invFact[n - 1 - k] % MOD;

        // m * C(n-1, k) * (m-1)^(n-1-k)
        long long answer = m;

        answer = answer * combinations % MOD;

        answer = answer *
                 power(m - 1, n - 1 - k) % MOD;

        return answer;
    }
};


int main(){
    return 0;
}