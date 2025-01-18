#include <iostream>
#include <math.h>
// Problem Statement: Given an integer N, return true it is an Armstrong number otherwise return false.
// An Amrstrong number is a number that is equal to the sum of its own digits each raised to the power of the number of digits.


using namespace std;
int main(){
    int n;
    cout<<"enter your number:"<<endl;
    cin>>n;
     int sum=0;
    int dup=n;
   
    while(n>0){
        int lastD=n%10;
        sum=sum+(lastD*lastD*lastD);
        n=n/10;
    }
    cout<<sum<<endl;
    if(dup==sum)
    cout<<"number is armstrong";
    else
    cout<<"number is not armstrong";
    return 0;
}