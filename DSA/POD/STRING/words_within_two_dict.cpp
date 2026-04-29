// Problem (easy wording):
// You are given two lists of words: queries and dictionary. Every word has the
// same length. A word from queries is called "within two edits" of the
// dictionary if there exists at least one word in dictionary that differs from
// it in at most 2 positions (letter changes only). Return all query words that
// satisfy this condition.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries,
                                vector<string>& dictionary) {
        int n = queries[0].size(); // All words have the same length.
        vector<string> ans;
        for (auto& it : queries) { // Try each query word.
            for (auto& i : dictionary) { // Compare against every dictionary word.
                int diff = 0; // Count different positions.
                for (int idx = 0; idx < n; idx++) {
                    if (it[idx] != i[idx]) {
                        diff++;
                    }
                    if (diff > 2)
                        break; // More than 2 edits, no need to continue.
                }
                if (diff <= 2) {
                    ans.push_back(it); // This query word is valid.
                    break; // No need to check other dictionary words.
                }
            }
        }
        return ans;
    }
};



int main(){
    Solution sol;
    vector<string> queries = {"word","note","ants","wood"};
    vector<string> dictionary = {"wood","joke","moat"};
    vector<string> result = sol.twoEditWords(queries, dictionary); // Run solution.
    cout << "Words within two edits: ";
    for (const string& word : result) {
        cout << word << " ";
    }
    
    return 0;
}
