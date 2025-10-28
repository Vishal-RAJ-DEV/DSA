#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int beautySum(string s) {
    int n = s.size();
    int sum = 0;
    for (int i = 0; i < n; i++) {
        unordered_map<char, int> mpp;
        for (int j = i; j < n; j++) {
            mpp[s[j]]++;  // Count character frequencies
            int maxi = 0;
            int mini = INT_MAX;
            for (auto &p : mpp) {
                maxi = max(maxi, p.second);
                mini = min(mini, p.second);
            }
            sum += (maxi - mini);  // ✅ add inside inner loop
        }
    }
    return sum;
}

int main(){
    string s = "aabcb";
    cout << beautySum(s) << endl; // Output: 5
    cout<<endl;
    return 0;
}

/*
Dry Run of beautySum("aab")
Initialization
n = s.size() = 3
sum = 0

Step 1: i = 0 (start index = 0)

Initialize map: mpp = {}
j = 0 → substring "a"
Update map: mpp['a'] = 1 → { 'a': 1 }
Calculate maxi = 1, mini = 1
Beauty = 1 - 1 = 0
Update sum: sum = 0 + 0 = 0

j = 1 → substring "aa"
Update map: mpp['a']++ → { 'a': 2 }
Calculate maxi = 2, mini = 2
Beauty = 2 - 2 = 0
Update sum: sum = 0 + 0 = 0

j = 2 → substring "aab"
Update map: mpp['b'] = 1 → { 'a': 2, 'b': 1 }
Calculate maxi = 2, mini = 1
Beauty = 2 - 1 = 1
Update sum: sum = 0 + 1 = 1

Step 2: i = 1 (start index = 1)

Initialize map: mpp = {}
j = 1 → substring "a"
Update map: mpp['a'] = 1 → { 'a': 1 }
Calculate maxi = 1, mini = 1
Beauty = 1 - 1 = 0
Update sum: sum = 1 + 0 = 1

j = 2 → substring "ab"
Update map: mpp['b'] = 1 → { 'a': 1, 'b': 1 }
Calculate maxi = 1, mini = 1
Beauty = 1 - 1 = 0
Update sum: sum = 1 + 0 = 1
Step 3: i = 2 (start index = 2)
Initialize map: mpp = {}

j = 2 → substring "b"
Update map: mpp['b'] = 1 → { 'b': 1 }
Calculate maxi = 1, mini = 1
Beauty = 1 - 1 = 0
Update sum: sum = 1 + 0 = 1
Step 4: Return Result
return sum = 1

✅ Key Points for Understanding

Outer loop i → starting index of substring

Inner loop j → ending index of substring

unordered_map keeps frequency of characters in current substring

For each substring, recompute:

maxi = max frequency

mini = min frequency

Add (maxi - mini) for every substring, not just once per start index
*/