#include <bits/stdc++.h>
using namespace std;

int main() {

    long double C;
    cin >> C;

    long double low = 0;
    long double high = sqrt(C);

    for (int i = 0; i < 100; i++) {

        long double mid = low + (high - low) / 2;

        long double value = mid * mid + sqrt(mid);

        if (value < C) {
            // mid is too small
            low = mid;
        } 
        else {
            // mid is large enough
            high = mid;
        }
    }

    cout << fixed << setprecision(15) << (double)low << endl;

    return 0;
}