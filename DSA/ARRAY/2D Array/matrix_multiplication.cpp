#include <iostream>
using namespace std;

int main() {
    int n, m, p;

    cout << "Enter rows and columns of Matrix A: ";
    cin >> n >> m;

    cout << "Enter columns of Matrix B: ";
    cin >> p;

    int A[n][m], B[m][p], C[n][p];

    cout << "Enter Matrix A:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Enter Matrix B:\n";
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < p; j++) {
            cin >> B[i][j];
        }
    }

    // Initialize result matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            C[i][j] = 0;
        }
    }

    // Matrix Multiplication
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            for(int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << "Result Matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}