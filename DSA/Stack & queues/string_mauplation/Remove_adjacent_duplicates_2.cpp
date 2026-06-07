#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeDuplicates(string s, int k) {
        int n =s.size();

        //this will store in the character and their frequency 
        vector<pair<char , int >> st;

        for ( int i = 0 ; i < n ; i++){
            //put the char in the map frequecy and when its not equal to last character 
            if( st.empty() || st.back().first != s[i]){
                st.push_back({s[i] , 1});
            }else{
                st.back().second++;
            }
            if( st.back().second == k ) st.pop_back();
            
        }

        string ans;
        for(auto & ch : st){
            int cnt = ch.second;
            char c = ch.first;
            ans += string(cnt , c);
        }

        return ans;

    }
};


int main(){
    Solution sol;
    string s
    = "deeedbbcccbdaa";
    int k = 3;
    string result = sol.removeDuplicates(s, k);
    cout << "Result after removing adjacent duplicates: " << result << endl;

    return 0;
}
