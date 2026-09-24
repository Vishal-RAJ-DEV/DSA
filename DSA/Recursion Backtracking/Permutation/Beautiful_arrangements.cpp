#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    void solve(int pos , int n , vector<int>&used , int &cnt){
        //if all the pos is full and valid then increase the cnt
        if( pos > n){
            cnt++;
        }

        for(int i = 1; i <= n ; i++){
            if(!used[i] && (pos % i == 0 || i % pos == 0)){
                used[i] = 1;
                solve(pos + 1 , n , used , cnt);
                used[i] = 0;
            }
        }
    }
public:
    int countArrangement(int n) {
        vector<int>used(n +1 , 0);
        int cnt = 0;
        //start from the position 1 
        solve(1 , n , used , cnt);
        return cnt;
    }
};



int main(){
    return 0;
}   