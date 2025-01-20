#include <iostream>
#include <bits/stdc++.h>
// Take a array from user and print the araay in the increasing order
using namespace std;
int main(){
    int n;
    cin>>n;
    int array[n];
    
    for(int i=0;i<n;i++){
        cin>>array[i];
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(array[i]>array[j]){
                int temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }
    }
    for(int i=0;i<n;i++){
        cout<<array[i]<<" ";
    }



    return 0;
}