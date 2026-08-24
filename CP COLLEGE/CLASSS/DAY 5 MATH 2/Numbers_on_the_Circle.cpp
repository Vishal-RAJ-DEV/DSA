#include <bits/stdc++.h>
using namespace std;

int main() {
    long long N;
    cin >> N;

    long long answer = 0;

    // Remove every neighboring pair
    for (long long i = 1; i <= N; i++) {

        long long next = (i % N) + 1;
        long long product = 1;

        // Multiply all numbers except i and next
        for (long long j = 1; j <= N; j++) {
            if (j == i || j == next)
                continue;

            product *= j;
        }

        answer += product;
    }

    cout << answer << '\n';

    return 0;
}