#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findPermutationDifference(string s, string t) {
        vector<int> posS(26, 0);
        vector<int> posT(26, 0);

        int i = 0, j = 0;

        while (i < s.size() || j < t.size()) {

            if (i < s.size()) {
                posS[s[i] - 'a'] = i;
                i++;
            }

            if (j < t.size()) {
                posT[t[j] - 'a'] = j;
                j++;
            }
        }

        int res = 0;

        for (char ch : s) {
            res += abs(posS[ch - 'a'] - posT[ch - 'a']);
        }

        return res;
    }
};

//more simpler one 
class Solution {
public:
    int findPermutationDifference(string s, string t) {
        vector<int> posS(26), posT(26);

        for (int i = 0; i < s.size(); i++) {
            posS[s[i] - 'a'] = i;
            posT[t[i] - 'a'] = i;
        }

        int ans = 0;

        for (char ch : s) {
            ans += abs(posS[ch - 'a'] - posT[ch - 'a']);
        }

        return ans;
    }
};
int main(){
    Solution sol;
    string s = "abcde";
    string t = "deabc";
    int result = sol.findPermutationDifference(s, t);
    cout << "The permutation difference between \"" << s << "\" and \"" << t << "\" is: " << result << endl;
    return 0;
}
