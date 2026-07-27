#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int RA, CA;
    cin >> RA >> CA;

    vector<vector<int>> A(RA, vector<int>(CA));
    for (int i = 0; i < RA; i++) {
        for (int j = 0; j < CA; j++) {
            cin >> A[i][j];
        }
    }

    int RB, CB;
    cin >> RB >> CB;

    vector<vector<int>> B(RB, vector<int>(CB));
    for (int i = 0; i < RB; i++) {
        for (int j = 0; j < CB; j++) {
            cin >> B[i][j];
        }
    }

    vector<vector<int>> C(RA, vector<int>(CB, 0));

    for (int i = 0; i < RA; i++) {
        for (int j = 0; j < CB; j++) {
            for (int k = 0; k < CA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for (int i = 0; i < RA; i++) {
        for (int j = 0; j < CB; j++) {
            cout << C[i][j];
            if (j + 1 < CB) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}