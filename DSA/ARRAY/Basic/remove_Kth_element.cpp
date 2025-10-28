#include <iostream>
#include <bits/stdc++.h>
using namespace std;

 int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int k = 0; //slow pointer
        for(int i = 0 ; i< n ;i++){
            if(nums[i] != val){
                nums[k] = nums[i];
                k++;
            }
        }
        return k ; 
    }
int main(){
    vector<int> nums = {3,2,2,3,4,3,5};
    int val = 3;
    int k = removeElement(nums, val);
    cout<<"The new length of the array is: "<<k<<endl;
    cout<<"The modified array is: ";
    for(int i = 0 ; i<k ;i++){
        cout<<nums[i]<<" ";
    }
    return 0;
}