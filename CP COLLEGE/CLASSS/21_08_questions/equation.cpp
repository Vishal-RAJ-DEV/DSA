#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n % 2 == 0) {
        cout << n + 4 << " " << 4 << '\n';
    } 
    else {
        cout << n + 9 << " " << 9 << '\n';
    }

    return 0;
}