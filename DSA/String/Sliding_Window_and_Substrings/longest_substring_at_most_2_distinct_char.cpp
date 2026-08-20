#include <bits/stdc++.h>
using namespace std;

int longSubstring(string s) {
    int n = s.length();
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        unordered_map<char, int> count;
        for (int j = i; j < n; j++) {
            count[s[j]]++;

            // If more than 2 distinct characters, break
            if (count.size() > 2) break;

            // Update maximum length
            maxLen = max(maxLen, j - i + 1);
        }
    }
    return maxLen;
}

int longSubstring(string s) {
    int n = s.length();
    unordered_map<char, int> count;
    int i = 0, maxLen = 0;

    for (int j = 0; j < n; j++) {
        count[s[j]]++;

        // If more than 2 distinct characters, shrink from left
        while (count.size() > 2) {
            count[s[i]]--;
            if (count[s[i]] == 0)
                count.erase(s[i]);
            i++;
        }

        // Update maximum length
        maxLen = max(maxLen, j - i + 1);
    }

    return maxLen;
}


int main() {
    cout << longSubstring("geeksforgeeks") << endl; 
    return 0;
}
