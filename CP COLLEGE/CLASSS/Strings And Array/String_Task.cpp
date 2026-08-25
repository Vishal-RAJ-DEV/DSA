#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    string result = "";

    for (char ch : s) {

        // Convert uppercase letters to lowercase
        ch = tolower(ch);

        // Check if it is a vowel
        if (ch == 'a' || ch == 'e' || ch == 'i' ||
            ch == 'o' || ch == 'u' || ch == 'y') {
            continue;
        }

        // It is a consonant
        result += '.';
        result += ch;
    }

    cout << result;

    return 0;
}