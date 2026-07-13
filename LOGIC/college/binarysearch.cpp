#include <stdio.h>
#include <stdlib.h>

int binarysearch(int arr[],int n,int target){
    int low =0; int high =n-1;

    while(low<=high){
        int mid=low+high/2;
        if(arr[mid]==target) return mid;
        else if(target>arr[mid])low=mid+1; //if target is greater than mid element then we will search in right side of mid element
        else high=mid-1; //else we will search in left side of mid element
    }
    return -1;
}
int main(){
    int n;
    printf("enter your number");
    scanf("%d",&n);
    int arr[n];
    printf("enter element of array");
    for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
    }
    int target ;
    printf("enter target element ");
    scanf("%d",&target);
    printf("target is at index %d",binarysearch(arr,n,target));
}