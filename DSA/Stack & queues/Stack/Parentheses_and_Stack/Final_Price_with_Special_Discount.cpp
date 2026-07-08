#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        /*
        INTUITION:
        For each item i, the discount is the first price[j] to the right
        where j > i and prices[j] <= prices[i]. If none exists, discount = 0.
        Final price = prices[i] - discount.

        We use a MONOTONIC INCREASING STACK (bottom → top) traversing
        right-to-left. This stack stores prices that are potential discounts
        for items to the left.

        Why right-to-left?
        - The discount for item i depends on items to its right.
        - By processing right-to-left, we've already seen all future items
          and stored relevant ones in the stack.
        - The stack maintains increasing order: prices decrease as we go
          from bottom to top (i.e., the top is the smallest).

        Algorithm:
        - Traverse from rightmost to leftmost item.
        - While stack top > current price, pop it — those prices are too
          large to be a discount for any item further left (since the
          current price is smaller AND closer).
        - After popping: either stack is empty (no discount) or top is the
          first smaller-or-equal price to the right (the discount).
        - ans[i] = prices[i] - (stack.empty() ? 0 : st.top())
        - Push current price onto stack for items to the left.

        VISUAL EXAMPLE:
        prices = [8, 4, 6, 2, 3]

        i=4 (price=3): stack=[] → ans[4]=3, push 3 → stack=[3]
        i=3 (price=2): top=3 > 2 → pop 3. stack=[] → ans[3]=2, push 2 → stack=[2]
        i=2 (price=6): top=2 ≤ 6 → ans[2]=6-2=4, push 6 → stack=[2,6]
        i=1 (price=4): top=6 > 4 → pop 6. top=2 ≤ 4 → ans[1]=4-2=2, push 4 → stack=[2,4]
        i=0 (price=8): top=4 ≤ 8 → ans[0]=8-4=4, push 8 → stack=[2,4,8]

        Result: [4, 2, 4, 2, 3]

        Time: O(n) — each price pushed/popped at most once.
        Space: O(n) for the stack and answer.
        */

        int n = prices.size();
        stack<int> st;
        vector<int> ans(n);

        for (int i = n - 1; i >= 0; i--) {
            // Pop prices greater than current — they can never be a discount
            // for items further left since current is smaller and closer.
            while (!st.empty() && st.top() > prices[i]) st.pop();

            // Top of stack is the first ≤ price to the right, or none
            ans[i] = st.empty() ? prices[i] : prices[i] - st.top();

            st.push(prices[i]);
        }

        return ans;
    }
};

int main(){
    Solution sol;

    // Helper lambda to print vectors
    auto print = [](const vector<int>& v) {
        cout << "[";
        for (size_t i = 0; i < v.size(); i++) {
            cout << v[i];
            if (i + 1 < v.size()) cout << ",";
        }
        cout << "]";
    };

    // Test 1: Example from comment
    vector<int> t1 = {8,4,6,2,3};
    cout << "Test 1: "; print(t1); cout << " -> ";
    print(sol.finalPrices(t1));
    cout << " (expected [4,2,4,2,3])" << endl;

    // Test 2: Strictly decreasing — each gets the next as discount
    vector<int> t2 = {5,4,3,2,1};
    cout << "Test 2: "; print(t2); cout << " -> ";
    print(sol.finalPrices(t2));
    cout << " (expected [1,1,1,1,1])" << endl;

    // Test 3: Strictly increasing — no discount for anyone
    vector<int> t3 = {1,2,3,4,5};
    cout << "Test 3: "; print(t3); cout << " -> ";
    print(sol.finalPrices(t3));
    cout << " (expected [1,2,3,4,5])" << endl;

    // Test 4: All equal — each gets the next as discount
    vector<int> t4 = {3,3,3,3};
    cout << "Test 4: "; print(t4); cout << " -> ";
    print(sol.finalPrices(t4));
    cout << " (expected [0,0,0,3])" << endl;

    // Test 5: Single element
    vector<int> t5 = {10};
    cout << "Test 5: "; print(t5); cout << " -> ";
    print(sol.finalPrices(t5));
    cout << " (expected [10])" << endl;

    // Test 6: Empty
    vector<int> t6 = {};
    cout << "Test 6: "; print(t6); cout << " -> ";
    print(sol.finalPrices(t6));
    cout << " (expected [])" << endl;

    // Test 7: Leetcode example
    vector<int> t7 = {10,1,1,6};
    cout << "Test 7: "; print(t7); cout << " -> ";
    print(sol.finalPrices(t7));
    cout << " (expected [9,0,1,6])" << endl;

    return 0;
}