#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
const int MAXN = 1e6;

// Fast power: calculates a^b % MOD
long long power(long long a, long long b) {
    long long result = 1;

    while (b > 0) {
        // If b is odd
        if (b & 1) {
            result = (result * a) % MOD;
        }

        // Square the base
        a = (a * a) % MOD;

        // Divide exponent by 2
        b /= 2;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // factorial[i] = i! % MOD
    vector<long long> factorial(MAXN + 1);

    factorial[0] = 1;

    for (int i = 1; i <= MAXN; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }

    // invFactorial[i] = (i!)^-1 % MOD
    vector<long long> invFactorial(MAXN + 1);

    // By Fermat's Little Theorem:
    // x^-1 = x^(MOD-2) % MOD
    invFactorial[MAXN] =
        power(factorial[MAXN], MOD - 2);

    // Calculate all inverse factorials
    for (int i = MAXN; i >= 1; i--) {
        invFactorial[i - 1] =
            (invFactorial[i] * i) % MOD;
    }

    // Answer each query
    while (n--) {
        int a, b;
        cin >> a >> b;

        // C(a,b) = a! / (b! * (a-b)!)
        //
        // Division modulo MOD:
        // a! * inverse(b!) * inverse((a-b)!)

        long long answer = factorial[a];

        answer = (answer * invFactorial[b]) % MOD;

        answer = (answer * invFactorial[a - b]) % MOD;

        cout << answer << '\n';
    }

    return 0;
}