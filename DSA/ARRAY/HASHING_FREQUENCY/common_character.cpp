#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
You are given a list of strings words.
Return all characters that show up in every string, including duplicates.

Important point:
If a character appears multiple times in every word,
then it should appear multiple times in the answer too.

Example:
words = ["bella", "label", "roller"]

Common characters are:
- 'e' appears in all words once
- 'l' appears in all words at least twice

So answer = ["e", "l", "l"]
*/

/*
Approach 1: Frequency intersection using minimum count

Main logic:
1. Create a frequency array cnt of size 26 and initialize every value to INT_MAX.
2. For each word:
   - count frequency of its characters in cnt1
   - update cnt[i] = min(cnt[i], cnt1[i])
3. After processing all words, cnt[i] tells the minimum frequency
   of character 'a' + i across all words.
4. If a character has minimum frequency x, it means it appears in every word x times,
   so we add it x times to the answer.

Intuition:
- We are finding the intersection of character frequencies.
- Example:
  word1 has 'l' = 2
  word2 has 'l' = 2
  word3 has 'l' = 3
  minimum is 2
  so 'l' is common exactly 2 times

Why minimum frequency?
- A character can only be common as many times as it appears in the word
  where it appears the least.
- That is why min() is the key idea here.

This is the most standard and efficient solution.
*/
class SolutionApproach1 {
public:
    vector<string> commonChars(vector<string>& words) {
        vector<int> cnt(26, INT_MAX);
        vector<string> result;

        for (auto s : words) {
            vector<int> cnt1(26, 0);

            // Count frequency of each character in the current word.
            for (auto ch : s) {
                cnt1[ch - 'a']++;
            }

            // Keep only the minimum frequency seen across all words.
            for (int i = 0; i < 26; i++) {
                cnt[i] = min(cnt[i], cnt1[i]);
            }
        }

        /*
        Now cnt[i] stores how many times character ('a' + i)
        is common in every word.
        If cnt[i] = 2, add that character 2 times.
        */
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < cnt[i]; j++) {
                result.push_back(string(1, i + 'a'));
            }
        }

        return result;
    }
};

/*
Approach 2: Check character by character and erase when used

Main logic:
1. Sort the words so we can start from the first word in a predictable way.
2. For every character c in words[0]:
   - check whether c exists in every other word
   - if any word does not contain c, then c is not common
   - if every word contains c, add c to the answer
3. After using c from a word, erase one occurrence of c from that word.

Why erase is important:
- It handles duplicates correctly.
- Example:
  if 'l' is common twice, then it must be found twice in every word.
- By erasing one used occurrence, we make sure the same character occurrence
  is not reused again unfairly.

Intuition:
- Think of taking one character from the first word
  and trying to match one copy of it in every other word.
- If match succeeds in every word, that character belongs to the answer.
- Then we remove the used copy from each word.

Difference from Approach 1:
- Approach 1 works with frequency counting mathematically.
- Approach 2 works more like direct matching and consuming characters.
- Approach 2 is easier to visualize, but less efficient because find() and erase()
  are used repeatedly on strings.
*/
class SolutionApproach2 {
public:
    vector<string> commonChars(vector<string>& words) {
        vector<string> res;

        sort(words.begin(), words.end());

        // Try each character from the first word.
        for (char c : words[0]) {
            bool common = true;

            for (int i = 1; i < words.size(); i++) {
                /*
                If current word does not contain c, then c is not common.
                Otherwise erase one occurrence so duplicates are handled properly.
                */
                if (words[i].find(c) == string::npos) {
                    common = false;
                    break;
                } else {
                    words[i].erase(words[i].find(c), 1);
                }
            }

            // If c was found in every word, include it in the answer.
            if (common) {
                res.push_back(string(1, c));
            }
        }
        return res;
    }
};

int main() {
    vector<string> words = {"bella", "label", "roller"};

    SolutionApproach1 a1;
    SolutionApproach2 a2;

    vector<string> ans1 = a1.commonChars(words);
    vector<string> ans2 = a2.commonChars(words);

    for (auto& ch : ans1) cout << ch << " ";
    cout << '\n';
    for (auto& ch : ans2) cout << ch << " ";
    cout << '\n';

    return 0;
}
