#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool solve ( string s ,  unordered_set<string> & st , vector<int> &dp , int idx , int maxlen){
        if (idx == s.length()) return true;
        
        //dp for the optimization 
        if( dp[idx] != -1) return dp[idx];

        //here we are trying all the possible lengths of the substring from the current index
        //use the maxlen to limit the length of the substring to avoid unnecessary checks
        for ( int l = 1 ;l<= maxlen && idx + l <=s.length() ; l++){
            string substring = s.substr( idx , l);
            //here we are checking if the substring is present in the set or not and then we are calling the function recursively for the next index 
            if( (st.find(substring) != st.end()) && solve(s , st, dp , idx + l , maxlen)){
                return dp[idx] = 1;
            }
        }
        return dp[idx] = 0;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> st( wordDict.begin() , wordDict.end());
        int maxlen = 0 ;
        for ( auto &w : wordDict){
            maxlen = max( maxlen , (int)w.length());
        }
        vector<int> dp ( s.length() , -1 );
        return solve (s , st , dp , 0 , maxlen );
    }
};

int main(){
    Solution obj;
    string s = "leetcode";
    vector<string> wordDict = {"leet", "code"};
    if( obj.wordBreak(s , wordDict )){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }
    return 0;
}