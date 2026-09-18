#include <iostream>
using namespace std;

bool canReach(long long n) {
    // Base case
    if (n == 1)
        return true;

    // If n cannot be divided by 10 or 20,
    // it could not have been obtained from 1.
    if (n % 10 != 0 && n % 20 != 0)
        return false;

    // Try dividing by 10
    if (n % 10 == 0 && canReach(n / 10))
        return true;

    // Try dividing by 20
    if (n % 20 == 0 && canReach(n / 20))
        return true;

    return false;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        long long N;
        cin >> N;

        if (canReach(N))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
