#include <iostream>
using namespace std;
//write a program to store first fibonacchi number.
int main(){
    int n;
    cout<<"enter your nummber (n>2) = ";
    cin>>n;

    int fib[n];
    fib[0]=0;
    fib[1]=1;
    cout<<fib[0]<<"\t"<<fib[1]<<"\t";

    for(int i=2;i<n;i++){
        fib[i]=fib[i-1]+fib[i-2];
        cout<<fib[i]<<"\t";
    }
    cout<<endl;
    

    
}