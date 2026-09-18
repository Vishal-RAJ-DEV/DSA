#include <iostream>
using namespace std;

long long sequenceLength(long long n) {
    // Base case
    if (n == 1) {
        return 1;
    }

    // If n is even
    if (n % 2 == 0) {
        return 1 + sequenceLength(n / 2);
    }

    // If n is odd
    return 1 + sequenceLength(3 * n + 1);
}

int main() {
    long long n;
    cin >> n;

    cout << sequenceLength(n) << endl;

    return 0;
}
