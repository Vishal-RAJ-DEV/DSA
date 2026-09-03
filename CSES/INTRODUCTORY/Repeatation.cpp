#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int current = 1;
    int maximum = 1;

    for (int i = 1; i < s.size(); i++) {
        if (s[i] == s[i - 1]) {
            current++;
        } else {
            current = 1;
        }

        maximum = max(maximum, current);
    }

    cout << maximum << '\n';

    return 0;
}