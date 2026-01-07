#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to check if the given array is a min-heap
    bool isMinHeap(vector<int>& nums) {
        int n = nums.size();

        // Iterate through all non-leaf nodes
        for (int i = 0; i <= (n / 2) - 1; i++) {

            // Calculate the left child index
            int left = 2 * i + 1;

            // If left child exists and is smaller than parent, not a min-heap
            if (left < n && nums[i] > nums[left]) {
                return false;
            }

            // Calculate the right child index
            int right = 2 * i + 2;

            // If right child exists and is smaller than parent, not a min-heap
            if (right < n && nums[i] > nums[right]) {
                return false;
            }
        }

        // If no violations found, it is a min-heap
        return true;
    }
};

// Driver code
int main() {
    Solution obj;
    vector<int> nums = {10, 20, 30, 21, 23};

    // Output result
    cout << (obj.isMinHeap(nums) ? "true" : "false") << endl;
    return 0;
}
