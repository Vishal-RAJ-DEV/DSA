#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n % 2 == 0) {
        // Maximum number of primes
        cout << n / 2 << '\n';

        // Print n/2 copies of 2
        for (int i = 0; i < n / 2; i++) {
            cout << 2 << ' ';
        }
    } 
    else {
        // One 3 + remaining sum using 2s
        cout << 1 + (n - 3) / 2 << '\n';

        cout << 3 << ' ';

        for (int i = 0; i < (n - 3) / 2; i++) {
            cout << 2 << ' ';
        }
    }

    return 0;
}