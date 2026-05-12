#include<bits/stdc++.h>
using namespace std;
// Problem Statement: Given an array, find the second smallest and second largest element in the array. Print ‘-1’ in the event that either of them doesn’t exist.

int secondSmallest(int arr[],int n)
{
    if(n<2)
        return -1;
    int small = INT_MAX; //also can be written as int small=arr[0];
    int second_small = INT_MAX; //also can be written as int second_small= INT_MAX;
    int i;
    for(i = 0; i < n; i++) 
    {
       if(arr[i] < small)
       {
          second_small = small; //previous small will be second small
          small = arr[i]; //current small will be the smallest
       }
       else if(arr[i] < second_small && arr[i] != small) //if current element is smaller than second small and not equal to small then it will be second small
       {
          second_small = arr[i];
       }
    }
   return second_small;     
}
int secondLargest(int arr[],int n)
{
	if(n<2)
	return -1;
    int large=INT_MIN; //also can be written as int large=arr[0];
    int second_large=INT_MIN; //also can be written as int second_large= -1;
    int i;
    for (i = 0; i < n; i++) 
    {
        if (arr[i] > large) 
        {
            second_large = large; //previous large wud be second large 
            large = arr[i];  //current large will be the largest
        }
 
        else if (arr[i] > second_large && arr[i] != large) //if current element is greater than second large and not equal to large then it will be second large
        {
            second_large = arr[i];
        }
    }
    return second_large;                
}

int main() {  //time complexity is O(n) and space complexity is O(1)
    int arr[]={1,2,4,7,7,5};  
    int n=sizeof(arr)/sizeof(arr[0]);
        int sS=secondSmallest(arr,n);
        int sL=secondLargest(arr,n);
    cout<<"Second smallest is "<<sS<<endl;
    cout<<"Second largest is "<<sL<<endl;
    return 0;
}


