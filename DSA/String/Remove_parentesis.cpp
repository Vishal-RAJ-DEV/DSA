#include <iostream>
#include <bits/stdc++.h>
using namespace std;

 string removeOuterParentheses(string s) {
        int size = s.size();
        string result = "";
        int depth = 0;

        for(int i= 0;i<size;i++){
            if(s[i]=='('){
                if(depth>0){
                    result += s[i];
                }
                depth++;
            }
            else{
                depth--;
                if(depth>0){
                    result +=s[i];
                }
            }
        }
        return result;
    }
int main(){
    string s = "(()())(())";
    string result = removeOuterParentheses(s);
    cout << result << endl;  // Output: ()()()
    return 0;
}

// Dry Run – "(()())(())"
// sql
// Copy
// Edit
// result = ""
// depth = 0

// '(' -> depth=0 so skip adding, depth=1
// '(' -> depth>0 so add '(', depth=2 -> result="("
// ')' -> depth=1 so add ')', result="()"
// '(' -> depth>0 so add '(', depth=2 -> result="()("
// ')' -> depth=1 so add ')', result="()()"
// ')' -> depth=0 so skip

// Next primitive:
// '(' -> skip, depth=1
// '(' -> add '(', depth=2 -> "()()("
// ')' -> add ')', depth=1 -> "()()()"
// ')' -> skip, depth=0

// Final result = "()()()"