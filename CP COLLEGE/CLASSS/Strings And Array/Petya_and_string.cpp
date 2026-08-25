#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1, s2;

    cin >> s1 >> s2;

    // Convert both strings to lowercase
    for (char &ch : s1) {
        ch = tolower(ch);
    }

    for (char &ch : s2) {
        ch = tolower(ch);
    }

    // Compare lexicographically
    if (s1 < s2) {
        cout << -1;
    }
    else if (s1 > s2) {
        cout << 1;
    }
    else {
        cout << 0;
    }

    return 0;
}