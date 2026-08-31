/*
==========================================================================
PROBLEM: Minimum Score by Changing Two Elements (LeetCode 2611)
==========================================================================
Given an integer array nums, you can change exactly TWO elements to any
values you want. The score of the array = max(nums) - min(nums).
Find the MINIMUM possible score after changing two elements.

EXAMPLE:
  nums = [1, 4, 3]
  Change 4->1 and 3->1 => array becomes [1,1,1], score = 1-1 = 0

==========================================================================
INTUITION:
==========================================================================
After sorting, the min is at index 0 and max is at index n-1.
Score = max - min. To minimize the score, we want to make max as small
as possible and min as large as possible.

Since we can change EXACTLY 2 elements, we can "remove" 2 elements from
the extremes of the sorted array. After removing 2 elements, the new
min and max come from the remaining elements.

Key observation: After sorting, there are only 3 meaningful ways to
remove 2 elements to minimize (new_max - new_min):

  Case 1: Remove 2 from RIGHT  -> new_max = nums[n-3], new_min = nums[0]
  Case 2: Remove 1 from EACH   -> new_max = nums[n-2], new_min = nums[1]
  Case 3: Remove 2 from LEFT   -> new_max = nums[n-1], new_min = nums[2]

We take the MINIMUM of these 3 cases.

WHY ONLY 3 CASES?
  - We must remove exactly 2 elements
  - Removing from the middle never helps (it doesn't reduce max or increase min)
  - So the only options are: (2 right), (1 left + 1 right), (2 left)

==========================================================================
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        // Step 1: Sort so min is at index 0 and max is at index n-1
        sort(nums.begin(), nums.end());

        int n = nums.size();

        // Case 1: Remove 2 largest elements (change them to something smaller)
        // New max becomes nums[n-3], min stays nums[0]
        int case1 = nums[n - 1] - nums[2];

        // Case 2: Remove 1 largest and 1 smallest
        // New max = nums[n-2], new min = nums[1]
        int case2 = nums[n - 2] - nums[1];

        // Case 3: Remove 2 smallest elements (change them to something larger)
        // New min becomes nums[2], max stays nums[n-1]
        int case3 = nums[n - 3] - nums[0];

        // Return the minimum score among all 3 cases
        return min({case1, case2, case3});
    }
};




int main(){
    return 0;
}

/*
==========================================================================
EXAMPLE WALKTHROUGH:
==========================================================================
nums = [1, 5, 2, 4, 3]   (n = 5)

After sorting: [1, 2, 3, 4, 5]

Case 1 (remove 2 right): 5 - 3 = 2  (keep [1,2,3])
Case 2 (remove 1 each):  4 - 2 = 2  (keep [2,3,4])
Case 3 (remove 2 left):  5 - 3 = 2  (keep [3,4,5])

Answer = 2

Another example: nums = [1, 4, 3]
After sorting: [1, 3, 4]

Case 1: 4 - 4 = 0  (change both 3 and 4 to 1)
Case 2: 3 - 3 = 0  (change 1 and 4 to 3)
Case 3: 4 - 1 = 3  (keep [1,4])

Answer = 0

==========================================================================
TIME COMPLEXITY: O(n log n) for sorting
SPACE COMPLEXITY: O(1) extra space (ignoring sort's internal space)
==========================================================================
*/