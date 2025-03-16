#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void insertionSORT(int arr[],int n){
    for(int i=0;i<=n-1;i++){
        int j=i;
        while(j>0 && arr[j-1]>arr[j]){ //if the element is smaller than the previous one, swap them until the correct position is found
            swap(arr[j],arr[j-1]);
            j--;  //the loop decrese the index until the correct position is found
        }
    }
}
int main(){
    int  n;
    cin>>n;

    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    cout<<"array before sorting"<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    cout<<"array after sorting"<<endl;
    insertionSORT(arr,n);
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
    
}