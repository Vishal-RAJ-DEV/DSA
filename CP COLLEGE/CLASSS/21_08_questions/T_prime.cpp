#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6;

int main() {
    // Step 1: Find all primes up to 10^6
    vector<bool> isPrime(MAX + 1, true);

    isPrime[0] = false;
    isPrime[1] = false;

    for (int i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                isPrime[j] = false;
            }
        }
    }

    int n;
    cin >> n;

    // Step 2: Check every number
    while (n--) {
        long long x;
        cin >> x;

        long long root = sqrtl(x);

        // T-prime = perfect square of a prime
        if (root * root == x && isPrime[root]) {
            cout << "YES\n";
        } 
        else {
            cout << "NO\n";
        }
    }

    return 0;
}