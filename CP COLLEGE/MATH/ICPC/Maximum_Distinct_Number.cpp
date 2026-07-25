#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    int64 n;
    cin >> n;

    int64 low = 1, high = 2000000000LL, ans = 0;

    while (low <= high) {
        int64 mid = low + (high - low) / 2;

        __int128 sum = (__int128)mid * (mid + 1) / 2;

        if (sum <= n) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << ans;
    return 0;
}