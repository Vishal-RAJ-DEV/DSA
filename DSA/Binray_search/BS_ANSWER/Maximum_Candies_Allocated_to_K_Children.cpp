#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool canGive(vector<int>& candies, long long k, long long x) {

        long long children = 0;

        for (long long pile : candies) {

            children += pile / x;

            if (children >= k)
                return true;
        }

        return false;
    }

    int maximumCandies(vector<int>& candies, long long k) {

        long long left = 1;
        long long right = *max_element(candies.begin(), candies.end());

        while (left <= right) {

            long long mid = left + (right - left) / 2;

            if (canGive(candies, k, mid)) {

                // mid is possible
                // Search for a larger value
                left = mid + 1;

            } else {

                // mid is not possible
                // Search for a smaller value
                right = mid - 1;
            }
        }

        // right = maximum possible (last TRUE)
        return right;
    }
};


int main(){
    return 0;
}