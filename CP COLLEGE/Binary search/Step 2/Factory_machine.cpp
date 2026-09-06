#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long t;

    cin >> n >> t;

    vector<long long> k(n);

    for (int i = 0; i < n; i++) {
        cin >> k[i];
    }

    long long low = 0;
    long long high = 1e18;

    while (low < high) {

        long long mid = low + (high - low) / 2;

        long long products = 0;

        for (int i = 0; i < n; i++) {
            products += mid / k[i];

            // No need to calculate further
            if (products >= t)
                break;
        }

        if (products >= t) {
            // mid seconds is enough
            high = mid;
        } else {
            // mid seconds is not enough
            low = mid + 1;
        }
    }

    cout << low << '\n';

    return 0;
}