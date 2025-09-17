#include <iostream>
#include <bits/stdc++.h>
using namespace std;

 int gcdOfOddEvenSums(int n) {
        int so = n*n;  //formula for sum of n odd number
        int se = n* (n +1 );//formula for sum of n even number 
        int r= min( so , se);
        while(r > 0){
            if(so % r == 0 && se % r == 0){
                break;
            }
            r--;
        }
        return r;
        
    }
int main(){
    int n = 5;
    cout << gcdOfOddEvenSums(n) << endl;
    return 0;
}