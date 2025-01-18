#include <iostream>
#include <bits/stdc++.h>
//Problem Statement: Given an integer N, return all divisors of N.

//A divisor of an integer N is a positive integer that divides N without leaving a remainder. In other words, if N is divisible by another integer without any remainder, then that integer is considered a divisor of N.
using namespace std;
void printdivisor(int n){
    vector<int>list;
    //6*6<=36 true
    //7*7<=36 flase   loop will stop
    for(int i=1;i*i<=n;i++){
        if(n%i==0){ //36%3==0 true then 3 will store in list
            list.push_back(i); //i will store in list one next one

            if((n/i)!=i){  //then 36/3=12 !=i true the 12 will store in list
                list.push_back(n/i); // i will store in list one next one
            }
        }
    }
    sort(list.begin(),list.end());//this will sort list in ascensing order
    cout<<"Divisor of : "<< n <<endl; 
    for(auto it:list)cout<<it<<"\t";  //print the list vector
}

int main(){
int n;
cout<<"enter your number";
cin>>n;
printdivisor(n);
    return 0;
}