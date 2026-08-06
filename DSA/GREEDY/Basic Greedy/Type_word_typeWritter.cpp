#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minTimeToType(string word) {
        int n = word.size();
        // store the word size in the ans 
        //beacuse each character take 1 to write 
        int res = n;
        char point = 'a';
        //now for each character check which is close
        // to go to a , either clockwise or anticlockwise 
        for(char ch : word){
            int Anticlockwise = abs(ch - point);
            int Clockwise =  26 - abs(ch - point);
            point = ch;

            res+= min( Anticlockwise , Clockwise);

        }

        return res;
    }
};



int main(){
    Solution sol;
    string word = "abc";
    cout << sol.minTimeToType(word) << endl; // Output: 5
    return 0;
}
