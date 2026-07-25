#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    int64 A, B, Q;
    cin >> A >> B >> Q;

    Q %= 3;

    if (Q == 1)
        cout << A;
    else if (Q == 2)
        cout << B;
    else
        cout << (A ^ B);

    return 0;
}