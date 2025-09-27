#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int maxDepth(string s) {
        int depth = 0;
        int maxDepth = INT_MIN;
        for(char ch : s){
            if(ch == '('){
                depth++;
                maxDepth = max(maxDepth , depth);
            }
            else if (ch == ')'){
                depth--;
            }
        }
        return maxDepth == INT_MIN ? 0 : maxDepth;
    }

int main(){
    string s = "(1+(2*3)+((8)/4))+1";
    cout<<maxDepth(s);
    return 0;
}