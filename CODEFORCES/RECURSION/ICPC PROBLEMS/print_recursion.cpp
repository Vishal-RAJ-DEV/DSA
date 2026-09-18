#include <iostream>
using namespace std;

void printRecursion(int n) {
    // Base case
    if (n == 0) {
        return;
    }

    cout << "I love Recursion" << endl;

    // Recursive call
    printRecursion(n - 1);
}

int main() {
    int N;
    cin >> N;

    printRecursion(N);

    return 0;
}