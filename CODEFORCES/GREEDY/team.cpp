#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<vector<int>> arr(n , vector<int>(3));
    for(int i = 0 ; i < n ; i++){
        for( int j = 0 ; j < 3 ; j++){
            cin>>arr[i][j];
        }
    }
    int maxcount = 0;
    for( int i = 0 ; i < n ; i++){
        int cnt = 0;
        for(int j = 0 ; j < 3 ; j++){
            if( arr[i][j] ==1){
                cnt++;
            }
        }
        if( cnt >= 2){
            maxcount++;
        }
    }
    cout<<maxcount<<endl;
    return 0;
}