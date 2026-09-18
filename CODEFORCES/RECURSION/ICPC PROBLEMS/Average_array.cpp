#include <iostream>
#include <iomanip>
using namespace std;

long long sumArray(long long A[], int index, int N) {
    // Base case
    if (index == N) {
        return 0;
    }

    return A[index] + sumArray(A, index + 1, N);
}

int main() {
    int N;
    cin >> N;

    long long A[N];

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    long long sum = sumArray(A, 0, N);

    double average = (double)sum / N;

    cout << fixed << setprecision(6) << average << endl;

    return 0;
}