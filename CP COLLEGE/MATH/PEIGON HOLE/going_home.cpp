#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);

    for (int &x : a)
        cin >> x;

    // We only need a small number of elements.
    // 5000 elements give us more than enough pairs.
    n = min(n, 5000);

    unordered_map<int, pair<int, int>> mp;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            int sum = a[i] + a[j];

            if (mp.count(sum)) {
                auto it = mp[sum];
                int x = it.first;
                int y = it.second;

                // Check that all four indices are different
                if (x != i && x != j &&
                    y != i && y != j) {

                    cout << "YES\n";
                    cout << x + 1 << " "
                         << y + 1 << " "
                         << i + 1 << " "
                         << j + 1 << "\n";

                    return 0;
                }
            }
            else {
                mp[sum] = {i, j};
            }
        }
    }

    cout << "NO\n";

    return 0;
}