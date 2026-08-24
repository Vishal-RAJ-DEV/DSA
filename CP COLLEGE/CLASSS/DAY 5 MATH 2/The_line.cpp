#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long P;

    cin >> n >> P;

    // dp[0] = 1
    // dp[1] = 1
    long long prev2 = 1;
    long long prev1 = 1;

    if (n == 1) {
        cout << 1 % P << '\n';
        return 0;
    }

    for (int i = 2; i <= n; i++) {
        long long current = (prev1 + prev2) % P;

        prev2 = prev1;
        prev1 = current;
    }

    cout << prev1 << '\n';

    return 0;
}