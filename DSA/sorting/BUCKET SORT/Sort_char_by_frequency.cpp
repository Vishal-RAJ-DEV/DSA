#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string frequencySort(string s) {

        unordered_map<char,int> freq;

        // Count frequency of every character
        for(char c : s)
            freq[c]++;

        // Maximum frequency cannot exceed string length
        vector<vector<char>> bucket(s.size()+1);

        // Put every character inside the bucket
        // representing its frequency.
        for(auto &it : freq){

            char ch = it.first;
            int frequency = it.second;

            bucket[frequency].push_back(ch);
        }

        string ans;

        // Traverse buckets from highest frequency
        // towards lowest.
        for(int f = s.size(); f >=1; f--){

            // Every character inside this bucket
            // appeared exactly 'f' times.
            for(char ch : bucket[f]){

                // Add character exactly 'f' times.
                for(int i=0;i<f;i++)
                    ans.push_back(ch);
            }
        }

        return ans;
    }
};


int main(){
    return 0;
}