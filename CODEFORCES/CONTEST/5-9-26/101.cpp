#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);

        for (int &x : a) {
            cin >> x;
        }

        vector<int> ones;

        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                ones.push_back(i);
            }
        }

        if (ones.empty()) {
            int bestL = -1;
            int bestR = -1;

            for (int i = 0; i < n; i++) {
                if (a[i] == -1) {
                    if (bestL == -1) {
                        bestL = i;
                    }
                    bestR = i;
                }
            }

            for (int i = 0; i < n; i++) {
                if (a[i] == -1) {
                    a[i] = 0;
                }
            }

            if (bestL != -1) {
                a[bestL] = 1;
                a[bestR] = 1;
            }
        } else {
            int bestLen = 1;
            int makeOne = -1;

            int firstOne = ones.front();

            for (int i = 0; i < firstOne; i++) {
                if (a[i] == -1) {
                    int len = firstOne - i + 1;

                    if (len > bestLen) {
                        bestLen = len;
                        makeOne = i;
                    }

                    break;
                }
            }

            for (int i = 1; i < (int)ones.size(); i++) {
                int prevOne = ones[i - 1];
                int curOne = ones[i];

                int len = curOne - prevOne + 1;

                if (len > bestLen) {
                    bestLen = len;
                    makeOne = -1;
                }
            }

            int lastOne = ones.back();

            for (int i = n - 1; i > lastOne; i--) {
                if (a[i] == -1) {
                    int len = i - lastOne + 1;

                    if (len > bestLen) {
                        bestLen = len;
                        makeOne = i;
                    }

                    break;
                }
            }

            for (int i = 0; i < n; i++) {
                if (a[i] == -1) {
                    a[i] = 0;
                }
            }

            if (makeOne != -1) {
                a[makeOne] = 1;
            }
        }

        for (int i = 0; i < n; i++) {
            cout << a[i] << (i + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}