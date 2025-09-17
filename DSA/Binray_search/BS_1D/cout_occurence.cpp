#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Problem Statement: You are given a sorted array containing N integers and a number X, you have to find the occurrences of X in the given array.



 int firstOccurence(vector<int>&arr ,int n, int target){
        int low = 0;
        int high = n-1;
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
    int lastOccurence(vector<int>&arr ,int n, int target){
        int low = 0;
        int high = n-1;
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

    int countFreq(vector<int>& arr, int target) {
        // code here
        int n = arr.size();
        int first = firstOccurence(arr, n, target);
        if (first == -1) return 0;
        int last = lastOccurence(arr, n, target);
        return last - first + 1;
    }
int main(){
    vector<int> arr = {1,2,2,3,4,5,6,6,6,7,8};
    int target = 6;
    int ans = countFreq(arr,target);
    cout<<"the occurence of the target is"<<" "<<ans<<endl;
    return 0;
}