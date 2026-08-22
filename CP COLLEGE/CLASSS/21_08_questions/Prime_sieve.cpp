#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<bool> isPrime(n + 1, true);

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; 1LL * i * i <= n; i++) {
        if (isPrime[i]) {
            for (long long j = 1LL * i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    int count = 0;

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            count++;
        }
    }

    cout << count << '\n';

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            cout << i << ' ';
        }
    }

    return 0;
}