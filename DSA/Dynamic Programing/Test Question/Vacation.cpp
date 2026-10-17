#include <bits/stdc++.h>
using namespace std;

int mrk(int i, int before, vector<int>& a, int n,
        vector<vector<int>>& dp) {

    // Base case: all days have been processed.
    if (i == n) return 0;

    // If this state is already calculated, return its answer.
    if (dp[i][before] != -1) return dp[i][before];

    // Option 1: Rest today.
    // Rest costs 1 day, and the previous activity becomes 0.
    int mini = 1 + mrk(i + 1, 0, a, n, dp);

    // Option 2: Write a contest if available and not done yesterday.
    if ((a[i] == 1 || a[i] == 3) && before != 1) {
        mini = min(mini, mrk(i + 1, 1, a, n, dp));
    }

    // Option 3: Do sport if available and not done yesterday.
    if ((a[i] == 2 || a[i] == 3) && before != 2) {
        mini = min(mini, mrk(i + 1, 2, a, n, dp));
    }

    // Store and return the minimum rest days for this state.
    return dp[i][before] = mini;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // before: 0 = Rest, 1 = Contest, 2 = Sport.
    // -1 means the state has not been calculated.
    vector<vector<int>> dp(n, vector<int>(3, -1));

    // Start at day 0 with no previous activity (before = 0).
    int ans = mrk(0, 0, a, n, dp);

    cout << ans << '\n';

    return 0;
}