#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        vector<int>left( n , 0);
        vector<int>right(n , 0);

        //here for the each security[i] >= security[i-1] that will count as one 
        //same for the right side if security[i]<= security[i+1] that will count 
        //and also add the previous prefix also 
        //left[0] and right[n-1] is 0 because there not element to compare with 

        for( int i = 1; i <n; i++){
            if(security[i] <= security[i-1]){
                left[i] = 1+ left[i-1];
                //current add 1 and precious counts prefix count 
            }
        }

        for( int i = n -2; i>= 0 ; i--){
            if( security[i] <= security[i+1]){
                right[i] = 1 + right[i+1];
            }
        }

        //now check the left and right sum is satisfies the time 
        //conditions is time <=left[i] and right[i];
        vector<int>ans;
        for( int i= time ; i < n-time; i++){
            if( left[i] >= time && time <= right[i]){
                ans.push_back(i);
            }
        }

        return ans;

    }
};

int main(){
    return 0;
}