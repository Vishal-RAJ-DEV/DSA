#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//optimal approach to solve the problem of two sum.
//time cmplexity of the code is o(n) and space complexity is o(n).
vector<int> twoSum(vector<int>&arr ,int target){
    unordered_map<int,int>mp;
    int n=arr.size();
    for(int i =0;i<n;i++){
        int num = arr[i];
        int rem = target-num;
        if(mp.find(rem)!=mp.end()){  //if the element which is rem = target-arr[i] is present in the map then return the index of that element and the current element.
        return {mp[rem],i};  // return the index of the element which is rem and the current element.
        }
        mp[num]= i;

    }
}

//below is the code for the same problem but with the sorted array.
//time complexity of the code is o(n) + o(nlogn) = o(nlogn) and space complexity is o(1).
vector<int> twoSum2(vector<int> &arr, int target) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    int left = 0, right = n - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) {
            return {left,right};
        }
        else if (sum < target) left++;  //if the sum is less than the target then we have increase the value of left++ to increase the sum.
        else right--;  //if the sum is greater than the target then we have to decrease the value of right-- to decrease the sum.
    }
    return {-1, -1};
}


int main(){
    vector<int>arr={2,7,11,15};
    int target = 26;
    vector<int>res = twoSum2(arr,target);
    for(auto i:res){
        cout<<i<<" ";
    }
    return 0;
}