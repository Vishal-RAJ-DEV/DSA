#include <bits/stdc++.h>
using namespace std;

const long long MOD = 9973;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int pos = -1;

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;

            if (x == n) {
                pos = i;
            }
        }
        //left part of the max elemnet in the array , so total subarray in the left will not contain the max element 
        long long left = pos;
        //same here for the right part of the max element in the array , so total subarray in the right will not contain the max element
        long long right = n - pos - 1;

        long long ans = 0;

        //use the formula where total no of subarray on array leength n is n*(n+1)/2
        //so here we will calculate the total subarray in the left and right part of the max element
        //and add them to the answer and take mod of the answer
        // that's it we will get the total subarray which does not contain the max element in the array

        ans += left * (left + 1) / 2;
        ans += right * (right + 1) / 2;

        ans %= MOD;

        cout << ans << '\n';
    }

    return 0;
}