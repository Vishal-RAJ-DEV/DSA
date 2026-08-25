#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int count = 1;

    for (int i = 1; i < s.length(); i++) {

        // If the current character is same as previous
        if (s[i] == s[i - 1]) {
            count++;
        } 
        else {
            // Different team starts, reset count
            count = 1;
        }

        // Check for 7 consecutive players
        if (count >= 7) {
            cout << "YES";
            return 0;
        }
    }

    cout << "NO";

    return 0;
}