#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxBridges(vector<pair<int, int>>& bridges) {
        int n = bridges.size();

        // QUESTION:
        // Each pair {north, south} represents a possible bridge
        // connecting a northern city to its corresponding southern city.
        // We need to build the maximum number of bridges such that
        // no two selected bridges cross each other.

        // APPROACH:
        // Sort bridges by north coordinates in ascending order.
        // If north coordinates are equal, sort south coordinates
        // in descending order to prevent selecting bridges that
        // share the same northern coordinate.
        //
        // After sorting, apply LIS on south coordinates using DP.
        sort(bridges.begin(), bridges.end(), [](auto& a, auto& b) {
            if (a.first == b.first)
                return a.second > b.second;

            return a.first < b.first;
        });

        // dp[i] = maximum number of non-crossing bridges
        // in a sequence ending at bridge i.
        // Every bridge can be selected individually, so initialize
        // each dp value with 1.
        vector<int> dp(n, 1);

        int ans = 1;

        // Consider each bridge as the ending bridge of a sequence.
        for (int i = 1; i < n; i++) {

            // Check all bridges before the current bridge.
            for (int j = 0; j < i; j++) {

                // North is already sorted.
                // If south also increases, the bridges do not cross.
                if (bridges[i].second > bridges[j].second) {

                    // Extend the best sequence ending at bridge j.
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }

            // Update the maximum number of bridges found so far.
            ans = max(ans, dp[i]);
        }

        // Return the maximum number of non-crossing bridges.
        return ans;
    }
};

int main() {
    Solution sol;

    vector<pair<int, int>> bridges = {
        {6, 2}, {4, 3}, {2, 6}, {1, 5}
    };

    cout << sol.maxBridges(bridges) << endl;

    return 0;
}