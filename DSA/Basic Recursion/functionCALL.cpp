#include <iostream>
#include <bits/stdc++.h>
using namespace std;
 int cnt=0;
void func(){
   if (cnt==4) return;
    else
    cout<<cnt<<endl;
    cnt++;

    func();
    }
int main(){
    func();
    
    
    return 0;
}
