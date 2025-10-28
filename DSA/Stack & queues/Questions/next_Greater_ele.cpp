#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater; // map element -> next greater
        stack<int> st;

        // Traverse nums2 from right to left
        for (int i = nums2.size() - 1; i >= 0; i--) {
            int num = nums2[i];

            // Pop smaller or equal elements
            while (!st.empty() && st.top() <= num) {
                st.pop();
            }

            // If stack is not empty, top is the next greater
            if (!st.empty()) {
                nextGreater[num] = st.top();
            } else {
                nextGreater[num] = -1;
            }

            // Push current number onto stack
            st.push(num);
        }

        // Build the result for nums1
        vector<int> ans; 
        for (int num : nums1) {  //now for the nums1 array we will check the next greater element from the map and push it to the ans array
            ans.push_back(nextGreater[num]);
        }

        return ans;
    }
};

int main() {
    Solution obj;
    vector<int> nums1 = {4, 1, 2};
    vector<int> nums2 = {1, 3, 4, 2};

    vector<int> result = obj.nextGreaterElement(nums1, nums2);

    cout << "Next greater elements: ";
    for (int x : result) cout << x << " ";
    return 0;
}
