#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    if (n % 3 == 0) {
        cout << 1 << " " << 1 << " " << n - 2 << endl;
    }
    else if (n % 3 == 1) {
        cout << 1 << " " << 2 << " " << n - 3 << endl;
    }
    else {
        cout << 2 << " " << 2 << " " << n - 4 << endl;
    }

    return 0;
}