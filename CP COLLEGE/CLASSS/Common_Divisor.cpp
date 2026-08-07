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

    // freq[x] = number of times x appears in the input
    // WHY we store this array:
    //   We need to know, for any candidate divisor d, how many of our
    //   input numbers are divisible by d. Instead of scanning the whole
    //   input again and again, we first build this freq[] table indexed
    //   by value. Now "how many inputs are divisible by d" becomes just
    //   summing freq[d], freq[2d], freq[3d], ... which is O(MAX/d).
    //   This turns the O(n^2) pair checking into a fast O(MAX log MAX)
    //   sieve-like loop. Without freq[] we could not jump over multiples
    //   in one shot.
    vector<int> freq(MAX + 1, 0);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;          // record how many times this value appeared
    }

    // WHY we scan d from MAX down to 1 (largest to smallest):
    //   The answer is the largest number that divides at least one pair.
    //   By trying d = MAX, MAX-1, ..., 1, the FIRST d that has >= 2
    //   multiples in our input is guaranteed to be the maximum possible
    //   GCD, so we can print it and stop immediately.
    //   (If we scanned from 1 up, we would find the smallest GCD first,
    //    which is not what we want.)

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