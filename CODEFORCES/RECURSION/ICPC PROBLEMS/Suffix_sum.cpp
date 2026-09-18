#include <iostream>
using namespace std;

long long suffixSum(long long A[], int index, int N) {
    // Base case
    if (index == N) {
        return 0;
    }

    return A[index] + suffixSum(A, index + 1, N);
}

int main() {
    int N, M;
    cin >> N >> M;

    long long A[N];

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    // Start from the first element of the last M elements
    int start = N - M;

    cout << suffixSum(A, start, N) << endl;

    return 0;
}