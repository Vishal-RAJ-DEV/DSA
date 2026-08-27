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

        // Default answer: n + 1
        int ans = n + 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] >= x) {
                // This is a possible answer
                ans = mid + 1;

                // Search for an earlier valid element
                right = mid - 1;
            }
            else {
                // arr[mid] < x
                left = mid + 1;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}