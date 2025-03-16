#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int partition (vector <int> &arr,int low,int high){
    int pivot = arr[low];
    int i=low;
    int j= high;

    while(i<j){
        while(i<=high-1 && arr[i]<=pivot){ //here if i will increase till the time arr[i] is less than or equal to pivot
            i++;
        }
        while( j>low && arr[j]>=pivot){ //here if j will decrease till the time arr[j] is greater than or equal to pivot
            j--;
        }
        if(i>=j) break;
         swap(arr[i],arr[j]);  //after element at i and j will be swap 
    }
    swap(arr[low],arr[j]);
    return j;
}

void quickSORT(vector <int> &arr,int low,int high){
    if(low<high){
        int pIndex = partition(arr,low,high);
        quickSORT(arr,low,pIndex-1);  //this will sort the left subarray 
        quickSORT(arr,pIndex+1,high); //this will sort the right subarray
        

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