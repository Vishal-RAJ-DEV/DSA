#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//Problem Statement: You are given an array. The task is to reverse the array and print it
void fun(int i,int n,int arr[]){
    if(i>=n/2)
    return ;
    swap(arr[i],arr[n-i-1]);
    fun(i+1,n,arr);

    
        

    }
    

int main(){
    int n; 
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++) cin>>arr[i];
    fun(0,n,arr);
    for(int i=0;i<n;i++) cout<<arr[i]<<" ";

     
    return 0;
}