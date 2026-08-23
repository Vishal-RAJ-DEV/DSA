#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // We need to find two composite numbers a and b such that a - b = n.
    // Instead of searching for them, construct a valid pair based on n's parity.
    if (n % 2 == 0) {
        // If n is even, n + 4 is also even and n + 4 >= 6.
        // Every even number greater than 2 is composite, and 4 is composite.
        // Therefore, a = n + 4 and b = 4 are both composite numbers.
        // Their difference is (n + 4) - 4 = n.
        cout << n + 4 << " " << 4 << '\n';
    } 
    else {
        // If n is odd, n + 4 would be odd and may be prime.
        // Instead, use a = n + 9 and b = 9.
        // Since odd + odd is even, n + 9 is even; also n + 9 >= 10.
        // Thus, n + 9 is composite, 9 is composite, and
        // (n + 9) - 9 = n.
        cout << n + 9 << " " << 9 << '\n';
    }

    return 0;
}