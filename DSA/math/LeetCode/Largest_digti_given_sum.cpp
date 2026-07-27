#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestInteger(int n, int s) {
        if( s > 9 * n)return -1;

        long long ans = 0;
        for(int i = 0 ; i < n ; i++){
            int digit = min(9 , s);
            ans = ans * 10 + digit;
            s -= digit;
        }

        return (int)ans;
        
    }
};



int main(){
    return 0;
}