#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Approach: Mathematical Observation (Greedy)

Intuition:
- We need to make all array elements equal.
- In one operation, we can increment n-1 elements by 1.
- Instead of thinking about incrementing n-1 elements, think about the one element we leave unchanged.
- This is equivalent to decrementing that one element by 1 because adding the same value to every element does not change their relative differences.

How does this transformation work?
- Suppose nums = [1, 2, 3].
- Increment the first two elements: [1, 2, 3] -> [2, 3, 3].
- Subtract 1 from every element: [2, 3, 3] -> [1, 2, 2].
- Effectively, only the third element was decremented by 1.
- Therefore, incrementing n-1 elements is equivalent to decrementing one element.

Why choose the minimum element?
- After transforming the operation, we can only decrement elements.
- So, we should bring every element down to the smallest element.
- Choosing any value smaller than the minimum would require unnecessary operations.
- Choosing a larger value is impossible using only decrements.

Logic:
- Find the minimum element in the array.
- Calculate how many decrements each element needs to reach that minimum.
- Add all these differences to get the minimum moves.

Formula:
- moves = sum(nums[i] - minimum)

Example:
- nums = [1, 2, 3]
- minimum = 1
- moves = (1-1) + (2-1) + (3-1)
- moves = 0 + 1 + 2 = 3

Time Complexity: O(n)
Space Complexity: O(1)
*/

class Solution {
public:
    int minMoves(vector<int>& nums) {
        // Find the minimum element
        int mini = *min_element(nums.begin(), nums.end());

        int moves = 0;

        // Calculate the decrements required for every element
        for(int i = 0; i < nums.size(); i++) {
            moves += nums[i] - mini;
        }

        // Return the total minimum moves
        return moves;
    }
};


int main(){
    return 0;
}