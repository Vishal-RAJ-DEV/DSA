#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {

        unordered_map<string,int> freq;

        // Count frequency of every word.
        for(string &w : words)
            freq[w]++;

        // bucket[i] stores every word
        // having frequency = i.
        vector<vector<string>> bucket(words.size()+1);

        // Place every word into its frequency bucket.
        for(auto &it : freq){

            bucket[it.second].push_back(it.first);
        }

        vector<string> ans;

        // Highest frequency first.
        for(int f = words.size(); f>=1 && ans.size()<k; f--){

            // If multiple words have same frequency,
            // they must be returned in
            // lexicographical order.
            sort(bucket[f].begin(), bucket[f].end());

            for(string &word : bucket[f]){

                ans.push_back(word);

                if(ans.size()==k)
                    break;
            }
        }

        return ans;
    }
};


int main(){
    return 0;
}