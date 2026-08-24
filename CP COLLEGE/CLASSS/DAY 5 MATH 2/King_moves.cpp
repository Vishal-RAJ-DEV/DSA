#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    char col = s[0];
    char row = s[1];

    bool edgeCol = (col == 'a' || col == 'h');
    bool edgeRow = (row == '1' || row == '8');

    if (edgeCol && edgeRow) {
        cout << 3 << '\n';   // Corner
    }
    else if (edgeCol || edgeRow) {
        cout << 5 << '\n';   // Edge
    }
    else {
        cout << 8 << '\n';   // Inside
    }

    return 0;
}