#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    ❝If the problem doesn’t ask for MOD — NEVER use MOD❞
    ❝Modulo + subtraction + negatives = disaster❞
    */
    long long max_total(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        vector<int> left(nums.size()), right(nums.size());

        // left ( previous ) greater element
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[i] > nums[st.top()])
                st.pop(); // if the top ele of stack is not greater than pop

            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        while (!st.empty())
            st.pop(); // empty the stack

        // right ( next ) greater element
        for (int i = nums.size() - 1; i >= 0; i--) {
            while (!st.empty() && nums[i] >= nums[st.top()])
                st.pop();

            right[i] = st.empty() ? nums.size() : st.top();
            st.push(i);
        }

        long long ans = 0;
        // long long mod = 1e9 + 7;

        for (int i = 0; i < n; i++) {
            long long leftcnt = i - left[i];
            long long rightcnt = right[i] - i;

            long long totalSubarray = (leftcnt * rightcnt);
            long long contribution = (nums[i] * totalSubarray);

            ans += contribution;
        }

        return ans;
    }
    long long min_total(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        vector<int> left(nums.size()), right(nums.size());

        // left ( previous ) greater element
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[i] < nums[st.top()])
                st.pop(); // if the top ele of stack is not greater than pop

            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        while (!st.empty())
            st.pop(); // empty the stack

        // right ( next ) greater element
        for (int i = nums.size() - 1; i >= 0; i--) {
            while (!st.empty() && nums[i] <= nums[st.top()])
                st.pop();

            right[i] = st.empty() ? nums.size() : st.top();
            st.push(i);
        }

        long long ans = 0;
        long long mod = 1e9 + 7;

        for (int i = 0; i < n; i++) {
            long long leftcnt = i - left[i];
            long long rightcnt = right[i] - i;

            long long totalSubarray = (leftcnt * rightcnt);
            long long contribution = (nums[i] * totalSubarray);

            ans += contribution;
        }

        return ans;
    }
    long long subArrayRanges(vector<int>& nums) {
        return max_total(nums) - min_total(nums);
    }
};
int main(){
    vector<int> arr={1,2,3};
    Solution obj;
    cout<<obj.subArrayRanges(arr);
    

    return 0;
}
