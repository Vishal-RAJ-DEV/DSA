#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    const long long INF = 1e18;

    // dp[mask] = minimum cost to obtain vitamins in mask
    vector<long long> dp(8, INF);

    // Initially, we have no vitamins with cost 0
    dp[0] = 0;

    while (n--) {
        long long cost;
        string s;

        cin >> cost >> s;

        int juiceMask = 0;

        // Convert vitamin string into bitmask
        for (char ch : s) {
            if (ch == 'A')
                juiceMask |= 1;
            else if (ch == 'B')
                juiceMask |= 2;
            else if (ch == 'C')
                juiceMask |= 4;
        }

        // Copy because each juice can be chosen at most once
        vector<long long> newDp = dp;

        for (int mask = 0; mask < 8; mask++) {
            if (dp[mask] == INF)
                continue;

            int newMask = mask | juiceMask;

            newDp[newMask] =
                min(newDp[newMask], dp[mask] + cost);
        }

        dp = newDp;
    }

    if (dp[7] == INF)
        cout << -1 << '\n';
    else
        cout << dp[7] << '\n';

    return 0;
}