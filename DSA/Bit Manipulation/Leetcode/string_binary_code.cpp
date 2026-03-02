#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Given a binary string s and an integer k, return true if every binary code of length k is a substring of s. Otherwise, return false.
Example 1:
Input: s = "00110110", k = 2
Output: true
Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.
*/
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        unordered_set<string> st; //for unique elements 
        int n = s.length();

        //calcualte the total numbers codes when the k is 2 
        //like for k = 2 , codes is 00 , 01  , 10 , 11

        int code = 1 << k ; //2 ^ k

        for( int i = k  ; i < n + 1 ; i++){ //start form kth elements so that there will two char before it 
            string substr  = s.substr( i - k , k);//last two char before i , till k , length

            if(!st.count(substr)){
                st.insert(substr);
                code--; //if required substring is found , then code becomes 0
            }

            if( code == 0 ){
                return true; //at the count 0 , we found all the substring 
                break;  //break after return , other wise it will stop at break
            }
        }
        return false;
    }
};

int main(){
    string s = "00110110";
    int k = 2;
    Solution obj;
    cout << obj.hasAllCodes(s, k) << endl;
    return 0;
}