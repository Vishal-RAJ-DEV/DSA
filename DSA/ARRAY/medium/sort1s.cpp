#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//sort colors question or sort 0s , 1s and 2s in an array
// time complexity O(n)
void sort(vector<int>& arr){
    int n = arr.size();
    int low  = 0 , mid  = 0 , high = n-1;
    while(mid<=high){
        if(arr[mid]==0){
            swap(arr[low],arr[mid]); //here we swap the mid with low because 0 should be at the start of the array then increase both low and mid
            low++;
            mid++;
        }
        else if(arr[mid]==1){//here we just increase the mid because 1 is already at the correct position
            mid++;
        }
        else{
            swap(arr[mid],arr[high]);   //here we swap the mid with high because 2 should be at the end of the array
            high--;
        }
    }
}
int main(){
    vector<int>arr={0,1,2,0,1,2};
    sort(arr);
    for(auto i:arr){
        cout<<i<<" ";
    }
    return 0;
}