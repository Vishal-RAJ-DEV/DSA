#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Algorithm:
// 1) Keep the smallest price seen so far (mini).
// 2) For each day, compute profit = price - mini.
// 3) Track the maximum profit.
// 4) Update mini if a smaller price appears.

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int maxprofit = 0; // best profit so far
    int mini = prices[0]; // smallest price so far

    for (int i = 1; i < n; i++) {
        int cost = prices[i] - mini; // profit if we sell today
        maxprofit = max(maxprofit, cost); // update best profit
        mini = min(mini, prices[i]); // update smallest price
    }
    return maxprofit;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    int maxprofit = maxProfit(prices);
    cout << "the maximun profit can obtian will : " << maxprofit;
    return 0;
}