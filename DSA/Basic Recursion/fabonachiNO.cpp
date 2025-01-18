#include <iostream>
#include <bits/stdc++.h>
//Given an integer N. Print the Fibonacci series up to the Nth term.
using namespace std;
int fib(int n){
    if(n==0){
        return 0;
    }
    if(n==1){
        return 1;

    }

    int last=fib(n-1);
    int scelast=fib(n-2);
    return last+scelast;


}
int main(){
    int n;
    cout<<"enter your number"<<endl;
    cin>>n;
    for(int i=0;i<=n;i++){
        cout<<fib(i)<<endl;

    }
    return 0;
}