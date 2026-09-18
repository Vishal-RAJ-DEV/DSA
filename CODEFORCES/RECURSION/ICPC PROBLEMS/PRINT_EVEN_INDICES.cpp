#include <iostream>
using namespace std;

void printEvenReverse(int A[], int i, int N) {
    // Base case
    if (i >= N) {
        return;
    }

    // Go to the next even index
    printEvenReverse(A, i + 2, N);

    // Print while returning from recursion
    cout << A[i] << " ";
}

int main() {
    int N;
    cin >> N;

    int A[N];

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    printEvenReverse(A, 0, N);

    return 0;
}