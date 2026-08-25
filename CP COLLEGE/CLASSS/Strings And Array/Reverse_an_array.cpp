#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> arr(N);

    // Input the array
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    // Print the array in reverse order
    for (int i = N - 1; i >= 0; i--) {
        cout << arr[i] << " ";
    }

    return 0;
}