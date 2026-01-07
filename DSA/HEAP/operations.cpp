#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class MaxHeap {
    public :
    int arr[100];
    int size = 0 ;

    void insert( int val ){
        int index = size;
        arr[index] = val;
        size = size + 1 ; //for next element

        while( index > 0){
            int parent = ( index - 1) / 2;
            if( arr[parent] < arr[index]){
                swap( arr[parent], arr[index]);
                index = parent;
            }
            else{
                return ;
            }
        }

    }
    void Delete(){
        if( size == 0){
            cout<<" heap is empty "<<endl;
            return;
        }

        //step 1 : put last element to first index
        arr[0] = arr[size - 1];

        //decrease the size so that last element is not considered
        size = size - 1 ;

        //now fix the position of the node
        int i = 0 ;
        while( i < size){
            int left = 2*i + 1;
            int right = 2 *i + 2;
            int largest = i ;

            // compare with left and right child
            if( left > 0 && arr[largest] < arr[left]){
                largest = left;
            }
            if( right > 0 && arr[largest] < arr[right]){
                largest = right;
            }
            // no need to swap
            if( largest == i ) break;
            else{ // swap
                swap( arr[largest] , arr[i]);
                i = largest; //and continue the loop for the next child node
            }
        }
    }
    
    void printHeap(){
        for( int i = 0 ; i < size ; i++ ){
            cout<< arr[i] << " ";
        }
        cout<< endl;

    }
    //for the max heapify function
    void heapify( int arr[] , int n , int i ){
        int largest = i ;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if( left < n && arr[largest] < arr[left]){
            largest = left;
        }
        if( right < n && arr[largest] < arr[right]){
            largest  =  right ;
        }
        if( largest != i ){
            swap( arr[largest] , arr[i]);
            heapify( arr , n , largest);   //recursive call beacuse the swapped node may violate the heap property so we need to heapify it again   
        }
    }

    void heapSort( int arr[] , int n , MaxHeap &h){
        //every index from n - 1 to 0 will be placed at its correct position that how its sorted array 
        for( int i = n - 1 ; i >= 0 ; i-- ){
            //step 1 : swap the first and last element
            swap( arr[0] , arr[i]);
            //step 2 : heapify the root node for the reduced heap
            h.heapify( arr , i , 0); // here i is reduced size of heap
        }
    }

    
};
int main(){
    MaxHeap h;
    h.insert( 50 );
    h.insert( 55 );
    h.insert( 53 );
    h.insert( 52 );
    h.insert( 54 );
    h.printHeap();
    h.Delete();
    h.printHeap();

    //here now we will and apply heapify function to build heap from array
    int nums[] = { 54, 53, 55, 52, 50 };
    int n = 5;
    cout<<" printing the original array "<<endl;
    for ( int i = 0 ; i < n ; i++ ){
        cout<< nums[i] << " ";
    }
    cout<< endl;
    //heapify process
    //so here the we heapify form the n/2 - 1 th index to 0 th index 
    //beacuse the n/2 - 1 th index is the last non leaf node
    //and form n / 2 to n - 1 th index all are leaf nodes
    for( int i = n / 2 - 1 ; i >= 0 ; i--){
        h.heapify( nums , n , i);
    }
    cout<<" printing the array after heapify "<<endl;
    for( int i = 0 ; i < n ; i++ ){
        cout<< nums[i] << " ";
    }
    cout<< endl;

    //heap sort 
    h.heapSort( nums , n , h);
    cout<<" printing the array after heap sort "<<endl;
    return 0;
}
