#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//approch 1 : using the sort function 
int kthLargest_sort( vector<int> & arr , int k){
    sort ( arr.begin() , arr.end());
    return arr[arr.size() - k ];
}
//approch 2 : using min heap
int KthLargest_MinHeap( vector<int> & arr ,int k ){
    priority_queue<int , vector<int> , greater<int> > minHeap;
    
}

int main(){
    vector<int> arr = { 3 , 2 , 1 , 5 , 6 , 4 };
    int k = 2;
    return 0;
}
