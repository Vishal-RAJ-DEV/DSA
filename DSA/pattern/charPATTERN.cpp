#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void print1(int n ){
    for(int i=1;i<=n;i++){
        for(int j = 1;j<=i;j++){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}

void print2(int n){
    
}
int main(){
    int n;
    cin>>n;

    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            cout<<" ";
        }
        for(char ch='A';ch<='A'+i;ch++){
            cout<<ch<<" ";
        }
        cout<<endl;
    }
    print1(n);
    return 0;
}