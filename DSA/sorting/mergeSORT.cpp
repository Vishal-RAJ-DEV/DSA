#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// time complexity : O(nlogn) on average case and O(nlogn) on worst case
// space complexity : O(n)
void merge(vector <int>& arr,int low,int mid,int high){
    vector <int> temp;

    int left = low;
    int right = mid+1;

    while(left<=mid && right<=high){ //if the both pointers are within the array
        if(arr[left]<=arr[right]){   //if the value in the left index is smaller than the value in the right index then it will be placed in the temp array
            temp.push_back(arr[left]);
            left++;  // after stroring the value in the temp array the left pointer will be incremented
        }
        else{
            temp.push_back(arr[right]); //if the value in the right index is smaller than the value in the left index then it will be placed in the temp array 
            right++; //then it also will be incremented
        }
    }
    while(left<=mid){
        temp.push_back(arr[left]); //if there are remaining elements in the left array then they will be placed in the temp array
        left++;
    }
    while(right<=high){
        temp.push_back(arr[right]); //if there are remaining elements in the right array then they will be placed in the temp array
        right++;
    }

    for(int i=low;i<=high;i++){  //here we are copying the elements from the temp array to the original array
        arr[i]= temp[i-low];
    }
}

void mergesort(vector <int>& arr,int low ,int high){
    if(low>=high) return ;
    int mid = low + (high-low)/2;
    mergesort(arr,low,mid); //here we are dividing the array into two halves untill we get the single element in the left and right subarray which is the base case of the recursion in the left sude of the array.
    mergesort(arr,mid+1,high);   //here also we are dividing the array into two halves untill we get the single element in the left and right subarray in the right side of the array
    merge(arr,low,mid,high);  //here the main logic of the merge sort algorithm is implemented which is to merge the two sorted subarrays into one sorted array.
}

int main(){                                //time complexity of the merge sort is O(nlog2^n) and space complexity is O(n)
    vector <int> arr = { 9,4,7,6,2,6,16};

    cout<<"before mergeing the array : "<<endl;
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }

    cout<<endl;


    mergesort(arr,0,arr.size()-1);

    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }

    return 0;
}