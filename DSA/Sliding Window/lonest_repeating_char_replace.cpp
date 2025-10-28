#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int characterReplacement(string s, int k)
{
    int left = 0;
    int right = 0;
    int result = 0;
    int maxFrequency = 0;
    vector<int> count(26, 0);
    while (right < s.size())
    {
        // increse the frequency of the each letter in the s
        count[s[right] - 'A']++;
        maxFrequency = max(maxFrequency, count[s[right] - 'A']);
        // now check the window is valid or not
        // if not valid then shrink the window form  the left and decrese the that letter frequency
        while ((right - left + 1) - maxFrequency > k)
        {
            count[s[left] - 'A']--;
            left++;
        }

        result = max(result, right - left + 1);
        right++;
    }
    return result;
}
int main()
{
    string s = "AABABBA";
    int k = 1;
    // Output: 4
    cout << characterReplacement(s, k) << endl;
    return 0;
}