#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeDuplicates(string s) {
        int n = s.size();
        string ans;
        for( int i = 0 ; i< n ; i++){
            if(!ans.empty() && ans.back() == s[i]){
                ans.pop_back();
            }else{
                ans.push_back(s[i]);
            }

        }

        return ans;
    }
};

int main(){
    Solution sol;
    string s = "abbaca";
    string result = sol.removeDuplicates(s);
    cout << "Result after removing adjacent duplicates: " << result << endl;
    return 0;
}
