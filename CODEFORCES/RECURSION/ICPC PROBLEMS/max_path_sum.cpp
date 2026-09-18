#include <iostream>
#include <vector>
using namespace std;

long long maxPath(vector<vector<long long>>& A, int i, int j, int N, int M) {
    // Reached destination
    if (i == N - 1 && j == M - 1)
        return A[i][j];

    // If we are at the last row, we can only move right
    if (i == N - 1)
        return A[i][j] + maxPath(A, i, j + 1, N, M);

    // If we are at the last column, we can only move down
    if (j == M - 1)
        return A[i][j] + maxPath(A, i + 1, j, N, M);

    // Two choices: down or right
    return A[i][j] + max(
        maxPath(A, i + 1, j, N, M),
        maxPath(A, i, j + 1, N, M)
    );
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<long long>> A(N, vector<long long>(M));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> A[i][j];
        }
    }

    cout << maxPath(A, 0, 0, N, M) << endl;

    return 0;
}
