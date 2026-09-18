#include <iostream>
using namespace std;

void printNumbers(int n) {
    if (n == 0) {
        return;
    }

    printNumbers(n - 1);  // first go down
    cout << n << endl;    // then print
}

int main() {
    int N;
    cin >> N;

    printNumbers(N);

    return 0;
}