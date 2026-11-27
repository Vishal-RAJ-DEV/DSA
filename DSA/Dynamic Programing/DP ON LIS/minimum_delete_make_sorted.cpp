#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minDeletions(vector<int> &arr) {
      // code here

      int n = arr.size();

      vector<int> temp;

      for (int i = 0; i < n; i++) {

        
        int index =
            lower_bound(temp.begin(), temp.end(), arr[i]) - temp.begin();

        if (index == temp.size()) {
          temp.push_back(arr[i]);
        }

        // Otherwise, replace that element
        else {
          temp[index] = arr[i];
        }
      }

      return n - temp.size();
    }
};

using namespace std;

class Solution {
public:
    int minDeletions(vector<int>& arr) {
        int n = arr.size();

        vector<int> dp(n, 1);

        int maxi = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] <= arr[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }

            maxi = max(maxi, dp[i]);
        }

        return n - maxi;
    }
};







int main(){
    return 0;
}