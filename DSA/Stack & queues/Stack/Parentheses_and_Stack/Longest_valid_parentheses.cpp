#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);

        int ans = 0;

        for (int i = 0; i < s.length(); i++) {

            if (s[i] == '(') {
                st.push(i);
            }
            else {
                st.pop();

                if (st.empty()) {
                    // This ')' is unmatched
                    st.push(i);
                }
                else {
                    // Valid substring found
                    ans = max(ans, i - st.top());
                }
            }
        }

        return ans;
    }
};



int main(){
    return 0;
}