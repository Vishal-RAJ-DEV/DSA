/*
Question: Codeforces 701B - They Are Everywhere (or similar "smallest window containing all distinct characters")
Given a string s of length n representing Pokemon types.
Find the minimum length substring that contains all distinct Pokemon types present in the entire string.

Approach: Sliding window (variable-length) with frequency map
1. Count all distinct characters in the string (freq map or set)
2. Use sliding window [l, r] to find the smallest window containing all distinct types
   - Expand r, add s[r] to window_freq
   - When window_freq.size() == totalDistinct (window has all types), shrink from left:
     - Update min_size, remove s[l] from window, l++
   - Continue expanding r

Two implementations:
- solve() uses an O(n) pass to build freq map, then sliding window
- solveWithSet() uses a set to get totalDistinct (O(n log k)), then sliding window
Both are effectively O(n) with O(k) space.
*/
#include <bits/stdc++.h>
using namespace std;

// Approach 1: Two-pass (frequency map + sliding window)
// Time  : O(n) — one O(n) pass to build freq map, then O(n) sliding window (each char visited at most twice)
// Space : O(k) where k = distinct characters in string
void solve(){
    int n;
    string s;
    cin >> n >> s;

    unordered_map<char, int> freq;
    for(char c : s) freq[c]++;

    int min_size = INT_MAX;
    int l = 0;

    unordered_map<char, int> window_freq;
    for(int r = 0 ; r < n ; r++){
        window_freq[s[r]]++;

        while(window_freq.size() == freq.size()){
            min_size = min(min_size , r - l + 1);

            window_freq[s[l]]--;
            if(window_freq[s[l]] == 0) window_freq.erase(s[l]);
            l++;
        }

    }
    if(min_size == INT_MAX) cout << -1 << endl;
    else cout << min_size << endl;
}

// Approach 2: Set-based (set + sliding window)
// Time  : O(n log k) — O(n log k) to build the set, then O(n) sliding window
//         Log factor from set insertion; still effectively O(n) in practice
// Space : O(k)
void solveWithSet(){
    int n;
    string s;
    cin >> n >> s;

    set<char> distinct(s.begin(), s.end());
    int totalDistinct = distinct.size();

    int minLen = n, l = 0;
    unordered_map<char, int> window;

    for (int r = 0; r < n; r++) {
        window[s[r]]++;

        while (window.size() == totalDistinct) {
            minLen = min(minLen, r - l + 1);
            if (--window[s[l]] == 0) window.erase(s[l]);
            l++;
        }
    }
    cout << minLen << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--){
        // solve();        // original approach
        solveWithSet();    // set-based approach
    }

    return 0;
}