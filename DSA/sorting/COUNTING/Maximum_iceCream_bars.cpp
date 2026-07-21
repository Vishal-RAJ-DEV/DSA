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
//
// Time Complexity Derivation:
//   Let n = costs.size() , k = maxCost
//
//   Step 1 — max_element:  O(n)
//     Linear scan over n elements to find the maximum.
//
//   Step 2 — Counting pass: O(n)
//     Single pass over costs[] to populate freq[].
//
//   Step 3 — Greedy sweep: O(k)
//     Loop from price = 1 to maxCost. In the worst case (coins are
//     plentiful), we visit all k distinct price levels. Each iteration
//     does O(1) work — min(), integer arithmetic, a push to freq[].
//     The early break (coins < price) may shorten this, but the bound
//     is O(k).
//
//   Total: T(n, k) = O(n) + O(n) + O(k) = O(n + k)
//
//   Space: O(k) for the freq[] array of size maxCost + 1.
//
//   Comparison with sorting-based approach:
//     Sorting:  O(n log n) time, O(1) extra space (in-place sort).
//     Counting: O(n + k) time, O(k) extra space.
//     When k is small relative to n (e.g., costs are bounded by 10^5
//     but n can be 10^5), counting sort is competitive or faster.
//     When k >> n log n, sorting is better.

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
