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
    
    void printHeap(){
        for( int i = 0 ; i < size ; i++ ){
            cout<< arr[i] << " ";
        }
        cout<< endl;
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
    return 0;
}
