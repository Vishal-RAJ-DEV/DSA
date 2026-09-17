#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void sumNatural(int i,int sum){
    if(i<1){
        cout<<sum<<endl;
        return;
    
    }
    sumNatural(i-1,sum+i);


}
int main(){
    int n;
    cin>>n;
    sumNatural(n,0);


    return 0;
}