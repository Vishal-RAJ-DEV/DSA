#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<ll> A(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    // Original values never change.
    sort(A.begin(), A.end());

    // Total amount subtracted from every element.
    i128 sub = 0;

    while (Q--) {
        int type;
        cin >> type;

        if (type == 1) {
            ll X;
            cin >> X;

            sub += X;
        }
        else {
            ll L, R, K;
            cin >> L >> R >> K;

            // Current value is:
            // original_value - sub
            //
            // L <= original_value - sub <= R
            //
            // Therefore:
            // L + sub <= original_value <= R + sub

            i128 leftValue = (i128)L + sub;
            i128 rightValue = (i128)R + sub;

            // First element >= leftValue
            auto left = lower_bound(
                A.begin(),
                A.end(),
                leftValue,
                [](ll value, i128 target) {
                    return (i128)value < target;
                }
            );

            // First element > rightValue
            auto right = upper_bound(
                A.begin(),
                A.end(),
                rightValue,
                [](i128 target, ll value) {
                    return target < (i128)value;
                }
            );

            // Number of elements inside [leftValue, rightValue]
            ll count = right - left;

            if (count < K) {
                cout << -1 << '\n';
            }
            else {
                // K-th element
                ll originalValue = *(left + (K - 1));

                // Convert back to current value
                i128 answer = (i128)originalValue - sub;

                // Print __int128
                if (answer == 0) {
                    cout << 0;
                }
                else {
                    if (answer < 0) {
                        cout << '-';
                        answer = -answer;
                    }

                    string s;

                    while (answer > 0) {
                        s.push_back('0' + answer % 10);
                        answer /= 10;
                    }

                    reverse(s.begin(), s.end());
                    cout << s;
                }

                cout << '\n';
            }
        }
    }

    return 0;
}