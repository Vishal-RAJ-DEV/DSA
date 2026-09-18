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

void pyramid(int row, int N) {
    // Base case
    if (row > N) {
        return;
    }

    // Print current row
    printRow(N - row, 2 * row - 1);
    cout << endl;

    // Move to next row
    pyramid(row + 1, N);
}

int main() {
    int N;
    cin >> N;

    pyramid(1, N);

    return 0;
}