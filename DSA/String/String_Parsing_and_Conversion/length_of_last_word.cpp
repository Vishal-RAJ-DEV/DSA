#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
leetcode 58. Length of Last Word
Given a string s consisting of words and spaces, return the length of the last word in the string.
A word is a maximal substring consisting of non-space characters only.
Example 1:
Input: s = "Hello World"
Output: 5
Explanation: The last word is "World" with length 5.
Example 2:
Input: s = "   fly me   to   the moon  "
Output: 4
Explanation: The last word is "moon" with length 4.
Example 3:
Input: s = "luffy is still joyboy"
Output: 6
Explanation: The last word is "joyboy" with length 6.
Constraints:
1 <= s.length <= 10^4
s consists of only English letters and spaces ' '.
s does not contain any leading or trailing spaces.
All the words in s are separated by a single space.
*/

class Solution
{
public:
    int lengthOfLastWord(string s)
    {
        int n = s.length();
        int count = 0;
        bool find = false;
        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] != ' ')
            {
                find = true;
                count++;
            }
            // break when the space found and its true that cahracter is there
            else if (find)
            {
                break;
            }
        }
        return count;
    }
};

int main()
{
    string s = "Hello World";
    Solution sol;
    int length = sol.lengthOfLastWord(s);
    cout << "The length of the last word in \"" << s << "\" is: " << length << endl;

    return 0;
}