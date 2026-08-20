#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int n = nums.size();  
         int xorr = 0;
         for(int i =0; i<n;i++){
            xorr = xorr ^ nums[i];
        }
        return xorr;
        
    }
};


int main(){
    return 0;
}