#include <iostream>
#include <bits/stdc++.h>
//Given a string, check if the string is palindrome or not."  A string is said to be palindrome if the reverse of the string is the same as the string.
using namespace std;
bool f(int i, string &s){
    if(i>=s.size()/2) return true;
    if(s[i]!=s[s.size()-i-1]) return false ;

    return f(i+1,s);

}

int main(){
    
    string s;
    getline(cin,s);
    cout<<f(0,s)<<endl;
    return 0;

} 