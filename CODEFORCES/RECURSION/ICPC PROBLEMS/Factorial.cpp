#include <iostream>
using namespace std;

long long factorial(int n) {
    // Base case
    if (n == 1) {
        return 1;
    }

    // Recursive case
    return n * factorial(n - 1);
}

int main() {
    int N;
    cin >> N;

    cout << factorial(N) << endl;

    return 0;
}