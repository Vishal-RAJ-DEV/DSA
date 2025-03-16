#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int maxconsecutive(vector<int>&arr){
    int n = arr.size();
    int maxI = 0;
    int CNT = 0;
    for(int i=0;i<n;i++){
        if(arr[i] == 1){   //if element is 1 then increase the count
            CNT++;
            maxI = max(maxI,CNT);  //update the maxI with the maximum of maxI and CNT
        }
        else{
            CNT = 0;  //if element is 0 then reset the count
        }
    }
    return maxI;
}
int main(){
    vector<int> arr = {1,1,0,0,1,1,1,0,1,1,1,1};
    cout<<"max consecutive 1's are"<<"\n"<<maxconsecutive(arr);
    return 0;
}