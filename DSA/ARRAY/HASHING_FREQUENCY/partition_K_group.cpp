#include <iostream>
#include <bits/stdc++.h>
using namespace std;
  bool partitionArray(vector<int>& nums, int k) {
        int size = nums.size();

        if(size % k != 0 ) return false;

        map<int , int > mpp;
        int group = size / k;// total size of the group 

        for(int i = 0 ; i< size ; i++){
            mpp[nums[i]]++;  //increment the count of the current number 
            if(mpp[nums[i]] > group){  //if the count exceeds than the group size return false 
                return false;
                break;
            }
        }
        return true;
    }
int main(){
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    int k = 3;
    cout << partitionArray(nums, k) << endl;
    return 0;
}
