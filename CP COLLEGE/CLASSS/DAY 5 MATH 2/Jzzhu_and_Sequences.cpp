#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x, y, n;
    cin >> x >> y;
    cin >> n;

    const long long MOD = 1000000007;

    long long ans;

    long long pos = n % 6;

    if (pos == 1) {
        ans = x;
    }
    else if (pos == 2) {
        ans = y;
    }
    else if (pos == 3) {
        ans = y - x;
    }
    else if (pos == 4) {
        ans = -x;
    }
    else if (pos == 5) {
        ans = -y;
    }
    else {
        ans = x - y;
    }

    // Handle negative values
    ans = (ans % MOD + MOD) % MOD;

    cout << ans << '\n';

    return 0;
}