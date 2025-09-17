#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int printpair(int arr[], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << "(" << arr[i] << ", " << arr[j] << ")" << " ";
        }
        cout<<endl;
    }
}
int main(){
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printpair(arr, n);
    return 0;
}
