#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void reversearrary(int arr[],int n){
    for(int i=0;i<=n/2;i++){
        int temp=arr[i];
        arr[i]=arr[n-i-1];
        arr[n-i-1]=temp;
    }
}
int main(){
    int arr[]={23,93,98,3,12,45};
    int n=sizeof(arr)/sizeof(arr[0]);
    reversearrary(arr,n);

    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}