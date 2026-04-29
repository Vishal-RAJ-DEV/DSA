#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& colors) {
        //here we use the xor propety to check the mismatch 
        //like 1 ^ 6 give the 1 so we get the first mismatch ( different color)
        int n = colors.size();
        int left = 0 ;
        int right = 0 ;
        
        //first mismatch from the left to last element
        for( int i = 0 ; i < n ; i++){
            if( colors[i] ^ colors[n-1]){
                left = i;
                break; //stop here
            }
        }

        //from the right first compare to the first element 
        for( int i = n -1 ; i >=0 ; i--){
            if( colors[i] ^ colors[0]){
                right= i;
                break ;
            }
        }

        return max( n - 1 - left , right);
        //here left have first mismatch house compare to last ele n - 1;
        //so to get the lenght of that we ( n -1 ) - left;
    }
};


int main(){
    Solution s;
    vector<int> colors = {1,1,1,6,1,1,1};
    cout<< s.maxDistance(colors) << endl;
    
    return 0;
}