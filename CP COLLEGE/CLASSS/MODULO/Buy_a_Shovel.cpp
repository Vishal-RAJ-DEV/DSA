#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, r;
    cin >> k >> r;

    for (int i = 1; i <= 10; i++) {

        int lastDigit = (i * k) % 10;

        // Can pay using only 10-burle coins
        // OR using the one r-burle coin
        if (lastDigit == 0 || lastDigit == r) {
            cout << i << endl;
            return 0;
        }
    }

    return 0;
}