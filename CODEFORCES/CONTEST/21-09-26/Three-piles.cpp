#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        long long a , b , c;
        cin>>a>>b>>c;
        
        long long diff = abs(a - b);
        cout<<max(diff , a - b + c)<<endl;
        
    }
    return 0;
}