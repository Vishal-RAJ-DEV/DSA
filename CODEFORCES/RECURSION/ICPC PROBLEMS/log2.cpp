#include <iostream>
using namespace std;

long long log2Rec(long long n) {
    // Base case
    if (n < 2) {
        return 0;
    }

    return 1 + log2Rec(n / 2);
}

int main() {
    long long N;
    cin >> N;

    cout << log2Rec(N) << endl;

    return 0;
}