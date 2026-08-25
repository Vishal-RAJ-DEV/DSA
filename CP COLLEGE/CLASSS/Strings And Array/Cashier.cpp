#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long L, a;

    cin >> n >> L >> a;

    long long answer = 0;
    long long currentTime = 0;

    for (int i = 0; i < n; i++) {
        long long t, l;
        cin >> t >> l;

        // Free time before this customer arrives
        long long freeTime = t - currentTime;

        // Maximum breaks possible in this free time
        answer += freeTime / a;

        // Vasya finishes serving this customer at:
        currentTime = t + l;
    }

    // Free time after the last customer
    answer += (L - currentTime) / a;

    cout << answer << endl;

    return 0;
}