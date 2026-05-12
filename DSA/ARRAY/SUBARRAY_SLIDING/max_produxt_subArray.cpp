//Given an integer array nums, find a subarray that has the largest product, and return the product.
//Input: nums = [2,3,-2,4]
//Output: 6
//Explanation: [2,3] has the largest product 6.

#include <bits/stdc++.h>
using namespace std;

int maxProductSubArray(vector<int> &arr) {
    int n = arr.size(); //size of array.

    int pre = 1, suff = 1;
    int ans = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (pre == 0) pre = 1;
        if (suff == 0) suff = 1;
        pre *= arr[i];
        suff *= arr[n - i - 1];
        ans = max(ans, max(pre, suff));
    }
    return ans;
}
//another approch 
class Solution {
public:
    // This function returns the maximum product
    // of any contiguous subarray using optimized approach
    int maxProduct(vector<int>& nums) {
        // Initialize answer, max and min product as first element
        int res = nums[0];
        int maxProd = nums[0];
        int minProd = nums[0];

        // Traverse from second element
        for (int i = 1; i < nums.size(); i++) {
            // Store current number
            int curr = nums[i];

            // If current number is negative, swap max and min
            //this is beacuse the min product have the lowest value that can be negative number, so if we multiply it with negative number then it will become the maximum product,
            // and the max product will become the minimum product because of negative number is multiplied with the maximun positive number that is stored in max product, so we need to swap the max and min product before updating them.
            if (curr < 0) swap(maxProd, minProd);

            // Update max and min product ending at current index
            maxProd = max(curr, maxProd * curr);
            minProd = min(curr, minProd * curr);

            // Update global result
            res = max(res, maxProd); 
        }

        // Return the result
        return res;
    }
};

int main()
{
    vector<int> arr = {1, 2, -3, 0, -4, -5};
    cout << "The maximum product subarray is: "
         << maxProductSubArray(arr) << "\n";
    return 0;
}

//Time Complexity: O(N), N = size of the given array.
//Space Complexity: O(1) as No extra data structures are used for computation.

/*
🚨 Why swapping is REQUIRED (not optional)
Suppose BEFORE current number:
maxProd = 10
minProd = -5

Now current number is:

curr = -2
❌ If we DON’T swap
maxProd * curr = 10 × -2 = -20
minProd * curr = -5 × -2 = 10  ← THIS is the best

But if we compute max first without swapping, we lose this logic.

✅ If we DO swap first

After swap:

maxProd = -5
minProd = 10

Now multiply:

maxProd = max(-2, -5 × -2) = 10  ✅
minProd = min(-2, 10 × -2) = -20
*/