#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> divisors(n + 1, 0);

    // Count divisors of every number
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            divisors[j]++;
        }
    }

    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        ans += divisors[i];
    }

    cout << ans << '\n';

    return 0;
}