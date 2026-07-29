#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, k;
        cin >> n >> k;

        string s;
        cin >> s;

        int zero = 0;
        for (char c : s)
            if (c == '0')
                zero++;

        int one = n - zero;

        if (zero < k || one < k) {
            cout << s << '\n';
        }
        else if (zero == k && one == k) {
            string t = s;
            for (char &c : t)
                c = (c == '0') ? '1' : '0';

            cout << min(s, t) << '\n';
        }
        else {
            cout << string(zero, '0') + string(one, '1') << '\n';
        }
    }

    return 0;
}