#include <iostream>
//Given an integer N, return the number of digits in N.
#include <math.h>
using namespace std;
 int main(){
    int n;
    cout<<"enter the number"<<endl;
    cin>>n;
      int count=0;
    while(n>0){
      int lastdigit=n % 10;
        count++;
        n=n/10;
         }
         cout<<"number of digits are: "<< count ;
         return 0;
    
 }