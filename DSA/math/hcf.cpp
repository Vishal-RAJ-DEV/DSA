#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//Problem Statement: Given two integers N1 and N2, find their greatest common divisor.
//The Greatest Common Divisor of any two integers is the largest number that divides both integers.
int main(){
    int a,b;
    cout<<"enter your number: ";
    cin>>a>>b;
    while(a>0&&b>0){
        if(a>b) a=a%b;
        else b=b%a;
    }
    if(a==0)cout<<b;
    else cout<<a;
    return 0;
}