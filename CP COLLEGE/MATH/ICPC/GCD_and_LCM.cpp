#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long A, B;
    cin >> A >> B;

    long long gcd = __gcd(A, B);
    long long lcm = (A / gcd) * B;

    cout << gcd << " " << lcm << "\n";

    return 0;
}