#include <bits/stdc++.h>
using namespace std;

/*
QUESTION (Deletive Editing - Codeforces):
You are given two strings s (source) and t (target).
You can repeatedly delete ANY character from s, BUT you can only delete
a character if it appears at least once MORE in the remaining string s
after that deletion.

In other words: You can delete a character only when there is ANOTHER
copy of the same character somewhere in s (so it won't disappear entirely).

Can you obtain string t from s by performing such deletions?

If yes, print YES, else NO.

EXAMPLE:
s = "DETERMINED"
t = "TRME"

Can we delete characters to get "TRME"? YES.

=========================================================
INTUITION & ALGORITHM (Processing from Right to Left):
=========================================================

KEY INSIGHT:
Start from the END of both strings. We need to match characters of t
in s, working backwards. The LAST occurrence of a needed character in s
is the one that should survive.

When scanning s from right to left:
- If s[i] == t[j] (the current target from the end):
    → MATCH! This character survives. Decrement freq, move j left.
- If s[i] != t[j]:
    → We're considering DELETING this character.
    → BUT: Is this character still NEEDED for the unmatched part of t?

    If YES (character is needed later in t):
      → We CANNOT delete it! If we delete it now, we might lose the
        only occurrence we need for a future match.
      → Answer = NO immediately.

    If NO (character is NOT needed later in t):
      → Safe to delete, continue scanning.

After scanning all of s:
  - If we matched ALL of t (j == -1) → YES.
  - If some of t is still unmatched (j >= 0) → NO.

WHY START FROM THE END?
When you delete a character in s, the RELATIVE ORDER of remaining
characters stays the same. If we process from the right, we're
effectively deciding which characters to KEEP for t. The rightmost
matching character for each position is ideal because deleting
characters to its left won't affect it.

THE FREQUENCY TRICK (solve function):
Instead of the nested loop in solve2 (O(n^2)), we precompute the
frequency of each character in t. As we match characters from the
end, we decrement the count. Now, when we encounter a non-matching
character:
  - If freq[char] > 0 → this char is STILL NEEDED in t → NO.
  - If freq[char] == 0 → this char is NOT needed → safe to delete.

This makes the check O(1) instead of O(n) per character → O(n) total.

CONDITIONS SUMMARY:
  • YES:  We can match all characters of t from right to left, and
          every non-matching character encountered is NOT needed in t.
  • NO:   A non-matching character IS still needed in t (freq > 0).
  • NO:   After scanning all of s, some characters of t remain unmatched.

EXAMPLE WALKTHROUGH:
s = "DETERMINED"
t = "TRME"

First, count frequencies in t: {T:1, R:1, M:1, E:1}

Scan s from right to left:

i=9: s[9]='D', target t[3]='E' → not match, freq['D']=0 → safe to delete
i=8: s[8]='E', target t[3]='E' → MATCH! freq['E']-- (now 0), j=2
i=7: s[7]='N', target t[2]='M' → not match, freq['N']=0 → safe
i=6: s[6]='I', target t[2]='M' → not match, freq['I']=0 → safe
i=5: s[5]='M', target t[2]='M' → MATCH! freq['M']-- (now 0), j=1
i=4: s[4]='R', target t[1]='R' → MATCH! freq['R']-- (now 0), j=0
i=3: s[3]='E', target t[0]='T' → not match, freq['E']=0 → safe
i=2: s[2]='T', target t[0]='T' → MATCH! freq['T']-- (now 0), j=-1
i=1: s[1]='E', already matched all (j=-1) → freq['E']=0 → safe
i=0: s[0]='D', already matched all → freq['D']=0 → safe

j = -1 after loop → YES
*/



/*

The One-Line Intuition You Should Remember
Since only the first occurrence can be deleted, the safest occurrence to keep is always the last one. Therefore, scan from right to left, greedily keep the last possible occurrence of each required character, and delete only those characters that are no longer needed.

Think of it like this
Imagine every character in t has put up a sign saying:
"I still need one copy of me!"
As you scan s from right to left:
If the current character satisfies that request, keep it and remove the sign.
If the current character doesn't match what you're currently trying to keep:
If its sign is already gone, delete it.
If its sign is still there, you are about to delete a character that the final string still needs, which is impossible because deletions always remove the first occurrence.

*/

void solve(){
    string s , t;
    cin>> s >> t;

    // Count frequency of each character in t
    vector<int> freq(26 , 0);
    for(int i = 0 ; i < t.size() ; i++){
        freq[t[i] - 'A']++;
    }

    int j = t.size() - 1;  // pointer at end of t

    for(int i = s.size() - 1; i >= 0 ; i--){
        if( j >= 0 && s[i] == t[j]){
            // Match found: keep this character, decrement its need count
            freq[s[i] - 'A']--;
            j--;
        }
        else{
            // Non-matching character: is it still needed in t?
            if( freq[s[i] - 'A'] > 0){
                cout<<"NO"<< endl;
                return;
            }
            // Otherwise, safe to delete (do nothing, just continue)
        }
    }

    // If all of t was matched, YES, else NO
    if(j >= 0){
        cout<<"NO"<< endl;
    }
    else{
        cout<<"YES"<< endl;
    }
}

void solve2() {
    string s, t;
    cin >> s >> t;

    int i = s.size() - 1;
    int j = t.size() - 1;

    while (i >= 0) {

        // Match found
        if (j >= 0 && s[i] == t[j]) {
            i--;
            j--;
        }
        else {

            // Check whether s[i] is still needed in unmatched part of t
            bool needed = false;

            for (int k = 0; k <= j; k++) {
                if (t[k] == s[i]) {
                    needed = true;
                    break;
                }
            }

            if (needed) {
                cout << "NO\n";
                return;
            }

            // Safe to delete, move on
            i--;
        }
    }

    if (j == -1)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        solve2();
    }

    return 0;
}