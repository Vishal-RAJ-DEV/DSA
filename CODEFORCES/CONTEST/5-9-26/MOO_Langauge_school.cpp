#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        string s;
        cin >> s;

        int ans = 0;

        for (int i = 0; i < n; i += k) {
            bool allOnes = true;

            for (int j = i; j < i + k; j++) {
                if (s[j] == '0') {
                    allOnes = false;
                    break;
                }
            }

            if (allOnes)
                ans++;
        }

        cout << ans << '\n';
    }

    return 0;
}