#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    // prefix[i] = sum of first i elements
    vector<long long> prefix(N + 1, 0);

    // Build prefix sum
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;

        prefix[i + 1] = prefix[i] + x;
    }

    // Answer queries
    while (Q--) {
        int A, B;
        cin >> A >> B;

        cout << prefix[B + 1] - prefix[A] << '\n';
    }

    return 0;
}