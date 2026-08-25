#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> candies(N);

    // Input candies for each kid
    for (int i = 0; i < N; i++) {
        cin >> candies[i];
    }

    int A, B;
    cin >> A >> B;

    long long sum = 0;

    // Sum candies from index A to B
    for (int i = A; i <= B; i++) {
        sum += candies[i];
    }

    cout << sum << endl;

    return 0;
}