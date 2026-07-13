#include <iostream>
using namespace std;

int isprime(int n){
    if (n<=1) return 0;
    for(int i=2;i*i<=n;i++){
        if(n % i==0) return 0;
    }
    return 1;
}

int main(){
    int n;
    cout<<"enter your number";
    cin>>n;
    if(isprime(n))
    cout<<"prime number";
    else
    cout<<"not a prime number";

    return 0;
}