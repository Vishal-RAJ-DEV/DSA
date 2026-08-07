#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*

for every character

    if '(' or ','
        ignore

    else if ')' encountered

        pop all operands

        pop operator

        evaluate

        push result

    else
        push current character
*/



class Solution {
public:
    bool parseBoolExpr(string expression) {

        stack<char> st;

        for (char ch : expression) {

            // Ignore commas and opening brackets
            if (ch == ',' || ch == '(')
                continue;

            // If current character is not ')', push it
            if (ch != ')') {
                st.push(ch);
            }
            else {

                int t = 0;
                int f = 0;

                // Collect all operands
                while (st.top() == 't' || st.top() == 'f') {
                    if (st.top() == 't')
                        t++;
                    else
                        f++;

                    st.pop();
                }

                // Operator
                char op = st.top();
                st.pop();

                // Evaluate
                if (op == '!') {
                    st.push(f == 1 ? 't' : 'f');
                }
                else if (op == '&') {
                    st.push(f > 0 ? 'f' : 't');
                }
                else { // '|'
                    st.push(t > 0 ? 't' : 'f');
                }
            }
        }

        return st.top() == 't';
    }
};


int main(){
    return 0;
}