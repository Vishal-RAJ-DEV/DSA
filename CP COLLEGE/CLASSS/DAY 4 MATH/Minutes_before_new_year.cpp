#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int h, m;
        cin >> h >> m;

        int minutesPassed = h * 60 + m;

        int answer = 1440 - minutesPassed;

        cout << answer << '\n';
    }

    return 0;
}