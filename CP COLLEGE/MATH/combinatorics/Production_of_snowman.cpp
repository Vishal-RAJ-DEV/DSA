#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int countValidShifts(const vector<int>& A, const vector<int>& B) {
    int n = A.size();
    int cnt = 0;

    // Try every cyclic shift of B
    for (int shift = 0; shift < n; shift++) {
        bool valid = true;

        // Check A[x] < B[(x + shift) % n]
        for (int x = 0; x < n; x++) {
            if (A[x] >= B[(x + shift) % n]) {
                valid = false;
                break;
            }
        }

        if (valid) {
            cnt++;
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n), b(n), c(n);

        for (int &x : a) cin >> x;
        for (int &x : b) cin >> x;
        for (int &x : c) cin >> x;

        int cntAB = countValidShifts(a, b);
        int cntBC = countValidShifts(b, c);

        long long ans = 1LL * n * cntAB * cntBC;

        cout << ans << '\n';
    }

    return 0;
}