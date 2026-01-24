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


int main(){
    int n;
    int m = 47;  //here m is taken as 47 just to avoid overflow for large n 
    cin>>n;
    cout<<factorial(n, m)<<endl;
    return 0;
}