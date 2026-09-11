#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

// Calculate A*x*x + B*x + C safely
i128 F(ll A, ll B, ll C, ll x) {
    return (i128)A * x * x + (i128)B * x + C;
}

// First positive x such that F(x) >= target
ll firstGreaterEqual(ll A, ll B, ll C, ll target) {
    ll lo = 1;
    ll hi = 1000000001LL; // F(x) will exceed 1e18 before this

    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;

        if (F(A, B, C, mid) >= target)
            hi = mid;
        else
            lo = mid + 1;
    }

    return lo;
}

// Last positive x such that F(x) <= target
ll lastLessEqual(ll A, ll B, ll C, ll target) {
    ll lo = 1;
    ll hi = 1000000001LL;

    while (lo < hi) {
        ll mid = lo + (hi - lo + 1) / 2;

        if (F(A, B, C, mid) <= target)
            lo = mid;
        else
            hi = mid - 1;
    }

    // If F(1) > target, there is no valid positive x
    if (F(A, B, C, lo) > target)
        return 0;

    return lo;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        ll A, B, C, L, R;
        cin >> A >> B >> C >> L >> R;

        ll left = firstGreaterEqual(A, B, C, L);

        // If even the first positive x is greater than R
        if (F(A, B, C, left) > R) {
            cout << 0 << '\n';
            continue;
        }

        ll right = lastLessEqual(A, B, C, R);

        cout << right - left + 1 << '\n';
    }

    return 0;
}