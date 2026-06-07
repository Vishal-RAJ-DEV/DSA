#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//<----------------Method 2------------------------->//
class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> result;

        sort(words.begin(), words.end(),
             [&](const string& a, const string& b) -> bool {
                 return a.size() > b.size();
             });

        for (int i = 0; i < words.size(); ++i) {
            for (int j = i + 1; j < words.size(); ++j) {
                if (words[i].find(words[j]) != string::npos) {
                    result.push_back(words[j]);
                }
            }
        }

        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());

        return result;
    }
};


int main(){
    vector<string> words = {"mass", "as", "hero", "superhero"};
    Solution sol; // create solution instance
    vector<string> matches = sol.stringMatching(words); // run the function

    cout << "Matching substrings: ";

    for (const string& word : matches) {
        cout << "\"" << word << "\" ";
    }

    cout << endl;
    
    return 0;
}