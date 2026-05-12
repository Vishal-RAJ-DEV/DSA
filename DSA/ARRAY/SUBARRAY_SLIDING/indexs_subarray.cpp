#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> subarraySum(vector<int> &arr, int target) {
        // code here
        //using the sliding window concept 
        int start = 0 , end = 0 ;
        vector<int>res ;
        int sum = 0;
        for( int i= 0 ; i < arr.size() ; i++){
            sum += arr[i];
            
            //now we we check on the when the sum becomes greater than the target or equals ot
            
            if( sum >= target){
                end = i ; // when the sum becomes the larger mark the end 
                
                
                //now decrese the window when the sum is greater than the target 
                while( sum > target && start < end){
                    sum-=arr[start];
                    start++;
                    
                }
                //when found the target ele , then store the starting index and end index
                if( sum == target){
                    res.push_back(start + 1);
                    res.push_back(end + 1);
                    return res;
                }
            }
        }
        return {-1};
    }
};

int main(){
    Solution sol;
    vector<int> arr = {1, 2, 3, 7, 5};
    int target = 12;
    vector<int> result = sol.subarraySum(arr, target);
    for(int i : result){
        cout << i << " ";
    }

    return 0;
}