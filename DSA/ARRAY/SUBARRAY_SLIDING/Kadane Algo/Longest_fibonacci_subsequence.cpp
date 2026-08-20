#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Let's understand the DP visually

Imagine:
arr = [1, 2, 3, 5, 8]
        0  1  2  3  4

We eventually want:
1 → 2 → 3 → 5 → 8

The DP states are:
dp[0][1]
  1,2
  length = 2

dp[1][2]
  2,3 b
previous = 3 - 2 = 1
index of 1 = 0


dp[1][2] = dp[0][1] + 1
          = 2 + 1
          = 3

sequence:
1 → 2 → 3

Next:
dp[2][3]
  3,5
previous = 5 - 3
         = 2

index of 2 = 1
dp[2][3] = dp[1][2] + 1
          = 3 + 1
          = 4
sequence:
1 → 2 → 3 → 5

Next:
dp[3][4]
  5,8
previous = 8 - 5
         = 3
index of 3 = 2
dp[3][4] = dp[2][3] + 1
          = 4 + 1
          = 5

So:
1 → 2 → 3 → 5 → 8


length = 5
*/
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {

        int n = arr.size();

        // value -> index
        unordered_map<int, int> mp;

        for (int i = 0; i < n; i++) {
            mp[arr[i]] = i;
        }

        // dp[i][j] = longest Fibonacci-like subsequence
        // ending with arr[i], arr[j]
        vector<vector<int>> dp(n, vector<int>(n, 2));

        int ans = 0;

        for (int j = 0; j < n; j++) {

            for (int i = 0; i < j; i++) {

                // We need:
                // arr[k] + arr[i] = arr[j]
                //
                // Therefore:
                // arr[k] = arr[j] - arr[i]

                int prev = arr[j] - arr[i];

                if (mp.count(prev)) {

                    int k = mp[prev];

                    // k must come before i
                    if (k < i) {
                        dp[i][j] = dp[k][i] + 1;
                    }
                }

                ans = max(ans, dp[i][j]);
            }
        }

        // A Fibonacci-like sequence must have length >= 3
        return ans >= 3 ? ans : 0;
    }
};


int main(){
    return 0;
}