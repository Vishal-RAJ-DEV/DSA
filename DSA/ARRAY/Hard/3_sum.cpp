// Problem Statement: Given an array of N integers, your task is to find unique triplets that add up to give a sum of zero. In short, you need to return an array of all the unique triplets [arr[a], arr[b], arr[c]] such that i!=j, j!=k, k!=i, and their sum is equal to zero.
#include <bits/stdc++.h>
using namespace std;

//better approch 
vector<vector<int>> triplet(int n, vector<int> &arr) {
    set<vector<int>> st;

    for (int i = 0; i < n; i++) {
        set<int> hashset;
        for (int j = i + 1; j < n; j++) {
            //Calculate the 3rd element:
            int third = -(arr[i] + arr[j]);

            //Find the element in the set:
            if (hashset.find(third) != hashset.end()) {
                vector<int> temp = {arr[i], arr[j], third};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
            hashset.insert(arr[j]);
        }
    }

    //store the set in the answer:
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

//optimal approch 
vector<vector<int>>threeSum(vector<int> &nums){
    vector<vector<int>> ans;
    sort(nums.begin(),nums.end());
    int n = nums.size();
    for(int i =0;i<n;i++){
        if(i>0 && nums[i] == nums[i-1]) continue;
        int j = i + 1;
        int k = n - 1;
        while(j<k){
            int sum = nums[i] + nums[j] + nums[k];
            if(sum>0)
            j++;

            else if(sum<0)
            k--;
            else{
                vector<int> temp = {nums[i],nums[j],nums[k]};
                ans.push_back(temp);
                j++;
                k--;
                while(j<k && nums[j] == nums[j-1]) j++;
                while(j<k && nums[k] == nums[k+1]) k--;

            }
        }
    }
    return ans;
}

//this is the code for the three sum closest problem
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        // Sort the array to enable two-pointer technique
        sort(nums.begin(), nums.end());
        // Initialize result with the sum of first three elements
        int result = nums[0] + nums[1] + nums[2];

        // Iterate through each element as the first element of triplet
        for(int i = 0; i < n - 2; i++){
            // Initialize left pointer after current element
            int left = i + 1;
            // Initialize right pointer at the end
            int right = n - 1;

            // Use two pointers to find the closest sum
            while(left < right){
                // Calculate sum of current triplet
                int sum = nums[i] + nums[left] + nums[right];

                // Update result if current sum is closer to target than previous result
                if(abs(target - result) > abs(target - sum)){
                    result = sum;
                }

                // If sum equals target, return immediately (exact match found)
                if(sum == target) return sum;
                // If sum is less than target, move left pointer right to increase sum
                else if(sum < target) left++;
                // If sum is greater than target, move right pointer left to decrease sum
                else right--;
            }
        }

        // Return the closest sum found
        return result;
    }
};

int main()
{
    vector<int> arr = { -1, 0, 1, 2, -1, -4};
    int n = arr.size();
    vector<vector<int>> ans = triplet(n, arr);
    vector<vector<int>> ans1 = threeSum(arr);
    for (auto it : ans1) {
        cout << "[";
        for (auto i : it) {
            cout << i << " ";
        }
        cout << "] ";
    }
    cout << "\n";
    return 0;
}

