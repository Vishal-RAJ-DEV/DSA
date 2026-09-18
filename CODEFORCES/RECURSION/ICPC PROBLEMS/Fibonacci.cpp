#include <iostream>
using namespace std;

int fibonacci(int n) {
    // Base cases
    if (n == 1)
        return 0;

    if (n == 2)
        return 1;

    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int N;
    cin >> N;

    cout << fibonacci(N) << endl;

    return 0;
}