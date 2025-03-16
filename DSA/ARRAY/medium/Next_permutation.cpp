#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int ind = -1;
    for(int i=n-2;i>=0;i--){   //first the arr iterate form second last element to 0 
        if(nums[i]<nums[i+1]){  //if the element in array is is less then their i+1 element 
            ind = i;             //it will store in the ind then it will break it ;
            break;
        }
    }
    if(ind == -1){
        reverse(nums.begin(),nums.end());    //if the ind is still -1 then we have to reverse the array then return it
        return;
    }
    for(int i = n-1;i>ind;i--){
        if(nums[i]>nums[ind]){       //then find the greater element than the ind and swap it with ind 
            swap(nums[i],nums[ind]);
            break;
        }
    }
    reverse(nums.begin()+ind+1,nums.end());   //at last reverse it to make it corrrect order 
}

int main(){

    vector<int> nums = {2, 1, 5, 4, 3, 0, 0};
    nextPermutation(nums);

    cout << "The next permutation is: [";
    for (auto it : nums) {
        cout << it << " ";
    }
    cout << "]n";

    return 0;
}