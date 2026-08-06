#include <bits/stdc++.h>
using namespace std;

const int MAX = 10000000;

// isPrime[i] = true if i is prime
vector<bool> isPrime(MAX + 1, true);

// good[i] = true if i is prime and can be written as x² + y⁴
vector<bool> good(MAX + 1, false);

// prefix[i] = number of valid primes <= i
vector<int> prefix(MAX + 1, 0);

void preprocess() {

    // ----------------------------
    // Step 1 : Sieve of Eratosthenes
    // ----------------------------
    isPrime[0] = isPrime[1] = false;

    for (long long i = 2; i * i <= MAX; i++) {

        if (isPrime[i]) {

            for (long long j = i * i; j <= MAX; j += i)
                isPrime[j] = false;
        }
    }

    // ----------------------------
    // Step 2 : Generate x² + y⁴
    // ----------------------------

    for (long long y = 1;; y++) {

        long long y4 = y * y;
        y4 *= y4;          // y⁴

        if (y4 > MAX)
            break;

        for (long long x = 1;; x++) {

            long long value = x * x + y4;

            if (value > MAX)
                break;

            if (isPrime[value])
                good[value] = true;
        }
    }

    // ----------------------------
    // Step 3 : Prefix Sum
    // ----------------------------

    for (int i = 1; i <= MAX; i++) {

        prefix[i] = prefix[i - 1];

        if (good[i])
            prefix[i]++;
    }
}

int main() {
    preprocess();

    int T;
    cin >> T;

    while (T--) {

        int n;
        cin >> n;

        cout << prefix[n] << "\n";
    }

    return 0;
}