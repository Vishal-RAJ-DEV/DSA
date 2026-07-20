#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// LeetCode 791: Custom Sort String
//
// Problem:
//   Given strings 'order' (unique chars, custom ordering) and 's',
//   permute s so that characters appear in the same relative order
//   as they do in 'order'. Characters not in 'order' go to the end
//   (any order).
//
// Custom Sort — How it works here:
//   This is NOT a comparison-based sort (no comparator function).
//   Instead, it uses a frequency map + ordered placement:
//
//   1) Count every character of 's' in a hashmap (char -> freq).
//   2) Walk through 'order' in sequence. For each char in 'order',
//      if it exists in the map, append it freq[char] times to result.
//      Then remove it from the map.
//   3) Any chars still in the map (i.e., not present in 'order') are
//      appended at the end.
//
//   By processing 'order' left-to-right and appending all occurrences
//   at once, the output mirrors the custom order. The remaining chars
//   (not in order) naturally end up at the tail end.
//
// Time : O(n + m)  — n = |s|, m = |order|
// Space: O(n)

class Solution {
public:
    string customSortString(string order, string s) {
        string result = "";
        unordered_map<int, int> mp;

        // Step 1: Count frequency of each char in s
        for (auto &it : s) {
            mp[it]++;
        }

        // Step 2: Place chars that appear in 'order', in order
        for (auto &it : order) {
            if (mp.find(it) != mp.end()) {
                result.append(mp[it], it);
                mp.erase(it);
            }
        }

        // Step 3: Append remaining chars (not in order) at the end
        for (auto &it : mp) {
            result.append(it.second, it.first);
        }

        return result;
    }
};

int main() {
    return 0;
}
