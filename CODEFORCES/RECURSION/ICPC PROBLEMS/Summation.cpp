#include <iostream>
using namespace std;

long long sumArray(long long A[], int index, int N) {
    // Base case
    if (index == N) {
        return 0;
    }

    // Current element + sum of remaining elements
    return A[index] + sumArray(A, index + 1, N);
}

int main() {
    int N;
    cin >> N;

    long long A[N];

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    cout << sumArray(A, 0, N) << endl;

    return 0;
}