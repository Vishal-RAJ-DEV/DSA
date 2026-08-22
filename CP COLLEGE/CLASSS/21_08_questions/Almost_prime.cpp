#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int ans = 0;

    for (int num = 2; num <= n; num++) {

        int x = num;
        int distinctPrimeFactors = 0;

        for (int i = 2; i * i <= x; i++) {

            if (x % i == 0) {
                distinctPrimeFactors++;

                // Remove all occurrences of i
                while (x % i == 0) {
                    x /= i;
                }
            }
        }

        // If something greater than 1 remains,
        // it is one more prime factor
        if (x > 1) {
            distinctPrimeFactors++;
        }

        if (distinctPrimeFactors == 2) {
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}