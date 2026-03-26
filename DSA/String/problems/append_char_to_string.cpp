#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int appendCharacters(string s, string t) {
        int sIdx = 0 ;
        int tIdx = 0 ;
        int slen = s.size();
        int tlen = t.size();
        while( sIdx < slen && tIdx < tlen){
            if( s[sIdx] == t[tIdx]){
                tIdx ++;
            }
            sIdx++;
        }
        //return the element that is not matched in the t string 
        return tlen - tIdx;
    }
};


int main(){
    
    return 0;
}
