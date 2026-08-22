#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, x, y;
    cin >> a >> b >> x >> y;

    // Reduce the aspect ratio
    long long g = __gcd(x, y);

    x /= g;
    y /= g;

    // Find how many multiples fit
    long long ans = min(a / x, b / y);

    cout << ans << '\n';

    return 0;
}