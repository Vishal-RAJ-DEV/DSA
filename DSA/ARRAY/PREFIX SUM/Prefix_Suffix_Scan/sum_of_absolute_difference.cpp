#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
You are given a sorted array nums.
For every index i, find the sum of absolute differences between nums[i]
and every other element of the array.

That means for each index i, we want:
|nums[i] - nums[0]| + |nums[i] - nums[1]| + ... + |nums[i] - nums[n-1]|

Example:
nums = [2, 3, 5]

For 2:
|2-2| + |2-3| + |2-5| = 0 + 1 + 3 = 4

For 3:
|3-2| + |3-3| + |3-5| = 1 + 0 + 2 = 3

For 5:
|5-2| + |5-3| + |5-5| = 3 + 2 + 0 = 5

Answer = [4, 3, 5]

Important condition:
- The array is sorted.

Why is sorted order important?
- Every element on the left of nums[i] is <= nums[i].
- Every element on the right of nums[i] is >= nums[i].

Because of this, absolute values become easy to handle:
- For the left side:
  |nums[i] - nums[j]| = nums[i] - nums[j]
- For the right side:
  |nums[i] - nums[j]| = nums[j] - nums[i]

Main intuition:
- Split the answer for each index into 2 parts:
  1. contribution from the left side
  2. contribution from the right side
- Use prefix and suffix sums so each part can be found quickly.
- This avoids recomputing the whole absolute-difference sum for every index.
*/

class Solution {
public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n);
        vector<int> right(n);
        left[0] = nums[0];
        right[n - 1] = nums[n - 1];

        /*
        left[i]  = sum of elements from nums[0] to nums[i]
        right[i] = sum of elements from nums[i] to nums[n-1]

        These arrays help us know the sum of all left elements and all right
        elements for any index in O(1) time.
        */
        for (int i = 1; i < n; i++) {
            left[i] = nums[i] + left[i - 1];
            right[n - i - 1] = nums[n - i - 1] + right[n - i];
        }

        /*
        Formula logic:

        1. Left contribution for index i
        There are i elements on the left of nums[i].

        Since the array is sorted:
        nums[0], nums[1], ... nums[i-1] are all <= nums[i]

        So:
        |nums[i] - nums[0]| + |nums[i] - nums[1]| + ... + |nums[i] - nums[i-1]|
        = (nums[i] - nums[0]) + (nums[i] - nums[1]) + ... + (nums[i] - nums[i-1])
        = nums[i] * i - (nums[0] + nums[1] + ... + nums[i-1])
        = nums[i] * i - left[i - 1]

        2. Right contribution for index i
        There are (n - i - 1) elements on the right of nums[i].

        Since the array is sorted:
        nums[i+1], nums[i+2], ... nums[n-1] are all >= nums[i]

        So:
        |nums[i] - nums[i+1]| + ... + |nums[i] - nums[n-1]|
        = (nums[i+1] - nums[i]) + ... + (nums[n-1] - nums[i])
        = (nums[i+1] + ... + nums[n-1]) - nums[i] * (n - i - 1)
        = right[i + 1] - nums[i] * (n - i - 1)

        Final answer at index i:
        left contribution + right contribution
        */
        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            // Sum of absolute differences with all elements on the left.
            int leftcnt = (i == 0) ? 0 : nums[i] * i - left[i - 1];

            // Sum of absolute differences with all elements on the right.
            int rightcnt = (i == n - 1) ? 0 : right[i + 1] - nums[i] * (n - i - 1);

            // Total absolute difference for nums[i].
            res[i] = leftcnt + rightcnt;
        }

        return res;
    }
};

int main() {
    Solution obj;
    vector<int> nums = {2, 3, 5};
    vector<int> result = obj.getSumAbsoluteDifferences(nums);

    return 0;
}
