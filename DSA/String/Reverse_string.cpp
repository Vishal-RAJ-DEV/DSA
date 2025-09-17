#include <iostream>
#include <bits/stdc++.h>
using namespace std;

string reverseWords(string s) {
    int left = 0;
    int right = s.size() - 1;

    string temp = "";
    string result = "";

    while (left <= right) {  
        char ch = s[left];
        if (ch != ' ') {  // here if the character is not a space then we add it to the current word  which is stored in temp
            temp += ch;
        } else {  // if the character is a space then we check if temp is not empty
            // ✅ commit only if we actually have a word
            if (!temp.empty()) {  // if temp is not empty then we add it to the result
                // ✅ if result is not empty then we add a space before adding temp to result
                if (!result.empty()) result = temp + " " + result;
                else result = temp;
                temp.clear();
            }
        }
        left++;
    }

    // ✅ add the last word if present
    if (!temp.empty()) {
        if (!result.empty()) result = temp + " " + result;
        else result = temp;
    }
    return result;
}

int main() {
    string s = "Hello World";
    cout << reverseWords(s) << endl;
    return 0;
}