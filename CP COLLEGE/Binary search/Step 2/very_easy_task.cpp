#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, x, y;
    cin >> n >> x >> y;

    // First copy must be made from the original.
    long long firstCopy = min(x, y);

    // If we only need one copy, we're done.
    if (n == 1) {
        cout << firstCopy << endl;
        return 0;
    }

    // We need n - 1 more copies.
    long long remaining = n - 1;

    // Binary search for the minimum additional time.
    long long low = 0;
    long long high = remaining * min(x, y);

    while (low < high) {
        long long mid = low + (high - low) / 2;

        // Number of copies both machines can make in 'mid' seconds.
        long long copies = mid / x + mid / y;

        if (copies >= remaining) {
            // 'mid' is enough.
            // Try to find an even smaller time.
            high = mid;
        } else {
            // 'mid' is not enough.
            low = mid + 1;
        }
    }

    cout << firstCopy + low << endl;

    return 0;
}