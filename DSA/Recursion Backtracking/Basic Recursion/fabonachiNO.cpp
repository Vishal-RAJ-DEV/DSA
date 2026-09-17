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

//space optimized approach
int fibSpaceOptimized(int n){
    if(n==0){
        return 0;
    }
    if(n==1){
        return 1;

    }
    int a=0;
    int b=1;
    for(int i=2;i<=n;i++){
        int next=a+b;
        a=b;
        b=next;

    }
    return b;

}
int main(){
    int n;
    cout<<"enter your number"<<endl;
    cin>>n;
    for(int i=0;i<=n;i++){
        cout<<fibSpaceOptimized(i)<<endl;

    }
    return 0;
}