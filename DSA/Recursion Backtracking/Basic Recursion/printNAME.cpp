#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//Problem: Print your Name N times using recursion
void printname(int i,int n){
    if(i>n)return;
    cout<<"vishal"<<endl;
    printname(i+1,n);
}
int main(){
    int n;
    cin>>n;
    printname(1,n);


    return 0;
}