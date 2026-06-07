#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int characterReplacement(string s, int k)
{
    /*
    Question:
    We can replace at most k characters in the string.
    Find the length of the longest substring that can be turned into
    a string of all same characters after at most k replacements.

    Example:
    s = "AABABBA", k = 1
    Best answer is 4 because "AABA" can become "AAAA" using 1 replacement.

    Core idea:
    For any window [left ... right], we try to make all characters equal
    to the most frequent character in that window.

    If the most frequent character appears maxFrequency times,
    then the number of replacements needed is:

        window length - maxFrequency

    because all the other characters must be changed.

    So the window is valid only when:

        (right - left + 1) - maxFrequency <= k

    If this becomes greater than k, the window is invalid,
    and that is the exact point where we must shrink it.
    */

    int left = 0;
    int right = 0;
    int result = 0;
    int maxFrequency = 0;
    vector<int> count(26, 0);
    while (right < s.size())
    {
        // Expand the window by including s[right].
        count[s[right] - 'A']++;

        // Track the highest frequency character inside the current window.
        maxFrequency = max(maxFrequency, count[s[right] - 'A']);

        /*
        This is the shrinking condition:

        Current window length       = (right - left + 1)
        Most frequent char count    = maxFrequency
        Characters to replace       = window length - maxFrequency

        If characters to replace > k,
        then we cannot convert this whole window into one repeating character
        with only k replacements.

        So we keep shrinking from the left until the window becomes valid again.
        */
        while ((right - left + 1) - maxFrequency > k)
        {
            // Remove the leftmost character from the window
            // because current window needs too many replacements.
            count[s[left] - 'A']--;
            left++;
        }

        // After shrinking if needed, this window is valid.
        // Update the best answer.
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
