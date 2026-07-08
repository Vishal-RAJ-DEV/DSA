#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*

1832. Check if the Sentence Is Pangram
Solved
Easy
Topics
premium lock icon
Companies
Hint
A pangram is a sentence where every letter of the English alphabet appears at least once.

Given a string sentence containing only lowercase English letters, return true if sentence is a pangram, or false otherwise.

Example 1:

Input: sentence = "thequickbrownfoxjumpsoverthelazydog"
Output: true
Explanation: sentence contains at least one of every letter of the English alphabet.
Example 2:

Input: sentence = "leetcode"
Output: false
 

*/
class Solution {
public:
    bool checkIfPangram(string sentence) {
        vector<int>freq(26 , 0);

        for(char ch : sentence ){
            freq[ch - 'a'] = 1;
        }

        for(int s : freq){
            if( s != 1) return false;
        }
        
        return true;
    }
};

int main(){
    return 0;
}
