#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<vector<int>> ans;

        sort(nums.begin(), nums.end());

        long long prev = (long long)lower - 1;

        for (int x : nums) {

            // Ignore numbers outside the required range
            if (x < lower) continue;
            if (x > upper) break;

            // Missing range exists
            if (x > prev + 1) {
                ans.push_back({(int)(prev + 1), x - 1});
            }

            prev = x;
        }

        // Check the range after the last number
        if (prev < upper) {
            ans.push_back({(int)(prev + 1), upper});
        }

        return ans;
    }
};


int main(){
    return 0;
}