#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<bool> isFib(n + 1, false);

    // Mark Fibonacci positions
    int a = 1, b = 2;

    isFib[1] = true;

    while (b <= n) {
        isFib[b] = true;

        int next = a + b;
        a = b;
        b = next;
    }

    // Build the name
    for (int i = 1; i <= n; i++) {
        if (isFib[i])
            cout << 'O';
        else
            cout << 'o';
    }

    cout << '\n';

    return 0;
}