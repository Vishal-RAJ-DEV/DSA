/*796. Rotate String
Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.
A shift on s consists of moving the leftmost character of s to the rightmost position.

For example, if s = "abcde", then it will be "bcdea" after one shift.
 
Example 1:
Input: s = "abcde", goal = "cdeab"
Output: true*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

 bool rotateString(string s, string goal) {
        if(s.size() != goal.size()) return false;
        string add = s + s;
        if(add.find(goal) == string::npos){
            return false;
        }
        return true;
    }
    
int main(){
    string s = "abcde";
    string goal = "cdeab";
    cout << rotateString(s, goal) << endl;  // Output: 1 (true)
    return 0;
}
