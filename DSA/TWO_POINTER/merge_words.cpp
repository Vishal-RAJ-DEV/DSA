#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int s1 = word1.length();
        int s2 = word2.length();
        int p = 0 ; //pointer to the word1 and word2
        string s = "";
        while ( p < s1 || p < s2){ //store the letter form the word1 and word2 both together
        //then move to the next pointer
            if( p < s1){
                s += word1[p];
            }
            if( p < s2){
                s += word2[p];
            }
            p++;
        }
        return s;
    }
};


int main(){
    string word1 = "abc";
    string word2 = "pqr";
    Solution s;
    string ans = s.mergeAlternately(word1, word2);
    cout << "The merged string is: " << ans << endl;
    return 0;
}