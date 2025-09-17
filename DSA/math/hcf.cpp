#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//Problem Statement: Given two integers N1 and N2, find their greatest common divisor.
//The Greatest Common Divisor of any two integers is the largest number that divides both integers.
int main(){
    int a,b;
    cout<<"enter your number: ";
    cin>>a>>b;
    int result =  min( a , b );  // Find the minimum of a and b because the GCD cannot be greater than the smaller number 
    while(result > 0){  
        if(  a % result == 0 && b % result == 0 )  
        //if  the result divides the a and b together than that will be the gcd  
        //for eg a = 8 and b = 12 so at and the result is at 4
        // that will completely divides the both a and b 
        cout<<result;
        result--;
    }
}