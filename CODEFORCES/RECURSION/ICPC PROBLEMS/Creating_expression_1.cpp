#include <iostream>
#include <vector>
using namespace std;

bool solve(vector<long long>& A, int index, long long current, long long X) {
    // All numbers have been used
    if (index == A.size()) {
        return current == X;
    }

    // Put '+'
    if (solve(A, index + 1, current + A[index], X))
        return true;

    // Put '-'
    if (solve(A, index + 1, current - A[index], X))
        return true;

    return false;
}

int main() {
    int N;
    long long X;

    cin >> N >> X;

    vector<long long> A(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    // First number is fixed
    if (solve(A, 1, A[0], X))
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}