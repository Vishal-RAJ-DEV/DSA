#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool rotateString(string s, string goal) {
        if(s.size() != goal.size()) return false;
        string add = s + s;
        if(add.find(goal) == string::npos){
            return false;
        }
        return true;
    }
};

/*
How .find() works
add.find(goal)

👉 It returns:
✅ index (0,1,2,...) → if found
❌ string::npos → if NOT found
*/


int main(){
    string s = "abcde";
    string goal = "cdeab";
    Solution sol; // create solution instance
    cout << "Can rotate s to goal? " << (sol.rotateString(s, goal) ? "Yes" : "No") << endl; // run and print

    return 0;
}
