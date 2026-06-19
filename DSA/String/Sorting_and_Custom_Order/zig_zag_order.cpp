#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if( numRows == 1 || numRows >= s.length()) return s;

        int idx = 0;
        int d = 1;
        vector<vector<char>>row(numRows);

        for( char c : s){
            row[idx].push_back(c);
            if( idx == 0){
                d = 1;
            }
            else if( idx ==  numRows - 1) d = -1; //numsrow -1 beacuse the idx is start from 0 in row 

            idx += d;
        }

        string res = "";
        for(const auto& line : row ){
            for( char c : line){
                res += c;
            }
        }

        return res;
    }
};

int main(){
    Solution sol;
    cout << sol.convert("PAYPALISHIRING", 3) << endl;
    return 0;
}