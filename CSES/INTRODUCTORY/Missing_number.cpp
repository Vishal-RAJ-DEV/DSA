#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int ans = 0;

    // XOR all numbers from 1 to n
    for (int i = 1; i <= n; i++) {
        ans ^= i;
    }

    // XOR all given numbers
    for (int i = 0; i < n - 1; i++) {
        int x;
        cin >> x;
        ans ^= x;
    }

    cout << ans << '\n';

    return 0;
}