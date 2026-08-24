#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Maximum possible k
    int maximumK = *max_element(a.begin(), a.end()) + m;

    // Minimum possible k
    for (int i = 0; i < m; i++) {
        int minIndex = min_element(a.begin(), a.end()) - a.begin();

        a[minIndex]++;
    }

    int minimumK = *max_element(a.begin(), a.end());

    cout << minimumK << " " << maximumK << '\n';

    return 0;
}