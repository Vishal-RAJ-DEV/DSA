#include <iostream>
using namespace std;
//writr a function to reverse an array.

int reverse(int arr[],int n){
    for(int i=0;i<=n/2;i++){
        int firstVALUE=arr[i];
        int secValue=arr[n-i-1];
        arr[i]=secValue;
        arr[n-i-1]=firstVALUE;
       
        }
        
}
void printnum(int arr[],int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<"\t";
    }
}

int main(){
    int arr[]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        cout<<arr[i]<<"\t";
    }
    cout<<endl;
    reverse(arr,5);
    printnum(arr,5);
    return 0;
}

