#include <iostream>
using namespace std;

void sumMatrix(int A[][100], int B[][100], int R, int C, int i, int j) {
    // Base case
    if (i == R) {
        return;
    }

    cout << A[i][j] + B[i][j];

    // Print space between columns
    if (j < C - 1) {
        cout << " ";
    }

    // Move to next element
    if (j == C - 1) {
        cout << endl;
        sumMatrix(A, B, R, C, i + 1, 0);
    } else {
        sumMatrix(A, B, R, C, i, j + 1);
    }
}

int main() {
    int R, C;
    cin >> R >> C;

    int A[100][100], B[100][100];

    // Input matrix A
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> A[i][j];
        }
    }

    // Input matrix B
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> B[i][j];
        }
    }

    sumMatrix(A, B, R, C, 0, 0);

    return 0;
}

/*⭐ Key idea

There are two recursive movements:

j + 1

→ move to the next column.

When the row ends:

i + 1, 0

→ move to the next row and start from column 0.

This is basically nested loops converted into recursion.

*/