#include <iostream>
#include<vector>
using namespace std;

// Encodes the array of strings into a single string
string encode(vector<string>& s) {
    string encoded;

    for (string &str : s) {
        encoded += to_string(str.length()); // store length
        encoded += '#';                     // fixed separator
        encoded += str;                     // actual string
    }

    return encoded;
}

// Decodes the encoded string back into the array of strings
vector<string> decode(string& s) {
    vector<string> result;
    int i = 0;
    int n = s.length();

    while (i < n) {
        int len = 0;

        // Extract the length
        while (s[i] != '#') {
            len = len * 10 + (s[i] - '0');
            i++;
        }

        i++; // skip '#'

        // Extract the actual string using the length
        string temp = s.substr(i, len);
        result.push_back(temp);

        i += len;
    }

    return result;
}

int main() {
    vector<string> s = {"Hello", "World"};

    string encoded = encode(s);
    vector<string> decoded = decode(encoded);

    for (int i = 0; i < decoded.size(); i++) {
        cout << decoded[i];
        if (i + 1 < decoded.size()) cout << " ";
    }

    return 0;
}