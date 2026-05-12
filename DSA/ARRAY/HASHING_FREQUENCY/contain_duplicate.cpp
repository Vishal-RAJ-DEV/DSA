#include <iostream>
#include <bits/stdc++.h>
using namespace std;
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int>mpp;;
        for (int i = 0 ;i <nums.size();i++){
            if(mpp.count(nums[i]))return true;//if mpp count nums[i] means it already present in the mpp return true 
            mpp.insert(nums[i]);
        }
        return false;
    }
int main(){
    vector<int> nums = {1,2,3,1};
    cout << (containsDuplicate(nums) ? "Contains Duplicate" : "No Duplicates") << endl;
    return 0;
}
