#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {

        unordered_map<int,int> freq;

        // Step 1: Count frequency of every element
        for(int x : nums)
            freq[x]++;

        // Maximum possible frequency = nums.size()
        // bucket[i] stores all numbers having frequency = i
        vector<vector<int>> bucket(nums.size()+1);

        // Step 2:
        // Instead of sorting by frequency,
        // directly put every number inside the bucket
        // corresponding to its frequency.
        for(auto &it : freq){

            int number = it.first;
            int frequency = it.second;

            bucket[frequency].push_back(number);
        }

        vector<int> ans;

        // Step 3:
        // Traverse from highest frequency bucket
        // towards lowest frequency bucket.
        for(int i = nums.size(); i >= 1 && ans.size() < k; i--){

            for(int x : bucket[i]){

                ans.push_back(x);

                if(ans.size()==k)
                    break;
            }
        }

        return ans;
    }
};


int main(){
    return 0;
}