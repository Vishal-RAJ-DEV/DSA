#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (long long k = 1; k <= n; k++) {
        int n = k * k;
        if(k == 1) {
            cout << 0 << '\n';
            continue;
        }
        //total ways to place 2 knights on a k x k chessboard is nC2 = n*(n-1)/2
        long long total = n * (n - 1) / 2;
        //attacking ways to place 2 knights on a k x k chessboard is 4*(k-1)*(k-2)
        long long attacking = 4 * (k - 1) * (k - 2);
        cout << total - attacking << '\n';
    }
}   