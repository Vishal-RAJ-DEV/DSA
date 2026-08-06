#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Question:
// You are given a string s. We want to partition the string into
// as many parts as possible so that each letter appears in at most
// one part. Return a list of integers representing the size of
// these parts.
//
// Example:
// Input: s = "ababcbacadefegdehijhklij"
// Output: [9,7,8]
// Explanation:
// The partition is "ababcbaca", "defegde", "hijhklij".
// Each letter appears in at most one part.
// ============================================================

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = s.size();          // length of the string

        // step 1: store the last index of each character (0..25 for 'a'..'z')
        vector<int>last( 26);

        for(int i = 0 ; i < n ; i++){
            last[s[i] - 'a'] = i;  // overwrite with the latest index of that char
        }

        // step 2: traverse and form partitions greedily
        // intuition:
        // At every position i, we maintain:
        // end = farthest last occurrence of every character seen so far
        //
        // This means:
        // We cannot end the partition before end, because some character
        // would appear again later.
        // Once i == end, every character we've seen ends within this
        // partition, so it's safe to cut.
        // Since we cut at the earliest possible valid position, we
        // maximize the number of partitions.

        int start = 0;              // start index of current partition
        int end = 0 ;               // farthest last index in the current partition
        vector<int>ans;             // stores the size of each partition
        for(int i = 0 ; i < n ; i++){
            // extend 'end' if current character's last occurrence is farther
            end = max( end , last[s[i] - 'a']);

            // current index reaches the partition boundary
            if( i == end){
                // partition from start to end is complete
                ans.push_back(end - start + 1);   // size of this partition
                start = i + 1;                    // reset start for next partition
            }
        }

        return ans;
    }
};


int main(){
    return 0;
}
