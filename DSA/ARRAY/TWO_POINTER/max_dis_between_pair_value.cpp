#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int i = 0 ; //pointer at nums1
        int j  = 0 ;//pointer at nums2

        while( i < nums1.size() && j < nums2.size()){
            //if invalid pair
            if( nums1[i] > nums2[j]) i++;
            j++; //j should be greater then i always to be pair 
        } 
        //index j - i is farthest differnce of the pair 
        //and here -1 beacuse the j is one step ahead in the while loop
        return max( 0 , j - i - 1);

    }
};


int main(){
    Solution s;
    vector<int> nums1 = {55,30,5,4,2};
    vector<int> nums2 = {100,20,10,10,5};
    cout<< s.maxDistance(nums1, nums2) << endl;

    return 0;
}