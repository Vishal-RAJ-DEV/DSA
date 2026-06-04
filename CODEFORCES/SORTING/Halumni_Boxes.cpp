#include <bits/stdc++.h>
using namespace std;

bool solve(){
    int n;
    int k;
    cin>> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin>> a[i];
    }
    if(k >= 2) return true;
    else{
        for(int i = 0;i < n -1 ; i++){
            if( a[i] > a[i+1]) return false;
        }
    }

    return true;
}
int main(){
    int n ;
    cin>> n ;

    while(n--){
        if( solve()){
            cout<< "YES" << endl;
        }
        else{
            cout<< "NO" << endl;
        }
    }
    return 0;
}
