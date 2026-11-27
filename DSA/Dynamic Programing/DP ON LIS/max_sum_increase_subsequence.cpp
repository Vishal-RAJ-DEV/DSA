#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSumIS(vector<int>& arr) {
        int n = arr.size();

        if (n == 0) return 0;

        vector<int> dp = arr;

        int ans = arr[0];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) {
                    dp[i] = max(dp[i], dp[j] + arr[i]);
                }
            }

            ans = max(ans, dp[i]);
        }

        return ans;
    }
};





class Solution {
  public:
    int maxSumIS(vector<int> &arr) {
      // code here
      int n = arr.size();

      vector<int> dp = arr;
      vector<int> parent(n);

      int maxi = 1;
      int lastidx = 0;

      for (int i = 0; i < n; i++) {
        parent[i] = i;
      }

      for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
          if (arr[j] < arr[i] && dp[j] + arr[i] > dp[i]) {
            dp[i] = max(dp[i], dp[j] + arr[i]);
            parent[i] = j;
          }
        }

        if (dp[i] > maxi) {
          maxi = dp[i];
          lastidx = i;
        }
      }

        int ans  = 0;

      while (parent[lastidx] != lastidx) {
        ans += arr[lastidx];
        lastidx = parent[lastidx];
      }
      ans+= arr[lastidx];

      return ans;
    }
};




int main(){
    return 0;
}