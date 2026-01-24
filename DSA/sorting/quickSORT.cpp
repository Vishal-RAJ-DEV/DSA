#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// time complexity : O(nlogn) on average case and O(n^2) on worst case
// space complexity : O(1)
int partition (vector <int> &arr,int low,int high){
    int pivot = arr[low];
    int i=low;
    int j= high;

    while(i<j){
        while(i<=high-1 && arr[i]<=pivot){ //here if i will increase till the time arr[i] is less than or equal to pivot or can say that till arr[i] is on the ele which is greater than pivot element
            i++;
        }
        while( j>low && arr[j]>=pivot){ //here if j will decrease till the time arr[j] is greater than or equal to pivot or can say that till arr[j] is on the ele which is smaller than pivot element
            j--;
        }
        if(i>=j) break; //if i is greater than or equal to j then we will break the loop means the partitioning is done
         swap(arr[i],arr[j]);  //after element at i and j will be swap  , this will place the smaller element on the left side of pivot and larger on the right side
    }
    swap(arr[low],arr[j]);  //then we will swap the pivot element with the element at j index so that pivot is at its correct position which is center of smaller and larger elements
    return j; //returning the pivot index so that we can use it to divide the array into two subarrays
}

void quickSORT(vector <int> &arr,int low,int high){
    if(low<high){
        int pIndex = partition(arr,low,high);
        quickSORT(arr,low,pIndex-1);  //this will sort the left subarray 
        quickSORT(arr,pIndex+1,high); //this will sort the right subarray
        //so first we are partitioning the array and then recursively calling the quickSORT function on the left and right subarrays and also dividing the subarrays further until the base condition is met and the array is sorted for the both left and right subarrays
        

    }
}
int main(){ //time complexity of the quick sort is O(nlog2^n) and space complexity is O(1)
    vector <int> arr = {4 ,6 ,2, 9 ,5 ,1 ,8 ,3 ,7 ,6};
    int n = arr.size();

    cout<<"before sorting array"<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }

    cout<<endl;

    quickSORT(arr,0,n-1);

    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }

    cout<<endl;

    return 0;
}