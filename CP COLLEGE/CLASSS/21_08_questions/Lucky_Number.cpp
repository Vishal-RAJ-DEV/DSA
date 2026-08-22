#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> lucky = {
        4, 7,
        44, 47, 74, 77,
        444, 447, 474, 477,
        744, 747, 774, 777
    };

    for (int x : lucky) {
        if (n % x == 0) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";

    return 0;
}