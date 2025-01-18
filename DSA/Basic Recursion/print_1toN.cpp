#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//Problem: Print from N to 1 using Recursion
void printname(int i,int n){
    if(i>n)return;
    cout<<i<<endl;
    printname(i+1,n);
}
int main(){
    int n;
    cin>>n;
    printname(1,n);


    return 0;
}