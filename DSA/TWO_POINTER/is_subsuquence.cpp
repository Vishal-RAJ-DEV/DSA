#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0 ;
        int j = 0 ;
        while( j < t.size() && i < s.size()){
            if( s[i] == t[j]) i++;
            j++;
        }
        return i == s.size();
    }
};

int main(){
    string s = "abc";
    string t = "ahbgdc";
    Solution sol;
    bool result = sol.isSubsequence(s, t);
    cout << "Is \"" << s << "\" a subsequence of \"" << t << "\"? " << (result ? "Yes" : "No") << endl;
    
    return 0;
}