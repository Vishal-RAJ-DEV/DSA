// LeetCode 962: Maximum Width Ramp
// A ramp is a pair (i, j) where i < j and nums[i] <= nums[j].
// The width of the ramp is j - i. Find the maximum width ramp.
//
// Three approaches are provided below:
//
// ============================================================
// APPROACH 1: Monotonic Decreasing Stack (Optimal) - O(n) time, O(n) space
// ============================================================
// Idea:
// - Build a stack of indices where values are strictly decreasing.
// - Then iterate from right to left, popping valid pairs.
//
// Why it works:
// - Stack only holds potential left endpoints (indices with small values).
// - Scanning right-to-left ensures we find the widest valid ramp for each left index.
// - If nums[st.top()] <= nums[j], we found a valid ramp → compute width and pop.
//
// Dry Run (nums = [6,0,8,2,5]):
// Stack build: i=0 → push 0. i=1: nums[0]=6 > nums[1]=0 → push 1. Stack = [0,1]
// i=2: nums[1]=0 < nums[2]=8 → skip. i=3: nums[1]=0 < nums[3]=2 → skip.
// i=4: nums[1]=0 < nums[4]=5 → skip.
// Scan from right:
//   j=4: nums[st.top()=1]=0 <= nums[4]=5 → width=4-1=3, pop. nums[st.top()=0]=6 <= 5? No.
//   j=3: nums[st.top()=0]=6 <= nums[3]=2? No.
//   j=2: nums[st.top()=0]=6 <= nums[2]=8 → width=2-0=2, pop. Stack empty.
// Max width = 3
//
// ============================================================
// APPROACH 2: Prefix Minimum + Two Pointers - O(n) time, O(n) space
// ============================================================
// Idea:
// - Create prefixMin[i] = min(nums[0..i]) → smallest value up to index i.
// - Use two pointers: i starts at 0, j from end.
// - If prefixMin[i] > nums[j], increment i (need smaller left value).
//
// Why it works:
// - prefixMin[i] gives the best (smallest) left value at or before index i.
// - Two pointers efficiently find valid ramps in one pass.
//
// Dry Run (nums = [6,0,8,2,5]):
// prefixMin = [6,0,0,0,0]
// i=0, j=4: prefixMin[0]=6 > nums[4]=5 → i=1
// i=1, j=4: prefixMin[1]=0 <= nums[4]=5 → ans=4-1=3
// i=1, j=3: prefixMin[1]=0 <= nums[3]=2 → ans=max(3,3-1)=3
// i=1, j=2: prefixMin[1]=0 <= nums[2]=8 → ans=max(3,2-1)=3
// i=1, j=1: loop ends
// Max width = 3
//
// ============================================================
// APPROACH 3: Brute Force - O(n²) time, O(1) space
// ============================================================
// Idea:
// - Check every pair (i, j) where i < j.
// - If nums[i] <= nums[j], update max width.
//
// Dry Run (nums = [6,0,8,2,5]):
// (0,1): 6<=0? No. (0,2): 6<=8? Yes → width=2. (0,3): 6<=2? No. (0,4): 6<=5? No.
// (1,2): 0<=8? Yes → width=2. (1,3): 0<=2? Yes → width=2. (1,4): 0<=5? Yes → width=3.
// (2,3): 8<=2? No. (2,4): 8<=5? No. (3,4): 2<=5? Yes → width=1.
// Max width = 3
// ============================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// APPROACH 1: Monotonic Decreasing Stack
class Solution1 {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;  // stack to store indices of decreasing values

        // Step 1: Build monotonic decreasing stack
        // Push index i if stack is empty or current value is smaller than stack top
        // This ensures stack stores indices with strictly decreasing values
        for(int i = 0; i < n; i++){
            if(st.empty() || nums[st.top()] > nums[i]){
                st.push(i);  // potential left endpoint for a ramp
            }
        }

        // Step 2: Scan from right to left, find maximum width
        int width = 0;
        for(int i = n - 1; i >= 0; i--){
            // While stack top satisfies ramp condition (nums[left] <= nums[right])
            while(!st.empty() && nums[st.top()] <= nums[i]){
                int left = st.top();  // get left index
                width = max(width, i - left);  // update maximum width
                st.pop();  // pop since we found the widest ramp for this left index
            }
        }

        return width;
    }
};

// APPROACH 2: Prefix Minimum + Two Pointers
class Solution2 {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();

        // Step 1: Build prefix minimum array
        // prefixMin[i] = minimum value from index 0 to i
        vector<int> prefixMin(n);
        prefixMin[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixMin[i] = min(prefixMin[i - 1], nums[i]);
        }

        // Step 2: Two pointers from both ends
        int ans = 0;
        int i = 0;  // left pointer starts at beginning

        // j scans from right to left
        for (int j = n - 1; j >= 0; j--) {
            // Move i forward if prefixMin[i] is too large (can't form ramp)
            while (i < j && prefixMin[i] > nums[j]) {
                i++;
            }
            // If valid ramp found, update answer
            if (i < j) {
                ans = max(ans, j - i);
            }
        }

        return ans;
    }
};

// APPROACH 3: Brute Force
class Solution3 {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        // Check all pairs (i, j) where i < j
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // If ramp condition is satisfied, update max width
                if (nums[i] <= nums[j]) {
                    ans = max(ans, j - i);
                }
            }
        }

        return ans;
    }
};

int main(){
    // Example usage:
    // Solution1 sol;
    // vector<int> nums = {6,0,8,2,5};
    // cout << sol.maxWidthRamp(nums) << endl;  // Output: 3
    return 0;
}