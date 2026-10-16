#include <iostream>
#include <bits/stdc++.h>
using namespace std;


/*
PROBLEM: LeetCode 1855 - Maximum Distance Between a Pair of Values
QUESTION:
We are given two integer arrays, nums1 and nums2, sorted in non-increasing
(descending) order. We need to find the maximum distance j - i such that:
1. i <= j
2. nums1[i] <= nums2[j]
Here, i is an index of nums1 and j is an index of nums2.
EXAMPLE:
nums1 = [55, 30, 25, 10]
nums2 = [60, 50, 35, 20, 10]
Output: 1
Explanation:
nums1[1] = 30 and nums2[2] = 35.
Since 1 <= 2 and 30 <= 35, this pair is valid.
Its distance is 2 - 1 = 1, which is the maximum possible distance.
APPROACH: TWO POINTERS
1. Start both pointers i and j at index 0.
2. If nums1[i] <= nums2[j] and i <= j, the pair is valid.
   Update ans = max(ans, j - i), then move j forward to try a larger distance.
3. Otherwise:
   - If i > j, move j forward to satisfy the index condition.
   - If nums1[i] > nums2[j], move i forward because nums2 is descending.
     Later elements of nums2 will be even smaller, so the current nums1[i]
     cannot form a valid pair with j or any later index.
4. Stop when either pointer reaches the end and return ans.
WHY TWO POINTERS?
Both arrays are sorted, so we never need to move a pointer backward.
Each pointer advances at most the length of its array.
TIME COMPLEXITY: O(n + m)
SPACE COMPLEXITY: O(1) auxiliary space
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        int i = 0; // Pointer for nums1
        int j = 0; // Pointer for nums2
        int ans = 0; // Stores the maximum valid distance found
        while (i < n && j < m) {
            // Case 1: i is greater than j, so the index condition i <= j is violated.
            // Move j forward until it catches up with i.
            if (i > j) {
                j++;
            }
            // Case 2: The indices are valid and nums1[i] <= nums2[j].
            // Therefore, (i, j) is a valid pair, and its distance is j - i.
            else if (nums1[i] <= nums2[j]) {
                // Save the largest distance found so far.
                ans = max(ans, j - i);
                // Try a farther index in nums2 to potentially increase the distance.
                j++;
            }
            // Case 3: nums1[i] > nums2[j], so this pair is invalid.
            // Because nums2 is descending, every later value is <= nums2[j].
            // Therefore, the current nums1[i] cannot pair with j or any later index.
            // Move i forward to try a smaller value in nums1.
            else {
                i++;
            }
        }
        return ans; // Return the maximum valid distance
    }
};


int main(){
    Solution s;
    vector<int> nums1 = {55,30,5,4,2};
    vector<int> nums2 = {100,20,10,10,5};
    cout<< s.maxDistance(nums1, nums2) << endl;

    return 0;
}