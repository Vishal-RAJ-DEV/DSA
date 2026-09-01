#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<double> ropes(n);

    double high = 0;

    for (int i = 0; i < n; i++) {
        cin >> ropes[i];
        high = max(high, ropes[i]);
    }

    double low = 0;

    for (int i = 0; i < 100; i++) {
        double mid = (low + high) / 2;

        int pieces = 0;

        for (double rope : ropes) {
            pieces += (int)(rope / mid);
        }

        if (pieces >= k) {
            // mid works, try a larger piece
            low = mid;
        } else {
            // mid doesn't work, need smaller piece
            high = mid;
        }
    }

    cout << fixed << setprecision(10) << low << '\n';

    return 0;
}