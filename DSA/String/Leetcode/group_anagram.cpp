#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
49. Group Anagrams
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

Example 1:
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Explanation:
There is no string in strs that can be rearranged to form "bat".
The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.

Example 2:
Input: strs = [""]
Output: [[""]]

Example 3:
Input: strs = ["a"]
Output: [["a"]]
*/

vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    unordered_map<string, vector<string>> mp;

    for (string s : strs)
    {
        string key = s;
        sort(key.begin(), key.end());
        mp[key].push_back(s); // store the sorted str(key) as the index of that respective anagram . sort key only stores the their unsorted matched str
    }

    vector<vector<string>> result;
    for (auto &ans : mp)
    {
        result.push_back(ans.second);
    }
    return result;
}
int main()
{
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> grouped = groupAnagrams(strs);
    for (const auto &group : grouped)
    {
        for (const auto &word : group)
        {
            cout << word << " ";
        }
        cout << endl;
    }
    return 0;
}


/*How the code works step by step:

Step 1: Initialize
unordered_map<string, vector<string>> mp;
(empty hash map)

Step 2: Process Each String
i) s = "eat"

key = "eat" → sort → "aet"

Insert into map:

mp["aet"] = ["eat"]

ii) s = "tea"

key = "tea" → sort → "aet"

Already exists in map:

mp["aet"] = ["eat", "tea"]

iii) s = "tan"

key = "tan" → sort → "ant"

Insert into map:

mp["ant"] = ["tan"]

iv) s = "ate"

key = "ate" → sort → "aet"

Add to existing group:

mp["aet"] = ["eat", "tea", "ate"]

v) s = "nat"

key = "nat" → sort → "ant"

Add to existing group:

mp["ant"] = ["tan", "nat"]

vi) s = "bat"

key = "bat" → sort → "abt"

Insert into map:

mp["abt"] = ["bat"]

Step 3: Final Hash Map State
"aet" → ["eat", "tea", "ate"]
"ant" → ["tan", "nat"]
"abt" → ["bat"]

Step 4: Convert Map → Result

Collect the values:

[
  ["eat", "tea", "ate"],
  ["tan", "nat"],
  ["bat"]
]
*/