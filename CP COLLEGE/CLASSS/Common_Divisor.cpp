#include <bits/stdc++.h>
using namespace std;



int maximumGCD(vector<int>& nums) {

    int n = nums.size();
    int ans = 1;

    // Check every possible pair
    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            // Compute GCD of the pair
            ans = max(ans, __gcd(nums[i], nums[j]));
        }
    }

    return ans;
}



const int MAX = 1000000;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // freq[x] = number of times x appears
    vector<int> freq(MAX + 1, 0);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }

    // Try every possible GCD from largest to smallest
    for (int d = MAX; d >= 1; d--) {

        int cnt = 0;

        // Count numbers divisible by d
        for (int multiple = d; multiple <= MAX; multiple += d) {
            cnt += freq[multiple];
        }

        // If at least two numbers are divisible by d,
        // then d is the largest possible GCD.
        if (cnt >= 2) {
            cout << d << "\n";
            return 0;
        }
    }
}