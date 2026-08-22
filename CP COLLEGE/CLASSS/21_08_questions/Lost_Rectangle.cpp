#include <bits/stdc++.h>
using namespace std;

int main() {
    long long A;
    cin >> A;

    // Start from sqrt(A) and move downward
    for (long long i = sqrt(A); i >= 1; i--) {

        if (A % i == 0) {
            long long length = i;
            long long width = A / i;

            cout << 2 * (length + width) << endl;
            break;
        }
    }

    return 0;
}