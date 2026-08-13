#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

// Binary Exponentiation
long long power(long long a, long long b) {
    long long result = 1;

    while (b > 0) {
        // If b is odd
        if (b & 1) {
            result = (result * a) % MOD;
        }

        // Square the base
        a = (a * a) % MOD;

        // Divide b by 2
        b /= 2;
    }

    return result;
}

int main() {
    long long n;
    cin >> n;

    cout << power(2, n) << '\n';

    return 0;
}