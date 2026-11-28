#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
static bool comp(vector<int>& a, vector<int>& b) {

    // If two envelopes have the same width, sort their heights
    // in decreasing order.
    //
    // REASON:
    // Envelopes with the same width cannot be nested because
    // nesting requires width1 < width2.
    //
    // If we sort their heights in increasing order, LIS may
    // incorrectly select both envelopes because their heights
    // would form an increasing subsequence.
    //
    // Sorting heights in decreasing order prevents LIS from
    // selecting both envelopes, ensuring the width condition
    // is not violated.
    if (a[0] == b[0]) {
        return a[1] > b[1];
    }

    // Sort widths in increasing order so that we can apply
    // LIS on the heights to find the maximum nested envelopes.
    return a[0] < b[0];
}
        
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), comp);
        int i, j, n=envelopes.size();
        vector<int>lis;
        
        for(i=0; i<n; i++){
            auto it = lower_bound(lis.begin(), lis.end(), envelopes[i][1]);
            if(it==lis.end()){lis.push_back(envelopes[i][1]);}
            else{
                *it = envelopes[i][1];
            }
        }
        return lis.size();
    }
};



class Solution {
public:
static bool comp(vector<int>& a, vector<int>& b) {

    // If two envelopes have the same width, sort their heights
    // in decreasing order.
    //
    // REASON:
    // Envelopes with the same width cannot be nested because
    // nesting requires width1 < width2.
    //
    // If we sort their heights in increasing order, LIS may
    // incorrectly select both envelopes because their heights
    // would form an increasing subsequence.
    //
    // Sorting heights in decreasing order prevents LIS from
    // selecting both envelopes, ensuring the width condition
    // is not violated.
    if (a[0] == b[0]) {
        return a[1] > b[1];
    }

    // Sort widths in increasing order so that we can apply
    // LIS on the heights to find the maximum nested envelopes.
    return a[0] < b[0];
}

    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), comp);

        int n = envelopes.size();

        vector<int> dp(n, 1);

        int ans = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {

                if (envelopes[j][0] < envelopes[i][0] &&
                    envelopes[j][1] < envelopes[i][1]) {

                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }

            ans = max(ans, dp[i]);
        }

        return ans;
    }
};


class Solution {
public:
    static bool compare(vector<int>& a, vector<int>& b) {
        if (a[0] == b[0]) {
            return a[1] > b[1];
        }
        return a[0] < b[0];
    }

    int solve(int i, vector<vector<int>>& envelopes, vector<int>& dp) {
        if (dp[i] != -1) {
            return dp[i];
        }

        int n = envelopes.size();
        int ans = 1;

        for (int j = i + 1; j < n; j++) {
            if (envelopes[i][0] < envelopes[j][0] &&
                envelopes[i][1] < envelopes[j][1]) {

                ans = max(ans, 1 + solve(j, envelopes, dp));
            }
        }

        return dp[i] = ans;
    }

    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), compare);

        int n = envelopes.size();

        vector<int> dp(n, -1);

        int ans = 1;

        for (int i = 0; i < n; i++) {
            ans = max(ans, solve(i, envelopes, dp));
        }

        return ans;
    }
};



int main(){
    return 0;
}