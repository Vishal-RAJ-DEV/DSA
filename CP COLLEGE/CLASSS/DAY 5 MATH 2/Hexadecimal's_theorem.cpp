#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    // Special cases
    if (n == 0) {
        cout << "0 0 0\n";
        return 0;
    }

    if (n == 1) {
        cout << "0 0 1\n";
        return 0;
    }

    // Generate Fibonacci numbers
    long long a = 0;
    long long b = 1;

    while (a + b < n) {
        long long next = a + b;
        a = b;
        b = next;
    }

    // Now a + b = n
    cout << a << " " << b << " " << 0 << '\n';

    return 0;
}   