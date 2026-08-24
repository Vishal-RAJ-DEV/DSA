#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long cost = 0;
    int negativeCount = 0;
    int zeroCount = 0;

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;

        if (x > 0) {
            // Convert x to 1
            cost += x - 1;
        }
        else if (x < 0) {
            // Convert x to -1
            cost += -1 - x;
            negativeCount++;
        }
        else {
            // Convert 0 to either 1 or -1
            cost += 1;
            zeroCount++;
        }
    }

    // Product is -1 if negatives are odd.
    // If no zero exists, changing -1 to 1 costs 2.
    if (negativeCount % 2 == 1 && zeroCount == 0) {
        cost += 2;
    }

    cout << cost << '\n';

    return 0;
}