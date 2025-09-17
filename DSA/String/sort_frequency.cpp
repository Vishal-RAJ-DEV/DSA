#include <bits/stdc++.h>
using namespace std;

/*Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.

Return the sorted string. If there are multiple answers, return any of them.*/

class Solution {
public:
    string frequencySort(string s) {
        typedef pair<char, int> P;   // first = char, second = frequency
        vector<P> vec(123, {'\0', 0});  // store char + frequency for ASCII chars

        // Count frequencies
        for (char ch : s) {
            vec[ch].first = ch;        // store character
            vec[ch].second += 1;       // increase frequency
        }

        // Lambda comparator: sort by frequency descending
        auto lambda = [&](P &p1, P &p2) {
            return p1.second > p2.second;
        };

        sort(begin(vec), end(vec), lambda);

        // Build result string
        string result = "";
        for (int i = 0; i < 123; i++) {
            if (vec[i].second > 0) {
                result += string(vec[i].second, vec[i].first);
            }
        }

        return result;
    }
};

int main() {
    Solution sol;

    string s1 = "tree";
    cout << "Input: " << s1 << "\nOutput: " << sol.frequencySort(s1) << "\n\n";

    string s2 = "cccaaa";
    cout << "Input: " << s2 << "\nOutput: " << sol.frequencySort(s2) << "\n\n";

    string s3 = "Aabb";
    cout << "Input: " << s3 << "\nOutput: " << sol.frequencySort(s3) << "\n\n";

    return 0;
}
