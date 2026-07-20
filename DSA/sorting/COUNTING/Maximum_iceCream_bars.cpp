#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// LeetCode 1833: Maximum Ice Cream Bars
//
// Intuition:
//   To maximize the number of ice cream bars you can buy with a fixed
//   amount of coins, always buy the cheapest bars first (greedy).
//   Sorting the costs array (O(n log n)) then greedily buying works,
//   but we can do better using Counting Sort when the costs range is
//   small, achieving O(n + maxCost) time.
//
// Counting Sort Concept:
//   Instead of comparing elements, we count how many times each cost
//   appears using a frequency array indexed by cost value. Then we
//   sweep from lowest to highest cost, buying as many bars as possible
//   at each price level. The natural ordering of array indices replaces
//   the need for an explicit sort.
//
// Algorithm:
//   1. Find max cost in the array.
//   2. Build a frequency array freq[] where freq[cost] = count.
//   3. Iterate price from 1 to maxCost:
//      - If no bars at this price, skip.
//      - Buy min(freq[price], coins / price) bars.
//      - Deduct coins spent and add bars to answer.
//      - If remaining coins cannot afford the next price, break.

class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        int maxCost = *max_element(costs.begin(), costs.end());

        vector<int> freq(maxCost + 1, 0);

        for (int cost : costs) {
            freq[cost]++;
        }

        int ans = 0;

        for (int price = 1; price <= maxCost; price++) {
            if (freq[price] == 0)
                continue;

            int canBuy = min(freq[price], coins / price);

            ans += canBuy;
            coins -= canBuy * price;

            if (coins < price)
                break;
        }

        return ans;
    }
};

int main(){
    return 0;
}
