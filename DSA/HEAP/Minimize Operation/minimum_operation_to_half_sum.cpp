#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: 2208. Minimum Operations to Halve Array Sum

    You are given an array nums of positive integers. In one operation, you
    can pick any element from the array and divide it by 2 (replace it with
    its half). Return the minimum number of operations needed to reduce the
    sum of the array to at least half (sum / 2).

    Example:
        Input: nums = [5,19,8,1]
        Output: 3
        Explanation:
            Initial sum = 33, target = 16.5
            Op 1: Pick 19 -> half = 9.5, nums becomes [5,9.5,8,1], sum = 23.5
            Op 2: Pick 9.5 -> half = 4.75, nums becomes [5,4.75,8,1], sum = 18.75
            Op 3: Pick 8 -> half = 4, nums becomes [5,4.75,4,1], sum = 14.75 < 16.5
            Answer = 3 operations.

    KEY INSIGHT:
        - To minimize the number of operations, each operation should give
          the maximum possible reduction in sum.
        - Halving a larger number reduces the sum by a larger amount.
        - Therefore, at each step, we must halve the current largest element.
        - This is a classic greedy problem solved optimally with a max-heap.
*/


// =========================================================
// APPROACH 1: Max-Heap (Greedy) — O((n + ops) log n)
// =========================================================
/*
    LOGIC:
        1. Compute total sum and target = sum / 2.
        2. Push all elements into a max-heap (largest element at top).
        3. While the current sum > target:
            a. Pop the largest element from the heap.
            b. Halve it (largest / 2.0).
            c. Subtract the halved amount from the current sum.
               (We remove "largest/2" from the sum, since the element
                changed from 'largest' to 'largest/2', a reduction of
                largest/2.)
            d. Push the halved value back into the heap.
            e. Increment operation count.
        4. Return total operations.

        Why greedy works:
        - Each operation reduces the sum by (selected element) / 2.
        - To reach the target in minimum operations, we need the largest
          possible reduction per operation.
        - Halving the current maximum element always gives the maximum
          possible reduction at that step.
        - This is optimal because the reduction amount is monotonic with
          respect to element value — bigger element => bigger reduction.

    TIME COMPLEXITY:
        - Building sum via accumulate: O(n)
        - Building max-heap: O(n)
        - Each iteration:
            - Pop from heap: O(log n)
            - Push halved value: O(log n)
            - Total per op: O(log n)
        - Let 'ops' be the number of operations needed.
          In worst case, we repeatedly halve elements. Each element can be
          halved roughly log(MAX) times before becoming negligible.
          With n elements, ops = O(n * log(MAX_VALUE)).
          For constraints like nums[i] ≤ 10^9, log(MAX) ≈ 30, so ops = O(30n) = O(n).
        - Overall: O((n + ops) log n) = O(n log n) for practical constraints.

    SPACE COMPLEXITY:
        - Max-heap stores n elements: O(n)
        - Overall: O(n)

    ALTERNATIVE APPROACHES:
        Sorting approach: Sort descending, repeatedly halve the largest.
        Each operation would require re-sorting or insertion, making it
        O(n log n + k * n) which is worse. The max-heap is optimal.
*/


class Solution {
public:
    int halveArray(vector<int>& nums) {

        double sum = accumulate(nums.begin(), nums.end(), 0.0);
        double target = sum / 2.0;

        priority_queue<double> pq;

        for (int num : nums)
            pq.push((double)num);

        int operations = 0;

        while (sum > target) {

            double largest = pq.top();
            pq.pop();

            double half = largest / 2.0;

            sum -= half;      // Sum decreases by the removed half
            pq.push(half);

            operations++;
        }

        return operations;
    }
};
int main(){
    return 0;
}

