#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".
*/
string longestCommonPrefix(vector<string> &strs)
{
    if (strs.empty())
        return "";

    string prefix = strs[0]; // Assume first string is the prefix

    for (int i = 1; i < strs.size(); i++)
    {
        while (strs[i].find(prefix) != 0)
        {
            /*If .find(prefix) == 0 → ✅ means prefix is at index 0 → valid prefix.

            If .find(prefix) != 0 → ❌ means:

            Either prefix doesn’t exist in strs[i], or

            It exists, but not at the beginning.
                        */
            // Shrink prefix until it matches
            prefix = prefix.substr(0, prefix.size() - 1);
            if (prefix.empty())
                return "";
        }
    }

    return prefix;
}

/*prefix = prefix.substr(0, prefix.size() - 1);

If the prefix isn’t valid, we shrink it by removing the last character.

👉 Example:

prefix = "flower"
prefix.substr(0, 5) → "flowe"
prefix.substr(0, 4) → "flow"
prefix.substr(0, 3) → "flo"
prefix.substr(0, 2) → "fl"
...*/

int main()
{
    vector<string> strs = {"flower", "flow", "flight"};
    cout << "Longest Common Prefix: " << longestCommonPrefix(strs) << endl;
    return 0;
}
