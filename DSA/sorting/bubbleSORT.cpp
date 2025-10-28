#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//algorithm of bubble sort
/*
here what is happening
-> we are looping end to start so we can make sure that the largest number is at the end of the array
-> in every iteration we are comparing each element with the next one and swapping them if they are in wrong order
-> if in one complete iteration no swap happened then we can say that the array is already sorted
*/
void bubbleSORT(int arr [],int n){
    for(int i=n-1;i>=0;i--){  //we loop through the array from the end to the start to make sure that the largest number is at the end of the array
        int didswap =0; //declare it  zero to check if any swap happened the loop will run
        for(int j=0;j<=i-1;j++){     //loop will run through the array from the start to the second last element to compare and swap the elements
            if(arr[j]>arr[j+1]){ //in every iteration we are comparing each element with the next one and swapping them if they are in wrong order
                swap(arr[j],arr[j+1]);
                didswap=1;  //if there is swap then didswap will be 1
            }
        }
        if(didswap==0)   // if no swap happened then the array is already sorted and then we can break the loop so this can take less time complexity 
        break;
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

    cout<<"array after sorting"<<endl;
    bubbleSORT(arr,n);
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    
    return 0;
}