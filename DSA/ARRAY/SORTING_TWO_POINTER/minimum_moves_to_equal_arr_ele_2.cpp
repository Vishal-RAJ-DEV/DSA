#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int mini = *min_element(nums.begin(), nums.end());
        int maxi = *max_element(nums.begin(), nums.end());

        int ans = INT_MAX;

        for(int target = mini; target <= maxi; target++) {
            int moves = 0;

            for(int x : nums) {
                moves += abs(x - target);
            }

            ans = min(ans, moves);
        }

        return ans;
    }
};

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int n = nums.size();
        int x = nums[n / 2];

        int moves = 0;

        for(int i = 0; i < n; i++) {
            moves += abs(x - nums[i]);
        }

        return moves;
    }
};


class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();

        nth_element(nums.begin(), nums.begin() + n / 2, nums.end());

        int median = nums[n / 2];
        int moves = 0;

        for(int x : nums) {
            moves += abs(x - median);
        }

        return moves;
    }
};



int main(){
    return 0;
}