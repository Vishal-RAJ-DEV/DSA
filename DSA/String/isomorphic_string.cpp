#include <iostream>
#include <bits/stdc++.h>

/*Given two strings s and t, determine if they are isomorphic.

Two strings s and t are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the */
using namespace std;

bool isIsomorphic(string s, string t) {
    if (s.size() != t.size()) return false;

    unordered_map<char, char> mapst; // s → t
    unordered_map<char, char> mapts; // t → s

    for (int i = 0; i < s.size(); i++) {
        char c1 = s[i];
        char c2 = t[i];

        // Check if c1 already mapped inconsistently
        if (mapst.count(c1) && mapst[c1] != c2) return false;

        // Check if c2 already mapped inconsistently
        if (mapts.count(c2) && mapts[c2] != c1) return false;

        // Add/Update mapping
        mapst[c1] = c2;
        mapts[c2] = c1;
    }

    return true;
}

/*
1. mapST.count(c1)
Checks if key c1 already exists in the hash map mapST.
Returns:
1 → if mapping for c1 exists.
0 → if no mapping exists yet.
So this is the existence check for character c1.

2. mapST[c1] != c2
If the key c1 already exists, this part compares its stored value with the current c2.
Meaning:
"Does the mapping for c1 still point to the same character c2?"*/



int main(){
    string s = "egg";
    string t = "add";
    cout << (isIsomorphic(s, t) ? "Isomorphic" : "Not Isomorphic") << endl;

    s = "foo";
    t = "bar";
    cout << (isIsomorphic(s, t) ? "Isomorphic" : "Not Isomorphic") << endl;

    s = "paper";
    t = "title";
    cout << (isIsomorphic(s, t) ? "Isomorphic" : "Not Isomorphic") << endl;

    return 0;
} // order of characters. No two characters may map to the same character, but a character may map to itself.