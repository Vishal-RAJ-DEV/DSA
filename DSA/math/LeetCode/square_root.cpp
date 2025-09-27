#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int mySqrt(int x) {
        if(x < 2 ) return x;
        int low = 1;
        int high = x/2;
        int ans = 0;
        while(low <= high){
            int mid = (low + high) / 2;
            if(mid * mid == x ) return x;
            else if(mid * mid < x ){
                ans = mid;   //this is to get ans as closet to the answer 
                low = mid + 1;
            } 
            else high = mid - 1;
        }
        return ans;
    }
int main(){
    int x;
    cout<<"enter a number: "<<endl;
    cin>>x;
    cout<<"Square root of "<<x<<" is "<<mySqrt(x)<<endl;    
    return 0;
}