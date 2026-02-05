#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0 ;
        int right = s.size()-1;

        while(left <= right){
            while(left< right && !isalnum(s[left]))left++;  // if the character is nor char skip 
            while(left < right && !isalnum(s[right])) right--;   //same here 

            if(tolower(s[left]) != tolower(s[right])) return false ; //convert the char in lower case 
            left++;
            right--;
        }
        return true;
    }
};
int main(){

    string s = "A man, a plan, a canal: Panama";
    Solution sol;
    if(sol.isPalindrome(s)){
        cout<<"The string is a valid palindrome"<<endl;
    }
    else{
        cout<<"The string is not a valid palindrome"<<endl;
    }
    
    return 0;
} 