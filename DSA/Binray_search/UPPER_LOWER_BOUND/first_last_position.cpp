#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
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

};


int main(){
    return 0;
}