#include <iostream>
using namespace std;

long long findMax(long long A[], int index, int N) {
    // Base case: last element
    if (index == N - 1) {
        return A[index];
    }

    // Find maximum in the remaining elements
    long long maxRest = findMax(A, index + 1, N);

    // Compare current element with maximum of rest
    return max(A[index], maxRest);
}

int main() {
    int N;
    cin >> N;

    long long A[N];

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    cout << findMax(A, 0, N) << endl;

    return 0;
}