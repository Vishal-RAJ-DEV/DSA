#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int factorial(int n  , int m ){
{
    if(n==0)
    return 1;
    
}
return n*factorial(n-1, m) % m;
}


int factorial1(int n){
    int fact = 1;
    if( n == 1) return n;
    
    else {
         fact = n * factorial1(n-1);
    }

    return fact;
}

int main(){
    int n = 5;
    int m = 47;  //here m is taken as 47 just to avoid overflow for large n 
    cout<<factorial(n, m)<<endl;
    cout<<factorial1(n)<<endl;
    return 0;
}