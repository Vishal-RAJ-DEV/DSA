#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.

// If target is not found in the array, return [-1, -1].

// You must write an algorithm with O(log n) runtime complexity.
 int firstOccurence(vector<int>&arr , int target){
        int low = 0;
        int high = arr.size()-1;
        int first = -1;

        while(low<=high){
            int mid = (low + high)/2;
            if(arr[mid] == target){
                first = mid;
                high = mid - 1;
            }
            else if(arr[mid]<target){
                low = mid+1;
            }
            else{
                high = mid-1;
            }
        }
        return first;
    }
    int lastOccurence(vector<int>&arr , int target){
        int low = 0;
        int high = arr.size()-1;
        int last = -1;

        while(low<=high){
            int mid = (low + high)/2;
            if(arr[mid] == target){
                last = mid;
                low = mid + 1;
            }
            else if(arr[mid]<target){
                low = mid+1;
            }
            else{
                high = mid-1;
            }
        }
        return last;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int first = firstOccurence(nums,target);
        int last = lastOccurence(nums,target);
        if(first == -1 ) return {-1,-1};
        return {first , last};
    }
int main(){
    vector<int> arr = {1,2,2,3,4,5,6,7,8,9,10,10,10};
    int target = 10;
    vector<int> ans = searchRange(arr,target);
    cout<<"the first and the last occurence of the target is "<<ans[0]<<" "<<ans[1]<<endl;
    //time complexity is o(log n);

    return 0;
}