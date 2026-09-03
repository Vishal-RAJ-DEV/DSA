#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long moves = 0;
    long long prev;

    cin >> prev;

    for (int i = 1; i < n; i++) {
        long long x;
        cin >> x;

        if (x < prev) {
            moves += prev - x;
            x = prev;
        }

        prev = x;
    }

    cout << moves << '\n';

    return 0;
}
