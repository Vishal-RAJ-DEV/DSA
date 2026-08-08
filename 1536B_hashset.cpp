#include <bits/stdc++.h>
using namespace std;

string solve(const string& s) {
    int n = s.size();
    
    // Check length 1
    unordered_set<char> has1;
    for (char c : s) has1.insert(c);
    for (char c = 'a'; c <= 'z'; c++) {
        if (!has1.count(c)) return string(1, c);
    }
    
    // Check length 2
    unordered_set<string> has2;
    for (int i = 0; i + 1 < n; i++) {
        has2.insert(s.substr(i, 2));
    }
    for (char c1 = 'a'; c1 <= 'z'; c1++) {
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            string cand = string(1, c1) + c2;
            if (!has2.count(cand)) return cand;
        }
    }
    
    // Check length 3
    unordered_set<string> has3;
    for (int i = 0; i + 2 < n; i++) {
        has3.insert(s.substr(i, 3));
    }
    for (char c1 = 'a'; c1 <= 'z'; c1++) {
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            for (char c3 = 'a'; c3 <= 'z'; c3++) {
                string cand = string(1, c1) + c2 + c3;
                if (!has3.count(cand)) return cand;
            }
        }
    }
    
    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        cout << solve(s) << '\n';
    }
    return 0;
}