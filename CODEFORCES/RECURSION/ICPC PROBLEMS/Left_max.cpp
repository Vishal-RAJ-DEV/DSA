#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void leftMax(vector<long long>& A, int i, long long maxVal, int N) {
    // Base case
    if (i == N)
        return;

    // Update maximum
    maxVal = max(maxVal, A[i]);

    // Print current prefix maximum
    cout << maxVal << " ";

    // Move to next element
    leftMax(A, i + 1, maxVal, N);
}

int main() {
    int N;
    cin >> N;

    vector<long long> A(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    leftMax(A, 0, A[0], N);

    return 0;
}

