#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long r, g, b;
        cin >> r >> g >> b;

        // Find the color having maximum lamps
        long long mx = max({r, g, b});

        // Number of lamps of the other two colors
        long long others = r + g + b - mx;

        // We need at least mx - 1 other lamps
        // to separate all mx lamps.
        if (mx <= others + 1)
            cout << "Yes\n";
        else
            cout << "No\n";
    }

    return 0;
}