#include <iostream>
#include <string>
using namespace std;

bool isVowel(char c) {
    c = tolower(c);

    return c == 'a' || c == 'e' || c == 'i' ||
           c == 'o' || c == 'u';
}

int countVowels(string &s, int index) {
    // Base case
    if (index == s.length()) {
        return 0;
    }

    // Count current character
    int count = isVowel(s[index]) ? 1 : 0;

    // Recursive call
    return count + countVowels(s, index + 1);
}

int main() {
    string S;
    getline(cin, S);

    cout << countVowels(S, 0) << endl;

    return 0;
}