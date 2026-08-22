#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> h(n);

    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    // prefix[i] = number of challenging peaks in [0 ... i-1]
    vector<int> prefix(n + 1, 0);

    for (int i = 1; i < n - 1; i++) {
        bool challenging = (h[i - 1] < h[i] && h[i] > h[i + 1]);

        prefix[i + 1] = prefix[i] + challenging;
    }

    // Fill remaining prefix values
    for (int i = 1; i <= n; i++) {
        prefix[i] = max(prefix[i], prefix[i - 1]);
    }

    int ans = 0;

    // Try every possible number of days
    for (int days = 1; days <= n; days++) {

        // Each day must have the same number of peaks
        if (n % days != 0) {
            continue;
        }

        int length = n / days;
        bool possible = true;

        // Check every day/block
        for (int start = 0; start < n; start += length) {
            int end = start + length;

            // Number of challenging peaks in [start, end - 1]
            if (prefix[end] - prefix[start] == 0) {
                possible = false;
                break;
            }
        }

        if (possible) {
            ans = max(ans, days);
        }
    }

    cout << ans << '\n';

    return 0;
}