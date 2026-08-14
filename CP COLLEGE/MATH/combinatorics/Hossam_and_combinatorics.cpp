#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<long long> a(n);

        long long mn = LLONG_MAX;
        long long mx = LLONG_MIN;

        for (int i = 0; i < n; i++) {
            cin >> a[i];

            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
        }

        long long cntMin = 0;
        long long cntMax = 0;

        for (int i = 0; i < n; i++) {
            if (a[i] == mn)
                cntMin++;

            if (a[i] == mx)
                cntMax++;
        }

        if (mn == mx) {
            cout << 1LL * n * (n - 1) << '\n';
        }
        else {
            cout << 2LL * cntMin * cntMax << '\n';
        }
    }

    return 0;
}