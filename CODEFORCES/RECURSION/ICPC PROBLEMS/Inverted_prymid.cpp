#include <iostream>
using namespace std;

void printRow(int spaces, int stars) {
    if (spaces > 0) {
        cout << " ";
        printRow(spaces - 1, stars);
        return;
    }

    if (stars > 0) {
        cout << "*";
        printRow(0, stars - 1);
    }
}

void invertedPyramid(int row, int N) {
    // Base case
    if (row > N) {
        return;
    }

    // Print current row
    printRow(row - 1, 2 * (N - row) + 1);
    cout << endl;

    // Next row
    invertedPyramid(row + 1, N);
}

int main() {
    int N;
    cin >> N;

    invertedPyramid(1, N);

    return 0;
}