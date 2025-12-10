#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// Check if a string has valid parentheses
bool isValid(string s) {
    int balance = 0;
    for (char c : s) {
        if (c == '(') balance++;
        else balance--;
        if (balance < 0) return false;
    }
    return balance == 0;
}

void generateAll(string curr, int n, vector<string>& res) {
    if (curr.length() == 2 * n) {
        if (isValid(curr)) res.push_back(curr);
        return;
    }
    generateAll(curr + '(', n, res);
    generateAll(curr + ')', n, res);
}

vector<string> generateParenthesis1(int n) {
    vector<string> res;
    generateAll("", n, res);
    return res;
}
//basic algorithm is first generate parenthesis where '('  and when the ')' is added then go back by return statement and add ')' only if the close count is less than open count to avoid unbalanced parenthesis
//this will create two part of recursion tree one where '(' is added and other where ')' is added only if close count is less than open count
void generateParenthesis( int n , string str , vector<string> &result , int open , int close){
    if( str.size() == 2 * n){
        if( open == close){
            result.push_back(str);
        }
        return;
    }

    if( open < n){
        generateParenthesis( n , str + '(' , result , open + 1 , close); //this is other recursive part where '(' is added only if open count is less than n
    }
    if( close < open) {
        generateParenthesis( n , str + ')' , result , open , close + 1);//this is other recursive part where ')' is added only if close count is less than open count
    }
}
int main(){
    int n;
    int open = 0 ;
    int close  = 0;
    cin>>n;
    vector<string> result;
    string str="";
    generateParenthesis(n, str, result , open , close);
    for(auto &it : result){
        cout<<it<<endl;
    }
    int l = 3;
    vector<string> result1 = generateParenthesis1(l);
    cout << "All combinations (brute-force):" << endl;
    for (const string& s : result1) {
        cout << s << endl;
    }
    return 0;
}
