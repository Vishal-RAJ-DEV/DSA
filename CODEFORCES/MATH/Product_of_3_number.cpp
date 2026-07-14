#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long n;
        cin >> n;

        long long a = -1, b = -1, c = -1;

        // Find first divisor
        for (long long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                a = i;
                n /= i;
                break;
            }
        }

        // Find second divisor (different from a)
        if (a != -1) {
            for (long long i = a + 1; i * i <= n; i++) {
                if (n % i == 0) {
                    b = i;
                    n /= i;
                    break;
                }
            }
        }

        c = n;

        if (a != -1 && b != -1 && c > 1 && c != a && c != b) {
            cout << "YES\n";
            cout << a << " " << b << " " << c << "\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}