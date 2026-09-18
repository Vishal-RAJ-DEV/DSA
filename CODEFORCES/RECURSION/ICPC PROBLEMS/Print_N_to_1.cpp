#include <iostream>
using namespace std;

void printNumbers(int n) {
    // Base case
    if (n == 0) {
        return;
    }

    cout << n;

    if (n > 1) {
        cout << " ";
    }

    printNumbers(n - 1);
}

int main() {
    int N;
    cin >> N;

    printNumbers(N);

    return 0;
}