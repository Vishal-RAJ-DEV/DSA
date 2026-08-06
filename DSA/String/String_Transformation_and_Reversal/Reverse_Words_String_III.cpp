#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
        How stringstream works:

        Suppose:
            s = "Let's take LeetCode contest"

        stringstream ss(s);

        It creates a stream from the string.

        Every time we do:
            ss >> word;

        It extracts the next word separated by whitespace.

        Iteration 1:
            word = "Let's"

        Iteration 2:
            word = "take"

        Iteration 3:
            word = "LeetCode"

        Iteration 4:
            word = "contest"

        After extracting a word, we reverse it and immediately append
        it to the answer, followed by a space.

        Result building:
            "s'teL "
            "s'teL ekat "
            "s'teL ekat edoCteeL "
            "s'teL ekat edoCteeL tsetnoc"

        Finally, remove the extra trailing space.
    */

    string reverseWords(string s) {

        // Convert the string into a stream to extract words one by one.
        stringstream ss(s);

        string word;
        string result;

        // Extract each word, reverse it, and append to the answer.
        while (ss >> word) {
            reverse(word.begin(), word.end());
            result += word + " ";
        }

        // Remove the extra space after the last word.
        result.pop_back();

        return result;
    }
};


class Solution {
public:
    string reverseWords(string s) {

        int start = 0;
        int n = s.size();

        for (int end = 0; end <= n; end++) {

            // End of a word
            if (end == n || s[end] == ' ') {
                reverse(s.begin() + start, s.begin() + end);
                start = end + 1;
            }
        }

        return s;
    }
};


int main(){
    return 0;
}