/*290. Word Pattern
Given a pattern and a string s, find if s follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s. Specifically:

Each letter in pattern maps to exactly one unique word in s.
Each unique word in s maps to exactly one letter in pattern.
No two letters map to the same word, and no two words map to the same letter.

Example 1:
Input: pattern = "abba", s = "dog cat cat dog"
Output: true
Explanation:
The bijection can be established as:
'a' maps to "dog".
'b' maps to "cat".

Example 2:
Input: pattern = "abba", s = "dog cat cat fish"
Output: false
Example 3:
Input: pattern = "aaaa", s = "dog cat cat dog"
Output: false*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
bool wordPattern(string pattern, string s) {
        vector<string> words;
        stringstream ss(s);  //using stringstream to split the string into words
        string word;
        while(ss>>word){   //extracting each word from the stringstream
            words.push_back(word);  //pushing each word into the words vector
        }                           


        if(words.size() != pattern.size())return false;

        unordered_map<char , string> charTOword; //map to store the mapping of character to word
        unordered_map<string , char> wordTOchar; //map to store the mapping of word to character

        for(int i = 0 ; i<pattern.size();i++){
            char c = pattern[i];
            string w = words[i];

            if(charTOword.count(c) && charTOword[c] != w)return false;  // Check if the character is already mapped to a different word
            if(wordTOchar.count(w) && wordTOchar[w] != c) return false;  // Check if the word is already mapped to a different character

            charTOword[c] = w;
            wordTOchar[w] = c;

        }
        return true;
    }
int main(){
    string pattern = "abba";
    string s = "dog cat cat dog";
    if(wordPattern(pattern, s)) {
        cout << "The string follows the pattern." << endl;
    } else {
        cout << "The string does not follow the pattern." << endl;
    }
    return 0;
}