#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maximum69Number (int num) {
        string s = to_string(num);

        for( char &ch  : s){
            if( ch =='6') {
                ch ='9';
                break;
            }
        }

        return stoi(s);
    }
};

int main(){
    Solution sol;
    cout << sol.maximum69Number(9669) << endl; // Output: 9969
    cout << sol.maximum69Number(9996) << endl; // Output: 9999
    cout << sol.maximum69Number(9999) << endl; // Output: 9999
    return 0;
}