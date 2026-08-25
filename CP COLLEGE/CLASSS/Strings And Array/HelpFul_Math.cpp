#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    vector<char> numbers;

    // Extract only the digits
    for (char ch : s) {
        if (ch != '+') {
            numbers.push_back(ch);
        }
    }

    // Sort the numbers
    sort(numbers.begin(), numbers.end());

    // Print with '+' between numbers
    for (int i = 0; i < numbers.size(); i++) {
        if (i > 0) {
            cout << "+";
        }

        cout << numbers[i];
    }

    return 0;
}