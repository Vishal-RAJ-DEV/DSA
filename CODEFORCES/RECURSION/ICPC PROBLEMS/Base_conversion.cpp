#include <iostream>
using namespace std;

void binary(int n) {
    // Base case
    if (n == 0) {
        return;
    }

    // First process the quotient
    binary(n / 2);

    // Then print the remainder
    cout << n % 2;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        binary(N);
        cout << endl;
    }

    return 0;
}