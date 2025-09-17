#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// Problem Statement: Given an array of N integers, left rotate the array by one place.

void  leftRotate(int arr[], int n) {
    int temp = arr[0];
    for(int i=1 ;i<n; i++){
        arr[i-1] = arr[i]; //shifting all elements to left by one place
    }
    arr[n-1] = temp;  //putting first element at last
}

int main(){
    int arr[] = {1,2,3,4,5};
    int n = sizeof(arr)/sizeof(arr[0]);
    leftRotate(arr,n);
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    return 0;
}

// Time Complexity: O(n), as we iterate through the array only once.

// Space Complexity: O(1) as no extra space is used