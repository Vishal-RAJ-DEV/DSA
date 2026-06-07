#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isvowel( char c){
        if( c == 'a' ||  c == 'e' || c == 'i' || c == 'o' || c == 'u') return true;
        return false;
    }
    int maxVowels(string s, int k) {
        int cnt = 0;
        int maxcnt = 0;
        int l = 0;
        int r = 0;
        while( r < s.size()){

            if( isvowel(s[r])) cnt++;
            if((r - l + 1) == k) {
                maxcnt = max( maxcnt , cnt);
                if(isvowel(s[l])) cnt--;
                l++;
            }
            r++;
        }

        return maxcnt;
    }
};


int main(){
    Solution sol;
    string s = "abciiidef";
    int k = 3;
    int result = sol.maxVowels(s, k);
    cout << "Maximum number of vowels in a substring of length " << k << ": " << result << endl;
    return 0;
}