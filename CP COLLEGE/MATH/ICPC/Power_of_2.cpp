#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    if ((n & (n - 1)) == 0)
        cout << "YES";
    else
        cout << "NO";

    return 0;
}