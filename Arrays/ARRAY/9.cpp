#include <stdio.h>
//write a function to count the number of odd numbers in an array
int countodd(int arr[],int n);

int main(){
    int arr[]={1,2,3,4,5,6};
    int n=6;
    printf("%d\n",countodd(arr,n));
    printf("%d\n",arr[0]);
    printf("%d\n",*arr);
    
     return 0;
}
int countodd(int arr[],int n){
    int count=0;
    for(int i=0;i<n;i++){
        if(arr[i] % 2!=0){
            count++;
        }
    }
    return count;
}
    


    
