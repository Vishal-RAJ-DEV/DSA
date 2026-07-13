#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    PROBLEM: Take Gifts From the Richest Pile (LeetCode 2558)

    You are given an integer array gifts denoting the number of coins in
    each pile. In each second, you pick the pile with the maximum coins,
    replace it with floor(sqrt(original coins)), and repeat for k seconds.

    Return the total coins remaining after k seconds.

    EXAMPLE:
    gifts = [25, 64, 9, 4, 100], k = 4
    Step 1: max=100 → floor(sqrt(100))=10 → [25,64,9,4,10]
    Step 2: max=64  → floor(sqrt(64))=8   → [25,8,9,4,10]
    Step 3: max=25  → floor(sqrt(25))=5   → [5,8,9,4,10]
    Step 4: max=10  → floor(sqrt(10))=3   → [5,8,9,4,3]
    Sum = 5+8+9+4+3 = 29

    ALGORITHM: Max-Heap (Priority Queue)
    ======================================

    INTUITION:
    - At each step, we need the pile with the current maximum value.
    - A max-heap gives us O(1) access to the max and O(log n) per push/pop.
    - Repeatedly extract max, apply sqrt, push back.

    STEPS:
    1. Push all gift pile values into a max-heap.
    2. For k iterations:
       a. Pop the largest pile (top of heap).
       b. Compute floor(sqrt(top)).
       c. Push the new value back.
    3. Sum all remaining values in the heap and return.

    TIME COMPLEXITY: O(n + k log n)  — O(n) to build heap, O(log n) per op
    SPACE COMPLEXITY: O(n)           — heap stores n elements

    EDGE CASES:
    - k can be larger than n: we keep reducing the same piles repeatedly.
    - sqrt of 1 is 1, so piles with 1 coin stay at 1 forever (idempotent).
*/

class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        // Max-heap to always access the richest pile in O(1)
        priority_queue<int> pq;

        // Push all gift piles into the heap
        for (int num : gifts) {
            pq.push(num);
        }

        // Perform k operations:
        // Take the max pile, replace it with floor(sqrt(original))
        while (k--) {
            int top = pq.top();
            pq.pop();
            int val = floor(sqrt(top)); // integer square root
            pq.push(val);
        }

        // Sum all remaining coins in all piles
        long long res = 0;
        while (!pq.empty()) {
            res += pq.top();
            pq.pop();
        }

        return res;
    }
};

int main() {
    Solution sol;

    // Test case 1
    vector<int> gifts1 = {25, 64, 9, 4, 100};
    cout << "Test 1: " << sol.pickGifts(gifts1, 4) << " (expected: 29)" << endl;

    // Test case 2
    vector<int> gifts2 = {1, 1, 1, 1};
    cout << "Test 2: " << sol.pickGifts(gifts2, 4) << " (expected: 4)" << endl;

    // Test case 3
    vector<int> gifts3 = {100, 100, 100};
    cout << "Test 3: " << sol.pickGifts(gifts3, 2) << " (expected: 120)" << endl;

    return 0;
}
