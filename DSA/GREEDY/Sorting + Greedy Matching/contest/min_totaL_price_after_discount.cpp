#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double minimumTotalPrice(vector<int>& prices, vector<int>& discounts) {
        
        // Largest prices first
        sort(prices.rbegin(), prices.rend());

        // Largest discounts first
        sort(discounts.rbegin(), discounts.rend());

        int k = min(prices.size(), discounts.size());

        double ans = 0.0;

        // Apply largest discount to largest price
        for (int i = 0; i < k; i++) {
            ans += (double)prices[i] * (100 - discounts[i]) / 100.0;
        }

        // Remaining prices get no discount
        for (int i = k; i < prices.size(); i++) {
            ans += prices[i];
        }

        return ans;
    }
};


int main(){
    return 0;
}