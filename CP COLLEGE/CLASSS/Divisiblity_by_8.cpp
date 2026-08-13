#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();

    // Try all subsequences of length 1, 2 and 3
    for (int len = 1; len <= 3; len++) {

        // length = 1
        if (len == 1) {
            for (int i = 0; i < n; i++) {

                string cur;
                cur += s[i];

                // Single 0 is allowed
                int num = cur[0] - '0';

                if (num % 8 == 0) {
                    cout << "YES\n";
                    cout << cur << "\n";
                    return 0;
                }
            }
        }

        // length = 2
        else if (len == 2) {
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {

                    string cur;
                    cur += s[i];
                    cur += s[j];

                    // Leading zero is not allowed
                    if (cur[0] == '0')
                        continue;

                    int num = stoi(cur);

                    if (num % 8 == 0) {
                        cout << "YES\n";
                        cout << cur << "\n";
                        return 0;
                    }
                }
            }
        }

        // length = 3
        else {
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    for (int k = j + 1; k < n; k++) {

                        string cur;
                        cur += s[i];
                        cur += s[j];
                        cur += s[k];

                        // Leading zero is not allowed
                        if (cur[0] == '0')
                            continue;

                        int num = stoi(cur);

                        if (num % 8 == 0) {
                            cout << "YES\n";
                            cout << cur << "\n";
                            return 0;
                        }
                    }
                }
            }
        }
    }

    cout << "NO\n";

    return 0;
}