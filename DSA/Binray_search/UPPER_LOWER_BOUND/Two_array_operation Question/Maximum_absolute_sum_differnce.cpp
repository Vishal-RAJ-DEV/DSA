#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {

        const int MOD = 1e9 + 7;

        // Make a sorted copy for binary search
        vector<int> sorted = nums1;
        sort(sorted.begin(), sorted.end());

        long long total = 0;
        int maxGain = 0;

        for (int i = 0; i < nums1.size(); i++) {

            int current = abs(nums1[i] - nums2[i]);

            // Original total
            total += current;

            // Find first element >= nums2[i]
            auto it = lower_bound(sorted.begin(), sorted.end(), nums2[i]);

            // Candidate 1: element >= target
            if (it != sorted.end()) {
                int newDiff = abs(*it - nums2[i]);

                maxGain = max(maxGain, current - newDiff);
            }

            // Candidate 2: element < target
            if (it != sorted.begin()) {
                --it;

                int newDiff = abs(*it - nums2[i]);

                maxGain = max(maxGain, current - newDiff);
            }
        }

        return (total - maxGain) % MOD;
    }
};



int main(){
    return 0;
}