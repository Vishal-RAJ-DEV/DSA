#include <iostream>
using namespace std;
//Problem Statement: Given an integer N return the reverse of the given number.

int main(){
    int n;
    cin>>n;
    int reverse=0;
    while(n!=0){
        int lastdigit=n%10;
        reverse=(reverse*10)+lastdigit;
        n=n/10;
    }
    cout<<"reverse of number : "<<reverse;
    return 0;
}