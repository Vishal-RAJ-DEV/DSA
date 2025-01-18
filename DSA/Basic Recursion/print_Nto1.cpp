#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//Problem: Print from N to 1 using Recursion
void printnumber(int i,int n){
    if(n<=i)return;
    cout<<n<<endl;

    printnumber(i,n-1);


}

int main(){
    int n;
    cin>>n;
    printnumber(1,n);
    return 0;
}