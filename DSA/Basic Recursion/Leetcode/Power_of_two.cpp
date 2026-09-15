#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int powerofX(int x , int n){
    if(n == 0) return 1; //base case
    if(x == 0) return 0; //if x is 0, then x^n is 0
    
    return x * powerofX(x, n-1); //recursive case
}



int main(){
    
    return 0;
}