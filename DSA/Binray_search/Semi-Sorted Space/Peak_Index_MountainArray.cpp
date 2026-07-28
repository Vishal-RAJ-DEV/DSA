#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        // Start low at 1 and high at arr.size() - 2 to prevent out of bounds
        int low = 1;
        int high = arr.size() - 2;
        
        while(low <= high){
            int mid = low + (high - low) / 2;
            
            if(arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]){
                return mid;
            } else if(arr[mid - 1] > arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return -1;
    }
};


int main(){
    return 0;
}