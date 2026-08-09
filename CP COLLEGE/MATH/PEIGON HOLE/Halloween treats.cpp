#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, n;

    while (cin >> c >> n) {
        if (c == 0 && n == 0)
            break;

        vector<int> a(n + 1);

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        // rem[r] = index where remainder r was first seen
        vector<int> rem(c, -1);

        // Prefix sum = 0 before taking any element
        rem[0] = 0;

        long long sum = 0;

        bool found = false;

        // We only need first c elements
        for (int i = 1; i <= c; i++) {

            sum += a[i];

            int r = sum % c;

            // Case 1: prefix sum itself is divisible by c
            if (r == 0) {
                for (int j = 1; j <= i; j++) {
                    cout << j << " ";
                }
                cout << '\n';

                found = true;
                break;
            }

            // Case 2: same remainder appeared before
            if (rem[r] != -1) {

                int start = rem[r] + 1;
                int end = i;

                for (int j = start; j <= end; j++) {
                    cout << j << " ";
                }

                cout << '\n';

                found = true;
                break;
            }

            // First time seeing this remainder
            rem[r] = i;
        }

        if (!found) {
            cout << "no sweets\n";
        }
    }

    return 0;
}