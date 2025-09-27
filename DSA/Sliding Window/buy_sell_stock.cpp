#include <iostream>
#include <bits/stdc++.h>
using namespace std;

    int maxProfit(vector<int>& prices) {
        int n = prices.size();         // Store the size of prices array
        int maxprofit = 0;             // Initialize maximum profit to 0
        int mini = prices[0];          // Initialize minimum price to the first day's price
        
        // Loop through each day starting from day 2
        for(int i = 1; i < n; i++) {
            // Calculate profit if we buy at minimum price so far and sell today
            int cost = prices[i] - mini;
            
            // Update maximum profit if current profit is higher
            maxprofit = max(maxprofit, cost);
            
            // Update minimum price seen so far
            mini = min(mini, prices[i]);
        }
        
        // Return the maximum possible profit
        return maxprofit;
        
    }
    
int main(){
    vector<int> prices = {7,1,5,3,6,4};
    cout << "Max Profit: " << maxProfit(prices) << endl;
    return 0;
}
/*
Step-by-Step with Example {7,1,5,3,6,4}:
Initialization:

maxprofit = 0
mini = 7 (first day's price)
Day 2 (i=1, price=1):

cost = 1 - 7 = -6 (would lose money, not better than 0)
maxprofit = max(0, -6) = 0 (no change)
mini = min(7, 1) = 1 (update minimum)
Day 3 (i=2, price=5):

cost = 5 - 1 = 4 (profit if bought at minimum and sell today)
maxprofit = max(0, 4) = 4 (update maximum profit)
mini = min(1, 5) = 1 (no change)
Day 4 (i=3, price=3):

cost = 3 - 1 = 2 (profit if bought at minimum and sell today)
maxprofit = max(4, 2) = 4 (no change)
mini = min(1, 3) = 1 (no change)
Day 5 (i=4, price=6):

cost = 6 - 1 = 5 (profit if bought at minimum and sell today)
maxprofit = max(4, 5) = 5 (update maximum profit)
mini = min(1, 6) = 1 (no change)
Day 6 (i=5, price=4):

cost = 4 - 1 = 3 (profit if bought at minimum and sell today)
maxprofit = max(5, 3) = 5 (no change)
mini = min(1, 4) = 1 (no change)
Return: maxprofit = 5

Complexity Analysis:
Time Complexity: O(n) - single pass through the array
Space Complexity: O(1) - constant extra space
*/