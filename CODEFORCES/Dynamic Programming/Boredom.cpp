#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    const int MAXV = 100000;

    vector<long long> points(MAXV + 1, 0);
    vector<long long> dp(MAXV + 1, 0);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        points[x] += x;
    }

    dp[0] = 0;
    dp[1] = points[1];

    for (int x = 2; x <= MAXV; x++) {
        dp[x] = max(dp[x - 1], dp[x - 2] + points[x]);
    }

    cout << dp[MAXV] << endl;

    return 0;
}