#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAX = 300000;

    // Step 1: Assume all numbers are prime
    vector<bool> isPrime(MAX + 1, true);

    // 0 and 1 are not prime
    isPrime[0] = false;
    isPrime[1] = false;

    // Sieve of Eratosthenes
    for (int i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {

            // Mark all multiples of i as non-prime
            for (int j = i * i; j <= MAX; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // Step 2: Build prefix sum
    vector<int> prefix(MAX + 1, 0);

    for (int i = 1; i <= MAX; i++) {
        prefix[i] = prefix[i - 1] + isPrime[i];
    }

    // Step 3: Answer queries
    int Q;
    cin >> Q;

    while (Q--) {
        int A, B;
        cin >> A >> B;

        cout << prefix[B] - prefix[A - 1] << '\n';
    }

    return 0;
}