#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
       int n = arr.size();
       int maxi = -1;

        //start from the right side 
        //keep the track of the greatest value form the right and store in the maxi 
        //store in the each index store the maxi value 
       for( int i = n -1 ; i >= 0 ; i--){
            int temp = arr[i];
            arr[i] = maxi;
            maxi  = max( maxi , temp);
        }

        return arr; 
    }
};

int main(){
    Solution s;
        vector<int> arr = {17,18,5,4,6,1};
        vector<int> ans = s.replaceElements(arr);
        for( auto i : ans){
            cout << i << " ";
        }
        cout << endl;   
    return 0;
}