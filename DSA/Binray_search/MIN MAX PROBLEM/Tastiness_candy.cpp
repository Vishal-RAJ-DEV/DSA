#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
QUESTION (Leetcode 2517 - Maximum Tastiness of Candy Basket):
You are given an array 'price' where price[i] is the price of the i-th candy.
You need to form a basket with EXACTLY k candies.
The "tastiness" of the basket is the MINIMUM absolute difference between
any two candies in the basket.

You want to MAXIMIZE this tastiness (i.e., make the smallest gap as large as possible).

EXAMPLE:
price = [1, 3, 5, 8], k = 3
Pick 3 candies to maximize the minimum difference.

If we pick [1, 5, 8]: differences = 4, 3 -> min diff = 3
If we pick [1, 3, 8]: differences = 2, 5 -> min diff = 2
If we pick [3, 5, 8]: differences = 2, 3 -> min diff = 2

Best answer = 3 (pick [1, 5, 8]).
*/

class Solution {
public:
    /*
    isValid(minDiff, price, k):
    Checks if we can pick k candies such that EVERY pair has
    difference >= minDiff.

    How? Greedy approach:
    1. Sort the array (done once in main function).
    2. Always pick the first candy (smallest).
    3. Then pick the next candy ONLY if its price - last picked >= minDiff.
    4. Count how many we can pick this way.
    5. If count >= k, it's possible -> return true.

    Why greedy works?
    Since the array is sorted, picking the smallest possible candy
    at each step leaves the most room for future picks. This gives
    the maximum number of candies we can select with the given minDiff.
    If even this greedy can't pick k candies, no arrangement can.
    */
    bool isValid(int minDiff , vector<int>&price  , int k){
        int cnt = 1;          // we always pick the first candy
        int prev = price[0];  // last picked candy

        for(int i = 1; i < price.size() ; i++){
            // Pick this candy only if it's far enough from the last picked
            if( price[i] - prev >= minDiff){
                cnt++;
                prev = price[i];
            }
        }

        // If we can pick at least k candies, this minDiff is achievable
        return cnt >= k;
    }

    int maximumTastiness(vector<int>& price, int k) {
        sort(price.begin() , price.end());
        int n = price.size();
        int start = 0;                    // minimum possible tastiness
        int end = price[n-1] - price[0];  // maximum possible tastiness

        // Binary search on the ANSWER (tastiness = minimum difference)
        // We ask: "Can we pick k candies with min diff >= mid?"
        // If yes -> try a larger min diff (search right)
        // If no  -> try a smaller min diff (search left)
        int ans = -1;
        while(start <= end){
            int mid = start + ( end - start) / 2;

            if(isValid(mid , price , k)){
                ans = mid;
                start = mid + 1;  // try for a larger tastiness
            }
            else end = mid - 1;   // too ambitious, reduce
        }

        return ans;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<int> price = {1, 3, 5, 8};
    int k = 3;

    int maxTastiness = sol.maximumTastiness(price, k);
    cout << "Maximum Tastiness: " << maxTastiness << endl; // Expected: 3

    return 0;
}