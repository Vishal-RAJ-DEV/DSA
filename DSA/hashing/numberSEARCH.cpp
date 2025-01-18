#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cout<<"enter your number : "<<endl;
    cin>>n;
    int arr[n];
    cout<<"enter the elementys of the array"<<endl;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    
    //precompute 
    int hash[13] ={0};
    for(int i=0;i<n;i++){
        hash[arr[i]]++;
    }

    int q;
    cout<<"enter the number of queries";
    cin>>q;
    while(q--){
        int number;
        cin>>number;
        //fetch
        cout<<hash[number];
    }

    
    return 0;
}