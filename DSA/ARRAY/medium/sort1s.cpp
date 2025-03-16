#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// time complexity 
void sort(vector<int>& arr){
    int n = arr.size();
    int low  = 0 , mid  = 0 , high = n-1;
    while(mid<=high){
        if(arr[mid]==0){
            swap(arr[low],arr[mid]);
            low++;
            mid++;
        }
        else if(arr[mid]==1){
            mid++;
        }
        else{
            swap(arr[mid],arr[high]);
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