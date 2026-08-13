#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long a, b, n;
        cin >> a >> b >> n;

        // We need only 1 movement if:
        // 1. All tabs can have fixed length b from the beginning
        //    => n * b <= a
        //
        // OR
        //
        // 2. a == b
        //    => rightmost close button always stays at a (= b)

        if (n * b <= a || a == b) {
            cout << 1 << '\n';
        } 
        else {
            // Otherwise:
            // 1 movement to a
            // 1 movement to b
            cout << 2 << '\n';
        }
    }

    return 0;
}