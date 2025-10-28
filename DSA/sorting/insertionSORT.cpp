#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
algorithm of insertion sort
-> we are looping through the array from the start to the end
->then in the inner loop we are comparing the current element with the previous element and the loop goes till its greater than 0 and the previous element is greater than the current element
->if the previous element is greater than the current element we swap them and decrease the index of the current element by 1
->this process is repeated until the current element is in the correct position
->then we move to the next element and repeat the process until the entire array is sorted
->time complexity is O(n^2) in the worst case and O(n) in the best case when the array is already sorted
*/
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