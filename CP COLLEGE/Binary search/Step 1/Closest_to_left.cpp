#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<long long> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    while (k--) {
        long long x;
        cin >> x;

        int left = 0;
        int right = n - 1;

        // Stores the 1-based answer
        int ans = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] <= x) {
                // This element is valid
                ans = mid + 1;

                // But maybe there is another valid element further right
                left = mid + 1;
            } else {
                // arr[mid] > x, search on the left
                right = mid - 1;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}