#include <bits/stdc++.h>
using namespace std;

string solve(const string& s) {
    int n = s.size();
    
    // Check length 1
    vector<bool> has1(26, false);
    for (char c : s) has1[c - 'a'] = true;
    for (int i = 0; i < 26; i++) {
        if (!has1[i]) return string(1, char('a' + i));
    }
    
    // Check length 2
    vector<vector<bool>> has2(26, vector<bool>(26, false));
    for (int i = 0; i + 1 < n; i++) {
        has2[s[i] - 'a'][s[i + 1] - 'a'] = true;
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (!has2[i][j]) {
                string ans;
                ans += char('a' + i);
                ans += char('a' + j);
                return ans;
            }
        }
    }
    
    // Check length 3
    vector<vector<vector<bool>>> has3(26, vector<vector<bool>>(26, vector<bool>(26, false)));
    for (int i = 0; i + 2 < n; i++) {
        has3[s[i] - 'a'][s[i + 1] - 'a'][s[i + 2] - 'a'] = true;
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            for (int k = 0; k < 26; k++) {
                if (!has3[i][j][k]) {
                    string ans;
                    ans += char('a' + i);
                    ans += char('a' + j);
                    ans += char('a' + k);
                    return ans;
                }
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