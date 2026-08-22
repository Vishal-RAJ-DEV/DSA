#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, x;
    cin >> n >> x;

    int ans = 0;

    for (long long i = 1; i <= n; i++) {
        
        // i must divide x
        if (x % i == 0) {
            
            long long j = x / i;

            // Column must exist in the n × n table
            if (j <= n) {
                ans++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}