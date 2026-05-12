#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> countWordOccurrences(vector<string>& chunks, vector<string>& queries) {
        string s = "";
        for (const string& chunk : chunks) {
            s += chunk;
        }

        unordered_map<string, int> wordFreq;
        int n = s.length();
        string currentWord = "";

        for (int i = 0; i < n; ++i) {
            if (islower(s[i])) {
                currentWord += s[i];
            } else if (s[i] == '-') {
                // Check if hyphen is surrounded by letters
                if (i > 0 && i < n - 1 && islower(s[i - 1]) && islower(s[i + 1])) {
                    currentWord += s[i];
                } else {
                    // Hyphen acts as a separator
                    if (!currentWord.empty()) {
                        wordFreq[currentWord]++;
                        currentWord = "";
                    }
                }
            } else {
                // Any other character (like space) is a separator
                if (!currentWord.empty()) {
                    wordFreq[currentWord]++;
                    currentWord = "";
                }
            }
        }
        
        // Final check for the last word in the string
        if (!currentWord.empty()) {
            wordFreq[currentWord]++;
        }

        vector<int> ans;
        for (const string& q : queries) {
            ans.push_back(wordFreq[q]);
        }

        return ans;
    }
};

int main(){
    Solution sol;
    vector<string> chunks = {"hello-world", "hello", "world"};
    vector<string> queries = {"hello", "world", "hello-world"};
    vector<int> result = sol.countWordOccurrences(chunks, queries);
    for (int count : result) {
        cout << count << " ";
    }
    return 0;
}
