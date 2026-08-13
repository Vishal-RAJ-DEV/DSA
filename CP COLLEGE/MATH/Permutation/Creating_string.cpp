#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

long long power(long long a, long long b) {
    long long result = 1;

    while (b > 0) {
        if (b & 1)
            result = result * a % MOD;

        a = a * a % MOD;
        b /= 2;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();

    // Count characters
    vector<int> freq(26, 0);

    for (char c : s)
        freq[c - 'a']++;

    // Calculate factorials
    vector<long long> fact(n + 1);

    fact[0] = 1;

    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i % MOD;

    // Calculate inverse factorials
    vector<long long> invFact(n + 1);

    invFact[n] = power(fact[n], MOD - 2);

    for (int i = n; i >= 1; i--)
        invFact[i - 1] = invFact[i] * i % MOD;

    // n! / (f1! * f2! * ...)
    long long answer = fact[n];

    for (int i = 0; i < 26; i++) {
        answer = answer * invFact[freq[i]] % MOD;
    }

    cout << answer << '\n';

    return 0;
}


