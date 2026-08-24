#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int totalSum = 0;

    for (char ch : s) {
        totalSum += ch - '0';
    }

    // Special case: all digits are 0
    if (totalSum == 0) {
        cout << "YES\n";
        return 0;
    }

    // Try every possible target sum
    for (int target = 1; target <= totalSum; target++) {

        // Total sum must be divisible by target
        if (totalSum % target != 0)
            continue;

        int currentSum = 0;
        int segments = 0;
        bool possible = true;

        for (char ch : s) {
            currentSum += ch - '0';

            if (currentSum == target) {
                segments++;
                currentSum = 0;
            }
            else if (currentSum > target) {
                possible = false;
                break;
            }
        }

        // At least 2 segments are required
        if (possible && currentSum == 0 && segments >= 2) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";

    return 0;
}